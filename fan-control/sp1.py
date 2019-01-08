#demonstrates how to control the output of OUT1
import RPi.GPIO as GPIO
import time

GPIO_PIN = 12

GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PIN, GPIO.OUT)
GPIO.setwarnings(False)

#GPIO.output(GPIO_PIN,GPIO.LOW)


while True:
	#turn on the power output, LED is on
	GPIO.output(GPIO_PIN,GPIO.LOW)
	print "Turn on the power output gpio low"
	time.sleep(10)


	#turn off the power output, LED is off
	GPIO.output(GPIO_PIN,GPIO.HIGH)
	print "Turn off the power output gpio high"
	time.sleep(10)
