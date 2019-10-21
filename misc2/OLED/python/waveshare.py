# Copyright (c) 2015 WaveShare
# Author: My MX
import time

import spidev as SPI
import SSD1306

import Image


# Raspberry Pi pin configuration:
RST = 19
DC = 16
bus = 0
device = 0


# 128x32 display with hardware I2C:
disp = SSD1306.SSD1306(rst=RST,dc=DC,spi=SPI.SpiDev(bus,device))

# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

# Load image based on OLED display height.  Note that image is converted to 1 bit color.
image = Image.open('waveshare.bmp').convert('1')

# Alternatively load a different format image, resize it, and convert to 1 bit color.
#image = Image.open('happycat.png').resize((disp.width, disp.height), Image.ANTIALIAS).convert('1')

# Display image.
disp.image(image)
disp.display()
