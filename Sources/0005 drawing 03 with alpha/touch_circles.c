/**********************************************
//
// Touch circles main loop
//
*//////////////////////////////////////////////


// touch_circles();
//
void touch_circles (void) {

	char text[100];

	// Make sure nothing is touching
	//
	while(TOUCH_DOWN);
	
	// Draw message box on start
	//
	LCD_DrawRectangle(55, 107, 212, 24, ORANGE, false);
	LCD_DrawRectangle(54, 106, 212, 24, YELLOW, false);
	sprintf(text, " Newman's touch circles.. ");
	LCD_WriteString(56,110, text, YELLOW, BLACK);
	
	// Wait for touch
	//
	while(!TOUCH_DOWN);
	
	// And GO
	//
	while(true) {
		
		// Draw few circles
		//
		for(int i=0; i<30; i++) {
			
			LCD_DrawCircle(rand()%319, rand()%239, rand()%100, rand()<<1, true);
		}
		
		// Wait for touch
		//
		while(!TOUCH_DOWN);
	}
}
