#demonstrates how to control the output of OUT1
import RPi.GPIO as GPIO
import time

GPIO_PIN = 27

GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PIN, GPIO.OUT)
GPIO.setwarnings(False)
while True:
	#turn on the power output, LED is on
	GPIO.output(GPIO_PIN,GPIO.HIGH)
	print "Turn on the power output"
	time.sleep(10)
	#turn off the power output, LED is off
	GPIO.output(GPIO_PIN,GPIO.LOW)
	print "Turn off the power output"
	time.sleep(10)