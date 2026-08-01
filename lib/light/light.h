#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "esp_err.h"
#include "led_strip.h"
#include "config.h"
#include <stdint.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Light_Color_t;

extern const Light_Color_t light_color_red;
extern const Light_Color_t light_color_green;
extern const Light_Color_t light_color_blue;
extern const Light_Color_t light_color_purple;

esp_err_t Light_Init(void);

void Headlight_SetColor(uint32_t index, Light_Color_t color);

#endif // __LIGHT_H_