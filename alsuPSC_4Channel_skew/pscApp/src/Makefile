TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = psc
# psc.dbd will be created and installed
DBD += psc.dbd


# psc.dbd will be made up from these files:
psc_DBD += base.dbd
psc_DBD += asSupport.dbd
psc_DBD += pscdrv.dbd
psc_DBD += aSubOperation.dbd
psc_DBD += calc.dbd
psc_DBD += aCalcoutRecord.dbd

psc_DBD += ch1_fsm.dbd
psc_DBD += ch2_fsm.dbd
psc_DBD += ch3_fsm.dbd
psc_DBD += ch4_fsm.dbd

# Includ dbd files from all support applications: 
psc_DBD += support.dbd
psc_DBD += calcSupport.dbd

# Add all the support libraries needed by this IOC
#psc_LIBS += xxx
psc_LIBS += app
psc_LIBS += calc

# psc_registerRecordDeviceDriver.cpp derives from psc.dbd
psc_SRCS += psc_registerRecordDeviceDriver.cpp

psc_SRCS += evbase.cpp
psc_SRCS += aSubOperation.c

psc_SRCS += psc.cpp
psc_SRCS += pscwrap.cpp
psc_SRCS += devcommon.cpp
psc_SRCS += devPSCString.cpp
psc_SRCS += devPSCWf.cpp
psc_SRCS += devPSCReg.cpp
psc_SRCS += devPSCCtrl.cpp

psc_SRCS += aSubOperations.c

# Build the main IOC entry point on workstation OSs.
psc_SRCS_DEFAULT += pscMain.cpp
psc_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#psc_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

psc_SRCS += ch1_fsm.st
psc_SRCS += ch2_fsm.st
psc_SRCS += ch3_fsm.st
psc_SRCS += ch4_fsm.st

LIBRARY_IOC += app

app_SRCS += int2flt.c


# Finally link to the EPICS Base libraries
psc_LIBS += $(EPICS_BASE_IOC_LIBS)
psc_LIBS += autosave
psc_LIBS += seq pv

psc_SYS_LIBS += event_core event_extra

ifeq ($(POSIX),YES)
psc_SYS_LIBS += event_pthreads
endif

ifneq ($(LIBEVENT),)
LDFLAGS += -L$(LIBEVENT)/lib
CPPFLAGS += -I$(LIBEVENT)/include
endif

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

