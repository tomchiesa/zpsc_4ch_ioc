TOP = ..
include $(TOP)/configure/CONFIG
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *src*))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *Src*))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *db*))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *Db*))
include $(TOP)/configure/RULES_DIRS
#$(COMMON_DIR)/psc.dbd: /usr/local/epics/synApps_6_1/support/calc-R3-7-3/dbd/CALC.dbd
#$(COMMON_DIR)/psc.dbd: /usr/local/epics/synApps_6_1/support/calc-R3-7-3/dbd/calccalcSupport_LOCAL.dbd


