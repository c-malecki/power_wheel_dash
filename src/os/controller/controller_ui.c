#include "controller_ui.h"
#include "esp_log.h"
#include "layer_top.h"
#include "screen_home.h"
#include "screen_light.h"
#include "screen_sound.h"
#include "state.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

SemaphoreHandle_t lvgl_mutex = NULL;

static void display_task(void *arg) {
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

  UI_Screen_ID screen_id = (UI_Screen_ID)lv_subject_get_int(subject);

  if (screen_id == UI_SCREEN_NONE) {
    return;
  }

  // handle

  lv_subject_set_int(&state_active_screen_id, screen_id);
}

void UI_Controller_Init(void) {
  lvgl_mutex = xSemaphoreCreateMutex();
  assert(lvgl_mutex != NULL);

  lv_subject_add_observer(&state_pending_screen_id, pending_screen_cb, NULL);

  Layer_Top_Init();

  Home_Screen_Init();
  Sound_Screen_Init();
  Light_Screen_Init();

  xTaskCreatePinnedToCore(display_task, "display_task", 16384, NULL, 5, NULL,
                          1);
}

void UI_Controller_RX(OS_Event_t *os_event) {}