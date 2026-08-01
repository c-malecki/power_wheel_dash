#ifndef __UI_H_
#define __UI_H_

#include "esp_log.h"
#include "lvgl.h"

void UI_CreateIcon(lv_obj_t *parent, lv_color_t color, const char *symbol, const char *name);

#endif // __UI_H_