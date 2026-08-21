#include "controller_ui.h"
#include "esp_log.h"
#include "layer_top.h"
#include "model.h"
#include "screen_home.h"
#include "screen_light.h"
#include "screen_sound.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

SemaphoreHandle_t lvgl_mutex = NULL;

static void ui_controller_task(void *arg) {
  const TickType_t period = pdMS_TO_TICKS(10);
  TickType_t last_wake = xTaskGetTickCount();

  while (1) {
    xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(lvgl_mutex);

    vTaskDelayUntil(&last_wake, period);
  }
}

static void pending_screen_cb(lv_observer_t *observer, lv_subject_t *subject) {
  ESP_LOGI("UI_CONTROLLER", "pending_screen_cb");

  Sys_Screen_ID screen_id = (Sys_Screen_ID)lv_subject_get_int(subject);

  if (screen_id == UI_SCREEN_NONE) {
    return;
  }

  // handle whatever other stuff needs to be done

  SYS_MODEL_SET_PROP(SYSTEM_MODEL_PROP_ACTIVE_SCREEN_ID, screen_id);
}

void UI_Controller_Init(void) {
  lvgl_mutex = xSemaphoreCreateMutex();
  assert(lvgl_mutex != NULL);

  lv_subject_add_observer(&SYS_MODEL.pending_screen_id, pending_screen_cb,
                          NULL);

  Layer_Top_Init();

  Home_Screen_Init();
  Sound_Screen_Init();
  Light_Screen_Init();

  xTaskCreatePinnedToCore(ui_controller_task, "ui_controller_task", 16384, NULL,
                          5, NULL, 1);
}

void UI_Controller_RX(Sys_Event_t *sys_event) {}