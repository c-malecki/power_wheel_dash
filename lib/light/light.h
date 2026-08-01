#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "esp_err.h"
#include "led_strip.h"
#include <stdint.h>

#define LIGHT_HEADLIGHT_OE_PIN 1
#define LIGHT_HEADLIGHT_DATA_PIN 2

#define LIGHT_BODYLIGHT_OE_PIN 41
#define LIGHT_BODYLIGHT_DATA_PIN 42

typedef enum {
    LIGHT_CTRL_HEADLIGHT = 0,
    LIGHT_CTRL_BODYLIGHT
} Light_Controllers;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Light_Color_t;

typedef struct
{
    led_strip_handle_t handle;
    Light_Color_t color;
    uint8_t total;
} Light_Control_t;

extern const Light_Color_t light_color_red;
extern const Light_Color_t light_color_green;
extern const Light_Color_t light_color_blue;
extern const Light_Color_t light_color_purple;

esp_err_t Light_Init(void);

void Light_Ctrl_SetColor(Light_Controllers ctrl, Light_Color_t color);

void Headlight_SetColor(uint32_t index, Light_Color_t color);

#endif // __LIGHT_H_