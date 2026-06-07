/*
 * I2C_DRIVER.h
 *
 *  Created on: Apr 18, 2026
 *      Author: sikor
 */

#ifndef INC_I2C_DRIVER_H_
#define INC_I2C_DRIVER_H_
#include <stdint.h>

void I2C_CONFIG();
void SEND_CMD(uint8_t cmd);
void SEND_PAGE(const uint8_t *image_data);

#endif /* INC_I2C_DRIVER_H_ */
