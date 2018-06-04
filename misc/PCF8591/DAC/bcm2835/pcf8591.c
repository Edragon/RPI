#include <bcm2835.h>  
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)  
{  
	char Buf[]={0,0};
	unsigned char value=0;

	if (!bcm2835_init())return 1;  
	bcm2835_i2c_begin(); 
	bcm2835_i2c_setSlaveAddress(0x48);  
    bcm2835_i2c_set_baudrate(10000);  
    printf("start..........\n"); 

    while(1)  
    {  
		Buf[0] = 0x40;
		Buf[1] = value++;
		bcm2835_i2c_write(Buf,2);
		printf("AOUT: %d\n",value);

        bcm2835_delay(20);  
	}  
         
    bcm2835_i2c_end();  
    bcm2835_close();  
    return 0;  
}  
