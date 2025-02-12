import time
import epics

timeout = 30  # Set timeout to 30 seconds
start_time = time.time()  # Record the start time


mode_executed_ch1_off = False  # Flag to check if the mode was executed
mode_executed_ch1_on = False  # Flag to check if the mode was executed

mode_executed_ch2_off = False  # Flag to check if the mode was executed
mode_executed_ch2_on = False  # Flag to check if the mode was executed

mode_executed_ch3_off = False  # Flag to check if the mode was executed
mode_executed_ch3_on = False  # Flag to check if the mode was executed

mode_executed_ch4_off = False  # Flag to check if the mode was executed
mode_executed_ch4_on = False  # Flag to check if the mode was executed


######################################################################################
#Channel 1 -On to Off
######################################################################################
while True:
    on_cmd_ch1 = epics.caget('ZPSC:SQK{PSC1:Chan1}On-Cmd')
    
    if on_cmd_ch1 == 0 and not mode_executed_ch1_off:
        epics.caput('ZPSC:SQK{PSC1}Chan1:On1-Cmd', 0, wait=True)
        time.sleep(1)
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan1}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan1}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch1_off = True  # Set the flag so the code only runs once
        
        while True:
            dac_value_ch1 = epics.caget('ZPSC:SQK{PSC1}Chan1-DAC-SP')

            if dac_value_ch1 is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value_ch1 < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan1:Park-Cmd', 1, wait=True)
                break  # Exit the inner while loop since the DAC value is low enough
                
    # Check for ZPSC:SQK{PSC1}Chan1:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd_ch1 == 1:
        mode_executed_ch1_off = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage

######################################################################################                
#Channel 1 -Off to On
######################################################################################
    on_cmd = epics.caget('ZPSC:SQK{PSC1:Chan1}On-Cmd')
    
    if on_cmd == 1 and not mode_executed_ch1_on:
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan1}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan1}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch1_on = True  # Set the flag so the code only runs once
        
        while True:
            dac_value = epics.caget('ZPSC:SQK{PSC1}Chan1-DAC-SP')

            if dac_value is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan1:Park-Cmd', 1, wait=True)
                print("Clear Faults")
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan12-sp', -1, wait=True)
                time.sleep(5)  # Wait for the system to update the channel
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan12-sp', 0, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan1:On1-Cmd', 1, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan1:Park-Cmd', 0, wait=True)
                time.sleep(3)
                print("Ready for operator to take control")
                break  # Exit the inner while loop since the DAC value is low enough
            
    # Check for ZPSC:SQK{PSC1}Chan1:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd == 0:
        mode_executed_ch1_on = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage   
    
######################################################################################
#Channel 2 -On to Off
######################################################################################
    on_cmd_ch2 = epics.caget('ZPSC:SQK{PSC1:Chan2}On-Cmd')
    
    if on_cmd_ch2 == 0 and not mode_executed_ch2_off:
        epics.caput('ZPSC:SQK{PSC1}Chan2:On1-Cmd', 0, wait=True)
        time.sleep(1)
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan2}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan2}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch2_off = True  # Set the flag so the code only runs once
        
        while True:
            dac_value_ch2 = epics.caget('ZPSC:SQK{PSC1}Chan2-DAC-SP')

            if dac_value_ch2 is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value_ch2 < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan2:Park-Cmd', 1, wait=True)
                break  # Exit the inner while loop since the DAC value is low enough
                
    # Check for ZPSC:SQK{PSC1}Chan2:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd_ch2 == 1:
        mode_executed_ch2_off = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage

######################################################################################                
#Channel 2 -Off to On
######################################################################################
    on_cmd = epics.caget('ZPSC:SQK{PSC1:Chan2}On-Cmd')
    
    if on_cmd == 1 and not mode_executed_ch2_on:
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan2}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan2}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch2_on = True  # Set the flag so the code only runs once
        
        while True:
            dac_value = epics.caget('ZPSC:SQK{PSC1}Chan2-DAC-SP')

            if dac_value is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan2:Park-Cmd', 1, wait=True)
                print("Clear Faults")
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan12-sp', -1, wait=True)
                time.sleep(5)  # Wait for the system to update the channel
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan12-sp', 0, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan2:On1-Cmd', 1, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan2:Park-Cmd', 0, wait=True)
                print("Ready for operator to take control")
                break  # Exit the inner while loop since the DAC value is low enough
            
    # Check for ZPSC:SQK{PSC1}Chan2:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd == 0:
        mode_executed_ch2_on = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage   

