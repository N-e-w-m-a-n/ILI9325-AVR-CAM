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
	//TOUCH_DOWN_INIT();
	TOUCH_Calibrate();
	
	if (KEY_SW) {
		
		while(TOUCH_DOWN);
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
		
		// draw
		//
		TOUCH_Reset();
		
		bool start = true;
		int x, y;
		unsigned int color = WHITE;

		while(true) {
			
			while(!TOUCH_DOWN) {
				
				// Do clear if back buttom is pressed
				//	
				if (KEY_SW || start) {
					
					// Wait for button release
					//
					while(KEY_SW);
					
					start = false;
					
					LCD_Clear(BLACK);
					
					// Show color bar
					//
					LCD_Fill(0, 200, 40, 35, BLACK);
					LCD_Fill(40, 200, 40, 35, BLUE);
					LCD_Fill(80, 200, 40, 35, GREEN);
					LCD_Fill(120, 200, 40, 35, RED);
					LCD_Fill(160, 200, 40, 35, MAGENTA);
					LCD_Fill(200, 200, 40, 35, ORANGE);
					LCD_Fill(240, 200, 40, 35, YELLOW);
					LCD_Fill(280, 200, 40, 35, WHITE);
					LCD_Fill(0, 235, 320, 5, color);
				}
			}
			
			// If is pen down
			//
			if (TOUCH_Get(&x, &y)) {
				
				// Do draw
				//
				if (y < 200-2) {
					
					// Draw pen
					//
					LCD_DrawCircle(x, y, 1, color, true);
				}
				else {	// if touch in the color table
					
					color = x/40;
					switch (color) {
						
					case 0:
						color = BLACK;
					break;
					case 1:
						color = BLUE;
					break;
					case 2:
						color = GREEN;
					break;
					case 3:
						color = RED;
					break;
					case 4:
						color = MAGENTA;
					break;
					case 5:
						color = ORANGE;
					break;
					case 6:
						color = YELLOW;
					break;
					case 7:
						color = WHITE;
					break;
					}
					
					// Show color in color line
					//
					LCD_Fill(0, 235, 320, 5, color);
					while(TOUCH_DOWN);
				}
			}
		}
	}
	
    while(true);
}
