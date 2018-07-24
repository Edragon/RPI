#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

#define PCF8574_Address 0x20
#define EXTEND_BASE 64
#define RIGHT EXTEND_BASE + 0
#define DOWM  EXTEND_BASE + 1
#define UP    EXTEND_BASE + 2
#define LEFT  EXTEND_BASE + 3
#define LED   EXTEND_BASE + 4
#define BEEP  EXTEND_BASE + 7


int main (void)
{
	wiringPiSetup();
    pcf8574Setup(EXTEND_BASE,PCF8574_Address);
	pinMode(RIGHT,INPUT);
	pinMode(DOWM,INPUT);
	pinMode(UP,INPUT);
	pinMode(LEFT,INPUT);
	pinMode(LED,OUTPUT);
	digitalWrite(LED,HIGH);
	pinMode(BEEP,OUTPUT);
	digitalWrite(BEEP,HIGH);
    while (1)
    {
    	if((digitalRead(UP) == LOW) || (digitalRead(DOWM) == LOW) || 
			(digitalRead(LEFT) == LOW) || (digitalRead(RIGHT) == LOW))
      	{
			digitalWrite(LED,LOW);
			digitalWrite(BEEP,LOW);
			if(digitalRead(LEFT) == LOW)
          		printf("left\n");
        	else if(digitalRead(UP) == LOW)
         		printf("up\n");
        	else if(digitalRead(DOWM) == LOW)
				printf("dowm\n");
			else if(digitalRead(RIGHT) == LOW)
          		printf("right\n");
			while((digitalRead(UP) == LOW) || (digitalRead(DOWM) == LOW) ||
				(digitalRead(LEFT) == LOW) || (digitalRead(RIGHT) == LOW))
			{
				delay(10);
			}
			digitalWrite(LED,HIGH);
			digitalWrite(BEEP,HIGH);
		}
     }
}

