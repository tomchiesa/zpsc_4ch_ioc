/* C code for program ch3_fsm, generated by snc from ../ch3_fsm.st */
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#include "seq_snc.h"

/* Variable declarations */
struct seqg_vars {
# line 12 "../ch3_fsm.st"
	short Park;
# line 13 "../ch3_fsm.st"
	short on_cmd;
# line 14 "../ch3_fsm.st"
	short ch3_dac_setpoint;
# line 15 "../ch3_fsm.st"
	short on1_cmd;
# line 16 "../ch3_fsm.st"
	short ch3_clr_flts;
# line 17 "../ch3_fsm.st"
	short ch3_mode;
# line 18 "../ch3_fsm.st"
	short ch3_ps_on_off_sts;
# line 21 "../ch3_fsm.st"
	short ch3_dac_rdbck;
# line 22 "../ch3_fsm.st"
	short ch3_ps_sts;
# line 25 "../ch3_fsm.st"
	string Chan3_seq_messages;
};


/* Function declarations */

#define seqg_var (*(struct seqg_vars *const *)seqg_env)

/* Program init func */
static void seqg_init(PROG_ID seqg_env)
{
}

/****** Code for state "INIT" in state set "OFF_ON_FSM" ******/

/* Event function for state "INIT" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_INIT(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
	if (TRUE)
	{
		*seqg_pnst = 1;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "INIT" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_INIT(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 30 "../ch3_fsm.st"
			seqg_var->Park = 1;
# line 31 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 0/*Park*/, DEFAULT, DEFAULT_TIMEOUT);
# line 32 "../ch3_fsm.st"
			seqg_var->on1_cmd = 0;
# line 33 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 3/*on1_cmd*/, DEFAULT, DEFAULT_TIMEOUT);
# line 34 "../ch3_fsm.st"
			seqg_var->ch3_mode = 0;
# line 35 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 5/*ch3_mode*/, DEFAULT, DEFAULT_TIMEOUT);
# line 36 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "PS OFF");
# line 37 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 38 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 1;
# line 39 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "IDLE" in state set "OFF_ON_FSM" ******/

/* Event function for state "IDLE" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_IDLE(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 43 "../ch3_fsm.st"
	if (seqg_var->on_cmd == 1)
	{
		*seqg_pnst = 2;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "IDLE" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_IDLE(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 44 "../ch3_fsm.st"
			seqg_var->Park = 1;
# line 45 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 0/*Park*/, DEFAULT, DEFAULT_TIMEOUT);
# line 46 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 0;
# line 47 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
# line 48 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Zero DAC");
# line 49 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 50 "../ch3_fsm.st"
			seqg_var->ch3_dac_setpoint = 0.0;
# line 51 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 2/*ch3_dac_setpoint*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "WAIT_FOR_DAC_CHANGE_ON" in state set "OFF_ON_FSM" ******/

/* Event function for state "WAIT_FOR_DAC_CHANGE_ON" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 56 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 3))
	{
		*seqg_pnst = 3;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "WAIT_FOR_DAC_CHANGE_ON" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
		}
		return;
	}
}

/****** Code for state "SET_DAC_TO_ZERO_ON" in state set "OFF_ON_FSM" ******/

/* Event function for state "SET_DAC_TO_ZERO_ON" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 60 "../ch3_fsm.st"
	if ((seqg_var->ch3_dac_rdbck < 0.01) && (seqg_var->ch3_dac_rdbck > -0.01))
	{
		*seqg_pnst = 4;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "SET_DAC_TO_ZERO_ON" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 61 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Zero DAC");
# line 62 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 63 "../ch3_fsm.st"
			seqg_var->ch3_dac_setpoint = 0.000;
# line 64 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 2/*ch3_dac_setpoint*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "POWER_ON" in state set "OFF_ON_FSM" ******/

