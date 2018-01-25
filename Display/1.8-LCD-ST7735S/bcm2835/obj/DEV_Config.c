#include "DEV_Config.h"
#include <bcm2835.h>
#include <stdio.h>		//printf()

/*********************************************


*********************************************/	
uint8_t System_Init(void)
{
    if(!bcm2835_init()) {
        printf("bcm2835 init failed   !!! \r\n");
        return 1;
    } else {
        printf("bcm2835 init success  !!! \r\n");
    }

    bcm2835_gpio_fsel(LCD_RST,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_DC,       BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_CS,       BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_UP_PIN,    BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_DOWN_PIN,  BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_LEFT_PIN,  BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_RIGHT_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY_PRESS_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY1_PIN,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY2_PIN,      BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(KEY3_PIN,      BCM2835_GPIO_FSEL_OUTP);

	printf("USE_SPI\r\n");
    bcm2835_spi_begin(); 										 //Start spi interface, set spi pin for the reuse function
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 1
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);   //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0

    return 0;
}

void System_Exit(void)
{
    bcm2835_spi_end();
    bcm2835_close();
}
/*********************************************


*********************************************/	
 void SPI_Write_Byte(uint8_t value)                                    
{    
	bcm2835_spi_transfer(value);
}

/*********************************************


*********************************************/	
void Driver_Delay_ms(uint32_t xms)	
{	
	bcm2835_delay(xms);
}

void Driver_Delay_us(uint32_t xus)
{
  int j;
  for(j=xus;j > 0;j--);    
}
