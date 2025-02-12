#!./bin/linux-x86_64/psc

epicsThreadSleep 1
epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES","20000000")
epicsEnvSet("IP1","10.0.140.160")
epicsEnvSet("IP2","10.0.140.161")
< envPaths
cd $(TOP)
epicsThreadSleep 1

dbLoadDatabase("./dbd/psc.dbd",0,0)
dbLoadDatabase("$(TOP)/dbd/seq.dbd")
psc_registerRecordDeviceDriver(pdbbase)


#Port 7: Cmd, 512 bytes
dbLoadRecords("./db/Command.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/CommandReg.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/CommandRegAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/CommandRegJumpAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/DigitalCommand.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/Calculation.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/CommandRegBip.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/Fault_Settings.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")


dbLoadRecords("./db/Command.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/CommandReg.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/CommandRegAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/CommandRegJumpAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/DigitalCommand.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/Calculation.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/CommandRegBip.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/Fault_Settings.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")

dbLoadRecords("./db/Command.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/CommandReg.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/CommandRegAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/CommandRegJumpAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/DigitalCommand.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/Calculation.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/CommandRegBip.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/Fault_Settings.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")

dbLoadRecords("./db/Command.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/CommandReg.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/CommandRegAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/CommandRegJumpAux.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/DigitalCommand.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/Calculation.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/CommandRegBip.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/Fault_Settings.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")

#Port 17: Status
dbLoadRecords("./db/Status.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/ADC.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan1")
dbLoadRecords("./db/Status.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/ADC.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan2")
dbLoadRecords("./db/Status.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/ADC.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan3")
dbLoadRecords("./db/Status.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/ADC.db","PriSys=SR:C04-MG,PSC=zPSC1,CHAN=Chan4")
dbLoadRecords("./db/BipPkt.db","PriSys=SR:C04-MG,PSC=zPSC1")


#Port 27: Ramping Table, 80K  2 second 10KHz
dbLoadRecords("./db/RampingTable.db","PriSys=SR:C04-MG,PSC=zPSC1,msgid1=81,msgid2=82,msgid3=83,msgid4=84,RT_LENGTH=100000")

#Port 37: ADC readback. 2,560,000 bytes, 32 ADC, 10KH, 10 second
dbLoadRecords("./db/ADCWaveform.db","PriSys=SR:C04-MG,PSC=zPSC1,ADC1K_POINTS=1000,ADCSnapShot_POINTS=20000,ADC10K_POINTS=2621440")

epicsThreadSleep 1

var(PSCDebug, 1)
display debug message var(PSCDebug, 2)

#make connection
createPSC("CmdPort_zPSC1", $(IP1), 7,0)
setPSCSendBlockSize("CmdPort_zPSC1", 80, 1280)
epicsThreadSleep 0.1

createPSC("RampTablePort_zPSC1", $(IP1), 27,0)
setPSCSendBlockSize("RampTablePort_zPSC1", 81, 400000)
setPSCSendBlockSize("RampTablePort_zPSC1", 82, 400000)
setPSCSendBlockSize("RampTablePort_zPSC1", 83, 400000)
setPSCSendBlockSize("RampTablePort_zPSC1", 84, 400000)
epicsThreadSleep 0.1

createPSC("StatusPort_zPSC1", $(IP1), 17,0)
epicsThreadSleep 0.1

createPSC("AdcPort_zPSC1", $(IP1), 37,0)
epicsThreadSleep 0.1


set_pass1_restoreFile("$(AUTOSAVE_DIR)/$(IOCNAME).sav")

iocInit()

# Create request file and start periodic 'save’
makeAutosaveFileFromDbInfo("$(AUTOSAVE_DIR)/$(IOCNAME).req","autosaveFields")
create_monitor_set("$(AUTOSAVE_DIR)/$(IOCNAME).req", 5,"")

#Enable Snapshot Buffer and Clear Faults for all channels 
epicsThreadSleep 1 

