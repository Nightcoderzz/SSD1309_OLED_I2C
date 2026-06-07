/*
 * CLK_CONFIG.c
 *
 *  Created on: Apr 18, 2026
 *      Author: sikor
 */
#include "stm32c0xx.h"

void SYS_CLK_CONFIG (){

	int timeout = 10000U;

	RCC->CR |= (1U << 16); // HSE enable
	while (!(RCC->CR & (1U << 17))){} // HSE enable flag

	RCC->CFGR &= ~(0b11 << 0);   // clear bits
	RCC->CFGR |= (0b001 << 0); // HSE as sysclock
	while (((RCC->CFGR & (0b111 << 3)) != (0b001 << 3)) && timeout--);  // confirmation that HSE is set

}
