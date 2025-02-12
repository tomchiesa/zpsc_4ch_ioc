/* Sequencer to control the on-demond record process: ramping table download, power supply mode change, and watch funciton upload */

#define PRINTF seqLog

program PSC

/* options */
option  +r;
option  -c; 

/* Rev1.4 add monitor of Sp1Valid1s so that the small negtive setpoint in unipolar case will not pass to Sp1Valid1s */
char Polarity;
assign Polarity to "{PriSys}-{SecSys}{PS}Pol:PSI-Sts";
monitor Polarity;

/*Rev1.2: add statemachine to compare Sp1Valid_, Sp1Valid1s_. The setpoint will only update when Sp1 is stable for 1 second. This allow user to use step click button to adjust setpoin. */
double Sp1SP;
double Sp1Valid;
double Sp1Valid1s;
assign Sp1SP to "{PriSys}-{SecSys}{PS}I:Sp1-SP.VAL";
assign Sp1Valid to "{PriSys}-{SecSys}{PS}Sp1Valid_.VAL";
assign Sp1Valid1s to "{PriSys}-{SecSys}{PS}Sp1Valid1s_.VAL";
monitor Sp1SP;
monitor Sp1Valid;
monitor Sp1Valid1s;
double Sp1ValidTemp;

double Sp2SP;
double Sp2Valid;
double Sp2Valid1s;
assign Sp2SP to "{PriSys}-{SecSys}{PS}I:Sp2-SP.VAL";
assign Sp2Valid to "{PriSys}-{SecSys}{PS}Sp2Valid_.VAL";
assign Sp2Valid1s to "{PriSys}-{SecSys}{PS}Sp2Valid1s_.VAL";
monitor Sp2SP;
monitor Sp2Valid;
monitor Sp2Valid1s;
double Sp2ValidTemp;

/* Monitoed PVs */
/* Rev1.1 Add Reset/release button to first reset the mask, and then release the buffers */
char ReleaseWFBuf;
assign ReleaseWFBuf to "{PriSys}-{SecSys}{PS}Rls-Cmd";
monitor ReleaseWFBuf;

/* Power supply system initilize button. Only init during power supply start. IOC reboot will not cause this sequencer to act. */
char psInit;
assign psInit to "{PriSys}-{SecSys}{PS}psInit-Cmd";
monitor psInit;


char Rmp1;
assign Rmp1 to "{PriSys}-{SecSys}{PS}RpStart1-Cmd";
monitor Rmp1;

char Rmp2;
assign Rmp2 to "{PriSys}-{SecSys}{PS}RpStart2-Cmd";
monitor Rmp2;

int RmpEnd1CNT;
assign RmpEnd1CNT to "{PriSys}-{SecSys}{PS}Sp1Cnt-Cal_";
monitor RmpEnd1CNT;

int RmpEnd1CNTSts;
assign RmpEnd1CNTSts to "{PriSys}-{SecSys}{PS}DAC1Cnt-Sts";
monitor RmpEnd1CNTSts;

int RmpEnd2CNT;
assign RmpEnd2CNT to "{PriSys}-{SecSys}{PS}Sp2Cnt-Cal_";
monitor RmpEnd2CNT;

int RmpEnd2CNTSts;
assign RmpEnd2CNTSts to "{PriSys}-{SecSys}{PS}DAC2Cnt-Sts";
monitor RmpEnd2CNTSts;

char CtctOn;
assign CtctOn to "{PriSys}-{SecSys}{PS}CtctOn-Cmd";
monitor CtctOn;

char OpMode;
assign OpMode to "{PriSys}-{SecSys}{PS}PsOnOff-Sel";
monitor OpMode;

char OpModeSts;
assign OpModeSts to "{PriSys}-{SecSys}{PS}PsOnOff-Sts";

char ResetFault1;
assign ResetFault1 to "{PriSys}-{SecSys}{PS}Rst:Flt1-Cmd";
monitor ResetFault1;

char WFBuf1Stop;
assign WFBuf1Stop to "{PriSys}-{SecSys}{PS}WFBuf1Stop-I";
monitor WFBuf1Stop;

char WFBuf2Stop;
assign WFBuf2Stop to "{PriSys}-{SecSys}{PS}WFBuf2Stop-I";
monitor WFBuf2Stop;

char WFReadTimes;

