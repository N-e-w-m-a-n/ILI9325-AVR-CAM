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

// Includes
//
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "BOARD/Config.h"
#include "LCD/ILI9325.h"
#include "TOUCH/XPT2046.h"
//#include "FAT/pff.h"
//#include "ov7670.h"
//#include "int.h"

#include "touch_circles.c"
#include "drawing.c"

////////////
//
// init();
//
void init(void) {
	
	// Data bridge and extern clock
	// from Camera to LCD initialization
	//
	HC245_INIT();
	EXCLK_INIT();
	//
	// and disable it both
	//
	HC245_DISABLE();
	EXCLK_DISABLE();
	
	// onboard KEY switch init
	//
	KEY_SW_INIT();
	
	// LCD initialize
	//
	LCD_DATA_OUTPUT();
    LCD_Init();
	
	// TOUCH Initialize
	//
	TOUCH_Reset();			// Without manual calibration
	//TOUCH_Calibrate();	// With manual calibration
}

/////////////////
//
// Main program
//
int main (void) {
	
	// Initialize board and periphery
	//
	init();
	
	//////////////////////////////////////////////////////////
	//
	// If board button is pressing down, start touch circles
	//
	if (KEY_SW) {
		
		touch_circles();
	}
	
	/////////////////////////
	//
	// Otherwise do Drawing
	//
	
	// Draw color bar and clean draw space
	//
	LCD_Clear(BLACK);
	draw_color_bar();
	
	// Main loop
	//
	while(true) {
		
		// Idle time //
		///////////////
		// there is check if
		// clear button is pressed
		// and other
		//
		idle_time();
		
		// If pen is down
		//
		if (TOUCH_Get(&x, &y)) {
			
			// Do draw
			//
			if (y < DRAWING_HEIGHT) {
				
				draw();
			} 
			
			// if touch to the color table
			//
			else if (!isDrawing) {
				
				color_bar();
			}
		}
	}
	
	while(true);
}
