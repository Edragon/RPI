#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_
/***********************************************************************************************************************
			------------------------------------------------------------------------
			|\\\																///|
			|\\\					Hardware interface							///|
			------------------------------------------------------------------------
***********************************************************************************************************************/
#include <bcm2835.h>

//GPIO config
//#define SPI_MISO 9
//#define SPI_MOSI 10
//#define SPI_SCK  11
#define LCD_CS   8
#define LCD_RST  27
#define LCD_DC   25
#define LCD_BL   24

//LCD
#define LCD_CS_0		bcm2835_gpio_write(LCD_CS,LOW)
#define LCD_CS_1		bcm2835_gpio_write(LCD_CS,HIGH)

#define LCD_RST_0		bcm2835_gpio_write(LCD_RST,LOW)
#define LCD_RST_1		bcm2835_gpio_write(LCD_RST,HIGH)

#define LCD_DC_0		bcm2835_gpio_write(LCD_DC,LOW)
#define LCD_DC_1		bcm2835_gpio_write(LCD_DC,HIGH)

#define LCD_BL_0		bcm2835_gpio_write(LCD_BL,LOW)
#define LCD_BL_1		bcm2835_gpio_write(LCD_BL,HIGH)

//KEY
#define KEY_UP_PIN      6
#define KEY_DOWN_PIN    19
#define KEY_LEFT_PIN    5
#define KEY_RIGHT_PIN   26
#define KEY_PRESS_PIN   13
#define KEY1_PIN        21
#define KEY2_PIN        20
#define KEY3_PIN        16

#define KEY_UP_RD       bcm2835_gpio_lev(KEY_UP_PIN)
#define KEY_DOWN_RD     bcm2835_gpio_lev(KEY_DOWN_PIN)
#define KEY_LEFT_RD     bcm2835_gpio_lev(KEY_LEFT_PIN)
#define KEY_RIGHT_RD    bcm2835_gpio_lev(KEY_RIGHT_PIN)
#define KEY_PRESS_RD    bcm2835_gpio_lev(KEY_PRESS_PIN)
#define KEY1_RD         bcm2835_gpio_lev(KEY1_PIN)
#define KEY2_RD         bcm2835_gpio_lev(KEY2_PIN)
#define KEY3_RD         bcm2835_gpio_lev(KEY3_PIN)
/*------------------------------------------------------------------------------------------------------*/
uint8_t System_Init(void);
void System_Exit(void);

void SPI_Write_Byte(uint8_t value);
void Driver_Delay_ms(uint32_t xms);
void Driver_Delay_us(uint32_t xus);

#endif
