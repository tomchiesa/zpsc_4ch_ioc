
#include "psc.h"

#include <errlog.h>

#define CATCH(NAME) catch(std::exception& e) {errlogPrintf("%s: " #NAME " error: %s\n", psc->name.c_str(), e.what());}

/* to avoid issues with lock order bufferevent callbacks
 * are run with the bufferevent unlocked (cf. BEV_OPT_UNLOCK_CALLBACKS).
 * Then we re-lock in the correct order.
 */
void PSC::bev_eventcb(bufferevent *, short evt, void *raw)
{
    PSC *psc=(PSC*)raw;
    try{
        Guard g(psc->lock);
        BEVGuard h(psc->session);
        psc->eventcb(evt);
    }CATCH(eventcb)
}

void PSC::bev_datacb(bufferevent *, void *raw)
{
    PSC *psc=(PSC*)raw;
    try{
        Guard g(psc->lock);
        BEVGuard h(psc->session);
        psc->recvdata();
    }CATCH(eventcb)
}

void PSC::bev_reconnect(int, short, void *raw)
{
    PSC *psc=(PSC*)raw;
    try{
        Guard g(psc->lock);
        psc->reconnect();
    }CATCH(eventcb)
}

void PSC::ioc_atexit(void *raw)
{
    PSC *psc=(PSC*)raw;
    try{
        Guard g(psc->lock);
        psc->stop();
    }CATCH(eventcb)
}
