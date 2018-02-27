/*#############################################################################
		The .c file
Author:		Tamas Revesz
E-mail:		justreveszthings@gmail.com
Date:		2018.02.26.
About: 		A multifunctional driver for oled displays,
		that you can use easy with several microcontrollers.
#############################################################################*/

#include "oled.h"
/*void oledpin_init(void){
	LED_SCL_Init;
	LED_SDA_Init;
	LED_RST_Init;
	LED_DC_Init;
	pinMode(SCL_PIN,OUTPUT);
	pinMode(SDA_PIN,OUTPUT);
	pinMode(RST_PIN,OUTPUT);
	pinMode(DC_PIN,OUTPUT);
}*/
void oled_init(void){
	unsigned char i;
        //oledpin_init();	//initialize for yourself
        pinset_scl_high();
        pinset_rst_low();    	
        delay_ms(50);
        pinset_rst_high();
	oled_display(0x00);		// Display Off (0x00/0x01)
	oled_clk(0x80);		// Set Clock as 100 Frames/Sec
	oled_multiplex_ratio(0x3F);	// 1/64 Duty (0x0F~0x3F)
	oled_offset(0x00);	// Shift Mapping RAM Counter (0x00~0x3F)
	oled_startline(0x00);		// Set Mapping RAM Display Start Line (0x00~0x3F)
	oled_charge_pump(0x04);		// Enable Embedded DC/DC Converter (0x00/0x04)
	oled_addressing_mode(0x02);	// Set Page Addressing Mode (0x00/0x01/0x02)
	oled_segment_remap(0x01);	// Set SEG/Column Mapping  
	oled_common_remap(0x08);	  	// Set COM/Row Scan Direction 
	oled_common_config(0x10);	// Set Sequential Configuration (0x00/0x10)
	oled_contrast_controll(0xCF);	// Set SEG Output Current
	oled_precharge_period(0xF1);	// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_VCOMH(0x40);		// Set VCOM Deselect Level
	oled_entire_display(0x00);	// Disable Entire Display On (0x00/0x01)
	oled_inverse_display(0x00);	// Disable Inverse Display On (0x00/0x01)  
	oled_display(0x01);	// Display On (0x00/0x01)
	oled_fill(0x00);                 //clear all
	oled_setpos(0,0); 	
}
void oled_write_data(unsigned char data)   
{
	unsigned char i = 8;
	pinset_cs_low();
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
		delay_ms(1);		//??asm("nop");   
                pinset_scl_low();
		data <<= 1;    
	}
	pinset_cs_high();
}
void oled_write_command(unsigned char cmd){
	unsigned char i = 8;
	pinset_cs_low();
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
                delay_ms(1);		//??asm("nop");  
              	pinset_scl_low();
		cmd <<= 1;   
	} 	
	pinset_cs_high();
}
void oled_display(unsigned char d){
	oled_write_command(0xAE|d);	// Set Display On/Off
					// Default => 0xAE
					// 0xAE (0x00) => Display Off
					// 0xAF (0x01) => Display On
}
void oled_clk(unsigned char d){
	oled_write_command(0xD5);	// Set Display Clock Divide Ratio / Oscillator Frequency
	oled_write_command(d);		// Default => 0x80
					// D[3:0] => Display Clock Divider
					// D[7:4] => Oscillator Frequency
}
void oled_multiplex_ratio(unsigned char d){
	oled_write_command(0xA8);	// Set Multiplex Ratio
	oled_write_command(d);		// Default => 0x3F (1/64 Duty)
}
void oled_offset(unsigned char d){
	oled_write_command(0xD3);	// Set Display Offset
	oled_write_command(d);		// Default => 0x00
}
void oled_startline(unsigned char d){
	oled_write_command(0x40|d);	// Set Display Start Line
					// Default => 0x40 (0x00)
}
void oled_charge_pump(unsigned char d){
	oled_write_command(0x8D);	// Set Charge Pump
	oled_write_command(0x10|d);	// Default => 0x10
					// 0x10 (0x00) => Disable Charge Pump
					// 0x14 (0x04) => Enable Charge Pump
}
void oled_addressing_mode(unsigned char d){
	oled_write_command(0x20);	// Set Memory Addressing Mode
	oled_write_command(d);		// Default => 0x02
					// 0x00 => Horizontal Addressing Mode
					// 0x01 => Vertical Addressing Mode
					// 0x02 => Page Addressing Mode
}
void oled_segment_remap(unsigned char d){
	oled_write_command(0xA0|d);	// Set Segment Re-Map
					// Default => 0xA0
					// 0xA0 (0x00) => Column Address 0 Mapped to SEG0
					// 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}
void oled_common_remap(unsigned char d){
	oled_write_command(0xC0|d);	// Set COM Output Scan Direction
					// Default => 0xC0
					// 0xC0 (0x00) => Scan from COM0 to 63
					// 0xC8 (0x08) => Scan from COM63 to 0
}
void oled_common_config(unsigned char d){
	oled_write_command(0xDA);	// Set COM Pins Hardware Configuration
	oled_write_command(0x02|d);	// Default => 0x12 (0x10)
					// Alternative COM Pin Configuration
					// Disable COM Left/Right Re-Map
}
void oled_contrast_controll(unsigned char d){
	oled_write_command(0x81);	// Set Contrast Control
	oled_write_command(d);		// Default => 0x7F
}
void oled_precharge_period(unsigned char d){
	oled_write_command(0xD9);	// Set Pre-Charge Period
	oled_write_command(d);		// Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
					// D[3:0] => Phase 1 Period in 1~15 Display Clocks
					// D[7:4] => Phase 2 Period in 1~15 Display Clocks
}
void oled_VCOMH(unsigned char d){
	oled_write_command(0xDB);	// Set VCOMH Deselect Level
	oled_write_command(d);		// Default => 0x20 (0.77*VCC)
}
void oled_entire_display(unsigned char d){
	oled_write_command(0xA4|d);	// Set Entire Display On / Off
					// Default => 0xA4
					// 0xA4 (0x00) => Normal Display
					// 0xA5 (0x01) => Entire Display On
}
void oled_inverse_display(unsigned char d){
	oled_write_command(0xA6|d);	// Set Inverse Display On/Off
					// Default => 0xA6
					// 0xA6 (0x00) => Normal Display
					// 0xA7 (0x01) => Inverse Display On
}
void oled_fill(unsigned char bmp_data){
	unsigned char y,x;
	for(y=0;y<8;y++){
		oled_write_command(0xb0+y);  
		oled_write_command(0x00);     
		oled_write_command(0x10);	     
		for(x=0;x<128;x++) oled_write_data(bmp_data);
	}
} 
void oled_setpos(unsigned char x, unsigned char y){ 
	oled_write_command(0xb0+y);
	oled_write_command(((x&0xf0)>>4)|0x10);
	oled_write_command((x&0x0f)|0x00); 
} 
void oled_printbmp(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char bmp[]){ 	
	int ii=0;
	unsigned char x,y;
	for(y=y0;y<=y1;y++)
	{
		LED_Set_Pos(x0,y);				
		for(x=x0;x<x1;x++)
		{      
			oled_write_data(bmp[ii++]);	    	
		}
	}
}
