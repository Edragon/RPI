# Copyright (c) 2015 WaveShare
# Author: My MX
import math
import time

import spidev as SPI
import SSD1306

import Image
import ImageFont
import ImageDraw


# Raspberry Pi pin configuration:
RST = 19
DC = 16
bus = 0
device = 0

# 128x32 display with hardware SPI:
disp = SSD1306.SSD1306(rst=RST,dc=DC,spi=SPI.SpiDev(bus,device))

# Initialize library.
disp.begin()

# Get display width and height.
width = disp.width
height = disp.height

# Clear display.
disp.clear()
disp.display()

# Create image buffer.
# Make sure to create image with mode '1' for 1-bit color.
image = Image.new('1', (width, height))

# Load default font.
font = ImageFont.load_default()

# Alternatively load a TTF font.  Make sure the .ttf font file is in the same directory as this python script!
# Some nice fonts to try: http://www.dafont.com/bitmap.php
# font = ImageFont.truetype('Minecraftia.ttf', 8)

# Create drawing object.
draw = ImageDraw.Draw(image)

# Define text and get total width.
text = 'SSD1306 ORGANIC LED DISPLAY. THIS IS AN OLD SCHOOL DEMO SCROLLER!! GREETZ TO: LADYADA & THE ADAFRUIT CREW, TRIXTER, FUTURE CREW, AND FARBRAUSCH'
maxwidth, unused = draw.textsize(text, font=font)

# Set animation and sine wave parameters.
amplitude = height/4
offset = height/2 - 4
velocity = -2
startpos = width

# Animate text moving in sine wave.
print 'Press Ctrl-C to quit.'
pos = startpos
while True:
	# Clear image buffer by drawing a black filled box.
	draw.rectangle((0,0,width,height), outline=0, fill=0)
	# Enumerate characters and draw them offset vertically based on a sine wave.
	x = pos
	for i, c in enumerate(text):
		# Stop drawing if off the right side of screen.
		if x > width:
			break
		# Calculate width but skip drawing if off the left side of screen.
		if x < -10:
			char_width, char_height = draw.textsize(c, font=font)
			x += char_width
			continue
		# Calculate offset from sine wave.
		y = offset+math.floor(amplitude*math.sin(x/float(width)*2.0*math.pi))
		# Draw text.
		draw.text((x, y), c, font=font, fill=255)
		# Increment x position based on chacacter width.
		char_width, char_height = draw.textsize(c, font=font)
		x += char_width
	# Draw the image buffer.
	disp.image(image)
	disp.display()
	# Move position for next frame.
	pos += velocity
	# Start over if text has scrolled completely off left side of screen.
	if pos < -maxwidth:
		pos = startpos
	# Pause briefly before drawing next frame.
	time.sleep(0.1)
