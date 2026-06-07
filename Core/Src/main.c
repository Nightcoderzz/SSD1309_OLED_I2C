
#include "main.h"
#include "stm32c0xx.h"
#include "CLK_CONFIG.h"
#include "I2C_DRIVER.h"
#include "SSD1309_CMD.h"
#include "IMAGES.h"



int main(void) {

	SYS_CLK_CONFIG();
    I2C_CONFIG();
    SSD1309_INIT();



    SEND_PAGE(smiley_128x64);

    while (1) {}
    return 0;
}
