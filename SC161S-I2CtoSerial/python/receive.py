# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import serial
import time

ser = serial.Serial("/dev/ttySC1",115200,timeout=1)
# ser = serial.Serial("/dev/ttySC1",115200,timeout=1)
time.sleep(1)
ser.flushInput()

data = ""
while 1: 
    while ser.inWaiting() > 0:
        data += ser.read(ser.inWaiting())
    if data != "":
        for i in range(len(data)):
            print data[i],
        print ""
        data = ""
