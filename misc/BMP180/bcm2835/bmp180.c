#include <bcm2835.h>
#include <stdio.h>
#include <math.h>
#include "bmp180.h"

#define OSS BMP180_STANDARD
short AC1,AC2,AC3,B1,B2,MB,MC,MD;
unsigned short AC4,AC5,AC6;

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
	int value =  buf[0]*0x100+buf[1];
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

void load_calibration()
{
	AC1 = I2C_readS16(BMP180_CAL_AC1);
	AC2 = I2C_readS16(BMP180_CAL_AC2);
	AC3 = I2C_readS16(BMP180_CAL_AC3);
	AC4 = I2C_readU16(BMP180_CAL_AC4);
	AC5 = I2C_readU16(BMP180_CAL_AC5);
	AC6 = I2C_readU16(BMP180_CAL_AC6);
	B1  = I2C_readS16(BMP180_CAL_B1);
	B2  = I2C_readS16(BMP180_CAL_B2);
	MB  = I2C_readS16(BMP180_CAL_MB);
	MC  = I2C_readS16(BMP180_CAL_MC);
    MD  = I2C_readS16(BMP180_CAL_MD);
}

int read_raw_temp()
{
	int raw;
	I2C_writeByte(BMP180_CONTROL,BMP180_READTEMPCMD);
	bcm2835_delay(5); //5ms
	raw = I2C_readByte(BMP180_TEMPDATA) << 8;
 	raw += I2C_readByte(BMP180_TEMPDATA+1);
	return raw;
}

int read_raw_pressure()
{
	int MSB,LSB,XLSB,raw;
	I2C_writeByte(BMP180_CONTROL,BMP180_READPRESSURECMD +(OSS << 6));
	switch(OSS)
	{
		case BMP180_ULTRALOWPOWER:
			bcm2835_delay(5);break;
		case BMP180_HIGHRES:
			bcm2835_delay(14);break;
		case BMP180_ULTRAHIGHRES:
			bcm2835_delay(26);break;
		default :
			bcm2835_delay(8);
	}
	MSB  = I2C_readByte(BMP180_PRESSUREDATA);
	LSB  = I2C_readByte(BMP180_PRESSUREDATA + 1);
	XLSB = I2C_readByte(BMP180_PRESSUREDATA + 2);
	raw = ((MSB << 16) + (LSB << 8) + XLSB) >> (8 - OSS);
	return raw;
}
float read_temperature()
{
	float T;
	int UT,X1,X2,B5;
	UT = read_raw_temp();
	X1 = ((UT - AC6)*AC5) >> 15;
	X2 = (MC << 11) / (X1 + MD);
  	B5 = X1 + X2;
  	T = ((B5 + 8) >> 4) /10.0;
	return T;
}
      
int read_pressure()
{
	int P;
	int UT,UP,X1,X2,X3,B3,B5,B6;
	unsigned int B4;
	int B7;
	UT = read_raw_temp();
	UP = read_raw_pressure();
	
	X1 = ((UT - AC6)*AC5) >> 15;
 	X2 = (MC << 11) / (X1 + MD);
	B5 = X1 + X2;
	
	//Pressure Calculations
	B6 = B5 - 4000;
	X1 = (B2 * (B6 * B6) >> 12) >> 11;
	X2 = (AC2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = (((AC1 * 4 + X3) << OSS) + 2) / 4;
	X1 = (AC3 * B6) >> 13;
	X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = (AC4 * (X3 + 32768)) >> 15;
	B7 = (UP - B3) * (50000 >> OSS);
	if (B7 < 0x80000000){P = (B7 * 2) / B4;}
	else {P = (B7 / B4) * 2;}
    X1 = (P >> 8) * (P >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * P) >> 16;
    P = P + ((X1 + X2 + 3791) >> 4);
    return P;

}
float read_altitude()
{
	float pressure,altitude;
	float sealevel_pa = 101325.0;
	pressure = (float)read_pressure();
	altitude = 44330.0 * (1.0 - pow(pressure / sealevel_pa,(1.0/5.255)));
	return altitude;
}
float read_sealevel_pressure()
{
	float altitude_m = 0.0;
	float pressure,p0;
	pressure =(float)read_pressure();
	p0 = pressure / pow(1.0 - altitude_m/44330.0,5.255);
	return p0;
}
int main(int argc,char **argv)
{
	printf("BMP180 Test Program ...\n");
	if(!bcm2835_init()) return 1;
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(BMP180_Address);
	bcm2835_i2c_set_baudrate(10000);
	load_calibration();
	while(1)
	{
		printf("\nTemperature : %.2f C\n",read_temperature());
		printf("Pressure :    %.2f Pa\n",read_pressure()/100.0);
	 	printf("Altitude :    %.2f h\n",read_altitude());
		bcm2835_delay(1000);
	}
	return 0;		
}

