
#include "devcommon.h"

#include <algorithm>

#include <biRecord.h>
#include <boRecord.h>
#include <longoutRecord.h>
#include <stringinRecord.h>

recAlarm::recAlarm()
    :std::exception()
    ,status(COMM_ALARM)
    ,severity(INVALID_ALARM)
{}

recAlarm::recAlarm(short sts, short sevr)
    :std::exception()
    ,status(sts)
    ,severity(sevr)
{}

namespace {

long init_common(dbCommon* prec, const char*link)
{
    try {
        PSC *psc = PSC::getPSC(link);
        if(!psc) {
            fprintf(stderr, "%s: can't find PSC '%s'", prec->name, link);
        }
        prec->dpvt = (void*)psc;
    }CATCH(init_common, prec)
    return 0;
}

template<class R>
long init_input(R* prec)
{
    assert(prec->inp.type==INST_IO);
    return init_common((dbCommon*)prec, prec->inp.value.instio.string);
}

template<class R>
long init_output(R* prec)
{
    assert(prec->out.type==INST_IO);
    return init_common((dbCommon*)prec, prec->out.value.instio.string);
}

long get_iointr_info(int cmd, dbCommon *prec, IOSCANPVT *io)
{
    if(!prec->dpvt)
        return -1;
    PSC *psc=(PSC*)prec->dpvt;

    *io = psc->scan;
    return 0;
}

long read_bi_connected(biRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    PSC *psc=(PSC*)prec->dpvt;
    try {
        Guard g(psc->lock);

        prec->rval = psc->isConnected();
    }CATCH(read_bi_connected, prec)

    return 0;
}

long read_si_message(stringinRecord *prec)
{
    if(!prec->dpvt)
        return -1;
    PSC *psc=(PSC*)prec->dpvt;
    try {
        Guard g(psc->lock);

        size_t len = std::max(psc->message.size(), (size_t)MAX_STRING_SIZE);

        strncpy(prec->val, psc->message.c_str(), len);
        prec->val[MAX_STRING_SIZE-1] = '\0';
    }CATCH(read_si_message, prec)

    return 0;
}

long write_bo_send_changed(boRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    PSC *psc=(PSC*)prec->dpvt;
    try {
        Guard g(psc->lock);

        if(!psc->isConnected())
            recGblSetSevr(prec, WRITE_ALARM, INVALID_ALARM);
        else
            psc->flushSend();

    }CATCH(write_bo_send_changed, prec)
    return 0;
}

long write_lo_send_block(longoutRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    PSC *psc=(PSC*)prec->dpvt;
    try {
        Guard g(psc->lock);

        if(prec->val < 0 || prec->val > 0xffff) {
            recGblSetSevr(prec, WRITE_ALARM, INVALID_ALARM);
        } else {
            psc->send(prec->val);
        }
    }CATCH(write_lo_send_block, prec)

    return 0;
}

MAKEDSET(bi, devPSCConnectedBi, &init_input<biRecord>, &get_iointr_info, &read_bi_connected);
MAKEDSET(stringin, devPSCMessageSI, &init_input<stringinRecord>, &get_iointr_info, &read_si_message);
MAKEDSET(bo, devPSCSendAllBo  , &init_output<boRecord>, NULL, &write_bo_send_changed);
MAKEDSET(longout, devPSCSendLo, &init_output<longoutRecord>, NULL, &write_lo_send_block);

} // namespace

#include <epicsExport.h>

epicsExportAddress(dset, devPSCConnectedBi);
epicsExportAddress(dset, devPSCMessageSI);
epicsExportAddress(dset, devPSCSendAllBo);
epicsExportAddress(dset, devPSCSendLo);
