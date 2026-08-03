#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "light.h"
#include "os.h"

static OS_t OS;

void app_main(void) {
  ESP_ERROR_CHECK(OS_Init(&OS));

  Light_SetColor(LIGHT_SECTION_HL_L, light_color_blue);

  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1500));

    // Light_SetColor(LIGHT_SECTION_HL_L, light_color_red);
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // Light_SetColor(LIGHT_SECTION_HL_L, light_color_green);
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // Light_SetColor(LIGHT_SECTION_HL_L, light_color_blue);
    // vTaskDelay(pdMS_TO_TICKS(1500));

    // Light_SetColor(LIGHT_SECTION_HL_L, light_color_purple);
    // vTaskDelay(pdMS_TO_TICKS(1500));
  }
}
