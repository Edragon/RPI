
/***********************************************************************************************************************
* | file      	:	OLED_Driver.c
* |	version		:	V1.0
* | date		:	2017-11-09
* | function	:	On the ST7735S chip driver and clear screen, drawing lines, drawing, writing
					and other functions to achieve

Image scanning:
Please use progressive scanning to generate images or fonts
***********************************************************************************************************************/
#include "OLED_Driver.h"
#include <stdio.h>
extern OLED_DIS sOLED_DIS;
/***********************************************************************************************************************
			------------------------------------------------------------------------
			|\\\																///|
			|\\\						Drive layer								///|
			------------------------------------------------------------------------
***********************************************************************************************************************/
/*******************************************************************************
function:
			Hardware reset
*******************************************************************************/
static void OLED_Reset(void)
{
    OLED_RST_1;
    Driver_Delay_ms(100);
    OLED_RST_0;
    Driver_Delay_ms(100);
    OLED_RST_1;
    Driver_Delay_ms(100);
}

/*******************************************************************************
function:
		Write register address and data
*******************************************************************************/
static void OLED_WriteReg(uint8_t Reg)
{
#if USE_SPI
    OLED_DC_0;
    SPI_Write_Byte(Reg);
#elif USE_IIC
    I2C_Write_Byte(Reg,IIC_CMD);
#endif
}

static void OLED_WriteData_nLen8Bit(uint8_t *pBuf, uint32_t Len)
{
    int i;
#if USE_SPI
    OLED_DC_1;
    for(i = 0; i < Len; i++) {
        SPI_Write_Byte(*pBuf);
        pBuf++;
    }
#elif USE_IIC
    for(i = 0; i < Len; i++) {
        I2C_Write_Byte(*pBuf,IIC_RAM);
        pBuf++;
    }

#endif

}

/*******************************************************************************
function:
		Common register initialization
*******************************************************************************/
static void OLED_InitReg(void)
{
    OLED_WriteReg(0xAE);//--turn off oled panel
    OLED_WriteReg(0x02);//---set low column address
    OLED_WriteReg(0x10);//---set high column address
    OLED_WriteReg(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WriteReg(0x81);//--set contrast control register
    OLED_WriteReg(0xA0);//--Set SEG/Column Mapping
    OLED_WriteReg(0xC0);//Set COM/Row Scan Direction
    OLED_WriteReg(0xA6);//--set normal display
    OLED_WriteReg(0xA8);//--set multiplex ratio(1 to 64)
    OLED_WriteReg(0x3F);//--1/64 duty
    OLED_WriteReg(0xD3);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WriteReg(0x00);//-not offset
    OLED_WriteReg(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WriteReg(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WriteReg(0xD9);//--set pre-charge period
    OLED_WriteReg(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WriteReg(0xDA);//--set com pins hardware configuration
    OLED_WriteReg(0x12);
    OLED_WriteReg(0xDB);//--set vcomh
    OLED_WriteReg(0x40);//Set VCOM Deselect Level
    OLED_WriteReg(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WriteReg(0x02);//
    OLED_WriteReg(0xA4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WriteReg(0xA6);// Disable Inverse Display On (0xa6/a7)

}

/********************************************************************************
function:	Set the display scan and color transfer modes
parameter:
		Scan_dir   :   Scan direction
		Colorchose :   RGB or GBR color format
********************************************************************************/
void OLED_SetGramScanWay(OLED_SCAN_DIR Scan_dir)
{
    //Get the screen scan direction
    sOLED_DIS.OLED_Scan_Dir = Scan_dir;

    //Get GRAM and OLED width and height
    if(Scan_dir == L2R_U2D || Scan_dir == L2R_D2U || Scan_dir == R2L_U2D || Scan_dir == R2L_D2U) {
        sOLED_DIS.OLED_Dis_Column	= OLED_WIDTH ;
        sOLED_DIS.OLED_Dis_Page = OLED_HEIGHT ;
        sOLED_DIS.OLED_X_Adjust = OLED_X;
        sOLED_DIS.OLED_Y_Adjust = OLED_Y;
    } else {
        sOLED_DIS.OLED_Dis_Column	= OLED_HEIGHT ;
        sOLED_DIS.OLED_Dis_Page = OLED_WIDTH ;
        sOLED_DIS.OLED_X_Adjust = OLED_Y;
        sOLED_DIS.OLED_Y_Adjust = OLED_X;
    }
}

/********************************************************************************
function:
			initialization
********************************************************************************/
void OLED_Init(OLED_SCAN_DIR OLED_ScanDir)
{
    //Hardware reset
    OLED_Reset();

    //Set the initialization register
    OLED_InitReg();

    //Set the display scan and color transfer modes
    OLED_SetGramScanWay(OLED_ScanDir );
    Driver_Delay_ms(200);

    //Turn on the OLED display
    OLED_WriteReg(0xAF);
}

/********************************************************************************
function:	Set the display point(Xpoint, Ypoint)
parameter:
		xStart :   X direction Start coordinates
		xEnd   :   X direction end coordinates
********************************************************************************/
void OLED_SetCursor(POINT Xpoint, POINT Ypoint)
{
    if((Xpoint > sOLED_DIS.OLED_Dis_Column) || (Ypoint > sOLED_DIS.OLED_Dis_Page))
        return;

    /* set page address */
    OLED_WriteReg(0xB0 + (Ypoint / 8));
    /* set low column address */
    OLED_WriteReg((Xpoint & 0x0f) + sOLED_DIS.OLED_X_Adjust);
    /* set high column address */
    OLED_WriteReg((Xpoint >> 4) + 0x10);
}

/********************************************************************************
function:	Set show color
parameter:
		Color  :   Set show color
********************************************************************************/
//static void OLED_SetColor(LENGTH Dis_Width, LENGTH Dis_Height, COLOR Color ){
void OLED_SetColor(POINT Xpoint, POINT Ypoint, COLOR Color)
{
    if(Xpoint < 0 || Xpoint >= sOLED_DIS.OLED_Dis_Column ||
       Ypoint < 0 || Ypoint >= sOLED_DIS.OLED_Dis_Page) {
        return;
    }
    //Transform line by line into column line
    if (Color) {
        Buffer[(Xpoint + (Ypoint / 8) * sOLED_DIS.OLED_Dis_Column)] |= 1 << (Ypoint % 8);
    } else {
        Buffer[(Xpoint + (Ypoint / 8) * sOLED_DIS.OLED_Dis_Column)] |= 0 << (Ypoint % 8);
    }
}
/********************************************************************************
function:
			Clear screen
********************************************************************************/
void OLED_Clear(COLOR Color)
{
    int i;
    for(i = 0; i < sizeof(Buffer); i++) {
        Buffer[i] = Color;
    }
}

/********************************************************************************
function:	Update memory to LCD
********************************************************************************/
void OLED_Display(void)
{
	//printf("OLED_Display \r\n");
    uint8_t page;
    char *pBuf = (char *)Buffer;

    for (page = 0; page < 8; page++) {
        /* set page address */
        OLED_WriteReg(0xB0 + page);
        /* set low column address */
        OLED_WriteReg(0x02);
        /* set high column address */
        OLED_WriteReg(0x10);

        /* write data */
        OLED_WriteData_nLen8Bit((uint8_t *)pBuf, sOLED_DIS.OLED_Dis_Column);
        pBuf += sOLED_DIS.OLED_Dis_Column;
    }
}
