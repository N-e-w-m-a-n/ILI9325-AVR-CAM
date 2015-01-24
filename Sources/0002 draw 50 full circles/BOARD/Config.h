/**********************************************
//
// ATMEGA32 Board with
//
// ILI9325	- 2.8" TFT LCD Display 240x320
// XPT2046	- Touchscreen controller
// OV7670	- Camera module 640x320
// SD(TF)	- Micro Socket with SDIO Mode
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

#ifndef _BOARD_CONFIG_H
#define _BOARD_CONFIG_H


///////////////////////
//
// Common definitions
//
#define true	1
#define false	0
#define bool	unsigned char


////////////////////////
//
// TOUCH SCREEN Driver
//
#define	TOUCH_CS_DDR	DDRB
#define TOUCH_CS_PORT	PORTB
#define TOUCH_CS_BIT	4

// where is hardware SPI
//
#define TOUCH_SPI_DDR	DDRB
#define TOUCH_SPI_PORT	PORTB
#define TOUCH_SCK_BIT	7
#define TOUCH_MISO_BIT	6
#define TOUCH_MOSI_BIT	5


///////////////
//
// KEY switch
//
#define KEY_DDR			DDRD
#define KEY_PORT		PORTD
#define KEY_PIN			PIND
#define KEY_BIT			5

#define KEY_SW_INIT()	KEY_DDR &= ~(1<< KEY_BIT); KEY_PORT |= 1<< KEY_BIT
#define KEY_SW			(!(KEY_PIN & (1<< KEY_BIT)))


//////////////////////////////////////////////
//
// Data port Camera to LCD bridge definition
// 

// 245 data bridge for Camera chip 
//
#define HC245_OE_DDR	DDRD
#define HC245_OE_PORT	PORTD
#define HC245_OE_PIN	PIND
#define HC245_OE_BIT	6

#define HC245_INIT()	HC245_OE_DDR |= 1<< HC245_OE_BIT
#define HC245_ENABLE()	HC245_OE_PORT &= ~(1<< HC245_OE_BIT)
#define HC245_DISABLE()	HC245_OE_PORT |= 1<< HC245_OE_BIT

// External clock Camera to LCD
//
#define EXCLK_DDR  DDRB
#define EXCLK_PORT PORTB
#define EXCLK_PIN  PINB
#define EXCLK_BIT  0

#define EXCLK_INIT()	EXCLK_DDR |= 1<< EXCLK_BIT
#define EXCLK_ENABLE()	EXCLK_PORT |= 1<< EXCLK_BIT 
#define EXCLK_DISABLE()	EXCLK_PORT &= ~(1<< EXCLK_BIT )


///////////////////////
//
// Camera definitions
//

// I2C for Camera chip
//
#define SCCB_DDR		DDRB
#define SCCB_PORT		PORTB
#define SCCB_PIN		PINB

#define SCCB_SIO_C		1
#define SCCB_SIO_D		2


////////////////////
//
// LCD definitions
//

// LCD Dataport
//
#define LCD_DATA_DDR  DDRC
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PIN  PINC

// LCD Extra Pins
//
#define LCD_CS_DDR  DDRA
#define LCD_CS_PORT PORTA
#define LCD_CS_PIN  PINA
#define LCD_CS_BIT  5

#define LCD_RS_DDR  DDRA
#define LCD_RS_PORT PORTA
#define LCD_RS_PIN  PINA
#define LCD_RS_BIT  6

#define LCD_RD_DDR  DDRA
#define LCD_RD_PORT PORTA
#define LCD_RD_PIN  PINA
#define LCD_RD_BIT  7

#define LCD_WR_DDR  DDRB
#define LCD_WR_PORT PORTB
#define LCD_WR_PIN  PINB
#define LCD_WR_BIT  3

#define LCD_RST_DDR  DDRB
#define LCD_RST_PORT PORTB
#define LCD_RST_PIN  PINB
#define LCD_RST_BIT  1

#define LCD_BL_DDR  DDRD
#define LCD_BL_PORT PORTD
#define LCD_BL_PIN  PIND
#define LCD_BL_BIT  7

// LCD Dimensions
//
#define LCD_MAX_WIDTH	320
#define LCD_MAX_HEIGHT	240


#endif // _BOARD_CONFIG_H