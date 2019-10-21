#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>

#define Address 0x48
#define BASE 64
#define A0 BASE+0
#define A1 BASE+1
#define A2 BASE+2
#define A3 BASE+3

int main()
{
	if (wiringPiSetup() < 0)return 1;
	pcf8591Setup(BASE,Address);

	while(1)
	{
  		printf("AD: %4dmv \n",analogRead(A3)*3300/255);
		delay(1000);
  	}
}
