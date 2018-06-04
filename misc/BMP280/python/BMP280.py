import time
import smbus

# BMP280 address.
BMP280_I2C_ADDRESS       =    0x76          #SDO = 0

#Registers  value
BMP280_ID_Value          =    0x58
BMP280_RESET_VALUE       =    0xB6

# BMP280 Registers definition  
BMP280_TEMP_XLSB_REG     =    0xFC		  #Temperature XLSB Register 
BMP280_TEMP_LSB_REG      =    0xFB         #Temperature LSB Register  
BMP280_TEMP_MSB_REG      =    0xFA         #Temperature LSB Register   
BMP280_PRESS_XLSB_REG    =    0xF9		  #Pressure XLSB  Register 
BMP280_PRESS_LSB_REG     =    0xF8		  #Pressure LSB Register 
BMP280_PRESS_MSB_REG     =    0xF7		  #Pressure MSB Register 						
BMP280_CONFIG_REG        =    0xF5         #Configuration Register 
BMP280_CTRL_MEAS_REG     =    0xF4         #Ctrl Measure Register  
BMP280_STATUS_REG        =    0xF3         #Status Register 
BMP280_RESET_REG         =    0xE0		  #Softreset Register  
BMP280_ID_REG            =    0xD0         #Chip ID Register 

#calibration parameters   
BMP280_DIG_T1_LSB_REG    =    0x88  
BMP280_DIG_T1_MSB_REG    =    0x89  
BMP280_DIG_T2_LSB_REG    =    0x8A  
BMP280_DIG_T2_MSB_REG    =    0x8B  
BMP280_DIG_T3_LSB_REG    =    0x8C  
BMP280_DIG_T3_MSB_REG    =    0x8D  
BMP280_DIG_P1_LSB_REG    =    0x8E  
BMP280_DIG_P1_MSB_REG    =    0x8F  
BMP280_DIG_P2_LSB_REG    =    0x90  
BMP280_DIG_P2_MSB_REG    =    0x91  
BMP280_DIG_P3_LSB_REG    =    0x92  
BMP280_DIG_P3_MSB_REG    =    0x93  
BMP280_DIG_P4_LSB_REG    =    0x94  
BMP280_DIG_P4_MSB_REG    =    0x95  
BMP280_DIG_P5_LSB_REG    =    0x96  
BMP280_DIG_P5_MSB_REG    =    0x97  
BMP280_DIG_P6_LSB_REG    =    0x98  
BMP280_DIG_P6_MSB_REG    =    0x99  
BMP280_DIG_P7_LSB_REG    =    0x9A  
BMP280_DIG_P7_MSB_REG    =    0x9B  
BMP280_DIG_P8_LSB_REG    =    0x9C  
BMP280_DIG_P8_MSB_REG    =    0x9D  
BMP280_DIG_P9_LSB_REG    =    0x9E  
BMP280_DIG_P9_MSB_REG    =    0x9F 