/* Event function for state "POWER_ON" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_POWER_ON(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 68 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 4))
	{
		*seqg_pnst = 5;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "POWER_ON" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_POWER_ON(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 69 "../ch3_fsm.st"
			seqg_var->Park = 1;
# line 70 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 0/*Park*/, DEFAULT, DEFAULT_TIMEOUT);
# line 71 "../ch3_fsm.st"
			seqg_var->ch3_mode = 0;
# line 72 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 5/*ch3_mode*/, DEFAULT, DEFAULT_TIMEOUT);
# line 73 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Pwr ON");
# line 74 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 75 "../ch3_fsm.st"
			seqg_var->on1_cmd = 1;
# line 76 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 3/*on1_cmd*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "CLEAR_FAULTS" in state set "OFF_ON_FSM" ******/

/* Event function for state "CLEAR_FAULTS" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_CLEAR_FAULTS(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 80 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 2))
	{
		*seqg_pnst = 6;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "CLEAR_FAULTS" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_CLEAR_FAULTS(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 81 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Clr Faults");
# line 82 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 83 "../ch3_fsm.st"
			seqg_var->ch3_clr_flts = 1;
# line 84 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 4/*ch3_clr_flts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "WAIT_TO_CLEAR" in state set "OFF_ON_FSM" ******/

/* Event function for state "WAIT_TO_CLEAR" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_WAIT_TO_CLEAR(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 88 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 5))
	{
		*seqg_pnst = 7;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "WAIT_TO_CLEAR" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_WAIT_TO_CLEAR(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 89 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Clearing");
# line 90 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 91 "../ch3_fsm.st"
			seqg_var->ch3_clr_flts = 0;
# line 92 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 4/*ch3_clr_flts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "PARK_OFF" in state set "OFF_ON_FSM" ******/

/* Event function for state "PARK_OFF" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_PARK_OFF(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 96 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 5))
	{
		*seqg_pnst = 8;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "PARK_OFF" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_PARK_OFF(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 97 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Park OFF");
# line 98 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 99 "../ch3_fsm.st"
			seqg_var->Park = 0;
# line 100 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 0/*Park*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "DONE_CHECK" in state set "OFF_ON_FSM" ******/

/* Event function for state "DONE_CHECK" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_DONE_CHECK(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 104 "../ch3_fsm.st"
	if (seqg_var->ch3_ps_sts == 0)
	{
		*seqg_pnst = 9;
		*seqg_ptrn = 0;
		return TRUE;
	}
# line 110 "../ch3_fsm.st"
	if (seqg_var->ch3_ps_sts == 1)
	{
		*seqg_pnst = 10;
		*seqg_ptrn = 1;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "DONE_CHECK" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_DONE_CHECK(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 105 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "FAULTED");
# line 106 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 107 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 1;
# line 108 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	case 1:
		{
		}
		return;
	}
}

/****** Code for state "RETRY_ON" in state set "OFF_ON_FSM" ******/

/* Event function for state "RETRY_ON" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_RETRY_ON(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 114 "../ch3_fsm.st"
	if (seqg_var->on_cmd == 0)
	{
		*seqg_pnst = 1;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "RETRY_ON" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_RETRY_ON(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 115 "../ch3_fsm.st"
			seqg_var->Park = 1;
# line 116 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 1;
# line 117 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
# line 118 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Try Again");
# line 119 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "DONE" in state set "OFF_ON_FSM" ******/

/* Event function for state "DONE" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_DONE(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 123 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 1))
	{
		*seqg_pnst = 11;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "DONE" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_DONE(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 124 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "PS Ready");
# line 125 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 126 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 1;
# line 127 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "READY" in state set "OFF_ON_FSM" ******/

