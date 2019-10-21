#include <bcm2835.h>  

int main(int argc, char **argv)  
{  
    char buf[1];

    if (!bcm2835_init())return 1;  
    bcm2835_i2c_begin(); 
    bcm2835_i2c_setSlaveAddress(0x20);  //i2c address
    bcm2835_i2c_set_baudrate(10000);    //1M baudrate

    while(1)  
    {   
        buf[0] = 0xEF;    //LED ON
        bcm2835_i2c_write(buf,1);
        bcm2835_delay(500);
        buf[0] = 0xFF;     //LED OFF
        bcm2835_i2c_write(buf,1);
        bcm2835_delay(500); 
    }    
    bcm2835_i2c_end();  
    bcm2835_close();  
    return 0;  
} 

