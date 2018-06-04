// IRM 
// After installing bcm2835, you can build this
// with something like:
// gcc -Wall IRM.c -o IRM -lbcm2835
// sudo ./IRM
#include <bcm2835.h>
#include <stdio.h>
#define PIN 18
#define IO bcm2835_gpio_lev(PIN)
unsigned char i,idx,cnt;
unsigned char count;
unsigned char data[4];

int main(int argc, char **argv)
{
    if (!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
	printf("IRM Test Program ... \n");

	while (1)
	{	
		if(IO == 0)
		{
			count = 0;
			while(IO == 0 && count++ < 200)   //9ms
		    	delayMicroseconds(60);
			
			count = 0;
			while(IO == 1 && count++ < 80)	  //4.5ms
		    	delayMicroseconds(60);
			
			idx = 0;
			cnt = 0;
			data[0]=0;
			data[1]=0;
			data[2]=0;
			data[3]=0;
			for(i =0;i<32;i++)
			{
				count = 0;
				while(IO == 0 && count++ < 15)  //0.56ms
		    		delayMicroseconds(60);
				
				count = 0;
				while(IO == 1 && count++ < 40)  //0: 0.56ms; 1: 1.69ms
		    		delayMicroseconds(60);

				if (count > 25)data[idx] |= (1<<cnt);
				if(cnt == 7)
				{
					cnt = 0;
					idx++;
				}
				else cnt++;
			}

			if(data[0]+data[1] == 0xFF && data[2]+data[3]==0xFF)	//check	
				printf("Get the key: 0x%02x\n",data[2]);
		}
	}
    bcm2835_close();
    return 0;

}
