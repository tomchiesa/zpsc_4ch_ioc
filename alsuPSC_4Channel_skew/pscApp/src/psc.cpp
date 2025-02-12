
#include "psc.h"

#include <stdexcept>
#include <memory>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include <errlog.h>
#include <epicsExit.h>
#include <dbAccess.h>
#include <initHooks.h>

#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/thread.h>

#define HEADER_SIZE 8
static const size_t max_size = 1024*1024;

extern "C" int PSCDebug;
int PSCDebug = 1;
extern "C" int PSCInactivityTime;
int PSCInactivityTime = 10;
extern "C" int PSCMaxSendBuffer;
int PSCMaxSendBuffer = 1024 * 1024;

PSC::pscmap_t PSC::pscmap;

Block::Block(PSC *p, epicsUInt16 c)
    :psc(*p)
    ,code(c)
    ,data()
    ,changed(false)
    ,queued(false)
    ,scan()
{
    scanIoInit(&scan);
}


PSC::PSC(const std::string &name,
         const std::string &host,
         unsigned short port,
         unsigned int timeoutmask)
    :name(name)
    ,host(host)
    ,port(port)
    ,mask(timeoutmask)
    ,timer_active(false)
    ,session(NULL)
    ,connected(false)
    ,have_head(false)
    ,header(0)
    ,bodylen(0)
    ,bodyblock(NULL)
    ,expect(HEADER_SIZE)
    ,sendbuf(evbuffer_new())
    ,message("Initialize")
{
    base = EventBase::makeBase();
    event_base *eb = base->get();
    if(!eb)
        throw std::bad_alloc();
    reconnect_timer = evtimer_new(eb, &bev_reconnect, (void*)this);
    dns = evdns_base_new(eb, 1);
    if(!reconnect_timer || !dns || !sendbuf)
        throw std::bad_alloc();

    scanIoInit(&scan);

    pscmap[name] = this;

    epicsAtExit(&ioc_atexit, (void*)this);
}

PSC::~PSC()
{
}


Block* PSC::getSend(epicsUInt16 block)
{
    block_map::const_iterator it = send_blocks.find(block);
    if(it!=send_blocks.end())
        return it->second;
    std::auto_ptr<Block> ret(new Block(this, block));
    send_blocks[block] = ret.get();
    return ret.release();
}

Block* PSC::getRecv(epicsUInt16 block)
{
    block_map::const_iterator it = recv_blocks.find(block);
    if(it!=recv_blocks.end())
        return it->second;
    std::auto_ptr<Block> ret(new Block(this, block));
    recv_blocks[block] = ret.get();
    return ret.release();
}

/* queue the requested register block */
void PSC::send(epicsUInt16 bid)
{
    block_map::const_iterator it = send_blocks.find(bid);
    if(it==recv_blocks.end())
        return;
    Block *block = it->second;

    queueSend(bid, &block->data[0], block->data.size());
}

/* add a new message to the send queue */
void PSC::queueSend(epicsUInt16 id, const void* buf, epicsUInt32 buflen)
{
    if(!connected)
        return;

    Block *blk = getSend(id);
    if(blk->queued)
        throw recAlarm();

    char hbuf[HEADER_SIZE];

    hbuf[0] = 'P';
    hbuf[1] = 'S';
    *(epicsUInt16*)(hbuf+2) = htons(id);
    *(epicsUInt32*)(hbuf+4) = htonl(buflen);

    if(PSCMaxSendBuffer>0 &&
       evbuffer_get_length(sendbuf)>=(size_t)PSCMaxSendBuffer)
        throw std::runtime_error("Enqueuing message would exceed buffer");

    if(evbuffer_expand(sendbuf, HEADER_SIZE+buflen))
        throw std::runtime_error("Unable to enqueue message.  Insufficient memory.");

    int err = evbuffer_add(sendbuf, hbuf, HEADER_SIZE);

    if(!err)
        err = evbuffer_add(sendbuf, buf, buflen);

    // calling evbuffer_expand should ensure the adds never fail
    assert(!err);

    blk->queued = true;

    if(PSCDebug>1)
        fprintf(stderr, "%s: enqueue block %u %lu bytes\n",
                name.c_str(), id, (unsigned long)buflen);
}

/* move contents of send queue to socket send buffer. (aka. actually send) */
void PSC::flushSend()
{
    if(!connected)
        return;
    if(PSCDebug>1)
        fprintf(stderr, "%s: flush\n", name.c_str());

    BEVGuard g(session);
    evbuffer *tx = bufferevent_get_output(session);

    if(PSCMaxSendBuffer>0 &&
       evbuffer_get_length(tx)>=(size_t)PSCMaxSendBuffer)
        throw std::runtime_error("Sending message would exceed buffer");

    if(evbuffer_add_buffer(tx, sendbuf)) {
        evbuffer_drain(sendbuf, evbuffer_get_length(sendbuf));
        throw std::runtime_error("Unable to send messages!");
    }

    for(block_map::const_iterator it = send_blocks.begin(), end = send_blocks.end();
        it!=end; ++it)
    {
        it->second->queued = false;
    }
}

