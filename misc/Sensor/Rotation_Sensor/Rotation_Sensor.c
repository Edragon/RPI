#include <stdio.h>
#include <wiringPi.h>

#define SIA 22
#define SIB 23
#define SW  26

char turn_flag;

// myInterrupt:  called every time an event occurs
void myInterrupt0(void) {
   turn_flag=1;
}
void myInterrupt1(void) {
   turn_flag=2;
}
void myInterrupt2(void) {
   turn_flag=3;
}


int main(void)
{
	if(wiringPiSetup () < 0) return 1;

  	if(wiringPiISR(SIA, INT_EDGE_BOTH, &myInterrupt0) < 0 )
	{
    	printf("Unable to setup ISR: SIA\n");
      	return 1;
  	}
 	if(wiringPiISR(SIB, INT_EDGE_BOTH, &myInterrupt1) < 0 ) 
	{
    	printf("Unable to setup ISR: SIB\n");
      	return 1;
  	}
  	if(wiringPiISR(SW, INT_EDGE_FALLING, &myInterrupt2) < 0 ) 
	{
    	printf("Unable to setup ISR: SW\n");
      	return 1;
  	}
 
	while (1)
	{ 
		if(turn_flag)
		{
			switch(turn_flag)
			{
				case 1:	printf("Turn right!\r\n");break;
				case 2:	printf("Turn left!\r\n");break;
				case 3:	printf("Turn down!\r\n");break;
				default:break;
			}
			delay(500);
			turn_flag=0;
		}
	}
	return 0;
}
