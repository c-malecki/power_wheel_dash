#include "os_manager.h"
#include "controller_light.h"
#include "controller_sound.h"
#include "controller_storage.h"
#include "controller_ui.h"
#include "esp_err.h"
#include "esp_log.h"
#include "os_kernel.h"
#include "state.h"
#include "types.h"

static void os_manager_task(void *arg) {
  OS_Event_t os_event;
  while (1) {
    if (xQueueReceive(os_event_queue, &os_event, portMAX_DELAY)) {

      switch (os_event.rx_controller_id) {
      case OS_CONTROLLER_UI:
        UI_Controller_RX(&os_event);
        break;

      case OS_CONTROLLER_LIGHT:
        Light_Controller_RX(&os_event);
        break;

      case OS_CONTROLLER_SOUND:
        Sound_Controller_RX(&os_event);
        break;

      case OS_CONTROLLER_STORAGE:
        Storage_Controller_RX(&os_event);
        break;

      case OS_CONTROLLER_NONE:

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

  System_State_Init();

  UI_Controller_Init();
  ESP_LOGI("OS_MANANGER", "UI_Controller initialized");

  Storage_Controller_Init();
  ESP_LOGI("OS_MANANGER", "Storage_Controller initialized");

  Sound_Controller_Init();
  ESP_LOGI("OS_MANANGER", "Sound_Controller initialized");

  Light_Controller_Init();
  ESP_LOGI("OS_MANANGER", "Light_Controller initialized");

  xTaskCreatePinnedToCore(os_manager_task, "os_manager_task", 8192, NULL, 10,
                          NULL, 0);

  // trigger nav to home

  return ESP_OK;
}
