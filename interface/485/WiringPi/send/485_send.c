#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


#define EN_485 4

int main(void)
{
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }
    pinMode(EN_485, OUTPUT);
    digitalWrite(EN_485,HIGH);

    int fd;
    if((fd = serialOpen ("/dev/ttyS0",9600)) < 0) {
        printf("serial err\n");
        return -1;
    }

    serialFlush(fd);
    serialPrintf(fd,"\r");
    
    serialPuts(fd, "12345\n");
    serialPuts(fd, "56789\n");

    serialClose(fd);
    return 0;
}
