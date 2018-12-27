/*****************************************************************************
* | File        :   SC16IS752GPIO.h
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
#ifndef __SC16IS752GPIO_
#define __SC16IS752GPIO_

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define NUM_MAXBUF  4
#define DIR_MAXSIZ  60

#define PIN0    504
#define PIN1    (PIN0 + 1)
#define PIN2    (PIN0 + 2)
#define PIN3    (PIN0 + 3)
#define PIN4    (PIN0 + 4)
#define PIN5    (PIN0 + 5)
#define PIN6    (PIN0 + 6)
#define PIN7    (PIN0 + 7)

int GPIOExport(int pin);
int GPIOUnexport(int pin);
int GPIODirection(int pin, int dir);
int GPIORead(int pin);
int GPIOWrite(int pin, int value);

#endif