char WFWaveformRbSem;
assign WFWaveformRbSem to "{PriSys}-{SecSys}{PS}WFRdSem-Cmd";
monitor WFWaveformRbSem;

/* Set PVs */
//SR Rev1.1 

char Buf1Rls; 
assign Buf1Rls to "{PriSys}-{SecSys}{PS}Buf1Rls-Cmd";
char Buf2Rls; 
assign Buf2Rls to "{PriSys}-{SecSys}{PS}Buf2Rls-Cmd";
char Msk28; 
assign Msk28 to "{PriSys}-{SecSys}{PS}DAC1Msk-Cmd";
char Msk27; 
assign Msk27 to "{PriSys}-{SecSys}{PS}DCCT1Msk-Cmd";
char Msk26; 
assign Msk26 to "{PriSys}-{SecSys}{PS}ERR1Msk-Cmd";
char Msk25; 
assign Msk25 to "{PriSys}-{SecSys}{PS}CTRL1Msk-Cmd";
char Msk24; 
assign Msk24 to "{PriSys}-{SecSys}{PS}VOL1Msk-Cmd";
char Msk23; 
assign Msk23 to "{PriSys}-{SecSys}{PS}GND1Msk-Cmd";
char Msk22; 
assign Msk22 to "{PriSys}-{SecSys}{PS}DAC2Msk-Cmd";
char Msk21; 
assign Msk21 to "{PriSys}-{SecSys}{PS}DCCT2Msk-Cmd";
char Msk20; 
assign Msk20 to "{PriSys}-{SecSys}{PS}ERR2Msk-Cmd";
char Msk19; 
assign Msk19 to "{PriSys}-{SecSys}{PS}CTRL2Msk-Cmd";
char Msk18; 
assign Msk18 to "{PriSys}-{SecSys}{PS}VOL2Msk-Cmd";
char Msk17; 
assign Msk17 to "{PriSys}-{SecSys}{PS}GND2Msk-Cmd";
char Msk16; 
assign Msk16 to "{PriSys}-{SecSys}{PS}UserMsk-Cmd";
char Msk15; 
assign Msk15 to "{PriSys}-{SecSys}{PS}Sts15Msk-Cmd";
char Msk14; 
assign Msk14 to "{PriSys}-{SecSys}{PS}Sts14Msk-Cmd";
char Msk13; 
assign Msk13 to "{PriSys}-{SecSys}{PS}Sts13Msk-Cmd";
char Msk12; 
assign Msk12 to "{PriSys}-{SecSys}{PS}Sts12Msk-Cmd";
char Msk11; 
assign Msk11 to "{PriSys}-{SecSys}{PS}Sts11Msk-Cmd";
char Msk10; 
assign Msk10 to "{PriSys}-{SecSys}{PS}Sts10Msk-Cmd";
char Msk9; 
assign Msk9 to "{PriSys}-{SecSys}{PS}Sts9Msk-Cmd";
char Msk8; 
assign Msk8 to "{PriSys}-{SecSys}{PS}Sts8Msk-Cmd";
char Msk7; 
assign Msk7 to "{PriSys}-{SecSys}{PS}Sts7Msk-Cmd";
char Msk6; 
assign Msk6 to "{PriSys}-{SecSys}{PS}Sts6Msk-Cmd";
char Msk5; 
assign Msk5 to "{PriSys}-{SecSys}{PS}Sts5Msk-Cmd";
char Msk4; 
assign Msk4 to "{PriSys}-{SecSys}{PS}Sts4Msk-Cmd";
char Msk3; 
assign Msk3 to "{PriSys}-{SecSys}{PS}Sts3Msk-Cmd";
char Msk2; 
assign Msk2 to "{PriSys}-{SecSys}{PS}Sts2Msk-Cmd";
char Msk1; 
assign Msk1 to "{PriSys}-{SecSys}{PS}Sts1Msk-Cmd";
char Msk0; 
assign Msk0 to "{PriSys}-{SecSys}{PS}Sts0Msk-Cmd";


char ClkSrc;
assign ClkSrc to "{PriSys}-{SecSys}{PS}ClkSrc-Sel";

char ClkDivider;
assign ClkDivider to "{PriSys}-{SecSys}{PS}ClkDiv-SP";

char SysReset;
assign SysReset to "{PriSys}-{SecSys}{PS}Rst:PSC-Cmd";

