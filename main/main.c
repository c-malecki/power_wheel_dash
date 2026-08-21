#include "config.h"
#include "controller_central.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "model.h"

void app_main(void) {
  esp_err_t err = CONFIG_DRIVERS_INIT();
  if (err != ESP_OK) {
    ESP_LOGE("app_main", "err code %d", err);
  }

  SYS_MODEL_INIT();

  // inits other controllers and UI controller
  // starts lvgl task
  Central_Controller_Init();

  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
