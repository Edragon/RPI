#!/bin/sh
cd /home/pi/RPi-Motor-Driver-Board-Demo-Code/mjpg-streamer/
sudo ./start.sh &
cd /home/pi/RPi-Motor-Driver-Board-Demo-Code/magpi-cambot
sudo webiopi -d -c config

