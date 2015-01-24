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
#include <avr/io.h>
#include <util/delay.h>

// Definitions
//
#define TOUCH_X			0x90
#define TOUCH_Y			0xD0
#define TOUCH_READ		0x00

// Macros
//

// Export function
//
void TOUCH_Reset (void);
void TOUCH_Read (unsigned int *x, unsigned int *y);
unsigned char TOUCH_ReadADC (unsigned char axis);

#endif /* _TOUCH_H */