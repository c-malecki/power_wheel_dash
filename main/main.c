#include "config.h"
#include "display.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "home_screen.h"
#include "light.h"

void app_main(void) {
  ESP_ERROR_CHECK(Light_Init());

  ESP_ERROR_CHECK(Display_Init());

  while (1) {
    Headlight_SetColor(0, light_color_red);
    vTaskDelay(pdMS_TO_TICKS(1500));

    Headlight_SetColor(0, light_color_green);
    vTaskDelay(pdMS_TO_TICKS(1500));

    Headlight_SetColor(0, light_color_blue);
    vTaskDelay(pdMS_TO_TICKS(1500));

    Headlight_SetColor(0, light_color_purple);
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}
