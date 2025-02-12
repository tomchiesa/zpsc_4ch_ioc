TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += Command.db
DB += CommandReg.db
DB += DigitalCommand.db
DB += Status.db
DB += ADC.db
DB += Calculation.db
DB += ADCWaveform.db
DB += RampingTable.db
DB += CommandRegAux.db
DB += CommandRegJumpAux.db
DB += CommandRegBip.db
DB += Fault_Settings.db
DB += BipPkt.db
#DB += Calibration.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
