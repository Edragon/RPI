#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h> 
#include <sys/time.h>

#define EN_485 4

int main(void)
{
    int nbytes;

    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }
    pinMode(EN_485, OUTPUT);
    digitalWrite(EN_485,LOW);

    int fd;
    int data;
    if((fd = serialOpen ("/dev/ttyS0",9600)) < 0) {
        printf("serial err\n");
        return -1;
    }

    serialFlush(fd);
    while(1) {
        nbytes = serialDataAvail (fd);
        if(nbytes == -1) {
            printf("receive data error\r\n");
            break;
        }else{
            // printf("%d\r\n", serialGetchar(fd));
            //data = serialGetchar(fd) - 48;
            printf("%c\r\n", serialGetchar(fd));
        }

    }

    serialClose(fd);
    return 0;
}
