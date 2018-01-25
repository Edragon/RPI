#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H		

#include "DEV_Config.h"

#define	COLOR				uint16_t		//The variable type of the color (unsigned short) 
#define	POINT				uint16_t		//The type of coordinate (unsigned short) 
#define	LENGTH				uint16_t		//The type of coordinate (unsigned short) 

/********************************************************************************
function:	
		Define the full screen height length of the display
********************************************************************************/
#define OLED_X_MAXPIXEL  132  //OLED width maximum memory 
#define OLED_Y_MAXPIXEL  64 //OLED height maximum memory
#define OLED_X	 2
#define OLED_Y	 0

#define OLED_WIDTH  (OLED_X_MAXPIXEL - 2 * OLED_X)  //OLED width
#define OLED_HEIGHT  OLED_Y_MAXPIXEL //OLED height

char Buffer[OLED_WIDTH * OLED_HEIGHT / 8];

/********************************************************************************
function:	
			scanning method
********************************************************************************/
typedef enum{
	L2R_U2D  = 0,	//The display interface is displayed , left to right, up to down 
	L2R_D2U  ,
	R2L_U2D  ,
	R2L_D2U  ,
	
	U2D_L2R  ,
	U2D_R2L  ,
	D2U_L2R  ,
	D2U_R2L  , 
}OLED_SCAN_DIR;
#define SCAN_DIR_DFT  L2R_U2D  //Default scan direction = L2R_U2D

/********************************************************************************
function:	
	Defines the total number of rows in the display area
********************************************************************************/
typedef struct{
	LENGTH OLED_Dis_Column;	//COLUMN
	LENGTH OLED_Dis_Page;	//PAGE
	OLED_SCAN_DIR OLED_Scan_Dir;
	POINT OLED_X_Adjust;		//OLED x actual display position calibration
	POINT OLED_Y_Adjust;		//OLED y actual display position calibration
}OLED_DIS;
OLED_DIS sOLED_DIS;

/********************************************************************************
function:	
			Macro definition variable name
********************************************************************************/
void OLED_Init( OLED_SCAN_DIR OLED_ScanDir);
void OLED_SetGramScanWay(OLED_SCAN_DIR Scan_dir);

//OLED set cursor + windows + color
void OLED_SetCursor(POINT Xpoint, POINT Ypoint);
void OLED_SetColor(POINT Xpoint, POINT Ypoint, COLOR Color);
void OLED_Clear(COLOR  Color);
void OLED_Display(void);
#endif  
	 
	 



