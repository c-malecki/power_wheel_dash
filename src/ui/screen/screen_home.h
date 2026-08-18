#ifndef __UI_SCREEN_HOME_H_
#define __UI_SCREEN_HOME_H_

#include "global.h"
#include "lvgl.h"

void Home_Screen_Render(lv_obj_t *screen,
                        g_event_ui_intercept_cb ui_controller_injection_cb);

#endif // __UI_SCREEN_HOME_H_