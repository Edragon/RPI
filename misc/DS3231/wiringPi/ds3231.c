#include <wiringPi.h>
#include <wiringPiI2C.h>  
#include <stdio.h>

#define DS3231_Address 0x68
//seconds,minutes,hours,weekdays,days,months,yeas
char  buf[]={0x00,0x47,0x11,0x05,0x19,0x06,0x15};
char  *str[]  ={"SUN","Mon","Tues","Wed","Thur","Fri","Sat"};
int fd,i;

void pcf8563SetTime()
{
	for(i = 0;i < 7;i++)
	{
		wiringPiI2CWriteReg8(fd,i,buf[i]);
	}
}

void pcf8563ReadTime() 
{   
	for(i = 0;i < 7;i++)
	{
		buf[i] = (char)wiringPiI2CReadReg8(fd,i);
	}
} 

int main(int argc, char **argv)  
{  
	if(wiringPiSetup() < 0)return 1;  
   	fd = wiringPiI2CSetup(DS3231_Address);
    printf("DS3231 Test Program ...\n\n"); 
   	
    pcf8563SetTime(); 
    while(1)  
    {  
       	pcf8563ReadTime();
		buf[0] = buf[0]&0x7F; //sec
		buf[1] = buf[1]&0x7F; //min
		buf[2] = buf[2]&0x3F; //hour
		buf[3] = buf[3]&0x07; //week
		buf[4] = buf[4]&0x3F; //day
		buf[5] = buf[5]&0x1F; //mouth
		//year/month/day
		printf("20%02x/%02x/%02x  ",buf[6],buf[5],buf[4]);
		//hour:minute/second
		printf("%02x:%02x:%02x  ",buf[2],buf[1],buf[0]);
		//weekday
		printf("%s\n",str[(unsigned char)buf[3]]);
		delay(1000); 
	} 
    return 0;  
}  
