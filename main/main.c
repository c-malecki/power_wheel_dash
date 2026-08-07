#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_controller.h"

void app_main(void) {
  ESP_ERROR_CHECK(System_Controller_Init());

  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}