class BMP180(object):
	def __init__(self, address=BMP280_I2C_ADDRESS):
		self._address = address
		self._bus = smbus.SMBus(1)
		# Load calibration values.
		if self._read_byte(BMP280_ID_REG) == BMP280_ID_Value:
			self._load_calibration()
			ctrlmeas = 0xFF #BMP280_T_MODE_1 << 5 | BMP280_P_MODE_1 << 2 | BMP280_SLEEP_MODE;  
			config = 0x14   #BMP280_T_SB1 << 5 | BMP280_FILTER_MODE_1 << 2;
			self._write_byte(BMP280_CTRL_MEAS_REG, ctrlmeas); 
			self._write_byte(BMP280_CONFIG_REG, config)
		else:
			print("Read BMP280 id error!\r\n")
	def _read_byte(self,cmd):
		return self._bus.read_byte_data(self._address,cmd)
	
	def _read_u16(self,cmd):
		LSB = self._bus.read_byte_data(self._address,cmd)
		MSB = self._bus.read_byte_data(self._address,cmd+1)
		return (MSB	<< 8) + LSB

	def _read_s16(self,cmd):
		result = self._read_u16(cmd)
		if result > 32767:result -= 65536
		return result

	def _write_byte(self,cmd,val):
		self._bus.write_byte_data(self._address,cmd,val)

	def _load_calibration(self):
		"load calibration"
		
		""" read the temperature calibration parameters """
		self.dig_T1 =self._read_u16(BMP280_DIG_T1_LSB_REG)
		self.dig_T2 =self._read_s16(BMP280_DIG_T2_LSB_REG)
		self.dig_T3 =self._read_s16(BMP280_DIG_T3_LSB_REG)
		""" read the pressure calibration parameters """
		self.dig_P1 =self._read_u16(BMP280_DIG_P1_LSB_REG)
		self.dig_P2 =self._read_s16(BMP280_DIG_P2_LSB_REG)
		self.dig_P3 =self._read_s16(BMP280_DIG_P3_LSB_REG)
		self.dig_P4 =self._read_s16(BMP280_DIG_P4_LSB_REG)
		self.dig_P5 =self._read_s16(BMP280_DIG_P5_LSB_REG)
		self.dig_P6 =self._read_s16(BMP280_DIG_P6_LSB_REG)
		self.dig_P7 =self._read_s16(BMP280_DIG_P7_LSB_REG)
		self.dig_P8 =self._read_s16(BMP280_DIG_P8_LSB_REG)
		self.dig_P9 =self._read_s16(BMP280_DIG_P9_LSB_REG)
		
		# print(self.dig_T1)
		# print(self.dig_T2)
		# print(self.dig_T3)
		# print(self.dig_P1)
		# print(self.dig_P2)
		# print(self.dig_P3)
		# print(self.dig_P4)
		# print(self.dig_P5)
		# print(self.dig_P6)
		# print(self.dig_P7)
		# print(self.dig_P8)
		# print(self.dig_P9)
		
	def compensate_temperature(self,adc_T):
		"""Returns temperature in DegC, double precision. Output value of "1.23"equals 51.23 DegC."""
		var1 = ((adc_T) / 16384.0 - (self.dig_T1) / 1024.0) * (self.dig_T2)
		var2 = (((adc_T) / 131072.0 - (self.dig_T1) / 8192.0)  * ((adc_T) / 131072.0  - (self.dig_T1) / 8192.0)) * (self.dig_T3)
		self.t_fine = var1 + var2
		temperature = (var1 + var2) / 5120.0
		return temperature
			
	def compensate_pressure(self,adc_P):
		"""Returns pressure in Pa as double. Output value of "6386.2"equals 96386.2 Pa = 963.862 hPa."""
		var1 = (self.t_fine / 2.0) - 64000.0
		var2 = var1 * var1 * (self.dig_P6) / 32768.0
		var2 = var2 + var1 * (self.dig_P5) * 2.0
		var2 = (var2 / 4.0) + ((self.dig_P4) * 65536.0) 
		var1 = ((self.dig_P3) * var1 * var1 / 524288.0  + (self.dig_P2) * var1) / 524288.0 
		var1 = (1.0 + var1 / 32768.0) * (self.dig_P1) 

		if var1 == 0.0: 
			return 0 # avoid exception caused by division by zero  

		pressure = 1048576.0 - adc_P
		pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1
		var1 = (self.dig_P9) * pressure * pressure / 2147483648.0
		var2 = pressure * (self.dig_P8) / 32768.0  
		pressure = pressure + (var1 + var2 + (self.dig_P7)) / 16.0

		return pressure; 

	def get_temperature_and_pressure(self):
		"""Returns pressure in Pa as double. Output value of "6386.2"equals 96386.2 Pa = 963.862 hPa."""
		xlsb = self._read_byte(BMP280_TEMP_XLSB_REG)
		lsb =  self._read_byte(BMP280_TEMP_LSB_REG)
		msb =  self._read_byte(BMP280_TEMP_MSB_REG)

		adc_T = (msb << 12) | (lsb << 4) | (xlsb >> 4)
		temperature = self.compensate_temperature(adc_T)

		xlsb = self._read_byte(BMP280_PRESS_XLSB_REG)
		lsb =  self._read_byte(BMP280_PRESS_LSB_REG) 
		msb =  self._read_byte(BMP280_PRESS_MSB_REG) 

		adc_P = (msb << 12) | (lsb << 4) | (xlsb >> 4)
		pressure = self.compensate_pressure(adc_P)
		return temperature,pressure
	
if __name__ == '__main__':

	import time
	
	print("BMP280 Test Program ...\n")
	
	bmp280 = BMP180()
				
	while True:
		time.sleep(1)
		temperature,pressure = bmp280.get_temperature_and_pressure()
		print(' Temperature = %.2f C Pressure = %.3f kPa'%(temperature,pressure/1000))
