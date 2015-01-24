/**********************************************
//
// INTERRUPT driver
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

// Includes
//
#include "int.h"
#include "lcd.h"

//volatile unsigned char val1 = 0;


//////////////////////////////////
//
// INT0 Initialization and start
//
void INT0_Init(void) {

	SREG |= 0x80 ;		// Global interrupt Enable
	MCUCR |= 0x02 ;		// The falling edge of INT0 generates an interrupt request
	GICR=(1<<INT0) ;	// External Interrupt0 Request Enable
}


///////////////////////
//
// Interrupt 0 driver
//
SIGNAL( SIG_INTERRUPT0 ) {

	cli();
	
//	if (val1) {
	
	// val1 = 0;
	
	// Camera to LCD external clock disable
	//
	EXCLK_DISABLE();
	
	// Camera 245 data bridge disable
	//
	HC245_DISABLE();
	
	// Set data port as output for settings LCD registers
	//
	LCD_DATA_OUPUT();
	
	// Screen landscape mirrored for Camera output
	//
	LCD_Direction(true, false, true);

	// Set boundaries
	//
	LCD_SetBounds(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT);
 
	// Start Camera source
	//
	LCD_RD_H();
	LCD_RS_H();
    LCD_CS_L();  
    LCD_WR_L();

	LCD_DATA_INPUT();	// MCU data port must be input
	EXCLK_ENABLE();		// Camera to LCD external clock enable
	HC245_ENABLE();		// Camera 245 bridge enable

/*	} else {

	val1 = 1;
	
	DISEN_EXCLK;	
	DISEN_HC245;	
    DATA_OUPUT();
	
	// Normal screen
	//
	LCD_Direction(true, true, false);
	LCD_write_english_string(20,206,"Newman's 2011-03",RED,BLACK);
	LCD_write_english_string(100,222,"OV7670 Demo",RED,BLACK);
	
	}
*/
	sei();
}
