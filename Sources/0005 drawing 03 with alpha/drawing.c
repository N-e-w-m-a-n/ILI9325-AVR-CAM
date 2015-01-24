/**********************************************
//
// Drawing funstions
//
*//////////////////////////////////////////////

// definice
//
#define DRAWING_HEIGHT	205

// globals
//
bool isDrawing = false;
int x, y, last_x = 0, last_y = 0;
unsigned int color = WHITE;
unsigned char alpha = 10;
bool do_alpha = true;


/////////////////
//
// idle_time();
//
void idle_time (void) {

	while(!TOUCH_DOWN) {
		
		isDrawing = false;
		
		// Do clear if back buttom is pressed
		//	
		if (KEY_SW) {
			
			// Wait for button release
			//
			while(KEY_SW);
			
			// Clean screen
			//
			LCD_DrawRectangle(0, 0, LCD_MAX_WIDTH, DRAWING_HEIGHT +1, BLACK, true);
		}
	}
}

////////////
//
// draw();
//
void draw (void) {

	if (!isDrawing) {
		
		isDrawing = true;
		
		last_x = x;
		last_y = y;
	}
	
	// Draw pen
	//
	LCD_SetBounds(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT);

	// Alpha lines 3x3 matrix
	//
	if (do_alpha) {
		
		LCD_DrawLineAlpha(x, y, last_x, last_y, color, alpha);
		LCD_DrawLineAlpha(x, y +1, last_x, last_y +1, color, alpha);
		LCD_DrawLineAlpha(x, y +2, last_x, last_y +2, color, alpha);
		LCD_DrawLineAlpha(x +1, y, last_x +1, last_y, color, alpha);
		LCD_DrawLineAlpha(x +1, y +1, last_x +1, last_y +1, color, alpha);
		LCD_DrawLineAlpha(x +1, y +2, last_x +1, last_y +2, color, alpha);
		LCD_DrawLineAlpha(x +2, y, last_x +2, last_y, color, alpha);
		LCD_DrawLineAlpha(x +2, y +1, last_x +2, last_y +1, color, alpha);
		LCD_DrawLineAlpha(x +2, y +2, last_x +2, last_y +2, color, alpha);
	}
	
	// Normal lines 2x2 matrix
	//
	else {
	
		LCD_DrawLine(x, y, last_x, last_y, color);
		LCD_DrawLine(x, y +1, last_x, last_y +1, color);
		LCD_DrawLine(x +1, y, last_x +1, last_y, color);
		LCD_DrawLine(x +1, y +1, last_x +1, last_y +1, color);
	}

	last_x = x;
	last_y = y;
}

//////////////////////
//
// draw_color_bar();
//
void draw_color_bar (void) {

	// Draw color bar
	//
	LCD_DrawRectangle(0, 207, 320, 34, BLACK, true);
	LCD_SetBounds(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT);
	LCD_DrawLine(0, 206, 320, 206, WHITE);

	LCD_DrawCircle(17, 220, 11, WHITE, !do_alpha);
	
	LCD_DrawRectangle(40, 208, 34, 26, BLACK, true);
	LCD_DrawRectangle(75, 208, 34, 26, BLUE, true);
	LCD_DrawRectangle(110, 208, 34, 26, GREEN, true);
	LCD_DrawRectangle(145, 208, 34, 26, RED, true);
	LCD_DrawRectangle(180, 208, 34, 26, MAGENTA, true);
	LCD_DrawRectangle(215, 208, 34, 26, ORANGE, true);
	LCD_DrawRectangle(250, 208, 34, 26, YELLOW, true);
	LCD_DrawRectangle(285, 208, 35, 26, WHITE, true);
	
	// Draw selected color
	//
	LCD_DrawRectangle(0, 235, 320, 5, color, true);
}

/////////////////
//
// color_bar();
//
void color_bar (void) {

	if (x < 40) {
		
		do_alpha = (do_alpha) ? false : true;
		
		draw_color_bar();
		
		while(TOUCH_DOWN);
		return;
	}
	
	// Get color from bar
	//
	LCD_SetBounds(0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT);
	color = LCD_GetPoint(x, y);
	
	// Show color in color line
	//
	LCD_DrawRectangle(0, 235, 320, 5, color, true);

	while(TOUCH_DOWN);
}
