/**********************************************
//
// LCD ILI9325 driver library
// 
// Rewrite by Newman 02/2011
//
*//////////////////////////////////////////////

// Includes
//
#include "ILI9325.h"
#include "font_8x16.h"


///////////////////////
//
// LCD initialization
//
void LCD_Init (void) {

	LCD_PORT_INI();
 
	// LCD Reset
	//
	LCD_RST_L();
	_delay_ms(100);
	LCD_RST_H();
	_delay_ms(100); 
	
	// SET registers
	//
	LCD_WR_REGISTER(0x00E3,0x3008); 					// Set the internal timing;   
	LCD_WR_REGISTER(0x00E7,0x0012); 					// Set the internal timing;   
	LCD_WR_REGISTER(0x00Ef,0x1231); 					// Set the internal timing;   
    LCD_WR_REGISTER(LCD_START_OSC,0x0001);				// Start Oscilator
	_delay_ms(50);

    LCD_WR_REGISTER(LCD_DRIVE_OUTPUT, 0x0000);			// Set standard drive mode
	LCD_WR_REGISTER(LCD_DRIVE_WAVE, 0x0700);			// Line inversion
	
	// 16 bits System interface (65536 colors)
	//
	LCD_WR_REGISTER(LCD_ENTRY_MODE,0x1028); 			// [12]BRG mode, [5:4]display rotate and [3]Landscape
	LCD_WR_REGISTER(LCD_RESIZE_CTRL, 0x0000);			// No resize
    LCD_WR_REGISTER(LCD_DISPLAY_CTRL2, 0x0202);			// Back & front porch = 2
    LCD_WR_REGISTER(LCD_DISPLAY_CTRL3, 0x0000);			// Non-display area refresh cycle
    LCD_WR_REGISTER(LCD_DISPLAY_CTRL4, 0x0000);			// FMARK function OFF
				
	// Select System interface
	//
    LCD_WR_REGISTER(LCD_DISPLAY_INTERFACE1, 0x0000);	// 16-bit RGB interface, internal clock (Still pictures))
    LCD_WR_REGISTER(LCD_FRM_MARKER_POS, 0x0000);		// Frame marker Position
    LCD_WR_REGISTER(LCD_DISPLAY_INTERFACE2, 0x0000);	// RGB interface polarity

	// Power On sequence 
	//
	LCD_WR_REGISTER(LCD_POWER_CTRL1, 0x0000);
    LCD_WR_REGISTER(LCD_POWER_CTRL2, 0x0007);			// Vci x1
    LCD_WR_REGISTER(LCD_POWER_CTRL3, 0x0000);
    LCD_WR_REGISTER(LCD_POWER_CTRL4, 0x0000);
    _delay_ms(200);										// Dis-charge capacitor power voltage
    
    LCD_WR_REGISTER(LCD_POWER_CTRL1, 0x1590);			// Power supply startup, Source driver enable
    LCD_WR_REGISTER(LCD_POWER_CTRL2, 0x0227);			// Step-up circuit1	Fosc/4, Step-up circuit2 Fosc/16
    _delay_ms(50);

	LCD_WR_REGISTER(LCD_POWER_CTRL3, 0x001e);			// Internal reference voltage= Vci;
    _delay_ms(50);
	
    LCD_WR_REGISTER(LCD_POWER_CTRL4, 0x1500);			// VCOM amplitude x1.04
    LCD_WR_REGISTER(LCD_POWER_CTRL7, 0x0026);			// VCOMH x0.875
    _delay_ms(50);
    
	// Adjust the Gamma Curve
	//
	LCD_WR_REGISTER(LCD_GAMMA_CTRL1,0x0007);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL2,0x0707);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL3,0x0107);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL4,0x0206);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL5,0x0406);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL6,0x0101);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL7,0x0101);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL8,0x0207);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL9,0x0504);
	LCD_WR_REGISTER(LCD_GAMMA_CTRL10,0x0806);
	
	// Set frame rate
	//
	LCD_WR_REGISTER(LCD_FRAME_RATE, 0x000F);
	
	// Set GRAM area
	//
	LCD_WR_REGISTER(LCD_GRAM_H_ADDRESS,0x0000);			// Horizontal GRAM address
    LCD_WR_REGISTER(LCD_GRAM_V_ADDRESS,0x0000);			// Vertical GRAM address
    LCD_WR_REGISTER(LCD_HORIZONTAL_START, 0x0000);		// Horizontal GRAM Start Address
    LCD_WR_REGISTER(LCD_HORIZONTAL_END, 0x00EF);		// Horizontal GRAM End Address
    LCD_WR_REGISTER(LCD_VERTICAL_START, 0x0000);		// Vertical GRAM Start Address
    LCD_WR_REGISTER(LCD_VERTICAL_END, 0x013F);			// Vertical GRAM Start Address
	
	// Gater scan control
	//
    LCD_WR_REGISTER(LCD_GATE_SCAN_CTRL1, 0x2700);		// Gate Scan for 320 lines
    LCD_WR_REGISTER(LCD_GATE_SCAN_CTRL2, 0x0003);		// From G1 to G320, vertical scroll enable
    LCD_WR_REGISTER(LCD_GATE_SCAN_CTRL3, 0x0000);		// Set scrolling line to 0x00
	
	// Partial display control (not used for now)
	//
	LCD_WR_REGISTER(LCD_PART_IMG1_DISP_POS, 0x0000);
    LCD_WR_REGISTER(LCD_PART_IMG1_START_AD, 0x0000);
    LCD_WR_REGISTER(LCD_PART_IMG1_END_AD, 0x0000);
    LCD_WR_REGISTER(LCD_PART_IMG2_DISP_POS, 0x0000);
    LCD_WR_REGISTER(LCD_PART_IMG2_START_AD, 0x0000);
    LCD_WR_REGISTER(LCD_PART_IMG2_END_AD, 0x0000);

	// Panel interface control
	//
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE1, 0x0010);		// 16 clocks per line
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE2, 0x0600);		// try 0x00 // gate output non-overlap 6 clocks period
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE3, 0x0003);		// ???
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE4, 0x0110);		// H1 - 16 clocks per line period, 4 DOTCLKS division ratio with RGB synchron
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE5, 0x0000);		// ???
    LCD_WR_REGISTER(LCD_PANEL_INTERFACE6, 0x0000);		// ???
	
	// Display ON with 262K color, normal display follow
	//
    LCD_WR_REGISTER(LCD_DISPLAY_CTRL1, 0x0133); 
	LCD_Clear(BLACK);
	
	// Set LCD backlight on
	//
	LCD_BL_H();	

}

