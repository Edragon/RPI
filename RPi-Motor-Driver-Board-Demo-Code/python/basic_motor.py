import RPi.GPIO as GPIO
import time

PIN = 18
PWMA1 = 6 
PWMA2 = 13
PWMB1 = 20
PWMB2 = 21
D1 = 12
D2 = 26

PWM = 50

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(PIN,GPIO.IN,GPIO.PUD_UP)

GPIO.setup(PWMA1,GPIO.OUT)
GPIO.setup(PWMA2,GPIO.OUT)
GPIO.setup(PWMB1,GPIO.OUT)
GPIO.setup(PWMB2,GPIO.OUT)
GPIO.setup(D1,GPIO.OUT)
GPIO.setup(D2,GPIO.OUT)

p1 = GPIO.PWM(D1,100)
p2 = GPIO.PWM(D2,100)
p1.start(90)
p2.start(90)

def	set_motor(A1,A2,B1,B2):
	GPIO.output(PWMA1,A1)
	GPIO.output(PWMA2,A2)
	GPIO.output(PWMB1,B1)
	GPIO.output(PWMB2,B2)

def forward():
	GPIO.output(PWMA1,1)
	GPIO.output(PWMA2,0)
	GPIO.output(PWMB1,1)
	GPIO.output(PWMB2,0)

def stop():
	set_motor(0,0,0,0)

def reverse():
	set_motor(0,1,0,1)

def left():
	set_motor(1,0,0,0)

def right():
	set_motor(0,0,1,0)



print('IRM Test Start ...')
stop()
try:
	while True:
		forward()
		print("forward")
		time.sleep(2)
		stop()
		print("stop")
		time.sleep(2)
		reverse()		
		print("reverse")
		time.sleep(2)

except KeyboardInterrupt:
	GPIO.cleanup();

