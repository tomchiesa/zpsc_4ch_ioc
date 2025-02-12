/* Sequencer to control the on-demond record process: ramping table download, power supply mode change, and watch funciton upload */

#define PRINTF seqLog

program ch2_fsm ("M0=SR:C04-MG{zPSC1}Chan2,M1=SR:C04-MG{zPSC1:Chan2}, M2=SR:C04-MG{zPSC1}")

/* options */
option  +r;
option  -c; 

/*Write Only PV's*/
short Park; assign Park to "{M0}:Park-Cmd"; monitor Park;
short on_cmd; assign on_cmd to "{M1}On-Cmd"; monitor on_cmd;
short ch2_dac_setpoint; assign ch2_dac_setpoint to "{M1}I-sp"; monitor ch2_dac_setpoint;  
short on1_cmd; assign on1_cmd to "{M0}:On1-Cmd"; monitor on1_cmd;
short ch2_clr_flts; assign ch2_clr_flts to "{M2}FltClearChan2-bo"; monitor ch2_clr_flts; 
short ch2_mode; assign ch2_mode to "{M1}Mode-cmd"; monitor ch2_mode; 
short ch2_ps_on_off_sts; assign ch2_ps_on_off_sts to "{M0}:PsOnOff-Sts"; monitor ch2_ps_on_off_sts; 

/*Read Only PV's*/
short ch2_dac_rdbck; assign ch2_dac_rdbck to "{M0}-DAC-SP"; monitor ch2_dac_rdbck; 
short ch2_ps_sts; assign ch2_ps_sts to "{M0}:Status0"; monitor ch2_ps_sts; 

/* stringout to display status or progress. */
string Chan2_seq_messages;  assign Chan2_seq_messages to "Chan2_seq_messages";

ss OFF_ON_FSM {
	state INIT {
		when(){
		   Park =1; 
		   pvPut(Park);
		   on1_cmd = 0; 
		   pvPut(on1_cmd); 
		   ch2_mode = 0; 
		   pvPut(ch2_mode); 
		   sprintf(Chan2_seq_messages, "PS OFF");
        	   pvPut(Chan2_seq_messages);
        	   ch2_ps_on_off_sts = 1; 
		   pvPut(ch2_ps_on_off_sts); 
		  } state IDLE
	} 
	state IDLE {
		when (on_cmd==1) {
			Park = 1; 
			pvPut(Park);
			ch2_ps_on_off_sts = 0; 
			pvPut(ch2_ps_on_off_sts); 
			sprintf(Chan2_seq_messages, "Zero DAC");
        	   	pvPut(Chan2_seq_messages);
        	   	ch2_dac_setpoint =0.0; 
        	   	pvPut(ch2_dac_setpoint); 
		} state WAIT_FOR_DAC_CHANGE_ON
			
	}
	state WAIT_FOR_DAC_CHANGE_ON {
		when (delay(3)) {
		} state SET_DAC_TO_ZERO_ON
	}
	state SET_DAC_TO_ZERO_ON {
		when ((ch2_dac_rdbck < 0.01) && (ch2_dac_rdbck > -0.01)) {
			sprintf(Chan2_seq_messages, "Zero DAC");
			pvPut(Chan2_seq_messages);  
			ch2_dac_setpoint =0.000; 
        	   	pvPut(ch2_dac_setpoint); 						
		} state POWER_ON
	}
	state POWER_ON {
		when (delay(4)) {
			Park = 1; 
			pvPut(Park); 
		        ch2_mode = 0; 
        	   	pvPut(ch2_mode); 
			sprintf(Chan2_seq_messages, "Pwr ON");
			pvPut(Chan2_seq_messages); 
			on1_cmd = 1; 
			pvPut(on1_cmd); 						
		} state CLEAR_FAULTS
	}
	state CLEAR_FAULTS {
		when (delay(2)) {
			sprintf(Chan2_seq_messages, "Clr Faults");
			pvPut(Chan2_seq_messages); 
			ch2_clr_flts = 1; 
			pvPut(ch2_clr_flts); 						
		} state WAIT_TO_CLEAR
	}
	state WAIT_TO_CLEAR {
		when (delay(5)) {
			sprintf(Chan2_seq_messages, "Clearing");
			pvPut(Chan2_seq_messages); 
			ch2_clr_flts = 0; 
			pvPut(ch2_clr_flts); 						
		} state PARK_OFF
	}			
	state PARK_OFF {
		when (delay(5)) {
			sprintf(Chan2_seq_messages, "Park OFF");
			pvPut(Chan2_seq_messages); 
			Park = 0; 
			pvPut(Park); 						
		} state DONE_CHECK
	}
	state DONE_CHECK{
		when (ch2_ps_sts == 0) {
			sprintf(Chan2_seq_messages, "FAULTED");
			pvPut(Chan2_seq_messages); 	
			ch2_ps_on_off_sts = 1;	
			pvPut(ch2_ps_on_off_sts); 				
		} state RETRY_ON
		when (ch2_ps_sts == 1) {				
		} state DONE
	}
	state RETRY_ON {
		when (on_cmd==0) {
			Park = 1; 
			ch2_ps_on_off_sts = 1; 
			pvPut(ch2_ps_on_off_sts); 
			sprintf(Chan2_seq_messages, "Try Again");
        	   	pvPut(Chan2_seq_messages);
		} state IDLE
	}
	state DONE {
		when (delay(1)) {
			sprintf(Chan2_seq_messages, "PS Ready");
			pvPut(Chan2_seq_messages); 	
			ch2_ps_on_off_sts = 1;	
			pvPut(ch2_ps_on_off_sts); 				
		} state READY
	}
	state READY {
		when (on_cmd==0) {
			Park = 1; 
			sprintf(Chan2_seq_messages, "Zero DAC");
        	   	pvPut(Chan2_seq_messages);
        	   	ch2_dac_setpoint =0.00; 
        	   	pvPut(ch2_dac_setpoint); 
        	   	ch2_ps_on_off_sts = 0;
        	   	pvPut(ch2_ps_on_off_sts); 
		} state SET_DAC_TO_ZERO_OFF
		when(on_cmd==1) {
			sprintf(Chan2_seq_messages, " PS Ready");
        	   	pvPut(Chan2_seq_messages);
		} state READY
			
	}
	state SET_DAC_TO_ZERO_OFF {
		when ((ch2_dac_rdbck < 0.01) && (ch2_dac_rdbck > -0.01)) {
			sprintf(Chan2_seq_messages, "Pls Wait");
			pvPut(Chan2_seq_messages);  						
		} state POWER_OFF
	}
	state POWER_OFF {
		when (delay(5)) {
			sprintf(Chan2_seq_messages, "Pwr OFF");
			pvPut(Chan2_seq_messages); 
			on1_cmd = 0; 
			pvPut(on1_cmd); 	
			Park = 0; 
			pvPut(Park); 					
		} state COMPLETE
	}
	state COMPLETE {
		when (delay(1)) {
			sprintf(Chan2_seq_messages, "Pwr OFF");
			pvPut(Chan2_seq_messages); 
			ch2_ps_on_off_sts = 1;
			pvPut(ch2_ps_on_off_sts); 
					
		} state INIT
	}
}