#EVR Frequency 
dbpf SR:C04-MG{zPSC1:Chan0}EVRFreq-val 125.0
#Pulsed Mode On = 1
dbpf SR:C04-MG{zPSC1}B21-Cmd 1

#Channel Initializations
#dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan12-sp 217517303
#dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan34-sp 217517303
dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan1 3319
dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan2 3319
dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan3 3319
dbpf SR:C04-MG{zPSC1:Chan0}FltEnableChan4 3319

dbpf SR:C04-MG{zPSC1:Chan0}PsOnFltDec-sp 2.5
dbpf SR:C04-MG{zPSC1:Chan0}PsHBFltDec-sp 2.5

dbpf SR:C04-MG{zPSC1}Chan1:On3-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan2:On3-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan3:On3-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan4:On3-Cmd 1


dbpf SR:C04-MG{zPSC1:Chan1}I-sp 0.0
dbpf SR:C04-MG{zPSC1:Chan2}I-sp 0.0
dbpf SR:C04-MG{zPSC1:Chan3}I-sp 0.0
dbpf SR:C04-MG{zPSC1:Chan4}I-sp 0.0

dbpf SR:C04-MG{zPSC1:Chan0}EVR-OneHz-Code-ao 122
dbpf SR:C04-MG{zPSC1:Chan0}EVR-Diagnostic-Code-ao 255
dbpf SR:C04-MG{zPSC1:Chan0}EVR-Spare2-Code-ao 255
dbpf SR:C04-MG{zPSC1:Chan0}EVR-BeamDump-Code-ao 255
dbpf SR:C04-MG{zPSC1:Chan0}EVR-TenKHz-Code-ao 31

dbpf SR:C04-MG{zPSC1:Chan1}BipIP1Addr-sp -1062731774
dbpf SR:C04-MG{zPSC1:Chan1}BipMAC1Hi-sp  33554532
dbpf SR:C04-MG{zPSC1:Chan1}BipMAC1Lo-sp  258


dbpf SR:C04-MG{zPSC1:Chan1}Impd-sp 1.2
dbpf SR:C04-MG{zPSC1:Chan2}Impd-sp 1.2 
dbpf SR:C04-MG{zPSC1:Chan3}Impd-sp 1.2 
dbpf SR:C04-MG{zPSC1:Chan4}Impd-sp 1.2

dbpf SR:C04-MG{zPSC1:Chan1}I-Gain-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan2}I-Gain-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan3}I-Gain-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan4}I-Gain-sp 1.0

dbpf SR:C04-MG{zPSC1:Chan1}RampRate-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan2}RampRate-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan3}RampRate-sp 1.0
dbpf SR:C04-MG{zPSC1:Chan4}RampRate-sp 1.0

dbpf SR:C04-MG{zPSC1}Chan1-DAC-SP-Impd 1.2
dbpf SR:C04-MG{zPSC1}Chan2-DAC-SP-Impd 1.2
dbpf SR:C04-MG{zPSC1}Chan3-DAC-SP-Impd 1.2
dbpf SR:C04-MG{zPSC1}Chan4-DAC-SP-Impd 1.2

dbpf SR:C04-MG{zPSC1}Chan1-DAC-SP-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-DAC-SP-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-DAC-SP-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-DAC-SP-Gain 1.0

dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan1-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan2-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan3-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan4-Impd 1.2

dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan1-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan2-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan3-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct1ADC:Chan4-Gain 1.0

dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan1-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan2-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan3-Impd 1.2
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan4-Impd 1.2

dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan1-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan2-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan3-Gain 1.0
dbpf SR:C04-MG{zPSC1}dcct2ADC:Chan4-Gain 1.0

dbpf SR:C04-MG{zPSC1}Chan1-PS-Err-Impd 0.003
dbpf SR:C04-MG{zPSC1}Chan2-PS-Err-Impd 0.003
dbpf SR:C04-MG{zPSC1}Chan3-PS-Err-Impd 0.003
dbpf SR:C04-MG{zPSC1}Chan4-PS-Err-Impd 0.003

