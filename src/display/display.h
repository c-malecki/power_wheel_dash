#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "esp_err.h"
#include "ui.h"
#include "lvgl.h"

#define DISPLAY_LCD_DC_PIN (8)
#define DISPLAY_LCD_RST_PIN (9)
#define DISPLAY_LCD_CS_PIN (10)
#define DISPLAY_LCD_LED_PIN (18)

#define DISPLAY_LCD_T_IRQ_PIN (16)
#define DISPLAY_LCD_T_CS_PIN (17)

esp_err_t Display_Init();
void Display_TaskRun(void);
void Display_Navigate(UI_Screen_IDs ui_screen_id);

#endif // __DISPLAY_H_