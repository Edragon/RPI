#!/usr/bin/python
# -*- coding:utf-8 -*-
import smbus
import time

address = 0x48
cmd = 0x40
value = 0

bus = smbus.SMBus(1)
while True:
	bus.write_byte_data(address,cmd,value)
	value += 1
	if value == 256:
		value =0
	print("AOUT:%3d" %value)
	time.sleep(0.01)


