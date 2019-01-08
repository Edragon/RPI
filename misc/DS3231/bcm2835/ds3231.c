#include <bcm2835.h>  
#include <stdio.h>
#include <unistd.h>

//regaddr,seconds,minutes,hours,weekdays,days,months,yeas
char  buf[]={0x00,0x00,0x47,0x11,0x05,0x19,0x06,0x15};
char  *str[]  ={"SUN","Mon","Tues","Wed","Thur","Fri","Sat"};
void pcf8563SetTime()
{
	bcm2835_i2c_write(buf,8);
}

void pcf8563ReadTime() 
{   
	buf[0] = 0x00;  
    bcm2835_i2c_write_read_rs(buf ,1, buf,7);  
} 

int main(int argc, char **argv)  
{  
	if (!bcm2835_init())return 1;  
   	bcm2835_i2c_begin();  
    bcm2835_i2c_setSlaveAddress(0x68);  
    bcm2835_i2c_set_baudrate(10000);  
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
		bcm2835_delay(1000); 
	}  

	bcm2835_i2c_end();  
   	bcm2835_close();  
      
    return 0;  
}  