///////////////////
//
// LCD_Scroll(y);
//
void LCD_Scroll (int y) {

    while (y < 0)
        y += 320;
	
    while (y >= 320)
        y -= 320;
	
    LCD_WR_REGISTER(LCD_GATE_SCAN_CTRL3, y);
}

//////////////////////////
//
// write data to LCD bus
//
void LCD_WR_DATA (unsigned int data) {

	LCD_RD_H();
	LCD_RS_H();
    LCD_CS_L();  
    LCD_WR_L();
	
    LCD_DATA_PORT = data>>8;
	
    LCD_WR_H();
    LCD_WR_L();
	
    LCD_DATA_PORT = data&0XFF; 
	
    LCD_WR_H();
    LCD_CS_H();
}

/////////////////////////
//
// Write register index
//
void LCD_WR_INDEX (unsigned int index) {

    LCD_RD_H();
	LCD_RS_L();
    LCD_CS_L();  
    LCD_WR_L();

    LCD_DATA_PORT = index>>8; 

    LCD_WR_H();
    LCD_WR_L();

    LCD_DATA_PORT = index&0XFF; 

    LCD_WR_H();
    LCD_CS_H();
}

///////////////////
//
// Write register
//
void LCD_WR_REGISTER (unsigned int index,unsigned int data) {

    LCD_WR_INDEX(index);
    LCD_WR_DATA(data);
}

