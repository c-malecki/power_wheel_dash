#ifndef __CONTROLLER_UI_H_
#define __CONTROLLER_UI_H_

#include "global.h"
#include "lvgl.h"
#include "ui_definitions.h"

typedef struct {
  lv_obj_t *current_screen_obj;
  lv_subject_t current_screen_is_home;
  UI_Screen_ID current_screen_id;
  SemaphoreHandle_t ui_mutex;
} UI_Controller_t;

void UI_Controller_Init(void);
void UI_Controller_RX(G_Event_t *g_event);

#endif // __CONTROLLER_UI_H_