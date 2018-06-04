#include <bcm2835.h>  
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)  
{  
	char Buf[]={0};
	unsigned char i;

	if (!bcm2835_init())return 1;  
	bcm2835_i2c_begin(); 
	bcm2835_i2c_setSlaveAddress(0x48);  
    bcm2835_i2c_set_baudrate(10000);  
    printf("start..........\n"); 

    while(1)  
    {  
		for(i = 0;i < 4;i++)
		{
			Buf[0] = i;  
        	bcm2835_i2c_write_read_rs(Buf,1,Buf,1);  
  	    	bcm2835_i2c_read (Buf,1);
			printf("AIN%d:%5.2f  ",i,(double)Buf[0]*3.3/255);
		}
		printf("\n");
        bcm2835_delay(100);  
	}  
         
    bcm2835_i2c_end();  
    bcm2835_close();  
    return 0;  
}  
