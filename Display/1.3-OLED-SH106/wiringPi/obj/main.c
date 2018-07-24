#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()

#include "OLED_Driver.h"
#include "OLED_GUI.h"
#include "DEV_Config.h"
#include <time.h>

char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int main(void)
{
	time_t now;
    struct tm *timenow;
	//1.System Initialization
	if(System_Init())
		exit(0);
	
	//2.show
	printf("**********Init OLED**********\r\n");
	OLED_SCAN_DIR OLED_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
	OLED_Init(OLED_ScanDir );	
	
	printf("OLED Show \r\n");
	GUI_Show();
	
	while(1){
		time(&now);
		timenow = localtime(&now);
	
		GUI_Disbitmap(0, 2, Signal816, 16, 8);
		GUI_Disbitmap(24, 2, Bluetooth88, 8, 8);
		GUI_Disbitmap(40, 2, Msg816, 16, 8);
		GUI_Disbitmap(64, 2, GPRS88, 8, 8);
		GUI_Disbitmap(90, 2, Alarm88, 8, 8);
		GUI_Disbitmap(112, 2, Bat816, 16, 8);
		
		GUI_DisString_EN(0, 52, "MUSIC", &Font12, FONT_BACKGROUND, WHITE); 
		GUI_DisString_EN(52, 52, "MENU", &Font12, FONT_BACKGROUND, WHITE); 
		GUI_DisString_EN(98, 52, "PHONE", &Font12, FONT_BACKGROUND, WHITE);

		GUI_DisChar(0, 16, value[timenow->tm_hour / 10], &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(16, 16, value[timenow->tm_hour % 10], &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(32, 16, ':', &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(48, 16, value[timenow->tm_min / 10],  &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(64, 16, value[timenow->tm_min % 10],  &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(80, 16, ':',  &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(96, 16, value[timenow->tm_sec / 10],  &Font24, FONT_BACKGROUND, WHITE);
		GUI_DisChar(112, 16, value[timenow->tm_sec % 10],  &Font24, FONT_BACKGROUND, WHITE);
		
		OLED_Display();		
		OLED_Clear(0x00);
	}
	
	//3.System Exit
	System_Exit();
	return 0;
	
}

