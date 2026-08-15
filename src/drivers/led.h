#ifndef __LED_H_
#define __LED_H_

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>

#define LED_HLL_OE_PIN (1)
#define LED_HLL_DC_PIN (2)

#define LED_HLR_OE_PIN (41)
#define LED_HLR_DC_PIN (42)

#define LED_HL_MAX_LEDS (8)

#define LED_BODY_OE_PIN (39)
#define LED_BODY_DC_PIN (38)

#define LED_BODY_MAX_LEDS (16)

typedef enum {
  LED_STRIP_NONE = 0,
  LED_STRIP_HEADLIGHT,
  LED_STRIP_BODYLIGHT,
} LED_Strip_ID;

typedef enum {
  LED_COLOR_NONE = 0,
  LED_COLOR_WHITE,
  LED_COLOR_RED,
  LED_COLOR_ORANGE,
  LED_COLOR_YELLOW,
  LED_COLOR_GREEN,
  LED_COLOR_BLUE,
  LED_COLOR_VIOLET,
} LED_Color_ID;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} LED_Color_t;

esp_err_t LED_Init(void);
void LED_SetHeadlights(LED_Color_ID color_id);
void LED_SetBodylights(LED_Color_ID color_id);

#endif // __LED_H_