char PSC_Disable;
assign PSC_Disable to "{PriSys}-{SecSys}{PS}Enbl:PSC-Cmd";


char PSC_Mode;
assign PSC_Mode to "{PriSys}-{SecSys}{PS}PsOpMode";

char CtctOff;
assign CtctOff to "{PriSys}-{SecSys}{PS}CtctOff-Cmd";

char ParkOn1;
assign ParkOn1 to "{PriSys}-{SecSys}{PS}ParkOn1-Cmd";

char ParkOff1;
assign ParkOff1 to "{PriSys}-{SecSys}{PS}ParkOff1-Cmd";

char ParkOn2;
assign ParkOn2 to "{PriSys}-{SecSys}{PS}ParkOn2-Cmd";

char ParkOff2;
assign ParkOff2 to "{PriSys}-{SecSys}{PS}ParkOff2-Cmd";

char ResetInterlock;
assign ResetInterlock to "{PriSys}-{SecSys}{PS}RstFlt-Cmd";

char DoutMode;
assign DoutMode to "{PriSys}-{SecSys}{PS}DoutMode-Sel";

int DoutPulseWidth;
assign DoutPulseWidth to "{PriSys}-{SecSys}{PS}DoPlsWdt-SP";

char WFBufSelect;
assign WFBufSelect to "{PriSys}-{SecSys}{PS}WFBuf-Sel";

char WFBufReadbackStart;
assign WFBufReadbackStart to "{PriSys}-{SecSys}{PS}RbStart-Seq_.PROC";

/* Variables */
char PSState;

/* Rev1.4 add monitor to prevent Delta(cnt) stuck */
int deltaCnt11;
int deltaCnt12;
int deltaCnt21;
int deltaCnt22; 

ss Rmp1_Monitor {
	state Monitor1_Idle {
		when (delay(3)) {
		deltaCnt11=RmpEnd1CNT-RmpEnd1CNTSts;
		} state Monitor1_Read
	}
	state Monitor1_Read {
		when (delay(3)) {
		deltaCnt12=RmpEnd1CNT-RmpEnd1CNTSts;
		} state Monitor1_Check
	}	
	state Monitor1_Check {
		/* If stuck */
		when ((deltaCnt11==deltaCnt12)&&(deltaCnt12>10)) {
		   Rmp1=0;
		   pvPut(Rmp1); 
		   } state Monitor1_SetGo
		when (deltaCnt11!=deltaCnt12) {
		} state Monitor1_Idle
	}
	state Monitor1_SetGo {
		when (delay(2)) {
		   Rmp1=1;
		   pvPut(Rmp1); 		
		} state Monitor1_Idle
	}
}
				
ss Rmp2_Monitor {
	state Monitor2_Idle {
		when (delay(3)) {
		deltaCnt21=RmpEnd2CNT-RmpEnd2CNTSts;
		} state Monitor2_Read
	}
	state Monitor2_Read {
		when (delay(3)) {
		deltaCnt22=RmpEnd2CNT-RmpEnd2CNTSts;
		} state Monitor2_Check
	}	
	state Monitor2_Check {
		/* If stuck */
		when ((deltaCnt21==deltaCnt22)&&(deltaCnt22>10)) {
		   Rmp2=0;
		   pvPut(Rmp2); 
		   } state Monitor2_SetGo
		when (deltaCnt21!=deltaCnt22) {
		} state Monitor2_Idle
	}
	state Monitor2_SetGo {
		when (delay(2)) {
		   Rmp2=1;
		   pvPut(Rmp2); 		
		} state Monitor2_Idle
	}
}



