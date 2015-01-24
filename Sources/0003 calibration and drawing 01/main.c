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
#include "FAT/pff.h"
//#include "ov7670.h"
//#include "int.h"


// ADC
//
#define ADC_INIT(p)						ADMUX = p; ADCSRA = (1<< ADEN) | (1<< ADSC); PORTA &= ~(1<< p); DDRA &= ~(1<< p)
#define ADC_START						ADCSRA |= (1<< ADSC)
#define ADC_WAIT						while (ADCSRA & (1<< ADSC))
#define ADC_GET_SAMPLE					ADC_START; ADC_WAIT


// my delay
//
void delay_ms (int ms) {
	
	while (ms--) _delay_ms(1);
}

/////////////////
//
// Main prorgam
//
int main (void) {

	char text[100];

	// Data bridge and extern clock Camera to LCD initialization
	//
	HC245_INIT();
	EXCLK_INIT();
	//
	// and disable it both
	//
	HC245_DISABLE();
	EXCLK_DISABLE();
	
	// KEY switch init
	//
	KEY_SW_INIT();

	// ADC initialization
	//
	//ADC_INIT(0);
	
	// LCD initialize
	//
	LCD_DATA_OUPUT();
    LCD_Init();
	
	// TOUCH calibrate
	//
	TOUCH_Calibrate();
	
	if (KEY_SW) {
		
		sprintf(text, "Newman's touch circles.. ");
		LCD_WriteString(50,110, text, YELLOW, BLACK);
		while(!TOUCH_DOWN);
		
		while(true) {
			
			for(int i=0; i<50; i++) {
				
				LCD_DrawCircle(rand()%319, rand()%239, rand()%100, rand()<<1, true);
			}
			
			while(!TOUCH_DOWN);
		}
	}
	else {
		
		int x, y;
		
//		LCD_Fill(0, 200, 40, 40, BLACK);
//		LCD_Fill(40, 200, 40, 40, BLUE);
//		LCD_Fill(80, 200, 40, 40, GREEN);
//		LCD_Fill(120, 200, 40, 40, RED);
//		LCD_Fill(160, 200, 40, 40, MAGENTA);
//		LCD_Fill(200, 200, 40, 40, YELLOW);
//		LCD_Fill(240, 200, 40, 40, CYAN);
//		LCD_Fill(280, 200, 40, 40, WHITE);
		
		// draw
		//
		TOUCH_Reset();
		
		while(true) {
			
			while(!TOUCH_DOWN);		// Wait for touch
			TOUCH_Read(&x, &y);	// Get data
			
			if (TOUCH_DOWN) {		// If data are valid
				
				// do draw
				//
//				sprintf(text, "x: %d   y: %d     ", x, y);
//				LCD_WriteString(10,0, text, YELLOW, BLACK);
				LCD_DrawCircle(x, y, 1, WHITE, true);
				
				
				// if right bottom corner... do clear
				//
				if (KEY_SW)
					LCD_Clear(BLACK);
			}
		}
	}
	
    while(true);
}

