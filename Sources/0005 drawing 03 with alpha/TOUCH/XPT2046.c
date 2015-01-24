/**********************************************
//
// Touch screen XPT2046 driver library
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

// Includes
//
#include <stdio.h>
#include <stdlib.h>
#include "XPT2046.h"

// Global variables
//
int TC_x_0 = X_0;		// Calibration
int TC_x_100 = X_100;	//
int TC_y_0 = Y_0;		//
int TC_y_100 = Y_100;	//

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
	SPCR = (1<< SPE) | (1<< MSTR);				// Initialize SPI port every /8 clock
	SPCR |= (1<< SPR0);
	SPSR = (1<< SPI2X);
	temp = SPSR;								// Clear interrupt flag	
	
	// Init external pin
	//
	TOUCH_DOWN_INIT();
}

///////////////////////
//
// TOUCH_Get(&x, &y);
//
bool TOUCH_Get (int *x, int *y) {

	int tx, ty;
	double dx, dy;

	if (!TOUCH_MultipleRead(&tx, &ty))
		return false;

	// Calculate 320x240
	//
	tx -= TC_x_0;
	dx = (double)tx / (double)TC_x_100;
	*x = LCD_MAX_WIDTH - (int)(LCD_MAX_WIDTH * dx);

	ty -= TC_y_0;
	dy = (double)ty / (double)TC_y_100;
	*y = (int)(LCD_MAX_HEIGHT * dy);
	
	return true;
}

////////////////////////////////
//
// TOUCH_MultipleRead(&x, &y);
//
bool TOUCH_MultipleRead (int *x, int *y) {

	char i, s = 0;
	long ix = 0, iy = 0;
	int tx, ty;
	unsigned int xmin = 0xFFFF, xmax = 0, ymin = 0xFFFF, ymax = 0;

	for(i=0; i<TOUCH_MULTIPLE_SAMPLE_COUNT; i++) {
		
		if (TOUCH_NativeRead(&tx, &ty)) {
			
			ix += tx;
			iy += ty;
			
			s++;
			
			if (tx > xmax)
				xmax = tx;
			
			if (tx < xmin)
				xmin = tx;
			
			if (ty > ymax)
				ymax = ty;
			
			if (ty < ymin)
				ymin = ty;
		}
	}
	
	if (s < TOUCH_MULTIPLE_SAMPLE_MIN_COUNT)
		return false;
	
	// If some nois is here -> cancel
	//
	xmax -= xmin;
	ymax -= ymin;
	xmax = (ymax > xmax) ? ymax : xmax;
	
	if (xmax > TOUCH_TRESHOLD)
		return false;
	
	// Calculate output
	//
	*x = ix / s;
	*y = iy / s;

	return true;
}

//////////////////////////////
//
// TOUCH_NativeRead(&x, &y);
//
bool TOUCH_NativeRead (int *x, int *y) {
	
	unsigned char buf_data[8];
	int z1, z2, p;

	// Enable touch screen CS
	//
	TOUCH_CS_PORT &= ~(1<< TOUCH_CS_BIT);

	buf_data[0] = TOUCH_ReadADC(TOUCH_X);		// Write Command Measure X-Position
	buf_data[0] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data X-Position (7-bit byte High) data: 0ddddddd	(bit11-bit5)
	buf_data[1] = TOUCH_ReadADC(TOUCH_Y);		// Write Command Measure Y-Position and Read ADC data X-Position (5-bit byte Low)  data: ddddd000 (bit)
	buf_data[2] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data Y-Position (7-bit byte High) data: 0ddddddd (bit11-bit5)
	buf_data[3] = TOUCH_ReadADC(TOUCH_Z1);		// Write Command Measure Z1 and Read ADC data Y-Position (5-bit byte Low)  data: ddddd000 (bit)
	buf_data[4] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data Z1 (7-bit byte High) data: 0ddddddd (bit11-bit5)
	buf_data[5] = TOUCH_ReadADC(TOUCH_Z2);		// Write Command Measure Z2 and Read ADC data Z1 (5-bit byte Low)  data: ddddd000 (bit)
	buf_data[6] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data Z2 (7-bit byte High) data: 0ddddddd (bit11-bit5)
	buf_data[7] = TOUCH_ReadADC(TOUCH_READ);	// Read ADC data Z2 (5-bit byte Low)  data: ddddd000 (bit)

	// Disable touch screen CS
	//
	TOUCH_CS_PORT |= (1<< TOUCH_CS_BIT);

	// Calculate
	//
	*x  = (int)buf_data[0] << 5;	// Shift 7 bit High
	*x |= (int)buf_data[1] >> 3;	// Shift 5 bit low
	
	*y  = (int)buf_data[2] << 5;	// Shift 7 bit High
	*y |= (int)buf_data[3] >> 3;	// Shift 5 bit low
	
	z1  = (int)buf_data[4] << 5;	// Shift 7 bit High
	z1 |= (int)buf_data[5] >> 3;	// Shift 5 bit low
	
	z2  = (int)buf_data[6] << 5;	// Shift 7 bit High
	z2 |= (int)buf_data[7] >> 3;	// Shift 5 bit low
	
	// Calculate pressure
	//
	p = ((double)*y/4096)*((double)z2/(double)z1-1) *10;
	p = ((p > 10) && (p < 35)) ? true : false;

	return p;
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
	
	int tmp, x, y;
	
	// Clean screen and reset TOUCH 
	//
	LCD_Clear(BLACK);
	TOUCH_Reset();

	//////////////////////
	//
	// Write first point 
	//
	LCD_DrawCircle(LCD_MAX_WIDTH/10, LCD_MAX_HEIGHT/10, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10, LCD_MAX_HEIGHT/10, 5, WHITE, false);
	LCD_SetPoint(LCD_MAX_WIDTH/10, LCD_MAX_HEIGHT/10, WHITE);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	while(!TOUCH_DOWN);
	while(!TOUCH_MultipleRead(&x, &y));

	TC_x_0 = x;
	TC_y_0 = y;

	while(TOUCH_DOWN);
	
	///////////////////////
	//
	// Write second point
	//
	LCD_Clear(BLACK);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*9, LCD_MAX_HEIGHT/10*5, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*9, LCD_MAX_HEIGHT/10*5, 5, WHITE, false);
	LCD_SetPoint(LCD_MAX_WIDTH/10*9, LCD_MAX_HEIGHT/10*5, WHITE);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	while(!TOUCH_DOWN);
	while(!TOUCH_MultipleRead(&x, &y));
	
	tmp = (TC_x_0 - x)/8;	// 10%
	TC_x_100 = tmp*10;		// 100%
	TC_x_0 = x - tmp;		// 0%
	
	while(TOUCH_DOWN);

	//////////////////////
	//
	// Write third point
	//
	LCD_Clear(BLACK);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*5, LCD_MAX_HEIGHT/10*9, 10, WHITE, false);
	LCD_DrawCircle(LCD_MAX_WIDTH/10*5, LCD_MAX_HEIGHT/10*9, 5, WHITE, false);
	LCD_SetPoint(LCD_MAX_WIDTH/10*5, LCD_MAX_HEIGHT/10*9, WHITE);
	
	// Wait for TOUCH and Read it
	//
	// Do multiple sampling for better result
	//
	while(!TOUCH_DOWN);
	while(!TOUCH_MultipleRead(&x, &y));
	
	y = (y - TC_y_0)/8;	// 10%
	TC_y_100 = y*10;		// 100%
	TC_y_0 -= y;			// 0%
	
	while(TOUCH_DOWN);
	LCD_Clear(BLACK);

#ifdef TOUCH_CALIBRATION_SHOW_DATA

	char text[100];

	// Draw final calibration data
	//
	sprintf(text, "x... 0 %%: %d  100 %%: %d ", TC_x_0, TC_x_100);
	LCD_WriteString(10,200, text, YELLOW, BLACK);
	sprintf(text, "y... 0 %%: %d  100 %%: %d ", TC_y_0, TC_y_100);
	LCD_WriteString(10,220, text, YELLOW, BLACK);

#endif

	while(!TOUCH_DOWN);
}
