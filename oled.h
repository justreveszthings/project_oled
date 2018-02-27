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
/*
#define Led_Toggle() do{ LATB0= ~LATB0; }while(0)
#define LED_SetLow() do { LATB0 = 0; } while (0)
*/

void LEDPIN_Init(void);
void LED_Init(void);


#endif // OLED_H_
