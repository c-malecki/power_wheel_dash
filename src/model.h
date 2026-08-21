#ifndef __MODEL_H_
#define __MODEL_H_

#include "core/lv_observer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "lvgl.h"
#include <stdint.h>

extern QueueHandle_t SYS_EVENT_QUEUE;

typedef enum {
  SYSTEM_MODEL_PROP_NONE = 0,
  //
  SYSTEM_MODEL_PROP_SHOW_HOME_BUTTON,
  SYSTEM_MODEL_PROP_ACTIVE_SCREEN_ID,
  SYSTEM_MODEL_PROP_PENDING_SCREEN_ID,
  //
  SYSTEM_MODEL_PROP_HEADLIGHT_COLOR_ID,
  SYSTEM_MODEL_PROP_BODYLIGHT_COLOR_ID,
} System_Model_Prop_ID;

typedef struct {
  // view/screens
  lv_subject_t show_home_button;
  lv_subject_t active_screen_id;
  lv_subject_t pending_screen_id;
  // accessories: lights
  lv_subject_t headlight_color_id;
  lv_subject_t bodylight_color_id;
} System_Model_t;

void SYS_MODEL_INIT(void);
void SYS_MODEL_ADD_OBSERVER(System_Model_Prop_ID prop_id,
                            lv_observer_cb_t observer_cb);
void SYS_MODEL_SET_PROP(System_Model_Prop_ID prop_id, uint32_t payload);

#endif // __MODEL_H_