# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import serial
import time

ser = serial.Serial("/dev/ttySC1",115200,timeout=1)
# ser = serial.Serial("/dev/ttySC1",115200,timeout=1) 
time.sleep(1)

command = ["a","b","c",",","1","5",0x24,0x48]
s = ""
print("send data:")
for item in command:
    s = s + str(item)
    print(item)
len = ser.write(command)
print("len:"),len

ser.flush()
