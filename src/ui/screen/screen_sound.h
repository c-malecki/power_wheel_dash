#ifndef __UI_SCREEN_SOUND_H_
#define __UI_SCREEN_SOUND_H_

#include "global.h"
#include "lvgl.h"

void Sound_Screen_Render(lv_obj_t *screen,
                         g_event_ui_intercept_cb ui_controller_injection_cb);

#endif // __UI_SCREEN_SOUND_H_