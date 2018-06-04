#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import smbus
import time

address = 0x20

def beep_on():
	bus.write_byte(address,0x7F&bus.read_byte(address))
def beep_off():
	bus.write_byte(address,0x80|bus.read_byte(address))
def led_off():
	bus.write_byte(address,0x10|bus.read_byte(address))
def led_on():
	bus.write_byte(address,0xEF&bus.read_byte(address))

bus = smbus.SMBus(1)
print("PCF8574 Test Program !!!")
while True:
	bus.write_byte(address,0x0F|bus.read_byte(address))
	value = bus.read_byte(address) | 0xF0
	if value != 0xFF:
		led_on()
		beep_on()
		if (value | 0xFE) != 0xFF:
			print("left")
		elif (value | 0xFD) != 0xFF:
			print("up")
		elif (value | 0xFB) != 0xFF:
			print("dowm")
		else :
			print("right")
		while value != 0xFF:
			bus.write_byte(address,0x0F|bus.read_byte(address))
			value = bus.read_byte(address) | 0xF0
			time.sleep(0.01)
		beep_off()
		led_off()
	time.sleep(0.1)


