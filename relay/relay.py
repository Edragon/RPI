#! /usr/bin/python

import smbus
import sys
import getopt
import time 

#bus = smbus.SMBus(0) Rev 1 board
bus = smbus.SMBus(1)  # New Rev 2 board 

address = 0x20 # I2C address of MCP23008, change this accordingly

bus.write_byte_data(0x20,0x00,0x00) # Set all to outputs, change this accordingly


# Handle the command line arguments
def main():
	a = 0
delay = 1   

while True:
# 4 - 8 is the binary number (1111 0000) that attached relay 
   for x in range(4,8):
     bus.write_byte_data(address,0x09,1 << x) # Turn relay on in turn
     time.sleep(delay)						  # 1 second delay	
     bus.write_byte_data(address,0x09,0) 	  # Turn relay off	

 
if __name__ == "__main__":
   main()
