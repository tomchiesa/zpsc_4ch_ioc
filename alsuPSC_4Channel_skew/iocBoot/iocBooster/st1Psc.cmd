#!../../bin/linux-x86/psc

epicsThreadSleep 5
## You may have to change psc to something else
## everywhere it appears in this file

## Register all support components
dbLoadDatabase("../../dbd/psc.dbd",0,0)
psc_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/Commands.db","PriSys=BR,PS=PSC17")
dbLoadRecords("../../db/Status.db","PriSys=BR,PS=PSC17")
dbLoadRecords("../../db/ADCWaveform.db","PriSys=BR,PS=PSC17,ADC1K_POINTS=1100,ADC10K_POINTS=11000")
dbLoadRecords("../../db/RampingTable.db","PriSys=BR,PS=PSC17,WF10K_LENGTH=43440")

var(PSCDebug, 2)

createPSC("Rx", "10.0.140.31", 20)
createPSC("Tx", "10.0.140.31", 7)
setPSCSendBlockSize("Tx", 80, 128)

iocInit()

