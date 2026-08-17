#include "os_kernel.h"
#include "display.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "led.h"
#include "storage.h"

esp_err_t OS_Kernel_Init(void) {
  esp_err_t err = Storage_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "storage initialized");

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