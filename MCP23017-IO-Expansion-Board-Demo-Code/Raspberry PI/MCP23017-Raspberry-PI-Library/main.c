#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "mymcp23017.h"



//Change this Macro definition to test differrnt demo
#define debug 0
#define outputTest 0
#define inputTest 0

//For interruptTest,you need connect PA7 and PB7 to a button(when the button pressed,it connect to GND)
#define interruptTest 1

void myInterruptService()
{
    printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\r\n");
    printf("the key has been pressed!!!\r\n");
    printf("the last interrupt Pin is: %d\r\n",mcp_getLastInterruptPin());
    printf("the last interrupt value is: %d\r\n",mcp_getLastInterruptPinValue());
    printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\r\n");
}


int main(int argc, char**argv)
{
    //init the wiring Pins
    if(wiringPiSetup()<0)
    {
        printf("wiringPiSetup error!!!");
        return -1;
    }
    
    /*the param can be 0 to 7,the default param is 7.means the dafault device address 0x27.
    Addr(BIN)  Addr(hex)   param
    010 0111    0x27        7
    010 0110    0x26        6
    010 0101    0x25        5
    010 0100    0x24        4
    010 0011    0x23        3
    010 0010    0x22        2
    010 0001    0x21        1
    010 0000    0x20        0
    init the i2caddr*/
	mcp_begin(7);
    
    //init the fd
    fd = wiringPiI2CSetup(MCP23017_ADDRESS | i2caddr);
    if(fd <0)
    {
        printf("wiringPiI2CSetup error!!!");
        return -1;
    }
    
    //init the MCP23017 Register
    mcp_initReg();
    
    //Configure pin 0 as an interrupt function
    pinMode(0,INPUT);
    pullUpDnControl(0,PUD_UP);
    if(wiringPiISR(0,INT_EDGE_FALLING,&myInterruptService)<0)
    {
        printf("unable to ISR\r\n");
    }
    
    //According to the macro to test different demo
	while(1)
    {
        delay(500);
        
        #if(debug)
        for(int addr = 0; addr< 22; addr++)
        {
            printf("addr:0x%02x,value:0x%02x\r\n",addr,mcp_readRegister(addr));
        }
        printf("------------------------------------------\r\n");
        #endif
        
        #if(outputTest)
        for(int i = 0; i<16; i++)
        {
            mcp_pinMode(i, 0);
        }
        
        for(int i = 0; i<16; i++)
        {
            mcp_digitalWrite(i,1);
        }
        
        delay(500);
        
        for(int i = 0; i<16; i++)
        {
            mcp_digitalWrite(i,0);
        }
        #endif
        
        #if(inputTest)
        //Pin0 Output
        mcp_pinMode(0, 0);
        //Pin1 Input
        mcp_pinMode(1, 1);
        //Pin1 Pullup
        mcp_pullUp(1,1);
        //Read the PA1 value and write to PA0
        mcp_digitalWrite(0, mcp_digitalRead(1));
        #endif
        
        #if(interruptTest)
        //mirroring, don't openDrain, INT output pin will be low when interrupt occur
        mcp_setupInterrupts(1,0,0);
        
        //input
        mcp_pinMode(7,1);
        //pullup
        mcp_pullUp(7,1);
        //1 means compare against given value,and 1 means when differ from 1 occur the interrupt
        mcp_setupInterruptPin(7,1);
        
        //input
        mcp_pinMode(15,1);
        //pullup
        mcp_pullUp(15,1);
        //1 means compare against given value,and 1 means when differ from 1 occur the interrupt
        mcp_setupInterruptPin(15,1);
        #endif
    }
	return 0;
}