/*Rev1.2 Compare Sp1Valid_, Sp1Valid1s_ */
ss Rmp1_Operation {
	/* 1st stage: wait for a stable setpoint */
	state Sp1Stable_INIT {
		when (delay(5)) {
		Sp1ValidTemp=Sp1SP;		
		Sp1Valid=Sp1SP;		
		pvPut(Sp1Valid);
	/* Rev1.4: Guard unipolar small setpoint */
		if((Polarity==1)&&(Sp1SP<0))
		Sp1Valid1s=0;
		else
		Sp1Valid1s=Sp1SP;		
		pvPut(Sp1Valid1s);
	        Rmp1=0;
		pvPut(Rmp1);			
		} state Sp1StableIdle
	}
	state Sp1StableIdle {
	/* New setpoing. Or during IOC reboot, the PSI has differnet values (for example, just turn on) */
		when (Sp1Valid!=Sp1ValidTemp) {
		Sp1ValidTemp=Sp1Valid;
		} state Sp1StableDly1Sec
		when ((Rmp1==0)&&(abs(RmpEnd1CNTSts-RmpEnd1CNT) > 8)) {
  	        Rmp1=1;
		pvPut(Rmp1);			
		} state Rmp1_DELAY	
	}
	state Sp1StableDly1Sec {
		when (delay(1.0)) {
		} state Sp1StableCheck
	}
	state Sp1StableCheck {
		when ((Sp1Valid==Sp1ValidTemp)&&(Rmp1==0)) {
	/* Rev1.4 * Guard unipolar small setpoing */
		if((Polarity==1)&&(Sp1Valid<0))
		Sp1Valid1s=0;
		else
		Sp1Valid1s=Sp1Valid;
		pvPut(Sp1Valid1s);
		} state Rmp1_CheckEnd
		when (Sp1Valid!=Sp1ValidTemp) {
		Sp1ValidTemp=Sp1Valid;
		} state Sp1StableDly1Sec
	}
	/* 2nd stage: check the new setpoint and ramp */
	state Rmp1_CheckEnd {
		//when ((Rmp1==1)||((Rmp1==0)&&(abs(RmpEnd1CNTSts-RmpEnd1CNT) > 8))) {
		//when ((Rmp1==1)||((Rmp1==0)&&(abs(RmpEnd1CNTSts-RmpEnd1CNT) > 0))) {
		when (delay(0.1)) {
		    Rmp1=1;
		    pvPut(Rmp1);			
		} state Rmp1_DELAY	
	}
	state Rmp1_DELAY {
		when (delay(0.5)) {
		} state Rmp1_END
	}
	state Rmp1_END {
		when (abs(RmpEnd1CNTSts-RmpEnd1CNT) < 8) {
		Rmp1 = 0;
		pvPut(Rmp1);
		} state Rmp1_DONE

	}
	state Rmp1_DONE {
		when (delay(0.5)) {
		} state Sp1StableIdle
	}
}

ss Rmp2_Operation {
	/* 1st stage: wait for a stable setpoint */
	state Sp2Stable_INIT {
		when (delay(5)) {
		Sp2ValidTemp=Sp2SP;		
		Sp2Valid=Sp2SP;		
		pvPut(Sp2Valid);
		if((Polarity==1)&&(Sp2SP<0))
		Sp2Valid1s=0;
		else
		Sp2Valid1s=Sp2SP;		
		pvPut(Sp2Valid1s);
	        Rmp2=0;
		pvPut(Rmp2);			
		} state Sp2StableIdle
	}
	state Sp2StableIdle {
		when (Sp2Valid!=Sp2ValidTemp) {
		Sp2ValidTemp=Sp2Valid;
		} state Sp2StableDly1Sec
		when ((Rmp2==0)&&(abs(RmpEnd2CNTSts-RmpEnd2CNT) > 8)) {
 	        Rmp2=1;
		pvPut(Rmp2);			
		} state Rmp2_DELAY	
	}
	state Sp2StableDly1Sec {
		when (delay(1.0)) {
		} state Sp2StableCheck
	}
	state Sp2StableCheck {
		when ((Sp2Valid==Sp2ValidTemp)&&(Rmp2==0)) {
		/* Rev1.4 Guard small unipolar small nagtive setpoint */
		if((Polarity==1)&&(Sp2Valid<0))
		Sp2Valid1s=0;
		else
		Sp2Valid1s=Sp2Valid;
		pvPut(Sp2Valid1s);
		} state Rmp2_CheckEnd
		when (Sp2Valid!=Sp2ValidTemp) {
		Sp2ValidTemp=Sp2Valid;
		} state Sp2StableDly1Sec
	}
	/* 2nd stage: check the new setpoint and ramp */
	state Rmp2_CheckEnd {
		//when ((Rmp2==1)||((Rmp2==0)&&(abs(RmpEnd2CNTSts-RmpEnd2CNT) > 8))) {
		//when ((Rmp2==1)||((Rmp2==0)&&(abs(RmpEnd2CNTSts-RmpEnd2CNT) > 0))) {
		when (delay(0.1)) {
		    Rmp2=1;
		    pvPut(Rmp2);			
		} state Rmp2_DELAY	
	}
	state Rmp2_DELAY {
		when (delay(0.5)) {
		} state Rmp2_END
	}
	state Rmp2_END {
		when (abs(RmpEnd2CNTSts-RmpEnd2CNT) < 8) {
		Rmp2 = 0;
		pvPut(Rmp2);
		} state Rmp2_DONE

	}
	state Rmp2_DONE {
		when (delay(0.5)) {
		} state Sp2StableIdle
	}
}

