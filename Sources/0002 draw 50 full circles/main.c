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
#define ADC_WAIT						while (ADCSRA & (1<< ADSC)){}
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
	
	LCD_DATA_OUPUT();
    LCD_Init();

	if (KEY_SW) {
		
		DDRD &= ~0b00001000;
		PORTD &= ~0b00001000;
		
		while(true) {
			
			while(PIND & 0b00001000);
			for(int i=0; i<50; i++) {
				
				LCD_DrawCircle(rand()%319, rand()%239, rand()%100, rand()<<1, 1);
			}
		}
	}
	else {
		
		unsigned int x = 0, y = 0, in;
		
		LCD_DrawCircle(150, 200, 80, RED, 1);
		
		while(true) {
			
			TOUCH_Reset();
			TOUCH_Read(&x, &y);
			
			DDRD &= ~0b00001000;
			PORTD &= ~0b00001000;
			in = PIND & 0b00001000;
			
			sprintf(text, "touch.. %d  X: %d, Y: %d    ", in, x, y);
			LCD_WriteString(10,220, text, YELLOW, BLACK);
			
			delay_ms(10);
		}
	}
	
    while(true);
}

