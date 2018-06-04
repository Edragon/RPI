#include <stdio.h>
#include<wiringPi.h>

#define D3 26

int main()
{
	if (wiringPiSetup() < 0)return 1 ;

	pinMode(D3,INPUT);
	digitalWrite(D3,0);

	while(1)
	{
  		if(digitalRead(D3) == LOW)
		{
			printf("Tilt\n");
		}
		else
		{
			printf("OK\n");
		}
		delay(500);
  	}
}
