#ifndef __LED_H_
#define __LED_H_

#include "esp_err.h"
#include "led_strip.h"
#include <stdint.h>
#include <stdbool.h>
#include "data_types.h"

#define LED_HLL_OE_PIN (1)
#define LED_HLL_DC_PIN (2)

#define LED_HLR_OE_PIN (41)
#define LED_HLR_DC_PIN (42)

#define LED_HL_MAX_LEDS (8)

#define LED_BODY_OE_PIN (39)
#define LED_BODY_DC_PIN (38)

#define LED_BODY_MAX_LEDS (16)

esp_err_t LED_Init(void);

void LED_SetColor(DATA_TYPE_ID_LEDStrips led_strip_id, DATA_TYPE_ID_LEDColors led_color_id);

#endif // __LED_H_