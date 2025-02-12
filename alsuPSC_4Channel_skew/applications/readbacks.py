import epics
import struct
import os

# Function to read PVs from a file using relative path
def read_pvs_from_file(file_path):
    pvs = []
    with open(file_path, 'r') as file:
        for line in file:
            # Skip empty lines and strip trailing whitespace
            line = line.strip()
            if line:
                pv_name, value2, value3, value4 = line.split(',')
                value2 = float(value2.strip())
                value3 = float(value3.strip())
                value4 = float(value4.strip())
                # Convert Counts back to voltage or current
                new_value = (value4) / (value3)

                pvs.append((pv_name.strip(), new_value))
    return pvs

# Function to process each PV
def process_pv(pv_name):

    # Create the new PV name by appending '_in' to the original name
    pv_name = pv_name + "_in"
    
    # Connect to the PV and read its value
    pv = epics.PV(pv_name)

    # Get the value of the PV
    gain_value = pv.get()

    # Check if the value is an integer (which represents IEEE 754 encoded float)
    if isinstance(gain_value, int):
        # Mask the integer to ensure it's within the 32-bit range
        gain_value_32bit = gain_value & 0xFFFFFFFF  # Masking to 32-bit unsigned

        if gain_value_32bit >= 0x80000000:  # Check if it's negative in signed 32-bit
            gain_value_32bit -= 0x100000000  # Convert to signed 32-bit

        # Convert the integer (32-bit) to IEEE 754 float (single precision)
        ieee754_float = struct.unpack('!f', struct.pack('!I', gain_value_32bit & 0xFFFFFFFF))[0]

        # Now, get the IEEE 754 representation as a hexadecimal string
        ieee754_hex = hex(struct.unpack('!I', struct.pack('!f', ieee754_float))[0])

        print(f"Processing PV: {pv_name}")
        print(f"Original integer value: {gain_value}")
        print(f"Interpreted IEEE 754 float: {ieee754_float}")
        print(f"IEEE 754 hex representation: {ieee754_hex}")
        
        # Create the new PV name by appending '_qspi' to the original name
        rdbck_pv_name = pv_name + "_qspi"
        
        # Perform caput to the new PV
        epics.caput(rdbck_pv_name, new_value*ieee754_float)
        print(f"Written IEEE 754 float value {new_value * ieee754_float} to PV: {rdbck_pv_name}")

    else:
        print(f"PV {pv_name} does not return an integer value, but got {type(gain_value)}")

# Sample usage: Reading in PVs from a relative file path and processing each one
file_path = os.path.join(os.path.dirname(__file__), 'cal_pv_list.txt')  # Change 'pvs.txt' to your file name or path

pvs_list = read_pvs_from_file(file_path)  # Reads the PVs from the relative path

# Process each PV
for pv_name, new_value in pvs_list:  # Unpack each tuple into pv_name and new_value
    process_pv(pv_name)  # Only pass pv_name to the process_pv function

