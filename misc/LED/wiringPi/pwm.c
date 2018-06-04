/* Buzzer.c
 * you can build this like: 
 * gcc -Wall Buzzer.c -o Buzzer -lwiringPi
 * sudo ./Buzzer
*/
#include <stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

int led = 25;
unsigned char i;

int main()
{
	wiringPiSetup();
	softPwmCreate(led,0,100);
	while(1)
	{
		i += 5;
		if (i > 100)i = 0;
		softPwmWrite(led,i);
		delay(200);
	}
}
