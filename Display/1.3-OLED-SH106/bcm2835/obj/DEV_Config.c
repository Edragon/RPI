#include "DEV_Config.h"
#include <bcm2835.h>
#include <stdio.h>		//printf()
/*********************************************
*
*
*********************************************/
uint8_t System_Init(void)
{
    if(!bcm2835_init()) {
        printf("bcm2835 init failed   !!! \r\n");
        return 1;
    } else {
        printf("bcm2835 init success  !!! \r\n");
    }

    bcm2835_gpio_fsel(OLED_RST,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(OLED_DC,       BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(OLED_CS,       BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_UP_PIN,    BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_DOWN_PIN,  BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_LEFT_PIN,  BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_RIGHT_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_PRESS_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY1_PIN,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY2_PIN,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY3_PIN,      BCM2835_GPIO_FSEL_OUTP);

#if USE_SPI
	printf("USE_SPI\r\n");
    bcm2835_spi_begin(); 										 //Start spi interface, set spi pin for the reuse function
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 1
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048);   //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0
#elif USE_IIC
    OLED_DC_0;
    OLED_CS_0;
    printf("USE_IIC\r\n");
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x3c);  //i2c address
//	bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_148);
    bcm2835_i2c_set_baudrate(100000  );    //100k baudrate

    /*	uint8_t  buf[1];
    	I2C_Write_Byte(0xAD);
    	buf[0] = bcm2835_i2c_read((char *)buf, 1);
    	printf("buf = %d",buf[0]);
    	*/
#endif

    return 0;
}

void System_Exit(void)
{
#if USE_SPI
    bcm2835_spi_end();
#elif USE_IIC
    bcm2835_i2c_end();
#endif
    bcm2835_close();
}

/*********************************************
*
*
*********************************************/
void SPI_Write_Byte(uint8_t value)
{
	char buf[1] = {0XFF};
	buf[0] = (char)value;
    bcm2835_spi_transfern(buf, 1);
}

void I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
    char buf[2] = {IIC_RAM,0XFF};
    int ref;
    buf[1] = (char)value;
	
    if(Cmd == IIC_RAM)
        buf[0] = IIC_RAM;
    else
        buf[0] = IIC_CMD;
	
    ref = bcm2835_i2c_write(buf, 2);
    while(ref != 0) {
        ref = bcm2835_i2c_write(buf, 2);
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
    bcm2835_delay(xms);
}

void Driver_Delay_us(uint32_t xus)
{
    int j;
    for(j=xus; j > 0; j--);
}
