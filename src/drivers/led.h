#ifndef __LED_H_
#define __LED_H_

#include "esp_err.h"
#include "led_strip.h"
#include <stdint.h>
#include <stdbool.h>

#define LED_HLL_OE_PIN (1)
#define LED_HLL_DC_PIN (2)

#define LED_HLR_OE_PIN (41)
#define LED_HLR_DC_PIN (42)

#define LED_HL_MAX_LEDS (8)

#define LED_BODY_OE_PIN (39)
#define LED_BODY_DC_PIN (38)

#define LED_BODY_MAX_LEDS (16)

typedef enum {
    LED_SECTION_HL_L = 0,
    LED_SECTION_HL_R,
    LED_SECTION_BODY
} LED_Strip_IDs;

typedef enum {
    LED_COLOR_ID_NONE = 0,
    LED_COLOR_ID_RED,
    LED_COLOR_ID_GREEN,
    LED_COLOR_ID_BLUE,
    LED_COLOR_ID_PURPLE,
} LED_Color_IDs;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} LED_Color_t;

extern const LED_Color_t LED_COLOR_NONE;
extern const LED_Color_t LED_COLOR_RED;
extern const LED_Color_t LED_COLOR_GREEN;
extern const LED_Color_t LED_COLOR_BLUE;
extern const LED_Color_t LED_COLOR_PURPLE;

esp_err_t LED_Init(void);

void LED_SetColor(LED_Strip_IDs strip_id, LED_Color_IDs color_id);

#endif // __LED_H_