#include <wiringPi.h>
#include <wiringPiI2C.h>

int main (void)
{
    int fd;
	wiringPiSetup();
    fd = wiringPiI2CSetup(0x20);

    while (1) 
    {   
        wiringPiI2CWrite(fd,0xEF);  //LED ON
        delay(500);
        wiringPiI2CWrite(fd,0xFF);  //LED OFF
        delay(500);
    }   
    return 0;
}

