#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>


static long int2flt(aSubRecord* prec) {
    float  *pFlt = (float *)prec->a;
    double *pDbl = (double *)prec->vala;

    *pDbl = (double)*pFlt;

    prec->neva = 1;

    return 0;
}

static registryFunctionRef asub_seq[] = {
    {"INT2FLT", (REGISTRYFUNCTION) &int2flt}
};

static void calcRegister(void) {
    registryFunctionRefAdd(asub_seq, 1);
}

epicsExportRegistrar(calcRegister);
