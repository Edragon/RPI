# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import serial

EN_485 =  4
GPIO.setmode(GPIO.BCM)
GPIO.setup(EN_485,GPIO.OUT)
GPIO.output(EN_485,GPIO.HIGH)

t = serial.Serial("/dev/ttyS0",115200)    
print t.portstr    
strInput = raw_input('enter some words:')    
n = t.write(strInput)    
print n    
str = t.read(n)    
print str   


