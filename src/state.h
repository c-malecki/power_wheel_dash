#ifndef __STATE_H_
#define __STATE_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "global.h"
#include "lvgl.h"
#include "ui_definitions.h"
#include <stdint.h>

extern QueueHandle_t g_event_queue;
extern SemaphoreHandle_t g_state_mutex;

extern lv_subject_t state_active_screen_id;
extern lv_subject_t state_pending_screen_id;
extern lv_subject_t state_headlight_color_id;
extern lv_subject_t state_bodylight_color_id;

typedef struct {
  G_Controller_ID tx_controller_id;
  G_Controller_ID rx_controller_id;
  G_Event_ID event_id;
  uint32_t payload;
  void *payload_data;
} G_Event_t;

typedef void (*g_event_ui_intercept_cb)(G_Event_t *g_event);

void G_State_Init(void);

#endif // __STATE_H_