######################################################################################
#Channel 3 -On to Off
######################################################################################
    on_cmd_ch3 = epics.caget('ZPSC:SQK{PSC1:Chan3}On-Cmd')
    
    if on_cmd_ch3 == 0 and not mode_executed_ch3_off:
        epics.caput('ZPSC:SQK{PSC1}Chan3:On1-Cmd', 0, wait=True)
        time.sleep(1)
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan3}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan3}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch3_off = True  # Set the flag so the code only runs once
        
        while True:
            dac_value_ch3 = epics.caget('ZPSC:SQK{PSC1}Chan3-DAC-SP')

            if dac_value_ch3 is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value_ch3 < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan3:Park-Cmd', 1, wait=True)
                break  # Exit the inner while loop since the DAC value is low enough
                
    # Check for ZPSC:SQK{PSC1}Chan3:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd_ch3 == 1:
        mode_executed_ch3_off = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage

######################################################################################                
#Channel 3 -Off to On
######################################################################################
    on_cmd = epics.caget('ZPSC:SQK{PSC1:Chan3}On-Cmd')
    
    if on_cmd == 1 and not mode_executed_ch3_on:
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan3}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan3}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch3_on = True  # Set the flag so the code only runs once
        
        while True:
            dac_value = epics.caget('ZPSC:SQK{PSC1}Chan3-DAC-SP')

            if dac_value is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan3:Park-Cmd', 1, wait=True)
                print("Clear Faults")
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan34-sp', -1, wait=True)
                time.sleep(5)  # Wait for the system to update the channel
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan34-sp', 0, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan3:On1-Cmd', 1, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan3:Park-Cmd', 0, wait=True)
                print("Ready for operator to take control")
                break  # Exit the inner while loop since the DAC value is low enough
            
    # Check for ZPSC:SQK{PSC1}Chan3:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd == 0:
        mode_executed_ch3_on = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage     
    
######################################################################################
#Channel 4-On to Off
######################################################################################
    on_cmd_ch4 = epics.caget('ZPSC:SQK{PSC1:Chan4}On-Cmd')
    
    if on_cmd_ch4 == 0 and not mode_executed_ch4_off:
        epics.caput('ZPSC:SQK{PSC1}Chan4:On1-Cmd', 0, wait=True)
        time.sleep(1)
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan4}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan4}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch4_off = True  # Set the flag so the code only runs once
        
        while True:
            dac_value_ch4 = epics.caget('ZPSC:SQK{PSC1}Chan4-DAC-SP')

            if dac_value_ch4 is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value_ch4 < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan4:Park-Cmd', 1, wait=True)
                break  # Exit the inner while loop since the DAC value is low enough
                
    # Check for ZPSC:SQK{PSC1}Chan4:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd_ch4 == 1:
        mode_executed_ch4_off = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage
    
######################################################################################    
#Channel 4 -Off to On
######################################################################################
    on_cmd = epics.caget('ZPSC:SQK{PSC1:Chan4}On-Cmd')
    
    if on_cmd == 1 and not mode_executed_ch4_on:
        print('Smooth Ramp Mode')
        # Set to Smooth Ramp Mode (Mode 0)
        epics.caput('ZPSC:SQK{PSC1:Chan4}Mode-cmd', 0, wait=True)
        time.sleep(1)

        # Set DAC to 0
        print('Ramp DAC to 0')
        epics.caput('ZPSC:SQK{PSC1:Chan4}I-sp', 0, wait=True)

        # Start tracking DAC value
        mode_executed_ch4_on = True  # Set the flag so the code only runs once
        
        while True:
            dac_value = epics.caget('ZPSC:SQK{PSC1}Chan4-DAC-SP')

            if dac_value is None:
                print("Warning: DAC value is None. Retrying...")
                time.sleep(1)  # Wait for the system to update the channel
                continue

            if dac_value < 0.2:
                print("DAC value is low enough, parking power supply.")
                epics.caput('ZPSC:SQK{PSC1}Chan4:Park-Cmd', 1, wait=True)
                print("Clear Faults")
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan34-sp', -1, wait=True)
                time.sleep(5)  # Wait for the system to update the channel
                epics.caput('ZPSC:SQK{PSC1:Chan0}FltClearChan34-sp', 0, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan4:On1-Cmd', 1, wait=True)
                time.sleep(3)
                epics.caput('ZPSC:SQK{PSC1}Chan4:Park-Cmd', 0, wait=True)
                print("Ready for operator to take control")
                break  # Exit the inner while loop since the DAC value is low enough
            
    # Check for ZPSC:SQK{PSC1}Chan4:On1-Cmd = 1 to reset the mode_executed flag
    if on_cmd == 0:
        mode_executed_ch4_on = False  # Reset the flag when On1-Cmd = 1

    time.sleep(1)  # Sleep to avoid tight looping and excessive CPU usage     
