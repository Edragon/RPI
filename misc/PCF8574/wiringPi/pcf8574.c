#include <wiringPi.h>  
#include <wiringPiI2C.h>
#include <stdio.h>

#define PCF8574_Address 0x20
#define beep_on  i2c_writeByte(0x7F & i2c_readByte())
#define beep_off i2c_writeByte(0x80 | i2c_readByte())
#define led_off  i2c_writeByte(0x10 | i2c_readByte())
#define led_on   i2c_writeByte(0xEF & i2c_readByte())

int fd;

void i2c_writeByte(char byte)
{
	wiringPiI2CWrite(fd,byte);
}
char i2c_readByte()
{
	return (char)wiringPiI2CRead(fd);
}

int main()  
{  
	char value;

	if (wiringPiSetup() < 0)return 1;  
	fd = wiringPiI2CSetup(PCF8574_Address); 
    printf("PCF8574 Test Program !!!\n"); 

    while(1)  
    {  
		i2c_writeByte(0x0F | i2c_readByte());
		value = i2c_readByte() | 0xF0;
		if(value != 0xFF)
		{
			beep_on;
			led_on;
			switch(value)
			{	
				case 0xFE:
					printf("left\n");break;	
				case 0xFD:
					printf("up\n");	break;
				case 0xFB:
					printf("dowm\n");break;	
				case 0xF7:
					printf("right\n");break;
				default :
					printf("unknow\n");
			}
			while(value != 0xFF)
			{
				i2c_writeByte(0x0F | i2c_readByte());
				value = i2c_readByte() | 0xF0;
				delay(10);
			}
			beep_off;
			led_off;
		}
		delay(10);	
	}           
}  
