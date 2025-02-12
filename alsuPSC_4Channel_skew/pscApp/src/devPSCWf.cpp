
#include "devcommon.h"

#include <stdio.h>
#include <arpa/inet.h>

#include <menuFtype.h>
#include <waveformRecord.h>

namespace {

long init_wf_record(waveformRecord* prec)
{
    assert(prec->inp.type==INST_IO);
    if(prec->ftvl!=menuFtypeDOUBLE) {
        fprintf(stderr, "%s: FTVL must be DOUBLE\n", prec->name);
        return 0;
    }
    try {
        std::auto_ptr<Priv> priv(new Priv(prec));

        parse_link(priv.get(), prec->inp.value.instio.string, 0);

        prec->dpvt = (void*)priv.release();

    }CATCH(init_wf_record, prec)
return 0;
}

long init_wf_record_bytes(waveformRecord* prec)
{
    assert(prec->inp.type==INST_IO);
    if(!(prec->ftvl==menuFtypeCHAR || prec->ftvl==menuFtypeUCHAR)) {
        fprintf(stderr, "%s: FTVL must be CHAR or UCHAR\n", prec->name);
        return 0;
    }
    try {
        std::auto_ptr<Priv> priv(new Priv(prec));

        parse_link(priv.get(), prec->inp.value.instio.string, 0);

        prec->dpvt = (void*)priv.release();

    }CATCH(init_wf_record, prec)
return 0;
}

long get_iointr_info(int cmd, dbCommon *prec, IOSCANPVT *io)
{
    if(!prec->dpvt)
        return -1;
    Priv *priv=(Priv*)prec->dpvt;

    *io = priv->block->scan;
    return 0;
}

template<typename T>
long read_wf(waveformRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    Priv *priv=(Priv*)prec->dpvt;

    try {
        Guard g(priv->psc->lock);

        if(!priv->psc->isConnected()) {
            int junk = recGblSetSevr(prec, READ_ALARM, INVALID_ALARM);
            junk += 1;
            return 0;
        }

        double *pto = (double*)prec->bptr;
        T *pfrom = (T*)&priv->block->data[0];

        size_t len = priv->block->data.size()/sizeof(T);
        if(len>=prec->nelm)
            len=prec->nelm;

        for(size_t i=0; i<len; i++) {
            // endian fix and cast to signed
            T ival = ntoh(pfrom[i]);
            pto[i] = ival;
        }

        prec->nord = len;
    }CATCH(read_wf, prec)

    return 0;
}

long read_wf_bytes(waveformRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    Priv *priv=(Priv*)prec->dpvt;

    try {
        Guard g(priv->psc->lock);

        if(!priv->psc->isConnected()) {
            int junk = recGblSetSevr(prec, READ_ALARM, INVALID_ALARM);
            junk += 1;
            return 0;
        }

        char *pto = (char*)prec->bptr;
        char *pfrom = &priv->block->data[0];

        size_t len = priv->block->data.size();
        if(len>=prec->nelm)
            len=prec->nelm;

        memcpy(pto, pfrom, len);

        prec->nord = len;

    }CATCH(read_wf_bytes, prec)

    return 0;
}

template<typename T>
long write_wf(waveformRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    Priv *priv=(Priv*)prec->dpvt;
    try {

        size_t len = prec->nord;

        double *pfrom = (double*)prec->bptr;
        std::vector<T> to(len);

        for(size_t i=0; i<len; i++) {
            T ival = pfrom[i];
            // endian fix and cast to unsigned
            to[i] = hton(ival);
        }

        Guard g(priv->psc->lock);

        if(!priv->psc->isConnected()) {
            int junk = recGblSetSevr(prec, READ_ALARM, INVALID_ALARM);
            junk += 1;
            return 0;
        }

        priv->psc->queueSend(priv->bid, &to[0], sizeof(T)*to.size());
    }CATCH(write_wf, prec)

    return 0;
}

long write_wf_bytes(waveformRecord* prec)
{
    if(!prec->dpvt)
        return -1;
    Priv *priv=(Priv*)prec->dpvt;
    try {
        Guard g(priv->psc->lock);

        if(!priv->psc->isConnected()) {
            int junk = recGblSetSevr(prec, READ_ALARM, INVALID_ALARM);
            junk += 1;
            return 0;
        }

        priv->psc->queueSend(priv->bid, prec->bptr, prec->nord);
    }CATCH(write_wf_bytes, prec)

    return 0;
}

MAKEDSET(waveform, devPSCBlockInWf8, &init_wf_record_bytes, &get_iointr_info, &read_wf_bytes);
MAKEDSET(waveform, devPSCBlockOutWf8, &init_wf_record_bytes, &get_iointr_info, &write_wf_bytes);

MAKEDSET(waveform, devPSCBlockInWf16, &init_wf_record, &get_iointr_info, &read_wf<epicsInt16>);
MAKEDSET(waveform, devPSCBlockOutWf16, &init_wf_record, &get_iointr_info, &write_wf<epicsInt16>);

MAKEDSET(waveform, devPSCBlockInWf32, &init_wf_record, &get_iointr_info, &read_wf<epicsInt32>);
MAKEDSET(waveform, devPSCBlockOutWf32, &init_wf_record, &get_iointr_info, &write_wf<epicsInt32>);

} // namespace

#include <epicsExport.h>

epicsExportAddress(dset, devPSCBlockInWf8);
epicsExportAddress(dset, devPSCBlockOutWf8);
epicsExportAddress(dset, devPSCBlockInWf16);
epicsExportAddress(dset, devPSCBlockOutWf16);
epicsExportAddress(dset, devPSCBlockInWf32);
epicsExportAddress(dset, devPSCBlockOutWf32);