/* Event function for state "READY" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_READY(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 131 "../ch3_fsm.st"
	if (seqg_var->on_cmd == 0)
	{
		*seqg_pnst = 12;
		*seqg_ptrn = 0;
		return TRUE;
	}
# line 140 "../ch3_fsm.st"
	if (seqg_var->on_cmd == 1)
	{
		*seqg_pnst = 11;
		*seqg_ptrn = 1;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "READY" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_READY(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 132 "../ch3_fsm.st"
			seqg_var->Park = 1;
# line 133 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Zero DAC");
# line 134 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 135 "../ch3_fsm.st"
			seqg_var->ch3_dac_setpoint = 0.00;
# line 136 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 2/*ch3_dac_setpoint*/, DEFAULT, DEFAULT_TIMEOUT);
# line 137 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 0;
# line 138 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	case 1:
		{
# line 141 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, " PS Ready");
# line 142 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "SET_DAC_TO_ZERO_OFF" in state set "OFF_ON_FSM" ******/

/* Event function for state "SET_DAC_TO_ZERO_OFF" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 147 "../ch3_fsm.st"
	if ((seqg_var->ch3_dac_rdbck < 0.01) && (seqg_var->ch3_dac_rdbck > -0.01))
	{
		*seqg_pnst = 13;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "SET_DAC_TO_ZERO_OFF" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 148 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Pls Wait");
# line 149 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "POWER_OFF" in state set "OFF_ON_FSM" ******/

/* Event function for state "POWER_OFF" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_POWER_OFF(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 153 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 5))
	{
		*seqg_pnst = 14;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "POWER_OFF" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_POWER_OFF(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 154 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Pwr OFF");
# line 155 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 156 "../ch3_fsm.st"
			seqg_var->on1_cmd = 0;
# line 157 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 3/*on1_cmd*/, DEFAULT, DEFAULT_TIMEOUT);
# line 158 "../ch3_fsm.st"
			seqg_var->Park = 0;
# line 159 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 0/*Park*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

/****** Code for state "COMPLETE" in state set "OFF_ON_FSM" ******/

/* Event function for state "COMPLETE" in state set "OFF_ON_FSM" */
static seqBool seqg_event_OFF_ON_FSM_0_COMPLETE(SS_ID seqg_env, int *seqg_ptrn, int *seqg_pnst)
{
# line 163 "../ch3_fsm.st"
	if (seq_delay(seqg_env, 1))
	{
		*seqg_pnst = 0;
		*seqg_ptrn = 0;
		return TRUE;
	}
	return FALSE;
}

/* Action function for state "COMPLETE" in state set "OFF_ON_FSM" */
static void seqg_action_OFF_ON_FSM_0_COMPLETE(SS_ID seqg_env, int seqg_trn, int *seqg_pnst)
{
	switch(seqg_trn)
	{
	case 0:
		{
# line 164 "../ch3_fsm.st"
			sprintf(seqg_var->Chan3_seq_messages, "Pwr OFF");
# line 165 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 9/*Chan3_seq_messages*/, DEFAULT, DEFAULT_TIMEOUT);
# line 166 "../ch3_fsm.st"
			seqg_var->ch3_ps_on_off_sts = 1;
# line 167 "../ch3_fsm.st"
			seq_pvPutTmo(seqg_env, 6/*ch3_ps_on_off_sts*/, DEFAULT, DEFAULT_TIMEOUT);
		}
		return;
	}
}

#undef seqg_var

/************************ Tables ************************/

