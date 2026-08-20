#include "state.h"
#include "global.h"

static G_State_t g_state;

QueueHandle_t g_event_queue = NULL;
SemaphoreHandle_t g_state_mutex = NULL;

void G_State_Init(void) {
  g_event_queue = xQueueCreate(10, sizeof(G_Event_t));
  g_state_mutex = xSemaphoreCreateMutex();

  lv_subject_init_int(&g_state.light_headlight_color, G_COLOR_NONE);
  lv_subject_init_int(&g_state.light_bodylight_color, G_COLOR_NONE);
}

void G_State_SetPropValue(G_State_Prop_ID state_prop_id, uint32_t payload) {
  switch (state_prop_id) {
  case G_STATE_PROP_HEADLIGHT_COLOR: {
    lv_subject_set_int(&g_state.light_headlight_color, payload);
    break;
  }

  case G_STATE_PROP_BODYLIGHT_COLOR: {
    lv_subject_set_int(&g_state.light_bodylight_color, payload);
    break;
  }

  case G_STATE_PROP_NONE:
    break;
  }
}

G_Event_t G_Event_Create(G_Controller_ID tx_controller_id,
                         G_Controller_ID rx_controller_id, G_Event_ID event_id,
                         uint32_t payload) {
  return (G_Event_t){
      .tx_controller_id = tx_controller_id,
      .rx_controller_id = rx_controller_id,
      .event_id = event_id,
      .payload = payload,
  };
}