ss WFBufRelease {
	state WFRelase_INIT {
		when ((ReleaseWFBuf==1)) {
		} state WFDisableMasks
	}
	state WFDisableMasks {
		when (delay(0.5)) {
		Msk0=0;
		pvPut(Msk0);
		Msk1=0;
		pvPut(Msk1);
		Msk2=0;
		pvPut(Msk2);
		Msk3=0;
		pvPut(Msk3);
		Msk4=0;
		pvPut(Msk4);
		Msk5=0;
		pvPut(Msk5);
		Msk6=0;
		pvPut(Msk6);
		Msk7=0;
		pvPut(Msk7);
		Msk8=0;
		pvPut(Msk8);
		Msk9=0;
		pvPut(Msk9);
		Msk10=0;
		pvPut(Msk10);
		Msk11=0;
		pvPut(Msk11);
		Msk12=0;
		pvPut(Msk12);
		Msk13=0;
		pvPut(Msk13);
		Msk14=0;
		pvPut(Msk14);
		Msk15=0;
		pvPut(Msk15);
		Msk16=0;
		pvPut(Msk16);
		Msk17=0;
		pvPut(Msk17);
		Msk18=0;
		pvPut(Msk18);
		Msk19=0;
		pvPut(Msk19);
		Msk20=0;
		pvPut(Msk20);
		Msk21=0;
		pvPut(Msk21);
		Msk22=0;
		pvPut(Msk22);
		Msk23=0;
		pvPut(Msk23);
		Msk24=0;
		pvPut(Msk24);
		Msk25=0;
		pvPut(Msk25);
		Msk26=0;
		pvPut(Msk26);
		Msk27=0;
		pvPut(Msk27);
		Msk28=0;
		pvPut(Msk28);		
		} state WFRleaseBuffers
	}
	state WFRleaseBuffers {
		when (delay(2)) {
		Buf1Rls=1;
		pvPut(Buf1Rls);
		Buf2Rls=1;
		pvPut(Buf2Rls);		
		} state WFRelase_DELAY
	}
	state WFRelase_DELAY {
		when (delay(2)) {
		Buf1Rls=0;
		pvPut(Buf1Rls);
		Buf2Rls=0;
		pvPut(Buf2Rls);		
		} state WFRelase_DELAY2
	}
	state WFRelase_DELAY2 {
		when (delay(6)) {
		ReleaseWFBuf=0;
		pvPut(ReleaseWFBuf);
		} state WFRelase_INIT
	}
}


