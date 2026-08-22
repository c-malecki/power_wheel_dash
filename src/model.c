#include "model.h"
#include "core/lv_observer.h"
#include "types.h"

static System_Model_t SYS_MODEL;
QueueHandle_t SYS_EVENT_QUEUE = NULL;

void SYS_MODEL_INIT(void) {
  SYS_EVENT_QUEUE = xQueueCreate(10, sizeof(Sys_Event_t));

  // view/screens
  lv_subject_init_int(&SYS_MODEL.show_home_button, 0);
  lv_subject_init_int(&SYS_MODEL.active_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&SYS_MODEL.pending_screen_id, UI_SCREEN_NONE);
  // accessories: lights
  lv_subject_init_int(&SYS_MODEL.headlight_color_id, G_COLOR_NONE);
  lv_subject_init_int(&SYS_MODEL.bodylight_color_id, G_COLOR_NONE);
}

void SYS_MODEL_ADD_OBSERVER(System_Model_Prop_ID prop_id,
                            lv_observer_cb_t observer_cb) {
  switch (prop_id) {

  case SYSTEM_MODEL_PROP_SHOW_HOME_BUTTON: {
    lv_subject_add_observer(&SYS_MODEL.show_home_button, observer_cb, NULL);
    break;
  }

  case SYSTEM_MODEL_PROP_ACTIVE_SCREEN_ID: {
    lv_subject_add_observer(&SYS_MODEL.active_screen_id, observer_cb, NULL);
    break;
  }

  case SYSTEM_MODEL_PROP_PENDING_SCREEN_ID: {
    lv_subject_add_observer(&SYS_MODEL.pending_screen_id, observer_cb, NULL);
    break;
  }

  case SYSTEM_MODEL_PROP_HEADLIGHT_COLOR_ID: {
    lv_subject_add_observer(&SYS_MODEL.headlight_color_id, observer_cb, NULL);
    break;
  }

  case SYSTEM_MODEL_PROP_BODYLIGHT_COLOR_ID: {
    lv_subject_add_observer(&SYS_MODEL.bodylight_color_id, observer_cb, NULL);
    break;
  }
  case SYSTEM_MODEL_PROP_NONE:
    break;
  }
}

void SYS_MODEL_SET_PROP(System_Model_Prop_ID prop_id, uint32_t payload) {
  switch (prop_id) {

  case SYSTEM_MODEL_PROP_SHOW_HOME_BUTTON: {
    lv_subject_set_int(&SYS_MODEL.show_home_button, payload);
    break;
  }

  case SYSTEM_MODEL_PROP_ACTIVE_SCREEN_ID: {
    lv_subject_set_int(&SYS_MODEL.active_screen_id, payload);
    break;
  }

  case SYSTEM_MODEL_PROP_PENDING_SCREEN_ID: {
    lv_subject_set_int(&SYS_MODEL.pending_screen_id, payload);
    break;
  }

  case SYSTEM_MODEL_PROP_HEADLIGHT_COLOR_ID: {
    lv_subject_set_int(&SYS_MODEL.headlight_color_id, payload);
    break;
  }

  case SYSTEM_MODEL_PROP_BODYLIGHT_COLOR_ID: {
    lv_subject_set_int(&SYS_MODEL.bodylight_color_id, payload);
    break;
  }
  case SYSTEM_MODEL_PROP_NONE:
    break;
  }
}

Sys_Event_t SYS_EVENT_CREATE(Sys_Controller_ID tx_controller_id,
                             Sys_Controller_ID rx_controller_id,
                             Sys_Event_ID event_id, uint32_t payload) {
  return (Sys_Event_t){
      .tx_controller_id = tx_controller_id,
      .rx_controller_id = rx_controller_id,
      .event_id = event_id,
      .payload = payload,
  };
}