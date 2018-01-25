#include "DEV_Config.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

int fd;

/*********************************************
*
*
*********************************************/
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
    pinMode(OLED_RST,      OUTPUT);
    pinMode(OLED_DC,       OUTPUT);
    pinMode(OLED_CS,       OUTPUT);
    pinMode(KEY_UP_PIN,    OUTPUT);
    pinMode(KEY_DOWN_PIN,  OUTPUT);
    pinMode(KEY_LEFT_PIN,  OUTPUT);
    pinMode(KEY_RIGHT_PIN, OUTPUT);
    pinMode(KEY_PRESS_PIN, OUTPUT);
    pinMode(KEY1_PIN,      OUTPUT);
    pinMode(KEY2_PIN,      OUTPUT);
    pinMode(KEY3_PIN,      OUTPUT);

#if USE_SPI
	//3.spi init
	printf("USE_SPI\r\n");       
    //wiringPiSPISetup(0,9000000);
    wiringPiSPISetupMode(0, 9000000, 0);
#elif USE_IIC
    OLED_DC_0;
    OLED_CS_0;
    printf("USE_IIC\r\n");
	fd = wiringPiI2CSetup(0x3c);

#endif

    return 0;
}

void System_Exit(void)
{
	OLED_CS_0;
	OLED_RST_1;
	OLED_DC_0;

}

/*********************************************
*
*
*********************************************/
void SPI_Write_Byte(uint8_t value)
{
    int read_data;
    read_data = wiringPiSPIDataRW(0,&value,1);
    if(read_data < 0)
        perror("wiringPiSPIDataRW failed\r\n");
}

void I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
	int ref;
	//wiringPiI2CWrite(fd,Cmd);
    ref = wiringPiI2CWriteReg8(fd, (int)Cmd, (int)value);
    while(ref != 0) {
        ref = wiringPiI2CWriteReg8 (fd, (int)Cmd, (int)value);
        if(ref == 0)
            break;
    }	
}

/*********************************************
*
*
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
