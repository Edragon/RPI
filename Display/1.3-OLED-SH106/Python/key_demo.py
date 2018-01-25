# -*- coding:utf-8 -*-

from luma.core.interface.serial import i2c, spi
from luma.core.render import canvas
from luma.core import lib

from luma.oled.device import sh1106
import RPi.GPIO as GPIO

import time
import subprocess

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

#GPIO define
RST_PIN        = 25
CS_PIN         = 8
DC_PIN         = 24
KEY_UP_PIN     = 6 
KEY_DOWN_PIN   = 19
KEY_LEFT_PIN   = 5
KEY_RIGHT_PIN  = 26
KEY_PRESS_PIN  = 13
KEY1_PIN       = 21
KEY2_PIN       = 20
KEY3_PIN       = 16

#SPI or IIC
USER_I2C = 0
if  USER_I2C == 1:
	GPIO.setup(RST_PIN,GPIO.OUT)	
	GPIO.output(RST_PIN,GPIO.HIGH)
	
	serial = i2c(port=1, address=0x3c)
else:
	serial = spi(device=0, port=0, bus_speed_hz = 8000000, transfer_size = 4096, gpio_DC = DC_PIN, gpio_RST = RST_PIN)
device = sh1106(serial, rotate=2) #sh1106  

#init GPIO
GPIO.setmode(GPIO.BCM) 
GPIO.setup(KEY_UP_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # Input with pull-up
GPIO.setup(KEY_DOWN_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Input with pull-up
GPIO.setup(KEY_LEFT_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Input with pull-up
GPIO.setup(KEY_RIGHT_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Input with pull-up
GPIO.setup(KEY_PRESS_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Input with pull-up
GPIO.setup(KEY1_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)      # Input with pull-up
GPIO.setup(KEY2_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)      # Input with pull-up
GPIO.setup(KEY3_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)      # Input with pull-up

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = 128
height = 64
image = Image.new('1', (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
draw.rectangle((0,0,width,height), outline=0, fill=0)


try:
	while 1:
		with canvas(device) as draw:
			if GPIO.input(KEY_UP_PIN): # button is released
				draw.polygon([(20, 20), (30, 2), (40, 20)], outline=255, fill=0)  #Up
			else: # button is pressed:
				draw.polygon([(20, 20), (30, 2), (40, 20)], outline=255, fill=1)  #Up filled
	 
			if GPIO.input(KEY_LEFT_PIN): # button is released
				draw.polygon([(0, 30), (18, 21), (18, 41)], outline=255, fill=0)  #left
			else: # button is pressed:
				draw.polygon([(0, 30), (18, 21), (18, 41)], outline=255, fill=1)  #left filled
			
			if GPIO.input(KEY_RIGHT_PIN): # button is released
				draw.polygon([(60, 30), (42, 21), (42, 41)], outline=255, fill=0) #right
			else: # button is pressed:
				draw.polygon([(60, 30), (42, 21), (42, 41)], outline=255, fill=1) #right filled
	 
			if GPIO.input(KEY_DOWN_PIN): # button is released
				draw.polygon([(30, 60), (40, 42), (20, 42)], outline=255, fill=0) #down
			else: # button is pressed:
				draw.polygon([(30, 60), (40, 42), (20, 42)], outline=255, fill=1) #down filled
	 
			if GPIO.input(KEY_PRESS_PIN): # button is released
				draw.rectangle((20, 22,40,40), outline=255, fill=0) #center 
			else: # button is pressed:
				draw.rectangle((20, 22,40,40), outline=255, fill=1) #center filled
	 
			if GPIO.input(KEY1_PIN): # button is released
				draw.ellipse((70,0,90,20), outline=255, fill=0) #A button
			else: # button is pressed:
				draw.ellipse((70,0,90,20), outline=255, fill=1) #A button filled
	 
			if GPIO.input(KEY2_PIN): # button is released
				draw.ellipse((100,20,120,40), outline=255, fill=0) #B button
			else: # button is pressed:
				draw.ellipse((100,20,120,40), outline=255, fill=1) #B button filled
				
			if GPIO.input(KEY3_PIN): # button is released
				draw.ellipse((70,40,90,60), outline=255, fill=0) #A button
			else: # button is pressed:
				draw.ellipse((70,40,90,60), outline=255, fill=1) #A button filled
except:
	print("except")
GPIO.cleanup()