/* Channel table */
static seqChan seqg_chans[] = {
	/* chName, offset, varName, varType, count, eventNum, efId, monitored, queueSize, queueIndex */
	{"{M0}:Park-Cmd", offsetof(struct seqg_vars, Park), "Park", P_SHORT, 1, 1, 0, 1, 0, 0},
	{"{M1}On-Cmd", offsetof(struct seqg_vars, on_cmd), "on_cmd", P_SHORT, 1, 2, 0, 1, 0, 0},
	{"{M1}I-sp", offsetof(struct seqg_vars, ch3_dac_setpoint), "ch3_dac_setpoint", P_SHORT, 1, 3, 0, 1, 0, 0},
	{"{M0}:On1-Cmd", offsetof(struct seqg_vars, on1_cmd), "on1_cmd", P_SHORT, 1, 4, 0, 1, 0, 0},
	{"{M2}FltClearChan3-bo", offsetof(struct seqg_vars, ch3_clr_flts), "ch3_clr_flts", P_SHORT, 1, 5, 0, 1, 0, 0},
	{"{M1}Mode-cmd", offsetof(struct seqg_vars, ch3_mode), "ch3_mode", P_SHORT, 1, 6, 0, 1, 0, 0},
	{"{M0}:PsOnOff-Sts", offsetof(struct seqg_vars, ch3_ps_on_off_sts), "ch3_ps_on_off_sts", P_SHORT, 1, 7, 0, 1, 0, 0},
	{"{M0}-DAC-SP", offsetof(struct seqg_vars, ch3_dac_rdbck), "ch3_dac_rdbck", P_SHORT, 1, 8, 0, 1, 0, 0},
	{"{M0}:Status0", offsetof(struct seqg_vars, ch3_ps_sts), "ch3_ps_sts", P_SHORT, 1, 9, 0, 1, 0, 0},
	{"Chan3_seq_messages", offsetof(struct seqg_vars, Chan3_seq_messages), "Chan3_seq_messages", P_STRING, 1, 10, 0, 0, 0, 0},
};