/* Sequencer 3: PS mode change */
ss Ps1Operation {
	/* No action during IOC reboot -- bumpless reboot */
	state Ps1_INIT {
		when(delay(2.0)) {
		if(CtctOn==1)
		OpMode=1;
		if(CtctOn==0)
		OpMode=0;
		PSState=OpMode;
		} state OP_IDLE
	}
	state OP_IDLE {
		/* mode change between ON and OFF */
		when (OpMode!=PSState) {
		OpModeSts=1;
		pvPut(OpModeSts);
		PSState=OpMode;
		} state OP_RAMP_START
	}
	state OP_RAMP_START {
		when (delay(0.1)) {
		/* If mode change, the first thing is to ramping down */
		Sp1SP=0.0;
		pvPut(Sp1SP);
		Sp2SP=0.0;
		pvPut(Sp2SP);
		} state OP_RAMP_DELAY1
	}
	state OP_RAMP_DELAY1 {
		when (delay(2.0)) {
		} state OP_RAMP_DELAY2
	}
	state OP_RAMP_DELAY2 {
                /* Rmp Down finished or time out */
		when ((Rmp1==0)||delay(200)) {		
		} state OP_RAMP_DELAY3
	}
        state OP_RAMP_DELAY3 {
                when (delay(0.1)) {
                    ResetInterlock = 0;
                    pvPut(ResetInterlock); 
                } state OP_RAMP_DONE
        }
        state OP_RAMP_DONE {
                when (delay (0.5)) {
                Rmp1=0;
                pvPut(Rmp1);
                Rmp2=0;
                pvPut(Rmp2);
                } state OP_RESET_FAULT 
        }
        state OP_RESET_FAULT {
                when (delay(0.1)) {
                /* if go to ON: reset the fault */
                if(OpMode==1) {
                    ResetInterlock = 1;
                    pvPut(ResetInterlock); }
                } state OP_PARK
        }
        state OP_PARK {
                when (delay(2)) {
			ParkOn1 = 1;	
                        pvPut(ParkOn1);
		        ParkOn2 = 1;
                        pvPut(ParkOn2);
			ParkOff1 = 0;	
                        pvPut(ParkOff1);
		        ParkOff2 = 0;
                        pvPut(ParkOff2); 
                } state OP_CONTACT
        }
        state OP_CONTACT {
                when (delay(2)) {
                /* go to on */
                if(OpMode==1) {
			CtctOn = 1;	
		        pvPut(CtctOn);  
			CtctOff = 0;	
		        pvPut(CtctOff); }  
                if(OpMode==0) {
			CtctOn = 0;	
		        pvPut(CtctOn);  
			CtctOff = 1;	
		        pvPut(CtctOff); }  
		} state OP_PARK2
	}
        state OP_PARK2 {
		/* if turn on, keep park off */
                when (delay(4.5)) {
			if(OpMode==1) {
			ParkOn1 = 0;	
                        pvPut(ParkOn1);
		        ParkOn2 = 0;
                        pvPut(ParkOn2); 
			ParkOff1 = 1;	
                        pvPut(ParkOff1);
		        ParkOff2 = 1;
                        pvPut(ParkOff2); }
                } state OP_END
        }
	state OP_END {
		when (delay(2)) {
		OpModeSts=0;
		pvPut(OpModeSts);
		} state OP_IDLE
	}
}



/* statemachine for WF Buf1 waveform readback */
ss WFMonitor1 {
    state WF_IDLE1 {
        when (WFBuf1Stop == 1) {
	} state WF_TRY_SEM1_DELAY
    }
    state WF_TRY_SEM1_DELAY {
        when(delay(1.0)) {
        } state WF_TRY_SEM1
    }
    state WF_TRY_SEM1 {	
        when (WFWaveformRbSem == 1)  {
        } state WF_IDLE1
        when (WFWaveformRbSem == 0)  {
                WFWaveformRbSem = 1;
                pvPut(WFWaveformRbSem);
		printf("\n\r Got semophone for Buf1.");
                WFReadTimes = 0;
                WFBufSelect = 0;
                pvPut(WFBufSelect);
        } state WF_READBACK_START_DELAY1
    }
    state WF_READBACK_START_DELAY1 {
        when(delay(1.0)) {
        } state WF_READBACK_START1
    }
    state WF_READBACK_START1 {
         when (1) {
            WFBufReadbackStart=1;
            printf("\n\r WF Buf1 readback start.\n\r");
            pvPut(WFBufReadbackStart);
            WFReadTimes = WFReadTimes + 1;
        } state WF_READING1
    }
    state WF_READING1 {
        when(delay(8.0)) {
        } state WF_READBACK_END1_CHECKING
    }

    state WF_READBACK_END1_CHECKING {
        when(WFReadTimes == 1) {
        } state WF_READBACK_END1
        when(WFReadTimes < 2) {
        } state WF_READBACK_START_DELAY1
    }
    state WF_READBACK_END1 {
        when (1) {
                WFWaveformRbSem = 0;   //release semiphore
                printf("\n\r WF Buf1 release semohone.\n\r");
                pvPut(WFWaveformRbSem);
        } state WF_WAIT1
    }
   state WF_WAIT1 {
        when(WFBuf1Stop == 0) {
        } state WF_IDLE1
    }
}


