/* blink.c
 * you can build this like: 
 * gcc -Wall blink.c -o blink -lwiringPi
 * sudo ./flash
*/
#include<wiringPi.h>

char LED = 25;

int main(void)
{
	if(wiringPiSetup() < 0)return 1;
	pinMode (LED,OUTPUT) ;

	while(1)
	{
  		digitalWrite(LED, 1) ;
    	delay (200);
  		digitalWrite(LED, 0) ;
    	delay (200);
	}
}
