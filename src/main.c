/**
  ******************************************************************************
  * @file    	main.c
  * @author		Florian von Zabiensky
  * @version 	V1.0
  * @date		14.03.2019
  * @brief  	Template using the LCD
  * @details    A lap time counter with Interrupt and Timer
  ******************************************************************************
*/


#include <lcd/lcd.h>
#include <stopwatch/stopwatch.h>
#include "stm32f4xx.h"
#include <stdio.h>

int main(void)
{
	HAL_Init();
	/*Initialization of user button*/
	stopwatch_gpio_init();
	/*Initialization of timer 2*/
	stopwatch_TIM_init();
	lcd_init();
	char buf[64];
	counter = 0;
	int i = 2;

	while(1) {
		/*Display time with format HH:MM:SS*/
		sprintf(buf, "%02d:%02d:%02d:%02d",stopwatch_h,stopwatch_m,stopwatch_s,stopwatch_milli_s);
		lcd_draw_text_at_line(buf, 1, BLACK, 2, WHITE);
		/*Display time when an interrupt is triggered */
		if(counter == 2){
			sprintf(buf, "%02d:%02d:%02d:%02d",h,m,s,milli_s);
			lcd_draw_text_at_line(buf, i, BLACK, 2, WHITE);
			counter += 1;
			i+=1;
			if(i == 16) i = 2;
		}
	}
}
