#include "controller_ui.h"
#include "core/lv_observer.h"
#include "esp_log.h"
#include "global.h"
#include "screen_home.h"
#include "screen_light.h"
#include "screen_sound.h"
#include "ui_definitions.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

void create_sys_home_btn(void);

static lv_subject_t show_sys_home;

lv_subject_t subject_pending_screen_id;
lv_subject_t subject_active_screen_id;

SemaphoreHandle_t ui_controller_mutex = NULL;

static void g_state_observer_cb(lv_observer_t *observer,
                                lv_subject_t *subject) {
  G_State_t *g_state = (G_State_t *)lv_subject_get_pointer(subject);

  if (status == SYSTEM_STATUS_CRITICAL_FAULT) {
    // Intercept and force the UI to display the error overlay or alert screen
    lv_subject_set_int(&active_screen_subject, UI_SCREEN_ID_SETTINGS);
  }
}

static void display_task(void *arg) {
  const TickType_t period = pdMS_TO_TICKS(10);
  TickType_t last_wake = xTaskGetTickCount();

  while (1) {
    xSemaphoreTake(ui_controller_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(ui_controller_mutex);

    vTaskDelayUntil(&last_wake, period);
  }
}

static void pending_screen_cb(lv_observer_t *observer, lv_subject_t *subject) {
  ESP_LOGI("UI_CONTROLLER", "pending_screen_cb");

  UI_Screen_ID screen_id = (UI_Screen_ID)lv_subject_get_int(subject);

  if (screen_id == UI_SCREEN_NONE) {
    return;
  }

  // handle

  lv_subject_set_int(&subject_active_screen_id, screen_id);
}

void UI_Controller_Init(void) {
  ui_controller_mutex = xSemaphoreCreateMutex();
  assert(ui_controller_mutex != NULL);

  lv_subject_init_int(&subject_pending_screen_id, UI_SCREEN_NONE);
  lv_subject_init_int(&subject_active_screen_id, UI_SCREEN_NONE);

  ESP_LOGI("UI_CONTROLLER", "before add subject observer");
  lv_subject_add_observer(&subject_pending_screen_id, pending_screen_cb, NULL);
  ESP_LOGI("UI_CONTROLLER", "after add subject observer");

  create_sys_home_btn();

  Home_Screen_Init();
  Sound_Screen_Init();
  Light_Screen_Init();

  xTaskCreatePinnedToCore(display_task, "display_task", 16384, NULL, 5, NULL,
                          1);
}

void UI_Controller_RX(G_Event_t *g_event) {
  /*

  */
}

/* */

static void sys_home_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  lv_subject_set_int(&subject_pending_screen_id, UI_SCREEN_HOME);
}

void create_sys_home_btn(void) {
  lv_obj_t *home_button =
      UI_Create_Button(lv_layer_top(), UI_STYLE_ELEMENT_SYS_BUTTON,
                       G_COLOR_GRAY, LV_SYMBOL_HOME);
  lv_obj_set_pos(home_button, 10, 10);
  lv_obj_add_event_cb(home_button, sys_home_touch_cb, LV_EVENT_CLICKED, NULL);

  lv_subject_init_int(&show_sys_home, 1);
  lv_obj_bind_flag_if_eq(home_button, &show_sys_home, LV_OBJ_FLAG_HIDDEN, 1);
}