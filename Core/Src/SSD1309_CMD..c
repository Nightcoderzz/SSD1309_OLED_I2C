/*
 * SSD1309_CMD..c
 *
 *  Created on: 26 Apr 2026
 *      Author: sikor
 */
#include "I2C_DRIVER.h"

void SSD1309_INIT (void) {

	    SEND_CMD(0xAE); // display off
	    SEND_CMD(0xD5); // set display clock
	    SEND_CMD(0x80);
	    SEND_CMD(0xA8); // set multiplex
	    SEND_CMD(0x3F);
	    SEND_CMD(0xD3); // display offset
	    SEND_CMD(0x00);
	    SEND_CMD(0x40); // start line
	    SEND_CMD(0x20); // memory addressing mode
	    SEND_CMD(0x02); // 0x00 = horizontal ← required for filling screen
	    SEND_CMD(0xA1); // segment remap
	    SEND_CMD(0xC8); // COM scan direction
	    SEND_CMD(0xDA); // COM pins
	    SEND_CMD(0x12);
	    SEND_CMD(0x81); // contrast
	    SEND_CMD(0xCF);
	    SEND_CMD(0xD9); // pre-charge
	    SEND_CMD(0xF1);
	    SEND_CMD(0xDB); // VCOMH deselect
	    SEND_CMD(0x40);
	    SEND_CMD(0xA4); // display from RAM
	    SEND_CMD(0xA6); // normal display (not inverted)
	    SEND_CMD(0xAF); // display ON
	}



