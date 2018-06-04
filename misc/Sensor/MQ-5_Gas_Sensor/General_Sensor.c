#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>

#define Address 0x48
#define BASE 64
#define A0 BASE+0
#define A1 BASE+1
#define A2 BASE+2
#define A3 BASE+3
#define D3 26

int main()
{
    if (wiringPiSetup() < 0)return 1;
    pcf8591Setup(BASE,Address);   
    pinMode(D3,INPUT);
    //digitalWrite(D3,0);

	while(1)
	{
  		if(digitalRead(D3) == LOW)
		{
			printf("Gas leakage\n");
			printf("AD: %04d \n",analogRead(A3)*3300/255);
		}
		else
		{
			printf("Gas not leakage\n");
		}
		delay(500);
  	}
}
