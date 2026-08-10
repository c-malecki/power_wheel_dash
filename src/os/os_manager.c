#include "os_manager.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "os_event.h"
#include "os_kernel.h"
#include "ui_controller.h"

SemaphoreHandle_t os_mutex = NULL;

static void os_manager_task(void *arg);
static void display_task(void *arg);

/* INTERFACE */

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

  xTaskCreatePinnedToCore(os_manager_task, "os_manager_task", 4096, NULL, 10,
                          NULL, 0);

  xTaskCreatePinnedToCore(display_task, "display task", 16384, NULL, 5, NULL,
                          1);

  return ESP_OK;
}

/* SETUP */

static void os_manager_task(void *arg) {
  OS_Event_t os_event;
  while (1) {
    if (xQueueReceive(os_event_queue, &os_event, portMAX_DELAY)) {
      xSemaphoreTake(os_mutex, portMAX_DELAY);
      ESP_LOGI("OS_MANAGER", "os_manager_task queue");

      switch (os_event.rx_controller_id) {
      case OS_CONTROLLER_UI:
        UI_Controller_RX(&os_event);
        break;

      case OS_CONTROLLER_LIGHT:

        break;

      case OS_CONTROLLER_NONE:

        break;
      }

      xSemaphoreGive(os_mutex);
    }
  }
}

static void display_task(void *arg) {
  while (1) {
    if (xSemaphoreTake(os_mutex, portMAX_DELAY) == pdTRUE) {
      lv_timer_handler();
      xSemaphoreGive(os_mutex);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}