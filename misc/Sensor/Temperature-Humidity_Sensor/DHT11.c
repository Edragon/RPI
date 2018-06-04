#include <stdio.h>
#include<wiringPi.h>

#define Data 26

char DHT11_Read(char *temperature,char *humidity)	   
{                 
	unsigned char t,i,j;
	unsigned char buf[5]={0,0,0,0,0};
	pinMode(Data,OUTPUT); 	    //SET OUTPUT
	pullUpDnControl(Data,PUD_UP);
    digitalWrite(Data,0); 	    //Data=0
    delay(20);         	        //Pull down Least 18ms
    digitalWrite(Data,1); 	    //Data =1
	delayMicroseconds(30);     	//Pull up 20~40us
	pinMode(Data,INPUT);        //SET INPUT
	
    while (digitalRead(Data) && t <100)//DHT11 Pull down 80us
	{
		t++;
		delayMicroseconds(1);
	};	 
	if(t >= 100)return 1;
	t = 0;
    while (!digitalRead(Data) && t<100)//DHT11 Pull up 80us
	{
		t++;
		delayMicroseconds(1);
	};
	if(t >= 100)return 1;	    
	for(i=0;i < 5;i++)
	{
		buf[i] = 0;
		for(j=0;j<8;j++)
		{
			buf[i] <<= 1;
			t = 0;
			while(digitalRead(Data) && t < 100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) return 1;
			t = 0;
			while(!digitalRead(Data) && t <100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) return 1;
			delayMicroseconds(40);
			if(digitalRead(Data))
				buf[i] += 1;
		}
	}
	if(buf[0]+buf[1]+buf[2]+buf[3]!=buf[4])return 2;
	*humidity = buf[0];
	*temperature =buf[2];
	return 0;
} 


int main(void)
{
	char temperature;  	    
	char humidity; 
	char value;

	if (wiringPiSetup() < 0)return 1;
	printf("Waveshare!\r\n");
	
  	while(1)
	{
		value = DHT11_Read(&temperature,&humidity);	
		if(value == 0)
		{ 
			printf("\ntemperature = %d\r\n",temperature);
			printf("humidity    = %d\r\n",humidity);
		}
		else if (value == 2)
		 	printf("\ncheck sum err\n");
		else
			printf("\ntime out\n");
 		delay(1000);
	}
}