/* Sequencer 5: WF Monitor: only monitor WFBuf2Stop */
ss WFMonitor2 {
    state WF_IDLE2 {
        when (WFBuf2Stop == 1) {
	} state WF_TRY_SEM2_DELAY
    }
    state WF_TRY_SEM2_DELAY {
        when(delay(1.0)) {
        } state WF_TRY_SEM2
    }
    state WF_TRY_SEM2 {	
        when (WFWaveformRbSem == 1)  {
        } state WF_IDLE2
        when (WFWaveformRbSem == 0)  {
                WFWaveformRbSem = 1;
                pvPut(WFWaveformRbSem);
		printf("\n\r Got semophone for Buf2.");
                WFReadTimes = 0;
                WFBufSelect = 1;
                pvPut(WFBufSelect);
        } state WF_READBACK_START_DELAY2
    }
    state WF_READBACK_START_DELAY2 {
        when(delay(1.0)) {
        } state WF_READBACK_START2
    }
    state WF_READBACK_START2 {
         when (1) {
            WFBufReadbackStart=1;
          pvPut(WFBufReadbackStart);
            printf("\n\r WF Buf2 readback start.\n\r");
            WFReadTimes = WFReadTimes + 1;
        } state WF_READING2
    }
    state WF_READING2 {
        when(delay(8.0)) {
        } state WF_READBACK_END2_CHECKING
    }

    state WF_READBACK_END2_CHECKING {
        when(WFReadTimes == 1) {
        } state WF_READBACK_END2
        when(WFReadTimes < 2) {
        } state WF_READBACK_START_DELAY2
    }
    state WF_READBACK_END2 {
        when (1) {
                WFWaveformRbSem = 0;   //release semiphore
                pvPut(WFWaveformRbSem);
                printf("\n\r WF Buf2 release semophone.\n\r");
        } state WF_WAIT2
    }
    state WF_WAIT2 {
        when(WFBuf2Stop == 0) {
        } state WF_IDLE2
    }
}

/* Sequencer 6: Initiliazation: straight forward. No PV monitor */
ss InitProcess {
	state PS_IDLE {
		when(psInit==1) {
		} state PSC_INIT_Setup1		
	}
	state PSC_INIT_Setup1 {
		when (delay(1.0)) {
		Rmp1=0;
		pvPut(Rmp1);
		Rmp2=0;
		pvPut(Rmp2);

		SysReset=0;
	        pvPut(SysReset);
		PSC_Mode=0;
	        pvPut(PSC_Mode);
		} state PSC_INIT_Setup2
	}
	state PSC_INIT_Setup2 {
		when (delay(5.0)) {
		PSC_Disable=0;
	        pvPut(PSC_Disable);		
		} state PSC_INIT_Setup4
	}
	state PSC_INIT_Setup4 {
		when (delay(2.0)) {
		SysReset=1;
	        pvPut(SysReset);
		} state PSC_INIT_Setup5
	}
	state PSC_INIT_Setup5 {
		when (delay(2.0)) {
		DoutMode =1;
	        pvPut(DoutMode);  
		DoutPulseWidth=100;
	        pvPut(DoutPulseWidth);  
		ClkSrc=0;
	        pvPut(ClkSrc);  
		ClkDivider=0;
	        pvPut(ClkDivider);  
		} state Regulator_INIT_Setup1
	}
	state Regulator_INIT_Setup1 {
		when (delay(1.0)) {
		ParkOn1 = 1;	
	        pvPut(ParkOn1);  
		ParkOn2 = 1;	
	        pvPut(ParkOn2);  
		} state Regulator_INIT_Setup2
	
	}
	state Regulator_INIT_Setup2 {
		when (delay(1.0)) {
		ResetInterlock = 1;	
	        pvPut(ResetInterlock);  
		} state Regulator_INIT_Setup3
	}
	state Regulator_INIT_Setup3 {
		when (delay(1.0)) {
		CtctOn = 0;	
	        pvPut(CtctOn);  
		} state Regulator_INIT_Setup4
	}
	state Regulator_INIT_Setup4 {
		when (delay(1.0)) {
		ResetInterlock = 0;	
	        pvPut(ResetInterlock);  
	        pvPut(ResetFault1);  
		PSC_Mode=4;
	        pvPut(PSC_Mode);
		PSC_Disable=1;
	        pvPut(PSC_Disable);		
		} state INIT_DONE
	}
	state INIT_DONE {
		when(delay(1.0)) {
		} state PS_IDLE	
	}
}
