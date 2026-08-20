#include "os_manager.h"
#include "controller_light.h"
#include "controller_sound.h"
#include "controller_storage.h"
#include "controller_ui.h"
#include "esp_err.h"
#include "esp_log.h"
#include "global.h"
#include "os_kernel.h"
#include "state.h"

static void os_manager_task(void *arg) {
  G_Event_t g_event;
  while (1) {
    if (xQueueReceive(g_event_queue, &g_event, portMAX_DELAY)) {

      switch (g_event.rx_controller_id) {
      case G_CONTROLLER_UI:
        UI_Controller_RX(&g_event);
        break;

      case G_CONTROLLER_LIGHT:
        Light_Controller_RX(&g_event);
        break;

      case G_CONTROLLER_SOUND:
        Sound_Controller_RX(&g_event);
        break;

      case G_CONTROLLER_STORAGE:
        Storage_Controller_RX(&g_event);
        break;

      case G_CONTROLLER_NONE:

        break;
      }
    }
  }
}

esp_err_t OS_Manager_Init(void) {
  esp_err_t err = OS_Kernel_Init();
  if (err != ESP_OK) {
    return err;
  }

  G_State_Init();

  UI_Controller_Init();
  ESP_LOGI("OS_MANANGER", "UI_Controller initialized");

  Storage_Controller_Init();
  // ESP_LOGI("OS_MANANGER", "Storage_Controller initialized");

  Sound_Controller_Init();
  // ESP_LOGI("OS_MANANGER", "Sound_Controller initialized");

  Light_Controller_Init();
  // ESP_LOGI("OS_MANANGER", "Light_Controller initialized");

  xTaskCreatePinnedToCore(os_manager_task, "os_manager_task", 8192, NULL, 10,
                          NULL, 0);

  return ESP_OK;
}
