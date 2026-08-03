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
#include "esp_timer.h"
//

#define DISPLAY_LCD_DC_PIN (8)
#define DISPLAY_LCD_RST_PIN (9)
#define DISPLAY_LCD_CS_PIN (10)
#define DISPLAY_LCD_LED_PIN (18)

#define DISPLAY_LCD_T_IRQ_PIN (16)
#define DISPLAY_LCD_T_CS_PIN (17)

esp_err_t Display_Control_Init(void);
void Display_Control_TaskRun(void);

lv_obj_t *Display_CreateIcon(lv_obj_t *parent, lv_color_t color, const char *symbol,
                             const char *name);

#endif // __DISPLAY_H_