/* Event masks for state set "OFF_ON_FSM" */
static const seqMask seqg_mask_OFF_ON_FSM_0_INIT[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_IDLE[] = {
	0x00000004,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON[] = {
	0x00000100,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_POWER_ON[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_CLEAR_FAULTS[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_WAIT_TO_CLEAR[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_PARK_OFF[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_DONE_CHECK[] = {
	0x00000200,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_RETRY_ON[] = {
	0x00000004,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_DONE[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_READY[] = {
	0x00000004,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF[] = {
	0x00000100,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_POWER_OFF[] = {
	0x00000000,
};
static const seqMask seqg_mask_OFF_ON_FSM_0_COMPLETE[] = {
	0x00000000,
};

/* State table for state set "OFF_ON_FSM" */
static seqState seqg_states_OFF_ON_FSM[] = {
	{
	/* state name */        "INIT",
	/* action function */   seqg_action_OFF_ON_FSM_0_INIT,
	/* event function */    seqg_event_OFF_ON_FSM_0_INIT,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_INIT,
	/* state options */     (0)
	},
	{
	/* state name */        "IDLE",
	/* action function */   seqg_action_OFF_ON_FSM_0_IDLE,
	/* event function */    seqg_event_OFF_ON_FSM_0_IDLE,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_IDLE,
	/* state options */     (0)
	},
	{
	/* state name */        "WAIT_FOR_DAC_CHANGE_ON",
	/* action function */   seqg_action_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON,
	/* event function */    seqg_event_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_WAIT_FOR_DAC_CHANGE_ON,
	/* state options */     (0)
	},
	{
	/* state name */        "SET_DAC_TO_ZERO_ON",
	/* action function */   seqg_action_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON,
	/* event function */    seqg_event_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_SET_DAC_TO_ZERO_ON,
	/* state options */     (0)
	},
	{
	/* state name */        "POWER_ON",
	/* action function */   seqg_action_OFF_ON_FSM_0_POWER_ON,
	/* event function */    seqg_event_OFF_ON_FSM_0_POWER_ON,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_POWER_ON,
	/* state options */     (0)
	},
	{
	/* state name */        "CLEAR_FAULTS",
	/* action function */   seqg_action_OFF_ON_FSM_0_CLEAR_FAULTS,
	/* event function */    seqg_event_OFF_ON_FSM_0_CLEAR_FAULTS,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_CLEAR_FAULTS,
	/* state options */     (0)
	},
	{
	/* state name */        "WAIT_TO_CLEAR",
	/* action function */   seqg_action_OFF_ON_FSM_0_WAIT_TO_CLEAR,
	/* event function */    seqg_event_OFF_ON_FSM_0_WAIT_TO_CLEAR,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_WAIT_TO_CLEAR,
	/* state options */     (0)
	},
	{
	/* state name */        "PARK_OFF",
	/* action function */   seqg_action_OFF_ON_FSM_0_PARK_OFF,
	/* event function */    seqg_event_OFF_ON_FSM_0_PARK_OFF,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_PARK_OFF,
	/* state options */     (0)
	},
	{
	/* state name */        "DONE_CHECK",
	/* action function */   seqg_action_OFF_ON_FSM_0_DONE_CHECK,
	/* event function */    seqg_event_OFF_ON_FSM_0_DONE_CHECK,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_DONE_CHECK,
	/* state options */     (0)
	},
	{
	/* state name */        "RETRY_ON",
	/* action function */   seqg_action_OFF_ON_FSM_0_RETRY_ON,
	/* event function */    seqg_event_OFF_ON_FSM_0_RETRY_ON,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_RETRY_ON,
	/* state options */     (0)
	},
	{
	/* state name */        "DONE",
	/* action function */   seqg_action_OFF_ON_FSM_0_DONE,
	/* event function */    seqg_event_OFF_ON_FSM_0_DONE,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_DONE,
	/* state options */     (0)
	},
	{
	/* state name */        "READY",
	/* action function */   seqg_action_OFF_ON_FSM_0_READY,
	/* event function */    seqg_event_OFF_ON_FSM_0_READY,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_READY,
	/* state options */     (0)
	},
	{
	/* state name */        "SET_DAC_TO_ZERO_OFF",
	/* action function */   seqg_action_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF,
	/* event function */    seqg_event_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_SET_DAC_TO_ZERO_OFF,
	/* state options */     (0)
	},
	{
	/* state name */        "POWER_OFF",
	/* action function */   seqg_action_OFF_ON_FSM_0_POWER_OFF,
	/* event function */    seqg_event_OFF_ON_FSM_0_POWER_OFF,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_POWER_OFF,
	/* state options */     (0)
	},
	{
	/* state name */        "COMPLETE",
	/* action function */   seqg_action_OFF_ON_FSM_0_COMPLETE,
	/* event function */    seqg_event_OFF_ON_FSM_0_COMPLETE,
	/* entry function */    0,
	/* exit function */     0,
	/* event mask array */  seqg_mask_OFF_ON_FSM_0_COMPLETE,
	/* state options */     (0)
	},
};

/* State set table */
static seqSS seqg_statesets[] = {
	{
	/* state set name */    "OFF_ON_FSM",
	/* states */            seqg_states_OFF_ON_FSM,
	/* number of states */  15
	},
};

/* Program table (global) */
seqProgram ch3_fsm = {
	/* magic number */      2002009,
	/* program name */      "ch3_fsm",
	/* channels */          seqg_chans,
	/* num. channels */     10,
	/* state sets */        seqg_statesets,
	/* num. state sets */   1,
	/* user var size */     sizeof(struct seqg_vars),
	/* param */             "M0=SR:C04-MG{zPSC1}Chan3,M1=SR:C04-MG{zPSC1:Chan3}, M2=SR:C04-MG{zPSC1}",
	/* num. event flags */  0,
	/* encoded options */   (0 | OPT_NEWEF | OPT_REENT),
	/* init func */         seqg_init,
	/* entry func */        0,
	/* exit func */         0,
	/* num. queues */       0
};

/* Register sequencer commands and program */
#include "epicsExport.h"
static void ch3_fsmRegistrar (void) {
    seqRegisterSequencerCommands();
    seqRegisterSequencerProgram (&ch3_fsm);
}
epicsExportRegistrar(ch3_fsmRegistrar);
