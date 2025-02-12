#ifndef DEVCOMMON_H
#define DEVCOMMON_H

#include "psc.h"

#include <cstdio>
#include <cstring>
#include <sstream>
#include <memory>

#include <epicsAssert.h>
#include <devLib.h> // for S_dev_* codes
#include <devSup.h>
#include <recGbl.h>
#include <dbScan.h>
#include <alarm.h>
#include <link.h>
#include <dbAccess.h>
#include <dbCommon.h>

#define CATCH(NAME, REC) \
    catch(recAlarm& e) {\
     int junk = recGblSetSevr(REC, e.status, e.severity);\
     junk+=0;\
     return S_dev_badRequest;\
    }catch(std::exception& e) {\
     int junk = recGblSetSevr(REC, COMM_ALARM, INVALID_ALARM);\
     junk+=0;\
     fprintf(stderr, "%s: " #NAME " error: %s\n", (REC)->name, e.what());\
     return S_dev_badRequest;\
    }

template<typename R>
struct dsetTyped {
    long	number;
    long (*report)(int);
    long (*init)(int);
    long (*init_record)(R*);
    long (*get_iointr_info)(int cmd, dbCommon *prec, IOSCANPVT *io);
};

template<typename R>
struct dset5 {
    dsetTyped<R> com;
    long (*readwrite)(R*);
};

#define MAKEDSET(REC, NAME, INIT_REC, IOINTR, READ) \
static dset5<REC ## Record> NAME = {{5, NULL, NULL, (INIT_REC), (IOINTR)}, (READ)}

struct Priv
{
    dbCommon *prec;
    PSC *psc;
    epicsUInt16 bid;
    Block *block;
    unsigned long offset;

    template<class R>
    Priv(R*pr) : prec((dbCommon*)pr), psc(0), bid(0), block(0) {}
};

int parse_link(Priv* priv, const char* link, int direction);

namespace detail {
    template<int L> struct nswap {};
    template<> struct nswap<1> {
        typedef epicsInt8 type;
        static type op(type in) {return in;}
    };
    template<> struct nswap<2> {
        typedef epicsInt16 type;
        static type op(type in) {return htons(in);}
    };
    template<> struct nswap<4> {
        typedef epicsInt32 type;
        static type op(type in) {return htonl(in);}
    };
}

template<typename T>
T hton(T in)
{
    typedef typename detail::nswap<sizeof(T)>::type stype;

    return (T)detail::nswap<sizeof(T)>::op(*(stype*)&in);
}
template<typename T>
T ntoh(T in)
{
    // hton and ntoh are symatrical for big and little endian.
    return hton(in);
}

#endif // DEVCOMMON_H
