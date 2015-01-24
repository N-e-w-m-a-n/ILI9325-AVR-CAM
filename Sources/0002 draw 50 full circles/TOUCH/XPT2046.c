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
	SPCR = (1<< SPE) | (1<< MSTR);				// Initialize SPI port every /128 clock
	SPCR |= (1<< SPR0) | (1<< SPR1);
	SPSR = 0x00;
	temp = SPSR;								// Clear interrupt flag	
}

////////////////////////
//
// TOUCH_Read(&x, &y);
//
void TOUCH_Read (unsigned int *x, unsigned int *y) {
	
	unsigned char buf_data[4];

	// Enable touch screen CS
	//
	TOUCH_CS_PORT &= ~(1<< TOUCH_CS_BIT);

	buf_data[0] = TOUCH_ReadADC(TOUCH_X);		//Write Command Measure X-Position
	buf_data[0] = TOUCH_ReadADC(TOUCH_READ);	//Read ADC data X-Position (7-bit byte High) data: 0ddddddd	(bit11-bit5)
	buf_data[1] = TOUCH_ReadADC(TOUCH_READ);	//Read ADC data X-Position (5-bit byte Low)  data: ddddd000 (bit)
	buf_data[2] = TOUCH_ReadADC(TOUCH_Y);		//Write Command Measure Y-Position
	buf_data[2] = TOUCH_ReadADC(TOUCH_READ);	//Read ADC data Y-Position (7-bit byte High) data: 0ddddddd (bit11-bit5)
	buf_data[3] = TOUCH_ReadADC(TOUCH_READ);	//Read ADC data Y-Position (5-bit byte Low)  data: ddddd000 (bit)

	// Disable touch screen CS
	//
	TOUCH_CS_PORT |= (1<< TOUCH_CS_BIT);

	// Calculate
	//
	*x  = (unsigned int)buf_data[0] << 5;	// Shift 7 bit High
	*x |= (unsigned int)buf_data[1] >> 3;	// Shift 5 bit low

	*y  = (unsigned int)buf_data[2] << 5;	// Shift 7 bit High
	*y |= (unsigned int)buf_data[3] >> 3;	// Shift 5 bit low
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