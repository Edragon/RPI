#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

#define EXTEND_BASE 64
#define LED EXTEND_BASE + 4
int main (void)
{
	wiringPiSetup();
    pcf8574Setup(EXTEND_BASE,0x20);
	pinMode(LED,OUTPUT);
    while (1)
    {
    	digitalWrite(LED,LOW);  //LED ON
        delay(500);
    	digitalWrite(LED,HIGH); //LED OFF
        delay(500);
    }
    return 0;
}

