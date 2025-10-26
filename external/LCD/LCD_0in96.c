/*****************************************************************************
 * | File      	:   LCD_0in96.c
 * | Author      :   Waveshare team
 * | Function    :   Hardware underlying interface
 * | Info        :
 *                Used to shield the underlying layers of each master
 *                and enhance portability
 *----------------
 * |	This version:   V1.0
 * | Date        :   2021-03-11
 * | Info        :   Basic version
 *
 ******************************************************************************/
#include "LCD_0in96.h"
#include "DEV_Config.h"

LCD_0IN96_ATTRIBUTES LCD_0IN96;

/******************************************************************************
function :	Hardware reset
parameter:
******************************************************************************/
static void LCD_0IN96_Reset(void)
{
	DEV_Digital_Write(LCD_RST_PIN, 1);
	DEV_Delay_ms(200);
	DEV_Digital_Write(LCD_RST_PIN, 0);
	DEV_Delay_ms(200);
	DEV_Digital_Write(LCD_RST_PIN, 1);
	DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
	 Reg : Command register
******************************************************************************/
static void LCD_0IN96_SendCommand(uint8_t Reg)
{
	DEV_Digital_Write(LCD_DC_PIN, 0);
	DEV_Digital_Write(LCD_CS_PIN, 0);
	DEV_SPI_WriteByte(LCD_SPI_PORT, Reg);
	// DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
	Data : Write data
******************************************************************************/
static void LCD_0IN96_SendData_8Bit(uint8_t Data)
{
	DEV_Digital_Write(LCD_DC_PIN, 1);
	DEV_Digital_Write(LCD_CS_PIN, 0);
	DEV_SPI_WriteByte(LCD_SPI_PORT, Data);
	DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
	Data : Write data
******************************************************************************/
static void LCD_0IN96_SendData_16Bit(uint16_t Data)
{
	DEV_Digital_Write(LCD_DC_PIN, 1);
	DEV_Digital_Write(LCD_CS_PIN, 0);
	DEV_SPI_WriteByte(LCD_SPI_PORT, (Data >> 8) & 0xFF);
	DEV_SPI_WriteByte(LCD_SPI_PORT, Data);
	DEV_Digital_Write(LCD_CS_PIN, 1);
}

/********************************************************************************
function :	Initialize the lcd
parameter:
********************************************************************************/
void LCD_0IN96_Init(uint8_t Scan_dir)
{
	DEV_SET_PWM(90);
	LCD_0IN96_Reset();
}

/********************************************************************************
function:	Sets the start position and size of the display area
parameter:
		Xstart 	:   X direction Start coordinates
		Ystart  :   Y direction Start coordinates
		Xend    :   X direction end coordinates
		Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_0IN96_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
	Xstart = Xstart + 1;
	Xend = Xend;
	Ystart = Ystart + 26;
	Yend = Yend + 25;

	LCD_0IN96_SendCommand(0x2a);
	LCD_0IN96_SendData_8Bit(Xstart >> 8);
	LCD_0IN96_SendData_8Bit(Xstart);
	LCD_0IN96_SendData_8Bit(Xend >> 8);
	LCD_0IN96_SendData_8Bit(Xend);

	LCD_0IN96_SendCommand(0x2b);
	LCD_0IN96_SendData_8Bit(Ystart >> 8);
	LCD_0IN96_SendData_8Bit(Ystart);
	LCD_0IN96_SendData_8Bit(Yend >> 8);
	LCD_0IN96_SendData_8Bit(Yend);

	LCD_0IN96_SendCommand(0x2C);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void LCD_0IN96_Clear(uint16_t Color)
{
	uint16_t j, i;
	uint16_t Image[LCD_0IN96.WIDTH * LCD_0IN96.HEIGHT];

	Color = ((Color << 8) & 0xff00) | (Color >> 8);

	for (j = 0; j < LCD_0IN96.HEIGHT * LCD_0IN96.WIDTH; j++)
	{
		Image[j] = Color;
	}

	LCD_0IN96_SetWindows(0, 0, LCD_0IN96.WIDTH - 1, LCD_0IN96.HEIGHT - 1);
	DEV_Digital_Write(LCD_DC_PIN, 1);
	DEV_Digital_Write(LCD_CS_PIN, 0);

	// for(j = 0; j < LCD_0IN96.WIDTH*LCD_0IN96.HEIGHT; j++){
	// LCD_0IN96_SendData_16Bit(Image[j]);

	for (j = 0; j < LCD_0IN96.HEIGHT; j++)
	{
		DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)&Image[j * LCD_0IN96.WIDTH], LCD_0IN96.WIDTH * 2);
	}
	DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
function :	Sends the image buffer in RAM to displays
parameter:
******************************************************************************/
void LCD_0IN96_Display(uint16_t *Image)
{
	uint16_t j;
	LCD_0IN96_SetWindows(0, 0, LCD_0IN96.WIDTH - 1, LCD_0IN96.HEIGHT - 1);
	DEV_Digital_Write(LCD_DC_PIN, 1);
	//   DEV_Digital_Write(LCD_CS_PIN, 0);

	for (j = 0; j < LCD_0IN96.HEIGHT; j++)
	{
		DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)&Image[j * LCD_0IN96.WIDTH], LCD_0IN96.WIDTH * 2);
	}
}

/******************************************************************************
function :	Set display position
parameter:
******************************************************************************/
void LCD_0IN96_DisplayWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t *Image)
{
	// display
	uint32_t Addr = 0;

	uint16_t j;
	LCD_0IN96_SetWindows(Xstart, Ystart, Xend, Yend);
	DEV_Digital_Write(LCD_DC_PIN, 1);
	DEV_Digital_Write(LCD_CS_PIN, 0);
	for (j = Ystart; j < Yend - 1; j++)
	{
		Addr = Xstart + j * LCD_0IN96.WIDTH;
		DEV_SPI_Write_nByte(LCD_SPI_PORT, (uint8_t *)&Image[Addr], (Xend - Xstart) * 2);
	}
	DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
function :	Show a point
parameter:
******************************************************************************/
void LCD_0IN96_DisplayPoint(uint16_t X, uint16_t Y, uint16_t Color)
{
	LCD_0IN96_SetWindows(X, Y, X, Y);
	LCD_0IN96_SendData_16Bit(Color);
}

