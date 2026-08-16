#include "os_kernel.h"
#include "display.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "led.h"

#define SPI_MOSI_PIN 11
#define SPI_CLK_PIN 12
#define SPI_MISO_PIN 13

esp_err_t OS_Kernel_Init(void) {
  spi_bus_config_t buscfg = {
      .sclk_io_num = SPI_CLK_PIN,
      .mosi_io_num = SPI_MOSI_PIN,
      .miso_io_num = SPI_MISO_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  esp_err_t err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "spi initialized");

  err = Display_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "display initialized");

  err = LED_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "leds initialized");

  return ESP_OK;
}