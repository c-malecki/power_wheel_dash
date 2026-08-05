#include "event_manager.h"
#include "data_types.h"
#include "esp_log.h"
#include "lvgl.h"
#include "os.h"
// #include <string.h>

void handle_action_set_value(DT_OS_Event_t *os_event, DT_UI_Input_t *ui_input);

static void input_touch_event_cb(lv_event_t *event) {
  ESP_LOGI("EVENT TRACE", "input_touch_event_cb");
  if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
    lv_obj_t *event_target = lv_event_get_target(event);
    DT_UI_Input_t *ui_input = lv_obj_get_user_data(event_target);

    DT_OS_Event_t os_event = {.from_input = ui_input};
    bool post_event = false;

    switch (ui_input->to_manager_id) {
    case OSMANAGER_VIEW_ID:

      // if (strcmp(ui_input->name, UI_INPUT_HOME_BUTTON_NAME) == 0) {
      os_event.data.view_id = (DT_UI_ViewDesc_ID)ui_input->action_data;
      post_event = true;
      // }
      break;

    case OSMANAGER_CAR_ID:
      handle_action_set_value(&os_event, ui_input);
      post_event = true;
      break;

    case OSMANAGER_MEDIA_ID:
      break;
    }

    if (post_event) {
      OS_PostEvent(os_event);
    }
  }
}

void handle_action_set_value(DT_OS_Event_t *os_event, DT_UI_Input_t *ui_input) {
  switch (os_event->event_id) {
  case OSEVENT_LED_UPDATE_ID:
    os_event->event_id = OSEVENT_LED_UPDATE_ID;
    os_event->data.led_strip_id = (DT_LED_Strip_ID)ui_input->action_data;
    os_event->data.led_color_id = (DT_LED_Color_ID)ui_input->action_data;
    os_event->data.led_strip_on = (bool)ui_input->action_data;
    break;

  case OSEVENT_NONE_ID:

    break;
  }
}

lv_event_cb_t Event_Manager_GetTouchHandler(void) {
  return input_touch_event_cb;
}