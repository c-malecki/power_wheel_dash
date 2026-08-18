#ifndef __DRIVER_DISPLAY_H_
#define __DRIVER_DISPLAY_H_

#include "esp_err.h"

#define SPI_MOSI_PIN_LCD (11)
#define SPI_CLK_PIN_LCD (12)
#define SPI_MISO_PIN_LCD (13)

#define DISPLAY_LCD_DC_PIN (8)
#define DISPLAY_LCD_RST_PIN (9)
#define DISPLAY_LCD_CS_PIN (10)
#define DISPLAY_LCD_LED_PIN (18)

#define DISPLAY_LCD_T_IRQ_PIN (16)
#define DISPLAY_LCD_T_CS_PIN (17)

esp_err_t DisplayDriver_Init();

#endif // __DRIVER_DISPLAY_H_