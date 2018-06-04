#include <bcm2835.h>  
#include <stdio.h>

#define beep_on  i2c_writeByte(0x7F & i2c_readByte())
#define beep_off i2c_writeByte(0x80 | i2c_readByte())
#define led_off   i2c_writeByte(0x10 | i2c_readByte())
#define led_on  i2c_writeByte(0xEF & i2c_readByte())
void i2c_writeByte(char byte)
{
	char buf[] = {byte};
	bcm2835_i2c_write(buf,1);
}
char i2c_readByte()
{
	char buf[1];
	bcm2835_i2c_read(buf,1);
	return buf[0];
}

int main(int argc, char **argv)  
{  
	char value;

	if (!bcm2835_init())return 1;  
	bcm2835_i2c_begin(); 
	bcm2835_i2c_setSlaveAddress(0x20);  
    bcm2835_i2c_set_baudrate(10000);  
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
				bcm2835_delay(10);
			}
			beep_off;
			led_off;
		}
		bcm2835_delay(10);	
	}           
    bcm2835_i2c_end();  
    bcm2835_close();  
    return 0;  
}  
