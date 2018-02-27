/*#############################################################################
		The header file
Author:		Tamas Revesz
E-mail:		justreveszthings@gmail.com
Date:		2018.02.26.
About: 		A multifunctional driver for oled displays,
		that you can use easy with several microcontrollers.
#############################################################################*/

#ifndef OLED_H_
#define OLED_H_
#include "usrdef.h"
/*
#define Led_Toggle() do{ LATB0= ~LATB0; }while(0)
#define LED_SetLow() do { LATB0 = 0; } while (0)
*/

void oled_init(void);
void oled_sdisplay(unsigned char d);	//1-on, or 0-off


#endif // OLED_H_
