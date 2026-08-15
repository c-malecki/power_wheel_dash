#ifndef __UI_SCREEN_LIGHT_SELECT_H_
#define __UI_SCREEN_LIGHT_SELECT_H_

#include "lvgl.h"
#include "os_event.h"

void Light_Select_Screen_Render(
    lv_obj_t *screen, os_event_ui_intercept_cb ui_controller_injection_cb);

#endif // __UI_SCREEN_LIGHT_SELECT_H_