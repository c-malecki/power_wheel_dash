#include "os_manager.h"
#include "esp_err.h"
#include "esp_log.h"
#include "light_controller.h"
#include "lvgl.h"
#include "os_event.h"
#include "os_kernel.h"
#include "ui_controller.h"

SemaphoreHandle_t os_mutex = NULL;

static void os_manager_task(void *arg);
static void display_task(void *arg);

esp_err_t OS_Manager_Init(void) {
  esp_err_t err = OS_Kernel_Init();
  if (err != ESP_OK) {
    return err;
  }

  OS_Event_Queue_Init();
  os_mutex = xSemaphoreCreateMutex();

  xSemaphoreTake(os_mutex, portMAX_DELAY);
  UI_Controller_Init();
  xSemaphoreGive(os_mutex);
  ESP_LOGI("OS_MANANGER", "UI_Controller initialized");

  Light_Controller_Init();
  ESP_LOGI("OS_MANANGER", "Light_Controller initialized");

  xTaskCreatePinnedToCore(os_manager_task, "os_manager_task", 4096, NULL, 5,
                          NULL, 0);

  xTaskCreatePinnedToCore(display_task, "display task", 16384, NULL, 10, NULL,
                          1);

  return ESP_OK;
}

static void os_manager_task(void *arg) {
  OS_Event_t os_event;
  while (1) {
    if (xQueueReceive(os_event_queue, &os_event, portMAX_DELAY)) {
      ESP_LOGI("OS_MANAGER", "os_manager_task queue receive event");

      switch (os_event.rx_controller_id) {
      case OS_CONTROLLER_UI:
        // xSemaphoreTake(os_mutex, portMAX_DELAY);
        // UI_Controller_RX(&os_event);
        // xSemaphoreGive(os_mutex);
        break;

      case OS_CONTROLLER_LIGHT:
        xSemaphoreTake(os_mutex, portMAX_DELAY);
        Light_Controller_RX(&os_event);
        xSemaphoreGive(os_mutex);
        break;

      case OS_CONTROLLER_NONE:

        break;
      }
    }
  }
}

static void display_task(void *arg) {
  const TickType_t period = pdMS_TO_TICKS(10);
  TickType_t last_wake = xTaskGetTickCount();

  while (1) {
    xSemaphoreTake(os_mutex, portMAX_DELAY);
    lv_timer_handler();
    xSemaphoreGive(os_mutex);

    vTaskDelayUntil(&last_wake, period);
  }
}