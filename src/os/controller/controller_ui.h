#ifndef __CONTROLLER_UI_H_
#define __CONTROLLER_UI_H_

#include "lvgl.h"
#include "state.h"
#include "ui_definitions.h"
#include <stdint.h>

extern lv_subject_t subject_active_screen_id;
extern lv_subject_t subject_pending_screen_id;

void UI_Controller_Init(void);
void UI_Controller_RX(G_Event_t *g_event);

#endif // __CONTROLLER_UI_H_