/**********************************************
//
// Touch screen XPT2046 driver library
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

// Includes
//
#include "XPT2046.h"

// Global variables
//
int TC_x_0;		// Calibration
int TC_x_100;	//
int TC_y_0;		//
int TC_y_100;	//

///////////////////
//
// TOUCH_Reset();
//
void TOUCH_Reset (void) {
	
	char temp;
	
	// Init port
	//
	TOUCH_CS_PORT |= (1<< TOUCH_CS_BIT);		// Disable CS
	TOUCH_CS_DDR |= (1<< TOUCH_CS_BIT);		// Turns on CS pin as output
	TOUCH_SPI_DDR |= (1<< TOUCH_SCK_BIT);		// Set as output
	TOUCH_SPI_DDR |= (1<< TOUCH_MOSI_BIT);		// Set as output
	TOUCH_SPI_PORT |= (1<< TOUCH_MISO_BIT);	// Internal pull up MISO

	// Init spi as master
	//
	SPCR = (1<< SPE) | (1<< MSTR);				// Initialize SPI port every /32 clock
	SPCR |= (1<< SPR1);
	SPSR = (1<< SPI2X);
	temp = SPSR;								// Clear interrupt flag	
}

////////////////////////
//
// TOUCH_Read(&x, &y);
//
void TOUCH_Read (int *x, int *y) {

	char i, s = 0;
	long ix = 0, iy = 0;
	int tx, ty;
	double dx, dy;

	for(i=0; i<TOUCH_SAMPLE_COUNT; i++) {
		
		TOUCH_NativeRead(&tx, &ty);
		
//		if ((tx < TC_x_MAX) && (ty > TC_y_MIN)) {
			
			ix += tx;
			iy += ty;
			
			s++;
//		}
	}
	
	if (!s) return;

	ix /= s;
	iy /= s;

	// Calculate 320x240
	//
	ix -= TC_x_0;
	dx = (double)ix / (double)TC_x_100;
	*x = LCD_MAX_WIDTH - (int)(LCD_MAX_WIDTH * dx);

	iy -= TC_y_0;
	dy = (double)iy / (double)TC_y_100;
	*y = (int)(LCD_MAX_HEIGHT * dy);
}

//////////////////////////////
//
// TOUCH_NativeRead(&x, &y);
//
void TOUCH_NativeRead (int *x, int *y) {
	
	unsigned char buf_data[4];

	// Enable touch screen CS
	//
	TOUCH_CS_PORT &= ~(1<< TOUCH_CS_BIT);

	buf_data[0] = TOUCH_ReadADC(TOUCH_X);		// Write Command Measure X-Position
	buf_data[0] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data X-Position (7-bit byte High) data: 0ddddddd	(bit11-bit5)
	buf_data[1] = TOUCH_ReadADC(TOUCH_Y);		// Write Command Measure Y-Position and Read ADC data X-Position (5-bit byte Low)  data: ddddd000 (bit)
	buf_data[2] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data Y-Position (7-bit byte High) data: 0ddddddd (bit11-bit5)
	buf_data[3] = TOUCH_ReadADC(TOUCH_READ);		// Write Command Measure Z1 and Read ADC data Y-Position (5-bit byte Low)  data: ddddd000 (bit)

	// Disable touch screen CS
	//
	TOUCH_CS_PORT |= (1<< TOUCH_CS_BIT);

	// Calculate
	//
	*x  = (int)buf_data[0] << 5;	// Shift 7 bit High
	*x |= (int)buf_data[1] >> 3;	// Shift 5 bit low
	
	*y  = (int)buf_data[2] << 5;	// Shift 7 bit High
	*y |= (int)buf_data[3] >> 3;	// Shift 5 bit low
}

////////////////////////
//
// TOUCH_ReadADC(axis);
//
unsigned char TOUCH_ReadADC (unsigned char axis) {

	SPDR = axis;
	
	while(!(SPSR & (1<< SPIF)));		// wait for complete
	return (SPDR);						// get data
}

///////////////////////
//
// TOUCH_Calibrate();
//
void TOUCH_Calibrate (void) {
	
	int tmp;
	int tx, ty;
	long x, y;
	char i, text[100];
	
	// Clean screen and reset TOUCH 
	//
	LCD_Clear(BLACK);
	TOUCH_Reset();
	TOUCH_DOWN_INIT();
	
	//////////////////////
	//
	// Write first point 
	//
	LCD_DrawCircle(LCD_MAX_WIDTH/10, LCD_MAX_HEIGHT/10, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10, LCD_MAX_HEIGHT/10, 3, WHITE, false);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	x = 0;
	y = 0;
	
	while(!TOUCH_DOWN);
	for(i=0; i<TOUCH_SAMPLE_COUNT; i++) {
		
		TOUCH_NativeRead(&tx, &ty);
		x += tx;
		y += ty;
	}
	x /= TOUCH_SAMPLE_COUNT;
	y /= TOUCH_SAMPLE_COUNT;
	
	TC_x_0 = x;
	TC_y_0 = y;
	
	///////////////////////
	//
	// Write second point
	//
	while(TOUCH_DOWN);
	LCD_Clear(BLACK);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*9, LCD_MAX_HEIGHT/10*5, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*9, LCD_MAX_HEIGHT/10*5, 3, WHITE, false);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	x = 0;
	y = 0;
	
	while(!TOUCH_DOWN);
	for(i=0; i<TOUCH_SAMPLE_COUNT; i++) {
		
		TOUCH_NativeRead(&tx, &ty);
		x += tx;
	}
	x /= TOUCH_SAMPLE_COUNT;
	
	tmp = (TC_x_0 - x)/8;	// 10%
	TC_x_100 = tmp*10;		// 100%
	TC_x_0 = x - tmp;		// 0%
	
	//////////////////////
	//
	// Write third point
	//
	while(TOUCH_DOWN);
	LCD_Clear(BLACK);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*5, LCD_MAX_HEIGHT/10*9, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*5, LCD_MAX_HEIGHT/10*9, 3, WHITE, false);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	x = 0;
	y = 0;
	
	while(!TOUCH_DOWN);
	for(i=0; i<TOUCH_SAMPLE_COUNT; i++) {
		
		TOUCH_NativeRead(&tx, &ty);
		y += ty;
	}
	y /= TOUCH_SAMPLE_COUNT;
	
	y = (y - TC_y_0)/8;	// 10%
	TC_y_100 = y*10;		// 100%
	TC_y_0 -= y;			// 0%

	
	while(TOUCH_DOWN);

	LCD_Clear(BLACK);
	sprintf(text, "x... 0 %%: %d  100 %%: %d ", TC_x_0, TC_x_100);
	LCD_WriteString(10,200, text, YELLOW, BLACK);
	sprintf(text, "y... 0 %%: %d  100 %%: %d ", TC_y_0, TC_y_100);
	LCD_WriteString(10,220, text, YELLOW, BLACK);

	while(!TOUCH_DOWN);
}