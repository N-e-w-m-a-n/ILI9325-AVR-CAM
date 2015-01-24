/**********************************************
//
// Touch screen XPT2046 driver library
// 
// Rewrite by Newman 03/2011
//
*//////////////////////////////////////////////

#ifndef _TOUCH_H
#define _TOUCH_H

// Includes
//
#include "BOARD/Config.h"
#include "LCD/ILI9325.h"
#include <avr/io.h>
#include <util/delay.h>

// Definitions
//
#define TOUCH_X				0x90
#define TOUCH_Y				0xD0
#define TOUCH_Z1			0xB0
#define TOUCH_Z2			0xC0
#define TOUCH_READ			0x00

#define TOUCH_SAMPLE_COUNT	10
#define TC_x_MAX			3800
#define TC_y_MIN			50
#define TC_rebound			200

// Macros
//
#define TOUCH_DOWN_INIT()	TOUCH_DOWN_DDR &= ~(1<< TOUCH_DOWN_BIT); TOUCH_DOWN_PORT &= ~(1<< TOUCH_DOWN_BIT)
#define TOUCH_DOWN			(!(TOUCH_DOWN_PIN & (1<< TOUCH_DOWN_BIT)))

// Export function
//
void TOUCH_Reset (void);
void TOUCH_Read (int *x, int *y);
void TOUCH_NativeRead (int *x, int *y);
unsigned char TOUCH_ReadADC (unsigned char axis);
void TOUCH_Calibrate (void);

#endif /* _TOUCH_H */