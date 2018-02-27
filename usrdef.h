/*#############################################################################
		usrdef
Author:		Tamas Revesz
E-mail:		justreveszthings@gmail.com
Date:		2018.02.26.
About: 		A multifunctional driver for oled displays,
		that you can use easy with several microcontrollers.
#############################################################################*/

#ifndef USRDEF_H_
#define USRDEF_H_

constant char wiremode='i';		// 'i' means i2c 's' spi ................

#define pinset_scl_low() do { SCL_PIN = 0; } while (0)
#define pinset_scl_high() do { SCL_PIN = 1; } while (0)
#define pinset_sda_low() do { SDA_PIN = 0; } while (0)
#define pinset_sda_high() do { SDA_PIN = 1; } while (0)
#define pinset_rst_low() do { RST_PIN = 0; } while (0)
#define pinset_rst_high() do { RST_PIN = 1; } while (0)
#define pinset_dc_low() do { DC_PIN = 0; } while (0)
#define pinset_dc_high() do { DC_PIN = 1; } while (0)
#define pinset_cs_low() do { CS_PIN = 0; } while (0)
#define pinset_cs_high() do { CS_PIN = 1; } while (0)

#define delay_ms() do { somethingdelaymsfunction(); } while (0)


#endif // USRDEF_H_
