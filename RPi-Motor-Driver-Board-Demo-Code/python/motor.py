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
p1 = GPIO.PWM(D1,500)
p2 = GPIO.PWM(D2,500)
p1.start(50)
p2.start(50)

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

def getkey():
	if GPIO.input(PIN) == 0:
		count = 0
		while GPIO.input(PIN) == 0 and count < 200:  #9ms
			count += 1
			time.sleep(0.00006)

		count = 0
		while GPIO.input(PIN) == 1 and count < 80:  #4.5ms
			count += 1
			time.sleep(0.00006)

		idx = 0
		cnt = 0
		data = [0,0,0,0]
		for i in range(0,32):
			count = 0
			while GPIO.input(PIN) == 0 and count < 15:    #0.56ms
				count += 1
				time.sleep(0.00006)
				
			count = 0
			while GPIO.input(PIN) == 1 and count < 40:   #0: 0.56ms
				count += 1                               #1: 1.69ms
				time.sleep(0.00006)
				
			if count > 8:
				data[idx] |= 1<<cnt
			if cnt == 7:
				cnt = 0
				idx += 1
			else:
				cnt += 1
		if data[0]+data[1] == 0xFF and data[2]+data[3] == 0xFF:  #check
			return data[2]

print('IRM Test Start ...')
stop()
try:
	while True:
		key = getkey()
		if(key != None):
			print("Get the key: 0x%02x" %key)
			if key == 0x18:
				forward()
				print("forward")
			if key == 0x08:
				left()
				print("left")
			if key == 0x1c:
				stop()
				print("stop")
			if key == 0x5a:
				right()
				print("right")
			if key == 0x52:
				reverse()		
				print("reverse")
			if key == 0x15:
				if(PWM + 10 < 101):
					PWM = PWM + 10
					p1.ChangeDutyCycle(PWM)
					p2.ChangeDutyCycle(PWM)
					print(PWM)
			if key == 0x07:
				if(PWM - 10 > -1):
					PWM = PWM - 10
					p1.ChangeDutyCycle(PWM)
					p2.ChangeDutyCycle(PWM)
					print(PWM)
except KeyboardInterrupt:
	GPIO.cleanup();