/* start a new connection */
void PSC::connect()
{
    assert(!connected);
    assert(!session);
    assert(!timer_active);

    session = bufferevent_socket_new(base->get(), -1,
                                     BEV_OPT_CLOSE_ON_FREE|BEV_OPT_THREADSAFE|
                                     BEV_OPT_DEFER_CALLBACKS|BEV_OPT_UNLOCK_CALLBACKS);
    if(!session)
        throw std::bad_alloc();

    bufferevent_setcb(session, &bev_datacb, NULL, &bev_eventcb, (void*)this);

    if(PSCInactivityTime>0) {
        timeval timo = {0,0};
        int ret = 0;
        timo.tv_sec = PSCInactivityTime;

        if(mask&1)
            ret=bufferevent_set_timeouts(session, &timo, &timo);
        else
            ret=bufferevent_set_timeouts(session, NULL, &timo);
        if(ret) {
            fprintf(stderr, "%s: Error setting timeout! %d\n", name.c_str(), ret);
        } else if(PSCDebug>0) {
            fprintf(stderr, "%s: will timeout on: send%s\n", name.c_str(),
                    mask&1?" and recv":"");
        }
    }

    bufferevent_setwatermark(session, EV_READ, expect, max_size);

    if(bufferevent_socket_connect_hostname(session, dns, AF_UNSPEC, host.c_str(), port))
    {
        bufferevent_free(session);
        session = NULL;
        timeval timo = {5,0};
        evtimer_add(reconnect_timer, &timo);
        timer_active = true;
        message = "Failed to initiate connection.";
    } else
        message = "Connecting...";
    if(PSCDebug>0)
        fprintf(stderr, "%s: %s\n", name.c_str(), message.c_str());
    scanIoRequest(scan);
}

/* close the socket and initiate a reconnect.
 * Called for socket and protocol errors.
 */
void PSC::start_reconnect()
{
    assert(session && !timer_active);

    bufferevent_free(session);
    session = NULL;

    timeval timo = {5,0};
    evtimer_add(reconnect_timer, &timo);

    connected = false;
    timer_active = true;
}

/* entry point for re-connect timer */
void PSC::reconnect()
{
    assert(!connected);
    assert(!session);
    timer_active = false;

    connect();
    assert(session || timer_active);
}

/* final shutdown and cleanup */
void PSC::stop()
{
    Guard g(lock);
    if(connected) {
        assert(session);
        bufferevent_free(session);
    }
    session=NULL;
    if(timer_active) {
        /*TODO: possible race if timer has expired, but callback hasn't run */
        evtimer_del(reconnect_timer);
    }
    timer_active = false;
    if(PSCDebug>1)
        fprintf(stderr, "%s: stop\n", name.c_str());
}

void PSC::eventcb(short events)
{
    if(events&BEV_EVENT_CONNECTED)
    {
        bufferevent_enable(session, EV_WRITE|EV_READ);

        connected = true;
        message = "Connected";

    } else if(events&(BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT))
    {
        std::string msg;
        if(events&BEV_EVENT_ERROR) {
            msg = "Socket Error: ";
            msg += evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR());
        } else if (events&BEV_EVENT_TIMEOUT) {
            msg = "Connection Timeout";
        } else
            msg = "Connection closed by PSC";

        start_reconnect();

        message = msg;
    } else {
        fprintf(stderr, "%s: eventcb %04x\n", name.c_str(), events);
        return;
    }

    if(PSCDebug>0)
        fprintf(stderr, "%s: %s\n", name.c_str(), message.c_str());
    scanIoRequest(scan);
}

void PSC::recvdata()
{
    assert(connected && session);

    evbuffer *buf = bufferevent_get_input(session);

    for(size_t nbytes = evbuffer_get_length(buf);
        nbytes >= expect;
        nbytes = evbuffer_get_length(buf))
    {

        if(!have_head) { /* decode header */
            assert(expect==HEADER_SIZE);

            char hbuf[HEADER_SIZE];

            evbuffer_remove(buf, &hbuf, sizeof(hbuf));

            if(hbuf[0]!='P' || hbuf[1]!='S') {
                /* unrecoverable protocol framing error detected! */
                start_reconnect();
                message = "Framing error!";
                fprintf(stderr, "%s: %s\n", name.c_str(), message.c_str());
                scanIoRequest(scan);
                return;
            }

            header = ntohs(*(epicsUInt32*)(hbuf+2));
            bodylen = ntohl(*(epicsUInt32*)(hbuf+4));
            have_head = true;

            block_map::const_iterator it=recv_blocks.find(header);
            if(it!=recv_blocks.end())
                bodyblock = it->second;
            else
                bodyblock = NULL;

            if(PSCDebug>2)
                fprintf(stderr, "%s: expect block %u with %lu bytes\n",
                        name.c_str(), header, (unsigned long)bodylen);

            expect = bodylen;

        } else { /* decode body */

            if(PSCDebug>2)
                fprintf(stderr, "%s: recv'd block %u with %lu bytes\n",
                        name.c_str(), header, (unsigned long)bodylen);

            if(bodyblock) {
                if(PSCDebug>2)
                    fprintf(stderr, "%s: Process message %u\n", name.c_str(), header);

                bodyblock->data.reserve(bodylen);
                bodyblock->data.resize(bodylen);

                evbuffer_remove(buf, &bodyblock->data[0], bodylen);
                bodyblock->changed = true;
                scanIoRequest(bodyblock->scan);

            } else {
                /* ignore valid, but uninteresting message body */
                if(PSCDebug>2)
                    fprintf(stderr, "%s: ignore message %u\n", name.c_str(), header);
                evbuffer_drain(buf, bodylen);
            }

            have_head = false;
            bodyblock = NULL;
            expect = HEADER_SIZE;
        }

        /* must have made some progress */
        assert(nbytes > evbuffer_get_length(buf));
    }

    if(PSCDebug>2)
        fprintf(stderr, "Wait for %lu bytes\n", (unsigned long)expect);
    bufferevent_setwatermark(session, EV_READ, expect,
                             expect > max_size ? expect+1 : max_size);
}

