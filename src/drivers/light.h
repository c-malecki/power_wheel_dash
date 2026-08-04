#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "esp_err.h"
#include "led_strip.h"
#include <stdint.h>
#include <stdbool.h>

#define LIGHT_HEADLIGHT_L_OE_PIN (1)
#define LIGHT_HEADLIGHT_L_DC_PIN (2)

#define LIGHT_HEADLIGHT_R_OE_PIN (41)
#define LIGHT_HEADLIGHT_R_DC_PIN (42)

#define LIGHT_HEADLIGHT_MAX_LEDS (8)

#define LIGHT_BODYLIGHT_OE_PIN (39)
#define LIGHT_BODYLIGHT_DC_PIN (38)

#define LIGHT_BODYLIGHT_MAX_LEDS (16)

typedef enum {
    LIGHT_SECTION_HL_L = 0,
    LIGHT_SECTION_HL_R,
    LIGHT_SECTION_BODY
} Light_Sections;

typedef enum {
    LIGHT_COLOR_NONE = 0,
    LIGHT_COLOR_RED,
    LIGHT_COLOR_GREEN,
    LIGHT_COLOR_BLUE,
    LIGHT_COLOR_PURPLE,
} Light_Colors;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Light_Color_t;

extern const Light_Color_t light_color_none;
extern const Light_Color_t light_color_red;
extern const Light_Color_t light_color_green;
extern const Light_Color_t light_color_blue;
extern const Light_Color_t light_color_purple;

esp_err_t Light_Init(void);

void Light_SetColor(Light_Sections section, Light_Color_t color);

#endif // __LIGHT_H_