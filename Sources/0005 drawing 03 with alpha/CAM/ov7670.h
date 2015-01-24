/**********************************************
//
// OV7670 Camera module 640x320 library
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

#ifndef _OV7670_H
#define _OV7670_H

// Includes
//
#include "BoardConfig.h"
#include "font.h"
#include <util/delay.h>
#include <avr/io.h>

// Device slave address
//
#define CAM_DEVICE_WRITE				0x42
#define CAM_DEVICE_READ					0x43


// Export functions
//
unsigned char CAM_Init (void);
unsigned char CAM_WriteReg (unsigned char regID, unsigned char regData);
unsigned char CAM_ReadReg (unsigned char regID, unsigned char *regData);

void CAM_SetBounds (unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void CAM_delay_ms (unsigned int time);


// Registers
//
#define CAM_REG_GAIN					0x00
#define CAM_REG_VREF					0x03
#define CAM_REG_COM3					0x0C
#define CAM_REG_COM7					0x12
#define CAM_REG_COM8					0x13
#define CAM_REG_HSTART					0x17
#define CAM_REG_HSTOP					0x18
#define CAM_REG_VSTRT					0x19
#define CAM_REG_VSTOP					0x1A
#define CAM_REG_HREF					0x32
#define CAM_REG_TSLB					0x3A
#define CAM_REG_COM14					0x3E
#define CAM_REG_COM15					0x40
#define CAM_REG_SCALING_XSC				0x70
#define CAM_REG_SCALING_YSC				0x71
#define CAM_REG_SLOP					0x7A
#define CAM_REG_GAM1					0x7B
#define CAM_REG_GAM2					0x7C
#define CAM_REG_GAM3					0x7D
#define CAM_REG_GAM4					0x7E
#define CAM_REG_GAM5					0x7F
#define CAM_REG_GAM6					0x80
#define CAM_REG_GAM7					0x81
#define CAM_REG_GAM8					0x82
#define CAM_REG_GAM9					0x83
#define CAM_REG_GAM10					0x84
#define CAM_REG_GAM11					0x85
#define CAM_REG_GAM12					0x86
#define CAM_REG_GAM13					0x87
#define CAM_REG_GAM14					0x88
#define CAM_REG_GAM15					0x89


#endif /* _OV7660_H */
