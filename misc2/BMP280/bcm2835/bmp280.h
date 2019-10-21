#ifndef _BMP280_
#define _BMP280_

//i2c address
#define BMP280_I2C_ADDRESS           0x76          //SDO = 0

//Registers  value
#define  BMP280_ID_Value             0x58
#define	 BMP280_RESET_VALUE          0xB6

/* BMP280 Registers definition  */
#define BMP280_TEMP_XLSB_REG         0xFC		  /*Temperature XLSB Register */
#define BMP280_TEMP_LSB_REG          0xFB         /*Temperature LSB Register */ 
#define BMP280_TEMP_MSB_REG          0xFA         /*Temperature LSB Register */  
#define BMP280_PRESS_XLSB_REG        0xF9		  /*Pressure XLSB  Register */
#define BMP280_PRESS_LSB_REG         0xF8		  /*Pressure LSB Register */
#define BMP280_PRESS_MSB_REG         0xF7		  /*Pressure MSB Register */						
#define BMP280_CONFIG_REG            0xF5         /*Configuration Register */
#define BMP280_CTRL_MEAS_REG         0xF4         /*Ctrl Measure Register */ 
#define BMP280_STATUS_REG            0xF3         /*Status Register */
#define BMP280_RESET_REG             0xE0		  /*Softreset Register */ 
#define BMP280_ID_REG                0xD0         /*Chip ID Register */

/*calibration parameters */  
#define BMP280_DIG_T1_LSB_REG        0x88  
#define BMP280_DIG_T1_MSB_REG        0x89  
#define BMP280_DIG_T2_LSB_REG        0x8A  
#define BMP280_DIG_T2_MSB_REG        0x8B  
#define BMP280_DIG_T3_LSB_REG        0x8C  
#define BMP280_DIG_T3_MSB_REG        0x8D  
#define BMP280_DIG_P1_LSB_REG        0x8E  
#define BMP280_DIG_P1_MSB_REG        0x8F  
#define BMP280_DIG_P2_LSB_REG        0x90  
#define BMP280_DIG_P2_MSB_REG        0x91  
#define BMP280_DIG_P3_LSB_REG        0x92  
#define BMP280_DIG_P3_MSB_REG        0x93  
#define BMP280_DIG_P4_LSB_REG        0x94  
#define BMP280_DIG_P4_MSB_REG        0x95  
#define BMP280_DIG_P5_LSB_REG        0x96  
#define BMP280_DIG_P5_MSB_REG        0x97  
#define BMP280_DIG_P6_LSB_REG        0x98  
#define BMP280_DIG_P6_MSB_REG        0x99  
#define BMP280_DIG_P7_LSB_REG        0x9A  
#define BMP280_DIG_P7_MSB_REG        0x9B  
#define BMP280_DIG_P8_LSB_REG        0x9C  
#define BMP280_DIG_P8_MSB_REG        0x9D  
#define BMP280_DIG_P9_LSB_REG        0x9E  
#define BMP280_DIG_P9_MSB_REG        0x9F 

#endif

