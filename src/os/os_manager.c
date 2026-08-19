#include "os_manager.h"
#include "controller_light.h"
#include "controller_sound.h"
#include "controller_storage.h"
#include "controller_ui.h"
#include "esp_err.h"
#include "esp_log.h"
#include "global.h"
#include "lvgl.h"
#include "os_kernel.h"

SemaphoreHandle_t os_mutex = NULL;

static void os_manager_task(void *arg);
static void display_task(void *arg);

esp_err_t OS_Manager_Init(void) {
  esp_err_t err = OS_Kernel_Init();
  if (err != ESP_OK) {
    return err;
  }

  G_Event_Queue_Init();
  os_mutex = xSemaphoreCreateMutex();

  xSemaphoreTake(os_mutex, portMAX_DELAY);
  UI_Controller_Init();
  xSemaphoreGive(os_mutex);
  ESP_LOGI("OS_MANANGER", "UI_Controller initialized");

  // xSemaphoreTake(os_mutex, portMAX_DELAY);
  // Storage_Controller_Init();
  // xSemaphoreGive(os_mutex);
  // ESP_LOGI("OS_MANANGER", "Storage_Controller initialized");

  // Sound_Controller_Init();
  // ESP_LOGI("OS_MANANGER", "Sound_Controller initialized");

  Light_Controller_Init();
  ESP_LOGI("OS_MANANGER", "Light_Controller initialized");

  xTaskCreatePinnedToCore(os_manager_task, "os_manager_task", 8192, NULL, 10,
                          NULL, 0);

  xTaskCreatePinnedToCore(display_task, "display_task", 16384, NULL, 5, NULL,
                          1);

  return ESP_OK;
}

// FILE *OS_Manager_Request_File(const char *path) {
/*
    get file from storage driver
*/
// }

static void os_manager_task(void *arg) {
  G_Event_t g_event;
  while (1) {
    if (xQueueReceive(g_event_queue, &g_event, portMAX_DELAY)) {

      switch (g_event.rx_controller_id) {
      case G_CONTROLLER_UI:
        xSemaphoreTake(os_mutex, portMAX_DELAY);
        UI_Controller_RX(&g_event);
        xSemaphoreGive(os_mutex);
        break;

      case G_CONTROLLER_LIGHT:
        xSemaphoreTake(os_mutex, portMAX_DELAY);
        Light_Controller_RX(&g_event);
        xSemaphoreGive(os_mutex);
        break;

      case G_CONTROLLER_SOUND:
        xSemaphoreTake(os_mutex, portMAX_DELAY);
        Sound_Controller_RX(&g_event);
        xSemaphoreGive(os_mutex);
        break;

      case G_CONTROLLER_STORAGE:
        xSemaphoreTake(os_mutex, portMAX_DELAY);
        Storage_Controller_RX(&g_event);
        xSemaphoreGive(os_mutex);
        break;

      case G_CONTROLLER_NONE:

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