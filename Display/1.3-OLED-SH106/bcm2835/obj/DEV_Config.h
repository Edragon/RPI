#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_
/***********************************************************************************************************************
			------------------------------------------------------------------------
			|\\\																///|
			|\\\					Hardware interface							///|
			------------------------------------------------------------------------
***********************************************************************************************************************/
#include <bcm2835.h>

#define USE_SPI 1
//#define USE_IIC 1
#define IIC_CMD        0X00
#define IIC_RAM        0X40

//OLED
//#define SPI_MOSI 10
//#define SPI_SCK  11
//#define I2C_SCL 3
//#define I2C_SDA 2
#define OLED_CS         8
#define OLED_RST        25
#define OLED_DC         24

#define OLED_CS_0      bcm2835_gpio_write(OLED_CS,LOW)
#define OLED_CS_1      bcm2835_gpio_write(OLED_CS,HIGH)

#define OLED_RST_0      bcm2835_gpio_write(OLED_RST,LOW)
#define OLED_RST_1      bcm2835_gpio_write(OLED_RST,HIGH)
#define OLED_RST_RD     bcm2835_gpio_lev(OLED_RST)

#define OLED_DC_0       bcm2835_gpio_write(OLED_DC,LOW)
#define OLED_DC_1       bcm2835_gpio_write(OLED_DC,HIGH)

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
void    System_Exit(void);

void SPI_Write_Byte(uint8_t value);
void I2C_Write_Byte(uint8_t value, uint8_t Cmd);

void Driver_Delay_ms(uint32_t xms);
void Driver_Delay_us(uint32_t xus);

#endif