dbpf SR:C04-MG{zPSC1}Chan1-PS-Err-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-PS-Err-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-PS-Err-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-PS-Err-Gain 1.0

dbpf SR:C04-MG{zPSC1}Chan1-PS-Reg-Out-Impd 1.0
dbpf SR:C04-MG{zPSC1}Chan2-PS-Reg-Out-Impd 1.0
dbpf SR:C04-MG{zPSC1}Chan3-PS-Reg-Out-Impd 1.0
dbpf SR:C04-MG{zPSC1}Chan4-PS-Reg-Out-Impd 1.0

dbpf SR:C04-MG{zPSC1}Chan1-PS-Reg-Out-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-PS-Reg-Out-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-PS-Reg-Out-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-PS-Reg-Out-Gain 1.0

dbpf SR:C04-MG{zPSC1}Chan1-VOLT-Mon-Impd 1.9
dbpf SR:C04-MG{zPSC1}Chan2-VOLT-Mon-Impd 1.9
dbpf SR:C04-MG{zPSC1}Chan3-VOLT-Mon-Impd 1.9
dbpf SR:C04-MG{zPSC1}Chan4-VOLT-Mon-Impd 1.9

dbpf SR:C04-MG{zPSC1}Chan1-VOLT-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-VOLT-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-VOLT-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-VOLT-Mon-Gain 1.0

dbpf SR:C04-MG{zPSC1}Chan1-GND-Mon-Impd 10.0
dbpf SR:C04-MG{zPSC1}Chan2-GND-Mon-Impd 10.0
dbpf SR:C04-MG{zPSC1}Chan3-GND-Mon-Impd 10.0
dbpf SR:C04-MG{zPSC1}Chan4-GND-Mon-Impd 10.0

dbpf SR:C04-MG{zPSC1}Chan1-GND-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-GND-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-GND-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-GND-Mon-Gain 1.0

dbpf SR:C04-MG{zPSC1}Chan1-Spare-Mon-Impd -5.0
dbpf SR:C04-MG{zPSC1}Chan2-Spare-Mon-Impd -5.0
dbpf SR:C04-MG{zPSC1}Chan3-Spare-Mon-Impd -5.0
dbpf SR:C04-MG{zPSC1}Chan4-Spare-Mon-Impd -5.0

dbpf SR:C04-MG{zPSC1}Chan1-Spare-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan2-Spare-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan3-Spare-Mon-Gain 1.0
dbpf SR:C04-MG{zPSC1}Chan4-Spare-Mon-Gain 1.0


dbpf SR:C04-MG{zPSC1:Chan1}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan2}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan3}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan4}Mode-cmd 0


#Initialize in Park 
dbpf SR:C04-MG{zPSC1}Chan1:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan2:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan3:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan4:Park-Cmd 1

#Initialze with AC ON2(INHIBIT) Enabled
dbpf SR:C04-MG{zPSC1}Chan1:On2-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan2:On2-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan3:On2-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan4:On2-Cmd 1


dbpf SR:C04-MG{zPSC1:Chan1}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan2}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan3}Mode-cmd 0
dbpf SR:C04-MG{zPSC1:Chan4}Mode-cmd 0


dbpf SR:C04-MG{zPSC1:Chan0}IgndFaltChan0LimitDec-sp 0.2
dbpf SR:C04-MG{zPSC1:Chan0}ErrFaltLimitDec-sp 0.2

#Initialize in Park 
dbpf SR:C04-MG{zPSC1}Chan1:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan2:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan3:Park-Cmd 1
dbpf SR:C04-MG{zPSC1}Chan4:Park-Cmd 1


#Set Clock Mux to 1
dbpf SR:C04-MG{zPSC1}B22-Cmd 1


#Enable snapshot circular buffer
dbpf SR:C04-MG{zPSC1:Chan2}Command-cmd 1
iocInit()
#seq ch1_fsm, "PriSys=SR:C04-MG,PSC=zPSC,CHAN=Chan1"
seq ch1_fsm
seq ch2_fsm
seq ch3_fsm
seq ch4_fsm






