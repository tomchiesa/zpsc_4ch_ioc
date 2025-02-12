import epics
import struct
import time
import subprocess  # Import subprocess module

def float_to_int32(f):
    """Convert a float to its IEEE 754 32-bit integer representation."""
    # Convert float to 4-byte binary using struct
    packed = struct.pack('!f', f)  # Big-endian format for 32-bit float
    # Unpack the packed bytes as a 32-bit integer
    return struct.unpack('!I', packed)[0]  # '!I' means unsigned 32-bit integer

def read_pvs_from_file(filename):
    """Reads the PVs and values from a file."""
    pv_list = []
    with open(filename, 'r') as file:
        for line in file:
            # Skip empty lines and strip trailing whitespace
            line = line.strip()
            if line:
                pv_name,value2,value3,value4 = line.split(',')
                value2 = float(value2.strip())
                value3 = float(value3.strip())
                value4 = float(value4.strip())
                # Convert to Counts
                new_value = (value2 * value3)/value4
                pv_list.append((pv_name.strip(), new_value))
    return pv_list

def main():
    # File containing PVs and values in the format "pv_name,value2,value3"
    filename = 'cal_pv_list.txt'  # Replace with your actual filename

    # Read PV names and values from the file
    pv_values = read_pvs_from_file(filename)

    # Convert each float value to a 32-bit integer and write it to the PV
    for pv_name, float_value in pv_values:
        # Convert the float to its 32-bit integer representation
        int_value = float_to_int32(float_value)
        # Perform a caput (write the 32-bit integer value to the PV)
        epics.caput(pv_name, int_value)
        # Print the results
        print(f"{pv_name} -> Calculated Value: {float_value} -> 32-bit Integer: {int_value} -> caput executed")
        
    epics.caput("SR:C04-MG{zPSC1:Chan0}write_cal_data", 0) 
    print("write_cal_data -> caput executed -> 0")
    print("Waiting 6 seconds")
    time.sleep(6)
    epics.caput("SR:C04-MG{zPSC1:Chan0}write_cal_data", 1) 
    print("write_cal_data -> caput executed -> 1")
    print("Done")


    print("Waiting 8 seconds for memory to update in ARM")
    time.sleep(8)
    # After completing all tasks, execute readbacks.py
    subprocess.run(['python3', 'readbacks.py'])  # Run the readbacks.py script
    
    print("Rerun")
    time.sleep(2)
    # After completing all tasks, execute readbacks.py
    subprocess.run(['python3', 'readbacks.py'])  # Run the readbacks.py script
    
    print("Rerun")
    time.sleep(2)
    # After completing all tasks, execute readbacks.py
    subprocess.run(['python3', 'readbacks.py'])  # Run the readbacks.py script
    
    print("Program Complete")
    
    print("readbacks.py has been executed.")

if __name__ == "__main__":
    main()