void PSC::startAll()
{
    pscmap_t::const_iterator it, end=pscmap.end();
    for(it=pscmap.begin(); it!=end; ++it) {
        Guard g(it->second->lock);
        it->second->connect();
    }
}

PSC* PSC::getPSC(const std::string& name)
{
    pscmap_t::const_iterator it=pscmap.find(name);
    if(it==pscmap.end())
        return NULL;
    return it->second;
}


extern "C"
void createPSC(const char* name, const char* host, int port, int timeout)
{
    try{
        new PSC(name, host, port, timeout);
    }catch(std::exception& e){
        fprintf(stderr, "Failed to create PSC '%s': %s\n", name, e.what());
    }
}

extern "C"
void setPSCSendBlockSize(const char* name, int bid, int size)
{
    try {
        PSC *psc = PSC::getPSC(name);
        if(!psc)
            throw std::runtime_error("Unknown PSC");
        Block *block = psc->getSend(bid);
        if(!block)
            throw std::runtime_error("Can't select PSC Block");
        block->data.resize(size, 0);
        fprintf(stderr, "Set PSC '%s' send block %d size to %lu bytes\n",
                name, bid, (unsigned long)block->data.size());
    }catch(std::exception& e){
        fprintf(stderr, "Failed to set PSC '%s' send block %d size to %d bytes: %s\n",
                name, bid, size, e.what());
    }
}

static void PSCHook(initHookState state)
{
    if(state!=initHookAfterIocRunning)
        return;
    PSC::startAll();
}

#include <iocsh.h>

static const iocshArg createPSCArg0 = {"name", iocshArgString};
static const iocshArg createPSCArg1 = {"hostname", iocshArgString};
static const iocshArg createPSCArg2 = {"port#", iocshArgInt};
static const iocshArg createPSCArg3 = {"enable recv timeout", iocshArgInt};
static const iocshArg * const createPSCArgs[] =
{&createPSCArg0,&createPSCArg1,&createPSCArg2,&createPSCArg3};
static const iocshFuncDef createPSCDef = {"createPSC", 4, createPSCArgs};
static void createPSCArgsCallFunc(const iocshArgBuf *args)
{
    createPSC(args[0].sval, args[1].sval, args[2].ival, args[3].ival);
}

static const iocshArg setPSCArg0 = {"name", iocshArgString};
static const iocshArg setPSCArg1 = {"block", iocshArgInt};
static const iocshArg setPSCArg2 = {"size", iocshArgInt};
static const iocshArg * const setPSCArgs[] = {&setPSCArg0,&setPSCArg1,&setPSCArg2};
static const iocshFuncDef setPSCDef = {"setPSCSendBlockSize", 3, setPSCArgs};
static void setPSCCallFunc(const iocshArgBuf *args)
{
    setPSCSendBlockSize(args[0].sval, args[1].ival, args[2].ival);
}

static void PSCRegister(void)
{
    int ret =
//#if defined(WIN32)
  //      evthread_use_windows_threads();
//#elif defined(_EVENT_HAVE_PTHREADS)
        evthread_use_pthreads();
//#else
  //      1;
//#error libevent threading not support for this target
//#endif
    if(ret!=0) {
        fprintf(stderr, "Failed to initialize libevent threading!.  PSC driver not loaded.\n");
        return;
    }
    iocshRegister(&createPSCDef, &createPSCArgsCallFunc);
    iocshRegister(&setPSCDef, &setPSCCallFunc);
    initHookRegister(&PSCHook);
}

#include <epicsExport.h>

epicsExportAddress(int, PSCDebug);
epicsExportAddress(int, PSCMaxSendBuffer);
epicsExportAddress(int, PSCInactivityTime);

epicsExportRegistrar(PSCRegister);
