#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>     //exit()
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>


#define UART_DEV1    "/dev/ttySC0"
#define UART_DEV2    "/dev/ttySC1"

int fd;

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:serialClose \r\n");
    serialClose(fd);

    exit(0);
}

int main(void)
{
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }

    if((fd = serialOpen (UART_DEV2, 115200)) < 0) {
        printf("serial err\n");
        return -1;
    }

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    for (;;) {
        putchar(serialGetchar(fd));
    }

    return 0;
}
