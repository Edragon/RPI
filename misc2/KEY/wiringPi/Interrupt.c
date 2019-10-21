/* Interrupt.c
 * you can build this like: 
 * gcc -Wall Interrupt.c -o Interrupt -lwiringPi
 * sudo ./Interrupt
*/
#include <stdio.h>
#include <wiringPi.h>

#define button 28
char flag = 0;
void myInterrupt()
{
	flag ++;
}

int main()
{
	if(wiringPiSetup() < 0)return 1;
	pinMode(button,INPUT);
	pullUpDnControl(button,PUD_UP);
	if(wiringPiISR(button,INT_EDGE_RISING,&myInterrupt) < 0)
	{
		printf("Unable to setup ISR \n");
	}
	printf("Interrupt test program\n");
	while(1)
	{
		if(flag)
		{
			while(digitalRead(button) ==0);
			printf("button press\n");
			flag = 0;
		}
	}
}
