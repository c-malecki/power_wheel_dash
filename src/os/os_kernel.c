#include "os_kernel.h"
#include "driver_display.h"
#include "driver_led.h"
#include "driver_sound.h"
#include "driver_storage.h"
#include "esp_log.h"

esp_err_t OS_Kernel_Init(void) {
  esp_err_t err = DisplayDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "display driver initialized");

  err = StorageDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "storage driver initialized");

  err = SoundDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "sound driver initialized");

  err = LEDDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "led driver initialized");

  return ESP_OK;
}