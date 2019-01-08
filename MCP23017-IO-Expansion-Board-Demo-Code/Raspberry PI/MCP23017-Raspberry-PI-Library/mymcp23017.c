#include "mymcp23017.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>


#define  bitSet(value, bit)   ((value) |= (1UL << (bit))) 
#define  bitClear(value, bit)   ((value) &= ~(1UL << (bit))) 
#define  bitWrite(value, bit, bitvalue)   (bitvalue ? bitSet(value, bit) : bitClear(value, bit)) 
#define  bitRead(value, bit)   (((value) >> (bit)) & 0x01) 



uint8_t i2caddr;
int fd;

/**
 * Bit number associated to a give Pin
 */
uint8_t mcp_bitForPin(uint8_t pin){
	return pin%8;
}

/**
 * Register address, port dependent, for a given PIN
 */
uint8_t mcp_regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr){
	return(pin<8) ?portAaddr:portBaddr;
}


/**
 * Reads a given register
 */
uint8_t mcp_readRegister(uint8_t regAddr){

	return wiringPiI2CReadReg8(fd, regAddr);
	
}


/**
 * Writes a given register
 */
void mcp_writeRegister(uint8_t regAddr, uint8_t regValue){

    wiringPiI2CWriteReg8(fd, regAddr, regValue);
	
}


/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void mcp_updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr) {
	uint8_t regValue;
	uint8_t regAddr=mcp_regForPin(pin,portAaddr,portBaddr);
	uint8_t bit=mcp_bitForPin(pin);
	regValue = mcp_readRegister(regAddr);

	// set the value for the particular bit
	bitWrite(regValue,bit,pValue);

	mcp_writeRegister(regAddr,regValue);
}

////////////////////////////////////////////////////////////////////////////////

/**
 * Initializes the MCP23017 given its HW selected address, see datasheet for Address selection.
 */
void mcp_begin(uint8_t addr) {
	if (addr > 7) {
		addr = 7;
	}
    
	i2caddr = addr;
}


/**
* This init the reg value, change the value to the default
*/
void mcp_initReg(void){
    // set defaults!
	// all inputs on port A and B
    for(int addr = 0; addr< 22; addr++)
    {
        if((addr==0)||(addr==1))
        {
            wiringPiI2CWriteReg8(fd,addr, 0xff);
        }
        else
        {
            wiringPiI2CWriteReg8(fd,addr,0x00);
        }
    }
}



/**
 * Sets the pin mode to either INPUT or OUTPUT
 * 0 means output, 1 means input
 */
void mcp_pinMode(uint8_t p, uint8_t d) {
	mcp_updateRegisterBit(p,d,MCP23017_IODIRA,MCP23017_IODIRB);
}



/**
 * Reads all 16 pins (port A and B) into a single 16 bits variable.
 */
uint16_t mcp_readGPIOAB(void) {
	uint16_t ba = 0;
	uint8_t a;
    
	// read the current GPIO output latches
    
    uint8_t reg_data[2];
	
	reg_data[0] = wiringPiI2CReadReg8(fd,MCP23017_GPIOA);
	//theoretically, the register addr is MCP23017_GPIOA is also OK!
	reg_data[1] = wiringPiI2CReadReg8(fd,MCP23017_GPIOB);
    
    a = reg_data[0];
    ba = reg_data[1];
    
	ba <<= 8;
	ba |= a;

	return ba;
}



/**
 * Read a single port, A or B, and return its current 8 bit value.
 * Parameter b should be 0 for GPIOA, and 1 for GPIOB.
 */
uint8_t mcp_readGPIO(uint8_t b) {

	// read the current GPIO output latches
    uint8_t reg_data;
    if(b == 0)
    {
        reg_data = wiringPiI2CReadReg8(fd,MCP23017_GPIOA);
    }
    else
    {
        reg_data = wiringPiI2CReadReg8(fd,MCP23017_GPIOB);
    }
	return reg_data;
}


/**
 * Writes all the pins in one go. This method is very useful if you are implementing a multiplexed matrix and want to get a decent refresh rate.
 */
void mcp_writeGPIOAB(uint16_t ba) {
    
    uint8_t reg_data[2] = {ba &0xFF, ba>>8};
	
	wiringPiI2CWriteReg8(fd, MCP23017_GPIOA, reg_data[0]);
	//theoretically, the register addr is MCP23017_GPIOA is also OK!
	wiringPiI2CWriteReg8(fd, MCP23017_GPIOB, reg_data[1]);
    
}