///////////////////////////////
//
// LCD_Clear(color);
//
// color is RGB(5-6-5) format
//
void LCD_Clear (unsigned int color) {

	LCD_Fill(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT, color);
}

///////////////////////////////
//
// LCD_Fill(x, y, width, height, color);
//
// color is RGB(5-6-5) format
//
void LCD_Fill (int x, int y, unsigned int width, unsigned int height, unsigned int color) {

	unsigned long index;
    int right = x + width;
    int bottom = y + height;

	// Fit to display area
	//
    right = min(right, LCD_MAX_WIDTH);
    bottom = min(bottom, LCD_MAX_HEIGHT);
	
    x = max(x, 0);
    y = max(y, 0);
	
    width = right - x;
    height = bottom - y;
	
    if ((width <= 0) || (height <= 0) || (bottom < 0) || (y >= LCD_MAX_HEIGHT))
        return;    

	// Set bounds
	//
	LCD_SetBounds(x, y, width, height);
	
	// LCD select enable
	//
	LCD_RD_H();
	LCD_RS_H();
	LCD_CS_L();
	
	index = (unsigned long)width *height;

	while(index--) {
		
		LCD_WR_L();
		
		LCD_DATA_PORT=color>>8; 
		
		LCD_WR_H();
		LCD_WR_L();
		
		LCD_DATA_PORT=color&0XFF; 
		
		LCD_WR_H();
	}
 
	// LCD select disable
	//
	LCD_CS_H();
}


///////////////////////////////////////////////
//
// LCD_WriteChar(x, y, ichar, color, bcolor);
//
void LCD_WriteChar (unsigned int x, unsigned int y, char ichar, unsigned int color, unsigned int bcolor) {

	unsigned char data, line, column;
	
	LCD_SetBounds(x, y, 8, 16);
  
	for(line = 0; line < 16; line++) {
		
		data = pgm_read_byte(&font_8x16[ichar-32][line]);
		
		for(column = 0; column < 8; column++) {
			
			if (data & 0x80)
				
				LCD_WR_DATA(color);
			else
				LCD_WR_DATA(bcolor);
			
			data <<= 1;
		}
	}
}

//////////////////////////////////////////////////
//
// LCD_WriteString(x, y, string, color, bcolor);
//
void LCD_WriteString (unsigned int x,unsigned int y,char *string,unsigned int color,unsigned int bcolor) {

	while(*string) {
		
		LCD_WriteChar(x, y, *string++, color, bcolor);
		x += 8;
	}
}

////////////////////////////////////////
//
// LCD_SetBounds(x, y, width, height);
//
void LCD_SetBounds (unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

	// my Vertical
	//
	LCD_WR_REGISTER(LCD_GRAM_H_ADDRESS, LCD_MAX_HEIGHT -y -1);
	LCD_WR_REGISTER(LCD_HORIZONTAL_START, LCD_MAX_HEIGHT -y -height);
	LCD_WR_REGISTER(LCD_HORIZONTAL_END, LCD_MAX_HEIGHT -y -1);
	
	// my Horizontal
	//
	LCD_WR_REGISTER(LCD_GRAM_V_ADDRESS, x);
	LCD_WR_REGISTER(LCD_VERTICAL_START, x);
	LCD_WR_REGISTER(LCD_VERTICAL_END, x + width -1);
	
	// Set Read & Write data registrer
	//
	LCD_WR_GRAM;
}

