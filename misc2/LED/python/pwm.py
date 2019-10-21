#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time
LED = 26
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED,GPIO.OUT)

p = GPIO.PWM(LED,50)
p.start(0)
try:
	while True:
		for dc in range(0,101,5):
			p.ChangeDutyCycle(dc)
			time.sleep(0.05)
		for dc in range(100,-1,-5):
			p.ChangeDutyCycle(dc)
			time.sleep(0.05)
except KeyboardInterrupt:
	pass
	p.stop()
	GPIO.cleanup()
