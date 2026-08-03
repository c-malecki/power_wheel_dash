#include "config.h"
#include "display.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "light.h"
#include "os.h"

static OS_t OS;

void app_main(void) {
  spi_bus_config_t buscfg = {
      .sclk_io_num = SPI_CLK_PIN,
      .mosi_io_num = SPI_MOSI_PIN,
      .miso_io_num = SPI_MISO_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  ESP_ERROR_CHECK(spi_bus_initialize(SPI_HOST_PIN, &buscfg, SPI_DMA_CH_AUTO));

  ESP_ERROR_CHECK(Display_Control_Init(&OS.display));
  ESP_ERROR_CHECK(Light_Control_Init(&OS.lights));

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
