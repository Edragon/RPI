/*****************************************************************************
* | File        :   SC16IS752GPIO.c
* | Author      :   Waveshare team
* | Function    :   Drive SC16IS752 GPIO
* | Info        :
*                The SC16IS752/SC16IS762 is an I2C-bus/SPI bus interface to 
*                a dual-channel high performance UART offering data rates up 
*                to 5 Mbit/s, low operating and sleeping current;it provides 
*                the application with 8 additional programmable I/O pins. 
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-28
* | Info        :   Basic version
*
******************************************************************************/
#include "SC16IS752GPIO.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int GPIOExport(int Pin)
{
    char buffer[NUM_MAXBUF];
    int len;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        printf( "Export Failed: Pin%d\n", Pin - 504);
        return -1;
    }

    len = snprintf(buffer, NUM_MAXBUF, "%d", Pin);
    write(fd, buffer, len);

    close(fd);
    return 0;
}

int GPIOUnexport(int Pin)
{
    char buffer[NUM_MAXBUF];
    int len;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) {
        printf( "unexport Failed: Pin%d\n", Pin - 504);
        return -1;
    }

    len = snprintf(buffer, NUM_MAXBUF, "%d", Pin);
    write(fd, buffer, len);

    close(fd);
    return 0;
}

int GPIODirection(int Pin, int Dir)
{
    static const char dir_str[]  = "in\0out";
    char path[DIR_MAXSIZ];
    int fd;

    snprintf(path, DIR_MAXSIZ, "/sys/class/gpio/gpio%d/direction", Pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        printf( "Set Direction failed: Pin%d\n", Pin - 504);
        return -1;
    }

    if (write(fd, &dir_str[Dir == IN ? 0 : 3], Dir == IN ? 2 : 3) < 0) {
        printf( "failed to set direction!\n");
        return -1;
    }

    close(fd);
    return 0;
}

int GPIORead(int Pin)
{
    char path[DIR_MAXSIZ];
    char value_str[3];
    int fd;

    snprintf(path, DIR_MAXSIZ, "/sys/class/gpio/gpio%d/value", Pin);
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf( "Read failed Pin%d\n", Pin - 504);
        return -1;
    }

    if (read(fd, value_str, 3) < 0) {
        printf( "failed to read value!\n");
        return -1;
    }

    close(fd);
    return(atoi(value_str));
}

int GPIOWrite(int Pin, int value)
{
    static const char s_values_str[] = "01";
    char path[DIR_MAXSIZ];
    int fd;

    snprintf(path, DIR_MAXSIZ, "/sys/class/gpio/gpio%d/value", Pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        printf( "Write failed : Pin%d,value = %d\n", Pin - 504, value);
        return -1;
    }

    if (write(fd, &s_values_str[value == LOW ? 0 : 1], 1) < 0) {
        printf( "failed to write value!\n");
        return -1;
    }

    close(fd);
    return 0;
}
