import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'

chan_list_1 = [11, 13, 16, 22]
chan_list_2 = [12, 15, 18, 7]

## Define a function named Blink()
def Blink(numTimes,speed, c_list):
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(c_list, GPIO.OUT)
		
        for i in range(0,numTimes):## Run loop numTimes
                print "Iteration " + str(i+1)## Print current loop
                GPIO.output(c_list, GPIO.HIGH)		
                time.sleep(speed)## Wait			
                GPIO.output(c_list, GPIO.LOW)			
                time.sleep(speed)## Wait
                print "Done" ## When loop is complete, print "Done"
        GPIO.cleanup()
		
		
## Ask user for total number of blinks and length of each blink
iterations = raw_input("Enter total number of times to blink: ")
speed = raw_input("Enter length of each blink(seconds): ")

## Start Blink() function. Convert user input from strings to numeric data types and pass to Blink() as parameters
Blink(int(iterations),float(speed), chan_list_1)
Blink(int(iterations),float(speed), chan_list_2)
