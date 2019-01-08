#include "DEV_Config.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

uint8_t System_Init(void)
{
	//1.wiringPiSetupGpio
    //if(wiringPiSetup() < 0)//use wiringpi Pin number table
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf(" set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf(" set wiringPi lib success  !!! \r\n");
    }
    //2.GPIO config
    pinMode(LCD_RST,OUTPUT);
    pinMode(LCD_DC,OUTPUT);
    pinMode(LCD_BL,OUTPUT);
    pinMode(LCD_CS,OUTPUT);	//must set cs output,Otherwise it does not work

    //3.spi init
    //wiringPiSPISetup(0,9000000);
    wiringPiSPISetupMode(0, 32000000, 0);
    return 0;
}

void System_Exit(void)
{
	LCD_CS_1;
}

/*********************************************


*********************************************/
void SPI_Write_Byte(uint8_t value)
{
    int read_data;
    read_data = wiringPiSPIDataRW(0,&value,1);
    if(read_data < 0)
        perror("wiringPiSPIDataRW failed\r\n");
}

/*********************************************


*********************************************/
void Driver_Delay_ms(uint32_t xms)
{
    delay(xms);
}

void Driver_Delay_us(uint32_t xus)
{
    int j;
    for(j=xus; j > 0; j--);
}
