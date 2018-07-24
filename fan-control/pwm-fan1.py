import RPi.GPIO as GPIO
import time

GPIO_PIN = 12

GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PIN, GPIO.OUT)

p=GPIO.PWM(GPIO_PIN,0.5)
p.start(1)
input('Press return to stop:')   # use raw_input for Python 2
p.stop()
GPIO.cleanup()
