/************************************************
//
// The Serial Camera Control Bus (SCCB)
// for OV7670 Camera module 640x320 library
// 
// Rewrite by Newman 02/2011
//
*////////////////////////////////////////////////

// Includes
//
#include "SCCB.h"


/////////////////
//
// SCCB_Init();
//
void SCCB_Init(void) {

	SCCB_DDR|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);
	SCCB_PORT|=(1<<SCCB_SIO_C)|(1<<SCCB_SIO_D);
}

//////////////////
//
// SCCB_Start();
//
void SCCB_Start(void) {

	SIO_D_H;
    _delay_us(100);

    SIO_C_H;
    _delay_us(100);
 
    SIO_D_L;
    _delay_us(100);

    SIO_C_L;
    _delay_us(100);
}

/////////////////
//
// SCCB_Stop();
//
void SCCB_Stop(void) {

	SIO_D_L;
    _delay_us(100);
 
    SIO_C_H;
    _delay_us(100);
  
    SIO_D_H;
    _delay_us(100);
}

///////////////
//
// SCCB_noAct
//
void SCCB_noAck(void) {
	
	SIO_D_H;
	_delay_us(100);
	
	SIO_C_H;
	_delay_us(100);
	
	SIO_C_L;
	_delay_us(100);
	
	SIO_D_L;
	_delay_us(100);
}

//////////////////////////
//
// SCCB_WriteByte(data);
//
unsigned char SCCB_WriteByte(unsigned char data) {

	unsigned char bit, sda;

	for(bit=0; bit<8; bit++) {
		
		if((data << bit) &0x80) {
			
			SIO_D_H;
			
		} else {
			
			SIO_D_L;
		}
		
		_delay_us(100);
		SIO_C_H;
		_delay_us(100);
		SIO_C_L;
		_delay_us(100);
	}
	
	_delay_us(100);
	
	SIO_D_IN;
	_delay_us(100);
	SIO_C_H;
	_delay_us(1000);
	
	if(SIO_D_STATE)
		
		sda=0;			// SDA = 1
	else
		sda=1;			// SDA = 0
	
	SIO_C_L;
	_delay_us(100);	
    SIO_D_OUT;

	return (sda);  
}

/////////////////////
//
// SCCB_ReadByte();
//
unsigned char SCCB_ReadByte(void) {

	unsigned char bit, data = 0x00;
	
	SIO_D_IN;
	_delay_us(100);
	
	for(bit=8; bit>0; bit--) {
		
		_delay_us(100);
		SIO_C_H;
		_delay_us(100);
		
		data <<= 1;
		
		if(SIO_D_STATE)
			data++;
		
		SIO_C_L;
		_delay_us(100);
	}	
	
	return (data);
}
