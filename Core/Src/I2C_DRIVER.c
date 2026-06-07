/*
 * I2C_DRIVER.c
 *
 *  Created on: Apr 18, 2026
 *      Author: sikor
 */
#include <stdint.h>
#include "I2C_DRIVER.h"
#include "stm32c0xx.h"



// Definitions
#define GPIOA_EN         (1U << 0)
#define I2C_EN

//GPIO config SCL-PA9, SDA-PA10

void I2C_CONFIG(){

	RCC->IOPENR |= GPIOA_EN; // GPIOA CLK enable

	GPIOA->MODER &= ~(0b11 << 18); // clear
	GPIOA->MODER |= (0b10 << 18); // set PA9 to alternate function

	GPIOA->MODER &= ~(0b11 << 20); // clear
	GPIOA->MODER |= (0b10 << 20); // set PA10 to alternate function



	GPIOA->AFR[1] &= ~(0b1111 << 4); //clear
	GPIOA->AFR[1] |= (0b0110 << 4); //I2C1_SCL PA9
	GPIOA->AFR[1] &= ~(0b1111 << 8); // clear
	GPIOA->AFR[1] |= (0b0110 << 8); // I2C1_SDA PA10

	// Configure open drain(hi resistance) so that slave or master can drive the line
	GPIOA->OTYPER |= (1U << 9) | (1U << 10); //PA9 and PA10 are open drain
	GPIOA->OSPEEDR |= (0b11 << 18) | (0b11 << 20); // very high speed gpio
	GPIOA->PUPDR &= ~(3U << 18);
	GPIOA->PUPDR &= ~(3U << 20); // ensure to eraser pullup/down config

	RCC->APBENR1 |= (1U << 21); // I2C1 CLK Enable

	// FROM RM0490 48MHz 400kHz I2C speed. Speed must be exactly defined
	I2C1->TIMINGR  =
					(0b00001001 << 0) | // 9 SCLL clocks
					(0b00000011 << 8) | // SCLH clock numbers
					(0b0011 << 16)    | // SDAdel
					(0b0011 << 20)    | // SCLdel
					(0b0101 << 28);     // PRESCALER


	I2C1->CR1 |= (1U << 0); // enable pe bit in cr1 register at the end

}

void SEND_CMD (uint8_t cmd){

	uint8_t size_bytes =2U;	// how many bytes do I send
	uint8_t addr = 0x3C;    // Display i2c address
	uint8_t cmd_data [2] = {0x00, cmd}; // 0x00 is a command mode

	while (I2C1->ISR & (1U << 15));  // wait, I2C is busy transferring

	I2C1->CR2 =
				(addr << 1)|
				(size_bytes << 16)|
				(1U << 25) ; // autoend

	I2C1->CR2 |= I2C_CR2_START;

	for (uint8_t i = 0; i < 2; i++) {

		while (!(I2C1->ISR & I2C_ISR_TXIS)){ //This bit is set by hardware when the I2C_TXDR register is empty
										     //and the data to be

	        if (I2C1->ISR & I2C_ISR_NACKF) {
	            I2C1->ICR |= I2C_ICR_NACKCF;
	            I2C1->ICR |= I2C_ICR_STOPCF;
	            return;
	        }
	    }									//transmitted must be written in the I2C_TXDR register.

	    I2C1->TXDR = cmd_data[i];

	}

	while (!(I2C1->ISR & I2C_ISR_STOPF));
	I2C1->ICR |= I2C_ICR_STOPCF;

}

void SEND_PAGE(const uint8_t *image_data) { // sends page by page

    uint8_t size= 128; // this how much I'll send each time. 1 page = 128bytes.

    for (uint8_t page = 0; page < 8; page++){    // Outer loop counting pages

    	// Explicitly tell display which page and column to write to
    	        SEND_CMD(0xB0 + page); // set page address (B0=page0 ... B7=page7)
    	        SEND_CMD(0x00);        // set lower column nibble to 0
    	        SEND_CMD(0x10);        // set upper column nibble to 0

    	uint16_t offset = page * 128; // this will be 128, 255 e

        uint8_t addr = 0x3C; // OLED address

        while (I2C1->ISR & I2C_ISR_BUSY);

        I2C1->CR2 =
                (addr << 1) |
                ((size+1) << 16) |
                I2C_CR2_AUTOEND;

        I2C1->CR2 |= I2C_CR2_START;


        	while (!(I2C1->ISR & I2C_ISR_TXIS)) {
        	    if (I2C1->ISR & I2C_ISR_NACKF) {
        	        I2C1->ICR |= I2C_ICR_NACKCF;
        	        I2C1->ICR |= I2C_ICR_STOPCF;
        	        return;
        	    }
        	}
        	I2C1->TXDR = 0x40;



    	for (uint16_t k = 0; k < 128; k++ ){

    		while (!(I2C1->ISR & I2C_ISR_TXIS))
    		        {
    		            if (I2C1->ISR & I2C_ISR_NACKF) // when things go wrong
    		            {
    		                I2C1->ICR |= I2C_ICR_NACKCF;
    		                I2C1->ICR |= I2C_ICR_STOPCF;
    		                return;
    		            }
    		        }
    		        I2C1->TXDR = image_data[offset + k];
    		    }


        while (!(I2C1->ISR & I2C_ISR_STOPF));

        I2C1->ICR |= I2C_ICR_STOPCF;

        // Reset peripheral before next page
        I2C1->CR1 &= ~(1U << 0);
        for (volatile int d = 0; d < 20; d++);
        I2C1->CR1 |=  (1U << 0);


    	}

}


