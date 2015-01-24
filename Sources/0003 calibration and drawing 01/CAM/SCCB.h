/************************************************
//
// The Serial Camera Control Bus (SCCB)
// for OV7670 Camera module 640x320 library
// 
// Rewrite by Newman 02/2011
//
*////////////////////////////////////////////////

#ifndef _SCCB_H
#define _SCCB_H

// Includes
//
#include "BoardConfig.h"
#include <avr/io.h>
#include <util/delay.h>


// Macros
//
#define SIO_C_H			SCCB_PORT |= (1<< SCCB_SIO_C);
#define SIO_C_L			SCCB_PORT &= ~(1<< SCCB_SIO_C);
#define SIO_D_H			SCCB_PORT |= (1<< SCCB_SIO_D);
#define SIO_D_L			SCCB_PORT &= ~(1<< SCCB_SIO_D);

#define SIO_D_IN		SCCB_DDR &= ~(1<< SCCB_SIO_D);
#define SIO_D_OUT		SCCB_DDR |= (1<< SCCB_SIO_D);

#define SIO_D_STATE	((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


// Export functions
//
void SCCB_Init (void);
void SCCB_Delay (void);
void SCCB_Start (void);
void SCCB_Stop (void);
void SCCB_noAck (void);

unsigned char SCCB_WriteByte (unsigned char data);
unsigned char SCCB_ReadByte (void);


#endif /* _SCCB_H */
