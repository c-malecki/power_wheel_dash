#ifndef __DRIVER_LED_H_
#define __DRIVER_LED_H_

#include "esp_err.h"
#include "global.h"
#include <stdbool.h>

#define LED_HLL_OE_PIN (1)
#define LED_HLL_DC_PIN (2)

#define LED_HLR_OE_PIN (41)
#define LED_HLR_DC_PIN (42)

#define LED_HL_MAX_LEDS (1) // 10

#define LED_BODY_OE_PIN (39)
#define LED_BODY_DC_PIN (38)

#define LED_BODY_MAX_LEDS (20)

typedef enum {
  LED_STRIP_NONE = 0,
  LED_STRIP_HEADLIGHT,
  LED_STRIP_BODYLIGHT,
} LED_Strip_ID;

esp_err_t LEDDriver_Init(void);
void LEDDriver_SetHeadlights(G_Color_ID color_id);
void LEDDriver_SetBodylights(G_Color_ID color_id);

#endif // __DRIVER_LED_H_