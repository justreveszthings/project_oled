/*#############################################################################
		The .c file
Author:		Tamas Revesz
E-mail:		justreveszthings@gmail.com
Date:		2018.02.26.
About: 		A multifunctional driver for oled displays,
		that you can use easy with several microcontrollers.
#############################################################################*/

#include "oled.h"
void LEDPIN_Init(void){
	/* LED_SCL_Init;
	LED_SDA_Init;
	LED_RST_Init;
	LED_DC_Init;*/
	pinMode(SCL_PIN,OUTPUT);
	pinMode(SDA_PIN,OUTPUT);
	pinMode(RST_PIN,OUTPUT);
	pinMode(DC_PIN,OUTPUT);
}
void LED_Init(void){
	unsigned char i;
        LEDPIN_Init();

        pinset_scl_high();
        pinset_rst_low();
//	for(i=0;i<100;i++)asm("nop");     	
        LED_DLY_ms(50);
        pinset_rst_high();
	Set_Display_On_Off(0x00);	// Display Off (0x00/0x01)
	Set_Display_Clock(0x80);	// Set Clock as 100 Frames/Sec
	Set_Multiplex_Ratio(0x3F);	// 1/64 Duty (0x0F~0x3F)
	Set_Display_Offset(0x00);	// Shift Mapping RAM Counter (0x00~0x3F)
	SetStartLine(0x00);		// Set Mapping RAM Display Start Line (0x00~0x3F)
	Set_Charge_Pump(0x04);		// Enable Embedded DC/DC Converter (0x00/0x04)
	SetAddressingMode(0x02);	// Set Page Addressing Mode (0x00/0x01/0x02)
	Set_Segment_Remap(0x01);	// Set SEG/Column Mapping  
	Set_Common_Remap(0x08);	  	// Set COM/Row Scan Direction 
	Set_Common_Config(0x10);	// Set Sequential Configuration (0x00/0x10)
	SetContrastControl(0xCF);	// Set SEG Output Current
	Set_Precharge_Period(0xF1);	// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	Set_VCOMH(0x40);		// Set VCOM Deselect Level
	Set_Entire_Display(0x00);	// Disable Entire Display On (0x00/0x01)
	Set_Inverse_Display(0x00);	// Disable Inverse Display On (0x00/0x01)  
	Set_Display_On_Off(0x01);	// Display On (0x00/0x01)
	LED_Fill(0x00);                 //clear all
	LED_Set_Pos(0,0); 	
}
void LED_WrDat(unsigned char data)   
{
	unsigned char i = 8;
	//LED_CS=0;
        pinset_dc_high(); 
        pinset_scl_low();
	while (i--)
	{
		if (data & 0x80)
		{
			pinset_sda_high();
		}
		else
		{
			pinset_sda_low();
		}
                pinset_scl_high();
		asm("nop");   
                pinset_scl_low();
		data <<= 1;    
	}
	//LED_CS=1;
}
void LED_WrCmd(unsigned char cmd){
	unsigned char i = 8;
	//LED_CS = 0;
        pinset_dc_low();
	pinset_scl_low();
        while (i--){
		if (cmd & 0x80){
                	pinset_sda_high();
		}
		else{
                	pinset_sda_low();
		}
		pinset_scl_high();
                asm("nop");
              	pinset_scl_low();
		cmd <<= 1;   
	} 	
	//LED_CS = 1;
}
void Set_Display_On_Off(unsigned char d){
	LED_WrCmd(0xAE|d);		// Set Display On/Off
					// Default => 0xAE
					// 0xAE (0x00) => Display Off
					// 0xAF (0x01) => Display On
}
void Set_Display_Clock(unsigned char d){
	LED_WrCmd(0xD5);		// Set Display Clock Divide Ratio / Oscillator Frequency
	LED_WrCmd(d);			// Default => 0x80
					// D[3:0] => Display Clock Divider
					// D[7:4] => Oscillator Frequency
}
void Set_Multiplex_Ratio(unsigned char d){
	LED_WrCmd(0xA8);		// Set Multiplex Ratio
	LED_WrCmd(d);			// Default => 0x3F (1/64 Duty)
}
void Set_Display_Offset(unsigned char d){
	LED_WrCmd(0xD3);		// Set Display Offset
	LED_WrCmd(d);			// Default => 0x00
}
void SetStartLine(unsigned char d){
	LED_WrCmd(0x40|d);		// Set Display Start Line
					// Default => 0x40 (0x00)
}
void Set_Charge_Pump(unsigned char d){
	LED_WrCmd(0x8D);		// Set Charge Pump
	LED_WrCmd(0x10|d);		// Default => 0x10
					// 0x10 (0x00) => Disable Charge Pump
					// 0x14 (0x04) => Enable Charge Pump
}
void SetAddressingMode(unsigned char d){
	LED_WrCmd(0x20);		// Set Memory Addressing Mode
	LED_WrCmd(d);			// Default => 0x02
					// 0x00 => Horizontal Addressing Mode
					// 0x01 => Vertical Addressing Mode
					// 0x02 => Page Addressing Mode
}
void Set_Segment_Remap(unsigned char d){
	LED_WrCmd(0xA0|d);		// Set Segment Re-Map
					// Default => 0xA0
					// 0xA0 (0x00) => Column Address 0 Mapped to SEG0
					// 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}
void Set_Common_Remap(unsigned char d){
	LED_WrCmd(0xC0|d);		// Set COM Output Scan Direction
					// Default => 0xC0
					// 0xC0 (0x00) => Scan from COM0 to 63
					// 0xC8 (0x08) => Scan from COM63 to 0
}
void Set_Common_Config(unsigned char d){
	LED_WrCmd(0xDA);		// Set COM Pins Hardware Configuration
	LED_WrCmd(0x02|d);		// Default => 0x12 (0x10)
					// Alternative COM Pin Configuration
					// Disable COM Left/Right Re-Map
}
void SetContrastControl(unsigned char d){
	LED_WrCmd(0x81);		// Set Contrast Control
	LED_WrCmd(d);			// Default => 0x7F
}
void Set_Precharge_Period(unsigned char d){
	LED_WrCmd(0xD9);		// Set Pre-Charge Period
	LED_WrCmd(d);			// Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
					// D[3:0] => Phase 1 Period in 1~15 Display Clocks
					// D[7:4] => Phase 2 Period in 1~15 Display Clocks
}
void Set_VCOMH(unsigned char d){
	LED_WrCmd(0xDB);		// Set VCOMH Deselect Level
	LED_WrCmd(d);			// Default => 0x20 (0.77*VCC)
}
void Set_Entire_Display(unsigned char d){
	LED_WrCmd(0xA4|d);		// Set Entire Display On / Off
					// Default => 0xA4
					// 0xA4 (0x00) => Normal Display
					// 0xA5 (0x01) => Entire Display On
}
void Set_Inverse_Display(unsigned char d){
	LED_WrCmd(0xA6|d);		// Set Inverse Display On/Off
					// Default => 0xA6
					// 0xA6 (0x00) => Normal Display
					// 0xA7 (0x01) => Inverse Display On
}
void LED_Fill(unsigned char bmp_data){
	unsigned char y,x;
	for(y=0;y<8;y++){
		LED_WrCmd(0xb0+y);  
		LED_WrCmd(0x00);     
		LED_WrCmd(0x10);	     
		for(x=0;x<128;x++) LED_WrDat(bmp_data);
	}
} 
void LED_Set_Pos(unsigned char x, unsigned char y){ 
	LED_WrCmd(0xb0+y);
	LED_WrCmd(((x&0xf0)>>4)|0x10);
	LED_WrCmd((x&0x0f)|0x00); 
} 
void LED_PrintBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char bmp[]){ 	
	int ii=0;
	unsigned char x,y;
	for(y=y0;y<=y1;y++)
	{
		LED_Set_Pos(x0,y);				
		for(x=x0;x<x1;x++)
		{      
			LED_WrDat(bmp[ii++]);	    	
		}
	}
}

