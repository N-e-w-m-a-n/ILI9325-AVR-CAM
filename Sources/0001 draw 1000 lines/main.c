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
#include "FAT/pff.h"
//#include "ov7670.h"
//#include "int.h"

//----------------------------------------------------------------------------
//
// definice
//
#define bit(x)							_BV(x)
#define false							0
#define	true							1

// ADC
//
#define ADC_INIT(p)						ADMUX = p; ADCSRA = bit(ADEN) | bit(ADSC); PORTA &= ~bit(p); DDRA &= ~bit(p)
#define ADC_START						ADCSRA |= bit(ADSC)
#define ADC_WAIT						while (ADCSRA & bit(ADSC)){}
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
int main(void) {

	char pokus[100];

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
	ADC_INIT(0);
	
	LCD_DATA_OUPUT();
    LCD_Init();

	if (KEY_SW) {
		
		int color = 0;
		
		while(true) {
			
			LCD_Clear(color);
			
			color = color ? 0 : 0xFFFF;
			delay_ms(300);
		}
	}
	else {
		
		int i = 0;
		
		while(true) {
			
			LCD_Clear(BLACK);
			
			for(i=0; i<1000; i++)
				LCD_DrawLine(rand()%319, rand()%239, rand()%319, rand()%239, rand()<<1);
			
			
//			LCD_Scroll(i++);
			
//			ADC_GET_SAMPLE;
			
//			sprintf(pokus, "pokus: %d, %d", i++, ACD);
//			LCD_WriteString(50,20, pokus,RED,BLACK);
			
			//delay_ms(3);
		}
	}
	
    while(true);
}

