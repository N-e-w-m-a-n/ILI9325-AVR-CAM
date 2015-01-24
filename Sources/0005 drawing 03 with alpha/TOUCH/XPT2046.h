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
#define TOUCH_X				0x93
#define TOUCH_Y				0xD3
#define TOUCH_Z1			0xB3
#define TOUCH_Z2			0xC2
#define TOUCH_READ			0x00

#define TOUCH_MULTIPLE_SAMPLE_COUNT		12
#define TOUCH_MULTIPLE_SAMPLE_MIN_COUNT	5
#define TOUCH_TRESHOLD					120

// Calibration default.
//
#define X_0								130
#define X_100							3600
#define Y_0								270
#define Y_100							3530
#define TOUCH_CALIBRATION_SHOW_DATA

// Macros
//
#define TOUCH_DOWN_INIT()	TOUCH_DOWN_DDR &= ~(1<< TOUCH_DOWN_BIT); TOUCH_DOWN_PORT &= ~(1<< TOUCH_DOWN_BIT)
#define TOUCH_DOWN			(!(TOUCH_DOWN_PIN & (1<< TOUCH_DOWN_BIT)))

// Export function
//
void TOUCH_Reset (void);
bool TOUCH_Get (int *x, int *y);
bool TOUCH_MultipleRead (int *x, int *y);
bool TOUCH_NativeRead (int *x, int *y);
unsigned char TOUCH_ReadADC (unsigned char axis);
void TOUCH_Calibrate (void);

#endif /* _TOUCH_H */