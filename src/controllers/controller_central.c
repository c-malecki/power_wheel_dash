#include "controller_central.h"
#include "controller_light.h"
#include "controller_sound.h"
#include "controller_storage.h"
#include "controller_ui.h"
#include "esp_log.h"
#include "model.h"
#include "types.h"

static void central_controller_task(void *arg) {
  Sys_Event_t sys_event;
  while (1) {
    if (xQueueReceive(SYS_EVENT_QUEUE, &sys_event, portMAX_DELAY)) {

      switch (sys_event.rx_controller_id) {
      case SYS_CONTROLLER_UI:
        UI_Controller_RX(&sys_event);
        break;

      case SYS_CONTROLLER_LIGHT:
        Light_Controller_RX(&sys_event);
        break;

      case SYS_CONTROLLER_SOUND:
        Sound_Controller_RX(&sys_event);
        break;

      case SYS_CONTROLLER_STORAGE:
        Storage_Controller_RX(&sys_event);
        break;

      case SYS_CONTROLLER_NONE:

        break;
      }
    }
  }
}

void Central_Controller_Init(void) {
  // starts lvgl task
  UI_Controller_Init();
  ESP_LOGI("CENTRAL_CTRL", "UI_Controller initialized");

  Storage_Controller_Init();
  ESP_LOGI("CENTRAL_CTRL", "Storage_Controller initialized");

  Sound_Controller_Init();
  ESP_LOGI("CENTRAL_CTRL", "Sound_Controller initialized");

  Light_Controller_Init();
  ESP_LOGI("CENTRAL_CTRL", "Light_Controller initialized");

  xTaskCreatePinnedToCore(central_controller_task, "central_controller_task",
                          8192, NULL, 10, NULL, 0);

  SYS_MODEL_SET_PROP(SYSTEM_MODEL_PROP_ACTIVE_SCREEN_ID, UI_SCREEN_HOME);
}
