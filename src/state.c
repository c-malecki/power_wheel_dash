#include "state.h"
#include "types.h"

QueueHandle_t os_event_queue = NULL;
SemaphoreHandle_t os_state_mutex = NULL;

lv_subject_t state_active_screen_id;
lv_subject_t state_pending_screen_id;
lv_subject_t state_headlight_color_id;
lv_subject_t state_bodylight_color_id;
lv_subject_t state_show_system_home_button;

void System_State_Init(void) {
  os_event_queue = xQueueCreate(10, sizeof(OS_Event_t));
  os_state_mutex = xSemaphoreCreateMutex();

  lv_subject_init_int(&state_show_system_home_button, 0);

  lv_subject_init_int(&state_active_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&state_pending_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&state_headlight_color_id, G_COLOR_NONE);
  lv_subject_init_int(&state_bodylight_color_id, G_COLOR_NONE);
}

OS_Event_t OS_Event_Create(OS_Controller_ID tx_controller_id,
                           OS_Controller_ID rx_controller_id,
                           OS_Event_ID event_id, uint32_t payload) {
  return (OS_Event_t){
      .tx_controller_id = tx_controller_id,
      .rx_controller_id = rx_controller_id,
      .event_id = event_id,
      .payload = payload,
  };
}