#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define UART_DEV1    "/dev/ttySC0"
#define UART_DEV2    "/dev/ttySC1"

int main(void)
{
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }

    int fd;
    if((fd = serialOpen (UART_DEV1, 115200)) < 0) {
        printf("serial err\n");
        return -1;
    }

    serialFlush(fd);
    serialPrintf(fd,"\r");

    char *buf = "abcdefgh";    
    serialPuts(fd, buf);

    printf("send data: %s\r\n", buf);    

    serialClose(fd);
    return 0;
}
