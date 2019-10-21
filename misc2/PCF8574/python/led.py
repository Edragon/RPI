#!/usr/bin/python
# -*- coding:utf-8 -*-
import smbus
import time

address = 0x20

bus = smbus.SMBus(1)
while True:
	bus.write_byte(address,0xEF)
	time.sleep(0.5)
	bus.write_byte(address,0xFF)
	time.sleep(0.5)
