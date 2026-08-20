#ifndef __STATE_H_
#define __STATE_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "global.h"
#include "lvgl.h"
#include <stdint.h>

extern QueueHandle_t g_event_queue;
extern SemaphoreHandle_t g_state_mutex;

typedef struct {
  G_Controller_ID tx_controller_id;
  G_Controller_ID rx_controller_id;
  G_Event_ID event_id;
  uint32_t payload;
  void *payload_data;
} G_Event_t;

typedef void (*g_event_ui_intercept_cb)(G_Event_t *g_event);

typedef enum {
  G_STATE_PROP_NONE = 0,
  G_STATE_PROP_HEADLIGHT_COLOR,
  G_STATE_PROP_BODYLIGHT_COLOR,
} G_State_Prop_ID;

typedef struct {
  lv_subject_t light_headlight_color;
  lv_subject_t light_bodylight_color;
} G_State_t;

void G_State_Init(void);
void G_State_SetPropValue(G_State_Prop_ID state_prop_id, uint32_t payload);

#endif // __STATE_H_