#ifndef __STATE_H_
#define __STATE_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "lvgl.h"

extern QueueHandle_t os_event_queue;
extern SemaphoreHandle_t os_state_mutex;

extern lv_subject_t state_active_screen_id;
extern lv_subject_t state_pending_screen_id;
extern lv_subject_t state_headlight_color_id;
extern lv_subject_t state_bodylight_color_id;
extern lv_subject_t state_show_system_home_button;

void System_State_Init(void);

#endif // __STATE_H_