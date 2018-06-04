/* key.c
 * you can build this like: 
 * gcc -Wall key.c -o key -lwiringPi
 * sudo ./key
*/
#include <stdio.h>
#include<wiringPi.h>

char KEY = 28;

int main()
{
	if (wiringPiSetup() < 0)return 1 ;
	pinMode (KEY,INPUT);
	pullUpDnControl(KEY, PUD_UP);
    printf("Key Test Program!!!\n");
	while(1)
	{
		if (digitalRead(KEY) == 0)  
    	{
			printf ("KEY PRESS\n") ;
    		while(digitalRead(KEY) == 0)
				delay(100);
		}
		delay(100);
	}
}
