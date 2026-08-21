#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdint.h>

/*
    This file contains conditional definitions based on build environment
    and hardware/driver specific
*/

#ifdef DEVELOPMENT
/* Development Configuration */
#define LED_STRIP_MAX_LEDS (1)
#define LOG_LEVEL LOG_LEVEL_INFO
// Macro to execute a block of development-only code
#define DEV_ONLY(code)                                                         \
  do {                                                                         \
    code;                                                                      \
  } while (0)
#else
/* Production Configuration */
#define LED_STRIP_MAX_LEDS (10)
#define LOG_LEVEL LOG_LEVEL_ERROR
// Compiles out completely in production
#define DEV_ONLY(code)                                                         \
  do {                                                                         \
  } while (0)
#endif

/* *** HARDWARE *** */

// avoid GPIO 0, 46, 45, 35, 36, 37

/*
  LCD
*/

#define LCD_PIN_SPI_MOSI (11)
#define LCD_PIN_SPI_CLK (12)
#define LCD_PIN_SPI_MISO (13)
#define LCD_PIN_DC (8)
#define LCD_PIN_RST (9)
#define LCD_PIN_CS (10)
#define LCD_PIN_LED (18)
#define LCD_PIN_T_IRQ (16)
#define LCD_PIN_T_CS (17)

/*
  MicroSD Card
  https://docs.espressif.com/projects/esp-idf/en/release-v6.1/esp32s3/api-reference/peripherals/sdmmc_host.html
*/

#define MICROSD_PIN_SPI_MOSI (37)
#define MICROSD_PIN_SPI_CLK (36)
#define MICROSD_PIN_SPI_MISO (35)
#define MICROSD_PIN_SPI_CS (38)
#define MICROSD_MAX_FREQ (10000)
#define MICROSD_MOUNT_POINT "/sdcard"

/*
  WS2812 LEDs
*/

#define LED_PIN_HLL_DC (1)
#define LED_PIN_HLR_DC (2)
#define LED_PIN_BLL_DC (41)
#define LED_PIN_BLR_DC (42)

/*
  MAX98357a Class D Audio Amplifier
*/

#define AUDIO_AMP_PIN_LRC (15)
#define AUDIO_AMP_PIN_BCLK (7)
#define AUDIO_AMP_PIN_DIN (6)

#endif // __CONFIG_H_