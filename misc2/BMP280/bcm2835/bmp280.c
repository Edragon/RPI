#include <bcm2835.h>
#include <stdio.h>
#include <math.h>
#include "bmp280.h"

short dig_T2,dig_T3,dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;
unsigned short dig_T1,dig_P1;
int t_fine;

/******************* BMP280 Driver Interface *****************************/
char I2C_readByte(char reg)
{	
	char buf[] = {reg}; 
	bcm2835_i2c_read_register_rs(buf,buf,1);
	return buf[0];	
}

unsigned short I2C_readU16(char reg)
{
	char buf[] = {reg,0};
	bcm2835_i2c_read_register_rs(buf,buf,2);
	int value =  buf[1]*0x100+buf[0];
	return value;
}

short I2C_readS16(char reg)
{
	int result;
	result = I2C_readU16(reg);
	if (result > 32767)result -= 65536;
	return (short)result;
}

void I2C_writeByte(char reg,char val)
{
	char buf[] = {reg,val};
	bcm2835_i2c_write(buf,2);
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

/*	printf("dig_T1 = %d\r\n",dig_T1);
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
*/	
}

uint8_t BSP_BMP280_Init(void)
{
	uint8_t id,ctrlmeas, config; 
	
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
double compensate_temperature(int32_t adc_T)  
{  
	double var1, var2, temperature;  
	var1 = (((double) adc_T) / 16384.0 - ((double) dig_T1) / 1024.0) * ((double) dig_T2); 
	var2 = ((((double) adc_T) / 131072.0 - ((double) dig_T1) / 8192.0)  * (((double) adc_T) / 131072.0  
					- ((double) dig_T1) / 8192.0)) * ((double) dig_T3);  
	t_fine = (int32_t) (var1 + var2);  
	temperature = (var1 + var2) / 5120.0;  
	
	return temperature;  
}  
  
  
/* Returns pressure in Pa as double. Output value of "6386.2"equals 96386.2 Pa = 963.862 hPa */  
double compensate_pressure(int32_t adc_P)  
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
	uint8_t lsb, msb, xlsb;  
	int32_t adc_P,adc_T;   

	xlsb = I2C_readByte(BMP280_TEMP_XLSB_REG);  
	lsb =  I2C_readByte(BMP280_TEMP_LSB_REG);  
	msb =  I2C_readByte(BMP280_TEMP_MSB_REG);  

	adc_T = (msb << 12) | (lsb << 4) | (xlsb >> 4); 

	* temperature = compensate_temperature(adc_T);

	xlsb = I2C_readByte(BMP280_PRESS_XLSB_REG);  
	lsb =  I2C_readByte(BMP280_PRESS_LSB_REG);  
	msb =  I2C_readByte(BMP280_PRESS_MSB_REG);  

	adc_P = (msb << 12) | (lsb << 4) | (xlsb >> 4); 
	
	* pressure = compensate_pressure(adc_P);     
} 

int main(int argc,char **argv)
{
	double temp,press;
	printf("\nBMP180 Test Program ...\n");
	if(!bcm2835_init()) return 1;
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(BMP280_I2C_ADDRESS);
	bcm2835_i2c_set_baudrate(10000);
	BSP_BMP280_Init();
	get_temperature_and_pressure(&temp,&press);
	while(1)
	{
		bcm2835_delay(1000);
		get_temperature_and_pressure(&temp,&press);
		printf("Temperature = %.2f C Pressure = %.3f kPa \r\n",temp,press/1000);
	}
	printf("\n");
	return 0;		
}

