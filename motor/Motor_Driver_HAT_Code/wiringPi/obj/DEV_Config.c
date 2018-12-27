/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-03
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include "Debug.h"  //DEBUG()

#include <wiringPi.h>
#include <wiringPiI2C.h>

int fd;

/**
 * Module Initialize, use BCM2835 library.
 *
 * Example:
 * if(DEV_ModuleInit())
 *   exit(0);
 */
UBYTE DEV_ModuleInit(void)
{
    //1.wiringPiSetupGpio
    //if(wiringPiSetup() < 0)//use wiringpi Pin number table
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        DEBUG("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        DEBUG("set wiringPi lib success  !!! \r\n");
    }

    return 0;
}

/**
 * Module Exit, close BCM2835 library.
 *
 * Example:
 * DEV_ModuleExit();
 */
void DEV_ModuleExit(void)
{
    // bcm2835_i2c_end();
    // bcm2835_close();
}

/**
 * Module Initialize, use BCM2835 library.
 *
 * @param addr: I2C Device address.
 *
 * Example:
 * DEV_I2C_Init(0X57);
 */
void DEV_I2C_Init(char addr)
{
    fd = wiringPiI2CSetup(addr);
}

/**
 * I2C write byte.
 *
 * @param reg: register.
 * @param value: value.
 *
 * Example:
 * DEV_I2C_WriteByte(0x00, 0xff);
 */
void DEV_I2C_WriteByte(UBYTE reg, UBYTE value)
{
    int ref;
    ref = wiringPiI2CWriteReg8(fd, (int)reg, (int)value);
    while(ref != 0) {
        ref = wiringPiI2CWriteReg8 (fd, (int)reg, (int)value);
        if(ref == 0)
            break;
    }
}

/**
 * I2C read byte.
 *
 * @param reg: register.
 *
 * Example:
 * UBYTE buf = PCA9685_Read(0x00);
 */
UBYTE DEV_I2C_ReadByte(UBYTE reg)
{
    return wiringPiI2CReadReg8(fd, reg);
}

/**
 * Millisecond delay.
 *
 * @param xms: time.
 *
 * Example:
 * DEV_Delay_ms(500);//delay 500ms
 */
void DEV_Delay_ms(uint32_t xms)
{
    delay(xms);
}

/**
 * Microsecond delay.
 *
 * @param xus: time.
 *
 * Example:
 * DEV_Delay_us(500);//delay 500us
 */
void DEV_Delay_us(uint32_t xus)
{
    int j;
    for(j=xus; j > 0; j--);
}