///////////////////////////////
//
// LCD_SetPoint(x, y, color);
//
void LCD_SetPoint (unsigned int x, unsigned int y,unsigned int color) {

	if ((x >= LCD_MAX_WIDTH) || (y >= LCD_MAX_HEIGHT))
		return;
	
	LCD_WR_REGISTER(LCD_GRAM_H_ADDRESS, LCD_MAX_HEIGHT -y -1);
    LCD_WR_REGISTER(LCD_GRAM_V_ADDRESS, x);   
	LCD_WR_GRAM;
	LCD_WR_DATA(color);
}

/////////////////////////////////////////
//
// LCD_DrawLine(x, y, xx, yy, color);
//
void LCD_DrawLine (unsigned int x, unsigned int y, unsigned int xx, unsigned int yy, unsigned int color) {

    int t, distance;
    int xerr=0, yerr=0, delta_x, delta_y;
    int incx, incy;

    // Compute the distances in both directions
	//
    delta_x = xx - x;
    delta_y = yy - y;

    // Compute the direction of the increment,
    // an increment of 0 means either a horizontal or vertical line.
	//
    if(delta_x > 0) 
		
		incx = 1;
    else 
	if(delta_x == 0) 
		
		incx=0;
    else 
		incx = -1;

    if(delta_y > 0)
		
		incy = 1;
    else 
	if(delta_y == 0)
		
		incy = 0;
    else 
		incy = -1;

    // Determine which distance is greater
	//
    delta_x = (delta_x < 0) ? delta_x*-1 : delta_x;	// abs(delta_x)
    delta_y = (delta_y < 0) ? delta_y*-1 : delta_y;	// abs(delta_y)
    
	if(delta_x > delta_y)
		
		distance = delta_x;
    else
		distance = delta_y;

    // Draw the line
	//
    for(t=0; t <= distance+1; t++) {
		
        LCD_SetPoint(x, y, color);
        
        xerr += delta_x;
        yerr += delta_y;
		
        if(xerr > distance) {
			
            xerr -= distance;
            x += incx;
        }
		
        if(yerr > distance) {
			
            yerr -= distance;
            y += incy;
        }
    }
}

///////////////////////////////////////////////
//
// LCD_DrawCircle(x, y, radius, color, fill);
//
void LCD_DrawCircle (int x, int y, unsigned int radius, unsigned int color, bool fill) {


	// Draw 4 mirrored points
	//
	void LCD_Draw4 (int x, int y, unsigned int dx, unsigned int dy, unsigned int color) {
		
		int	mx, my;
		
		mx = x - dx;
		my = y - dy;
		
		x += dx;
		y += dy;
		
		LCD_SetPoint(x, y, color);
		
		if (dx != 0)
			LCD_SetPoint(mx, y, color);
		
		if (dy != 0)
			LCD_SetPoint(x, my, color);
		
		LCD_SetPoint(mx, my, color);
	}

	// Draw 8 mirrored points
	//
	void LCD_Draw8 (int x, int y, unsigned int dx, unsigned int dy, unsigned int color, bool fill) {
		
		if (fill) {
			
			LCD_Fill(x-dy, y-dx, dy<< 1, 1, color);
			LCD_Fill(x-dx, y-dy, dx<< 1, 1, color);
			LCD_Fill(x-dx, y+dy, dx<< 1, 1, color);
			LCD_Fill(x-dy, y+dx, dy<< 1, 1, color);
			LCD_SetBounds(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT);
		}
		else {
			
			LCD_Draw4(x, y, dx, dy, color);
			
			if (dx != dy)
				LCD_Draw4(x, y, dy, dx, color);
		}
	}

	int error = -radius;
	int dx = radius;
	int dy = 0;

	//	draws in 4 strips from top down and middle up + reflection about y
	//
	while (dx >= dy) {
		
		LCD_Draw8(x, y, dx, dy, color, fill);
		
		error += dy;
		dy++;
		error += dy;
		
		if (error >= 0) {
			
			dx--;
			error -= dx<< 1;
		}
	}
}

