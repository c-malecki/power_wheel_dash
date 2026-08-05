#ifndef __LED_H_
#define __LED_H_

#include "esp_err.h"
#include "led_strip.h"
#include <stdint.h>
#include <stdbool.h>

#define LED_HEADLED_L_OE_PIN (1)
#define LED_HEADLED_L_DC_PIN (2)

#define LED_HEADLED_R_OE_PIN (41)
#define LED_HEADLED_R_DC_PIN (42)

#define LED_HEADLED_MAX_LEDS (8)

#define LED_BODYLED_OE_PIN (39)
#define LED_BODYLED_DC_PIN (38)

#define LED_BODYLED_MAX_LEDS (16)

typedef enum {
    LED_SECTION_HL_L = 0,
    LED_SECTION_HL_R,
    LED_SECTION_BODY
} LED_Sections;

typedef enum {
    LED_COLOR_NONE = 0,
    LED_COLOR_RED,
    LED_COLOR_GREEN,
    LED_COLOR_BLUE,
    LED_COLOR_PURPLE,
} LED_Colors;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} LED_Color_t;

extern const LED_Color_t LED_color_none;
extern const LED_Color_t LED_color_red;
extern const LED_Color_t LED_color_green;
extern const LED_Color_t LED_color_blue;
extern const LED_Color_t LED_color_purple;

esp_err_t LED_Init(void);

void LED_SetColor(LED_Sections section, LED_Color_t color);

#endif // __LED_H_