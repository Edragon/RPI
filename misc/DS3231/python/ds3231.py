#!/usr/bin/python
# -*- coding: utf-8 -*-
import smbus
import time

address = 0x68
register = 0x00
#sec min hour week day mout year
NowTime = [0x00,0x00,0x18,0x04,0x12,0x08,0x15]
w  = ["SUN","Mon","Tues","Wed","Thur","Fri","Sat"];
#/dev/i2c-1
bus = smbus.SMBus(1)
def ds3231SetTime():
	bus.write_i2c_block_data(address,register,NowTime)

def ds3231ReadTime():
	return bus.read_i2c_block_data(address,register,7);

ds3231SetTime()
while 1:
	t = ds3231ReadTime()
	t[0] = t[0]&0x7F  #sec
	t[1] = t[1]&0x7F  #min
	t[2] = t[2]&0x3F  #hour
	t[3] = t[3]&0x07  #week
	t[4] = t[4]&0x3F  #day
	t[5] = t[5]&0x1F  #mouth
	print("20%x/%02x/%02x %02x:%02x:%02x %s" %(t[6],t[5],t[4],t[2],t[1],t[0],w[t[3]-1]))
	time.sleep(1)
