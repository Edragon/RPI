import RPi.GPIO as GPIO
import time

GPIO_PIN = 12

GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PIN, GPIO.OUT)

p=GPIO.PWM(GPIO_PIN,50)   # channel=12 frequency=50Hz
p.start(0)
try:
    while 1:
        for dc in range(0, 101, 5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.5)
        for dc in range(100, -1, -5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.5)
except KeyboardInterrupt:
    pass
p.stop()
GPIO.cleanup()
