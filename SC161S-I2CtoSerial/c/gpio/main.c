/*****************************************************************************
* | File        :   MotorDriver.h
* | Author      :   Waveshare team
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-04
* | Info        :   Basic version
*
******************************************************************************/
#include "SC16IS752GPIO.h"
#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <signal.h>
#include <wiringPi.h>

void GPIO_Init(void)
{
    GPIOExport(PIN0);
    GPIOExport(PIN1);
    GPIOExport(PIN2);
    GPIOExport(PIN3);
    GPIOExport(PIN4);
    GPIOExport(PIN5);
    GPIOExport(PIN6);
    GPIOExport(PIN7);
    GPIODirection(PIN0, OUT);
    GPIODirection(PIN1, OUT);
    GPIODirection(PIN2, OUT);
    GPIODirection(PIN3, OUT);
    GPIODirection(PIN4, OUT);
    GPIODirection(PIN5, OUT);
    GPIODirection(PIN6, OUT);
    GPIODirection(PIN7, OUT);
}

void GPIO_Exit(void)
{
    GPIOUnexport(PIN0);
    GPIOUnexport(PIN1);
    GPIOUnexport(PIN2);
    GPIOUnexport(PIN3);
    GPIOUnexport(PIN4);
    GPIOUnexport(PIN5);
    GPIOUnexport(PIN6);
    GPIOUnexport(PIN7);
}

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:GPIO Stop\r\n");
    GPIO_Exit();

    exit(0);
}

int main(int argc, char *argv[])
{
    int i = 0;

    GPIO_Init();

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    for(i = 0; i < 8; i++) {
        GPIOWrite(PIN0 + i, 1);
        delay(200);
        GPIOWrite(PIN0 + i, 0);
        delay(200);
    }
    GPIO_Exit();
    return 0;
}