void mcp_digitalWrite(uint8_t pin, uint8_t d) {
	uint8_t gpio;
	uint8_t bit=mcp_bitForPin(pin);


	// read the current GPIO output latches
	uint8_t regAddr=mcp_regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
	gpio = mcp_readRegister(regAddr);

	// set the pin and direction
	bitWrite(gpio,bit,d);

	// write the new GPIO
	regAddr=mcp_regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	mcp_writeRegister(regAddr,gpio);
}



void mcp_pullUp(uint8_t p, uint8_t d) {
	mcp_updateRegisterBit(p,d,MCP23017_GPPUA,MCP23017_GPPUB);
}



uint8_t mcp_digitalRead(uint8_t pin) {
	uint8_t bit=mcp_bitForPin(pin);
	uint8_t regAddr=mcp_regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	return (mcp_readRegister(regAddr) >> bit) & 0x1;
}

/**
 * Configures the interrupt system. both port A and B are assigned the same configuration.
 * Mirroring will OR both INTA and INTB pins.
 * Opendrain will set the INT pin to value or open drain.
 * polarity will set LOW or HIGH on interrupt.
 * Default values after Power On Reset are: (false, false, LOW)
 * If you are connecting the INTA/B pin to arduino 2/3, you should configure the interupt handling as FALLING with
 * the default configuration.
 */
void mcp_setupInterrupts(uint8_t mirroring, uint8_t openDrain, uint8_t polarity){
	// configure the port A
	uint8_t ioconfValue=mcp_readRegister(MCP23017_IOCONA);
	bitWrite(ioconfValue,6,mirroring);
	bitWrite(ioconfValue,2,openDrain);
	bitWrite(ioconfValue,1,polarity);
	mcp_writeRegister(MCP23017_IOCONA,ioconfValue);

	// Configure the port B
	ioconfValue=mcp_readRegister(MCP23017_IOCONB);
	bitWrite(ioconfValue,6,mirroring);
	bitWrite(ioconfValue,2,openDrain);
	bitWrite(ioconfValue,1,polarity);
	mcp_writeRegister(MCP23017_IOCONB,ioconfValue);
}

/**
 * Set's up a pin for interrupt. uses arduino MODEs: CHANGE, FALLING, RISING.
 *
 * Note that the interrupt condition finishes when you read the information about the port / value
 * that caused the interrupt or you read the port itself. Check the datasheet can be confusing.
 *
 */
void mcp_setupInterruptPin(uint8_t pin, uint8_t mode) {

	// set the pin interrupt control (0 means change, 1 means compare against given value);
	mcp_updateRegisterBit(pin,mode,MCP23017_INTCONA,MCP23017_INTCONB);
	// if the mode is not CHANGE, we need to set up a default value, different value triggers interrupt

	// In a RISING interrupt the default value is 0, interrupt is triggered when the pin goes to 1.
	// In a FALLING interrupt the default value is 1, interrupt is triggered when pin goes to 0.
	mcp_updateRegisterBit(pin,mode,MCP23017_DEFVALA,MCP23017_DEFVALB);

	// enable the pin for interrupt
	mcp_updateRegisterBit(pin,1,MCP23017_GPINTENA,MCP23017_GPINTENB);

}

uint8_t mcp_getLastInterruptPin(void){
	uint8_t intf;

	// try port A
	intf=mcp_readRegister(MCP23017_INTFA);
	for(int i=0;i<8;i++) 
    {
        if (bitRead(intf,i))
        {
            return i;
        }
    }

	// try port B
	intf=mcp_readRegister(MCP23017_INTFB);
	for(int i=0;i<8;i++) 
    {
        if (bitRead(intf,i)) 
        {
            return i+8;
        }
    }

	return MCP23017_INT_ERR;

}

uint8_t mcp_getLastInterruptPinValue(void){
	uint8_t intPin=mcp_getLastInterruptPin();
	if(intPin!=MCP23017_INT_ERR){
		uint8_t intcapreg=mcp_regForPin(intPin,MCP23017_INTCAPA,MCP23017_INTCAPB);
		uint8_t bit=mcp_bitForPin(intPin);
		return (mcp_readRegister(intcapreg)>>bit) & (0x01);
	}

	return MCP23017_INT_ERR;
}
