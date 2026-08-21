#include "state.h"
#include "global.h"

QueueHandle_t g_event_queue = NULL;
SemaphoreHandle_t g_state_mutex = NULL;

lv_subject_t state_show_layer_os;

lv_subject_t state_active_screen_id;
lv_subject_t state_pending_screen_id;
lv_subject_t state_headlight_color_id;
lv_subject_t state_bodylight_color_id;

void G_State_Init(void) {
  g_event_queue = xQueueCreate(10, sizeof(G_Event_t));
  g_state_mutex = xSemaphoreCreateMutex();

  lv_subject_init_int(&state_show_layer_os, 0);

  lv_subject_init_int(&state_active_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&state_pending_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&state_headlight_color_id, G_COLOR_NONE);
  lv_subject_init_int(&state_bodylight_color_id, G_COLOR_NONE);
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