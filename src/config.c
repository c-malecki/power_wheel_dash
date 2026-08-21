#include "config.h"
#include "driver_display.h"
#include "driver_led.h"
#include "driver_sound.h"
#include "driver_storage.h"

esp_err_t CONFIG_DRIVERS_INIT(void) {
  esp_err_t err = Driver_Display_Init();
  if (err != ESP_OK) {
    return err;
  }
  // ESP_LOGI("OS_KERNEL", "display driver initialized");

  err = Driver_Storage_Init();
  if (err != ESP_OK) {
    return err;
  }
  // ESP_LOGI("OS_KERNEL", "storage driver initialized");

  err = Driver_Sound_Init();
  if (err != ESP_OK) {
    return err;
  }
  // ESP_LOGI("OS_KERNEL", "sound driver initialized");

  err = Driver_LED_Init();
  if (err != ESP_OK) {
    return err;
  }
  // ESP_LOGI("OS_KERNEL", "led driver initialized");

  return ESP_OK;
}