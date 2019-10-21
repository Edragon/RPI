#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>
#include "bmp280.h"

short dig_T2,dig_T3,dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;
unsigned short dig_T1,dig_P1;
int t_fine;
int fd;

/******************* BMP280 Driver Interface *****************************/
char I2C_readByte(int reg)
{	
	return (char)wiringPiI2CReadReg8(fd,reg);
}

unsigned short I2C_readU16(int reg)
{
	int MSB,LSB;
	LSB = I2C_readByte(reg);
	MSB = I2C_readByte(reg + 1);
	int value = (MSB << 8) +LSB;
	return (unsigned short)value;
}

short I2C_readS16(int reg)
{
	int result;
	result = I2C_readU16(reg);
	if (result > 32767)result -= 65536;
	return (short)result;
}
void I2C_writeByte(int reg,int val)
{
	wiringPiI2CWriteReg8(fd,reg,val);
}

/******************* BMP280 operation functions *****************************/
void load_calibration()
{
	/* read the temperature calibration parameters */  
	dig_T1 = I2C_readU16(BMP280_DIG_T1_LSB_REG);  
	dig_T2 = I2C_readS16(BMP280_DIG_T2_LSB_REG);
	dig_T3 = I2C_readS16(BMP280_DIG_T3_LSB_REG);
	
	/* read the pressure calibration parameters */   
	dig_P1 = I2C_readU16(BMP280_DIG_P1_LSB_REG);
	dig_P2 = I2C_readS16(BMP280_DIG_P2_LSB_REG);
	dig_P3 = I2C_readS16(BMP280_DIG_P3_LSB_REG);
	dig_P4 = I2C_readS16(BMP280_DIG_P4_LSB_REG);
	dig_P5 = I2C_readS16(BMP280_DIG_P5_LSB_REG);
	dig_P6 = I2C_readS16(BMP280_DIG_P6_LSB_REG);
	dig_P7 = I2C_readS16(BMP280_DIG_P7_LSB_REG);
	dig_P8 = I2C_readS16(BMP280_DIG_P8_LSB_REG);
	dig_P9 = I2C_readS16(BMP280_DIG_P9_LSB_REG);

	printf("dig_T1 = %d\r\n",dig_T1);
	printf("dig_T2 = %d\r\n",dig_T2);
	printf("dig_T3 = %d\r\n",dig_T3);
	printf("dig_P1 = %d\r\n",dig_P1);
	printf("dig_P2 = %d\r\n",dig_P2);
	printf("dig_P3 = %d\r\n",dig_P3);
	printf("dig_P4 = %d\r\n",dig_P4);
	printf("dig_P5 = %d\r\n",dig_P5);
	printf("dig_P6 = %d\r\n",dig_P6);
	printf("dig_P7 = %d\r\n",dig_P7);
	printf("dig_P8 = %d\r\n",dig_P8);
	printf("dig_P9 = %d\r\n",dig_P9);
	
}

unsigned char BSP_BMP280_Init(void)
{
	unsigned char id,ctrlmeas, config; 
	
	id = I2C_readByte(BMP280_ID_REG);  
		
	if(id == BMP280_ID_Value)
	{
		load_calibration();
		
		ctrlmeas = 0xFF; //BMP280_T_MODE_1 << 5 | BMP280_P_MODE_1 << 2 | BMP280_SLEEP_MODE;  
		config = 0x14;   //BMP280_T_SB1 << 5 | BMP280_FILTER_MODE_1 << 2; 
		
		I2C_writeByte(BMP280_CTRL_MEAS_REG, ctrlmeas); 
		I2C_writeByte(BMP280_CONFIG_REG, config);  	
		
		return 0;
	}
	else
	{
		printf("Read BMP280 id error!\r\n"); 
		return 1;
	}
}

/* Returns temperature in DegC, double precision. Output value of "1.23"equals 51.23 DegC. */  
double compensate_temperature(int adc_T)  
{  
	double var1, var2, temperature;  
	var1 = (((double) adc_T) / 16384.0 - ((double) dig_T1) / 1024.0) * ((double) dig_T2); 
	var2 = ((((double) adc_T) / 131072.0 - ((double) dig_T1) / 8192.0)  * (((double) adc_T) / 131072.0  
					- ((double) dig_T1) / 8192.0)) * ((double) dig_T3);  
	t_fine = ( int) (var1 + var2);  
	temperature = (var1 + var2) / 5120.0;  
	
	return temperature;  
}  
  
  
/* Returns pressure in Pa as double. Output value of "6386.2"equals 96386.2 Pa = 963.862 hPa */  
double compensate_pressure(int adc_P)  
{  
	double var1, var2, pressure;  

	var1 = ((double)t_fine / 2.0) - 64000.0; 
	var2 = var1 * var1 * ((double) dig_P6) / 32768.0;  
	var2 = var2 + var1 * ((double) dig_P5) * 2.0;  
	var2 = (var2 / 4.0) + (((double) dig_P4) * 65536.0);  
	var1 = (((double) dig_P3) * var1 * var1 / 524288.0  + ((double) dig_P2) * var1) / 524288.0;  
	var1 = (1.0 + var1 / 32768.0) * ((double) dig_P1);  

	if (var1 == 0.0) {  
		return 0; // avoid exception caused by division by zero  
	}  

	pressure = 1048576.0 - (double) adc_P;  
	pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;  
	var1 = ((double) dig_P9) * pressure * pressure / 2147483648.0;  
	var2 = pressure * ((double) dig_P8) / 32768.0;  
	pressure = pressure + (var1 + var2 + ((double) dig_P7)) / 16.0;  

	return pressure;  
}

/* Returns pressure in Pa as double. Output value of "6386.2"equals 96386.2 Pa = 963.862 hPa */  
void get_temperature_and_pressure(double *temperature, double *pressure)  
{  
	unsigned char lsb, msb, xlsb;  
	 int adc_P,adc_T;   

	xlsb = I2C_readByte(BMP280_TEMP_XLSB_REG);  
	lsb =  I2C_readByte(BMP280_TEMP_LSB_REG);  
	msb =  I2C_readByte(BMP280_TEMP_MSB_REG);  

	adc_T = (msb << 12) | (lsb << 4) | (xlsb >> 4); 
	//adc_T = 415148;
	* temperature = compensate_temperature(adc_T);

	xlsb = I2C_readByte(BMP280_PRESS_XLSB_REG);  
	lsb =  I2C_readByte(BMP280_PRESS_LSB_REG);  
	msb =  I2C_readByte(BMP280_PRESS_MSB_REG);  

	adc_P = (msb << 12) | (lsb << 4) | (xlsb >> 4); 
	//adc_P = 51988;
	* pressure = compensate_pressure(adc_P);     
} 

int main(int argc,char **argv)
{
	double temp,press;
	printf("BMP180 Test Program ...\n");
	if(wiringPiSetup() < 0) return 1;
	fd = wiringPiI2CSetup(BMP280_I2C_ADDRESS);
	load_calibration();
	while(1)
	{
		get_temperature_and_pressure(&temp,&press);
		printf("Temperature = %.2f C Pressure = %.3f kPa \r\n",temp,press/1000);
		delay(1000);
	}
	return 0;		
}

