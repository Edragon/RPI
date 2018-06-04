import time

import spidev as SPI
import SSD1306

import Image
import ImageDraw
import ImageFont

# Raspberry Pi pin configuration:
RST = 19
# Note the following are only used with SPI:
DC = 16
bus = 0
device = 0

# 128x64 display with hardware SPI:
disp = SSD1306.SSD1306(RST, DC, SPI.SpiDev(bus,device))

# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new('1', (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
draw.rectangle((0,0,width,height), outline=0, fill=0)

# Draw some shapes.
# First define some constants to allow easy resizing of shapes.
padding = 1
top = padding
x = padding
# Load default font.
font = ImageFont.load_default()

# Alternatively load a TTF font.
# Some other nice fonts to try: http://www.dafont.com/bitmap.php
#font = ImageFont.truetype('Minecraftia.ttf', 8)

# Write two lines of text.
draw.text((x, top),    'This is first line', font=font, fill=255)
draw.text((x, top+10), 'This is second line', font=font, fill=255)
draw.text((x, top+20), 'This is third line', font=font, fill=255)
draw.text((x, top+30), 'This is fourth line', font=font, fill=255)
draw.text((x, top+40), 'This is fifth line', font=font, fill=255)
draw.text((x, top+50), 'This is last line', font=font, fill=255)

# Display image.
disp.image(image)
disp.display()

