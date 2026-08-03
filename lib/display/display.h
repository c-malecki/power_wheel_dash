#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_err.h"
#include "esp_lcd_touch_xpt2046.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include <stdio.h>
#include "config.h"
#include "home_screen.h"
#include "esp_timer.h"

#define DISPLAY_LCD_DC_PIN (8)
#define DISPLAY_LCD_RST_PIN (9)
#define DISPLAY_LCD_CS_PIN (10)
#define DISPLAY_LCD_LED_PIN (18)

#define DISPLAY_LCD_T_IRQ_PIN (16)
#define DISPLAY_LCD_T_CS_PIN (17)

typedef enum {
    DISPLAY_SCREEN_HOME = 0,
    DISPLAY_SCREEN_LIGHTS,
} Display_Screens;

typedef struct
{
    Display_Screens current_screen;
} Display_Control_t;

esp_err_t Display_Control_Init(Display_Control_t *ctrl);

esp_lcd_touch_handle_t Display_GetTouchHandle(void);

esp_err_t Display_SetScreen(Display_Screens screen);

#endif // __DISPLAY_H_