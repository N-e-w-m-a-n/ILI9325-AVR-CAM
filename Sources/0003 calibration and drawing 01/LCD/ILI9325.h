/**********************************************
//
// LCD ILI9325 driver library
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

#ifndef _LCD_H
#define _LCD_H

// Includes
//
#include "BOARD/Config.h"
#include <avr/io.h>
#include <util/delay.h>

// Colors
// 	
#define	BLACK	0x0000
#define	BLUE	0x001F
#define	RED 	0xF800
#define	GREEN 	0x07E0
#define CYAN	0x07FF
#define MAGENTA 0xF81F
#define YELLOW	0xFFE0
#define WHITE	0xFFFF		

// Macros
//
#define LCD_DATA_INPUT()   LCD_DATA_DDR = 0x00;
#define LCD_DATA_OUPUT()   LCD_DATA_DDR = 0xFF;

#define LCD_CS_H() LCD_CS_PORT |= 1<<LCD_CS_BIT
#define LCD_CS_L() LCD_CS_PORT &= ~(1<<LCD_CS_BIT)

#define LCD_RS_H() LCD_RS_PORT |= 1<<LCD_RS_BIT
#define LCD_RS_L() LCD_RS_PORT &= ~(1<<LCD_RS_BIT)

#define LCD_WR_L() LCD_WR_PORT |= 1<<LCD_WR_BIT//
#define LCD_WR_H() LCD_WR_PORT &= ~(1<<LCD_WR_BIT)//

#define LCD_RD_H() LCD_RD_PORT |= 1<<LCD_RD_BIT
#define LCD_RD_L() LCD_RD_PORT &= ~(1<<LCD_RD_BIT)

#define LCD_RST_H() LCD_RST_PORT |= 1<<LCD_RST_BIT
#define LCD_RST_L() LCD_RST_PORT &= ~(1<<LCD_RST_BIT)

#define LCD_BL_H() LCD_BL_PORT |= 1<<LCD_BL_BIT
#define LCD_BL_L() LCD_BL_PORT &= ~(1<<LCD_BL_BIT)

#define LCD_PORT_INI(){ LCD_BL_DDR |= 1<<LCD_BL_BIT;\
						LCD_CS_DDR |= 1<<LCD_CS_BIT;\
						LCD_RS_DDR |= 1<<LCD_RS_BIT;\
						LCD_WR_DDR |= 1<<LCD_WR_BIT;\
						LCD_RD_DDR |= 1<<LCD_RD_BIT;\
						LCD_RST_DDR|= 1<<LCD_RST_BIT;\
					   }

#define LCD_WR_GRAM	LCD_WR_INDEX(LCD_RW_GRAM)

#define max(_a,_b) (((_a) > (_b)) ? (_a) : (_b))
#define min(_a,_b) (((_a) < (_b)) ? (_a) : (_b))


// Screen control
//
#define LCD_NORMAL_MODE				0
#define LCD_LANDSCAPE_MODE			1


// Export functions
//
void LCD_WR_INDEX (unsigned int index);
void LCD_WR_DATA (unsigned int data);
void LCD_WR_REGISTER (unsigned int index, unsigned int data);

void LCD_Init (void);
void LCD_Scroll (int y);

void LCD_SetPoint (unsigned int x, unsigned int y,unsigned int color);
void LCD_DrawLine (unsigned int x, unsigned int y, unsigned int xx, unsigned int yy, unsigned int color);
void LCD_DrawCircle (int x, int y, unsigned int radius, unsigned int color, bool fill);

void LCD_SetBounds (unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void LCD_Fill (int x, int y, unsigned int width, unsigned int height, unsigned int color);
void LCD_Clear (unsigned int color);

void LCD_WriteChar (unsigned int x, unsigned int y, char ichar, unsigned int color, unsigned int bcolor);
void LCD_WriteString (unsigned int x, unsigned int y, char *string, unsigned int color, unsigned int bcolor);


// Registers
//
#define LCD_START_OSC				0x00
#define LCD_DRIVE_OUTPUT			0x01
#define LCD_DRIVE_WAVE				0x02
#define LCD_ENTRY_MODE				0x03
#define LCD_RESIZE_CTRL				0x04
#define LCD_DISPLAY_CTRL1			0x07
#define LCD_DISPLAY_CTRL2			0x08
#define LCD_DISPLAY_CTRL3			0x09
#define LCD_DISPLAY_CTRL4			0x0A
#define LCD_DISPLAY_INTERFACE1		0x0C
#define LCD_FRM_MARKER_POS			0x0D
#define LCD_DISPLAY_INTERFACE2		0x0F
#define LCD_POWER_CTRL1				0x10
#define LCD_POWER_CTRL2				0x11
#define LCD_POWER_CTRL3				0x12
#define LCD_POWER_CTRL4				0x13
#define LCD_GRAM_H_ADDRESS			0x20
#define LCD_GRAM_V_ADDRESS			0x21
#define LCD_RW_GRAM					0x22
#define LCD_POWER_CTRL7				0x29
#define LCD_FRAME_RATE				0x2B
#define LCD_GAMMA_CTRL1				0x30
#define LCD_GAMMA_CTRL2				0x31
#define LCD_GAMMA_CTRL3				0x32
#define LCD_GAMMA_CTRL4				0x35	
#define LCD_GAMMA_CTRL5				0x36
#define LCD_GAMMA_CTRL6				0x37
#define LCD_GAMMA_CTRL7				0x38
#define LCD_GAMMA_CTRL8				0x39
#define LCD_GAMMA_CTRL9				0x3C
#define LCD_GAMMA_CTRL10			0x3D
#define LCD_HORIZONTAL_START		0x50
#define LCD_HORIZONTAL_END			0x51
#define LCD_VERTICAL_START			0x52
#define LCD_VERTICAL_END			0x53
#define LCD_GATE_SCAN_CTRL1			0x60
#define LCD_GATE_SCAN_CTRL2			0x61
#define LCD_GATE_SCAN_CTRL3			0x6A
#define LCD_PART_IMG1_DISP_POS		0x80
#define LCD_PART_IMG1_START_AD		0x81
#define LCD_PART_IMG1_END_AD		0x82
#define LCD_PART_IMG2_DISP_POS		0x83
#define LCD_PART_IMG2_START_AD		0x84
#define LCD_PART_IMG2_END_AD		0x85
#define LCD_PANEL_INTERFACE1		0x90
#define LCD_PANEL_INTERFACE2		0x92
#define LCD_PANEL_INTERFACE3		0x93
#define LCD_PANEL_INTERFACE4		0x95
#define LCD_PANEL_INTERFACE5		0x97
#define LCD_PANEL_INTERFACE6		0x98

#endif /* _LCD_H */