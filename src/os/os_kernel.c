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

  err = LEDDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "led driver initialized");

  // err = SoundDriver_Init();
  // if (err != ESP_OK) {
  //   return err;
  // }
  // ESP_LOGI("OS_KERNEL", "sound driver initialized");

  err = StorageDriver_Init();
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("OS_KERNEL", "storage driver initialized");

  return ESP_OK;
}

/*

E (477) SD_HOST: sd_host_sdmmc_controller_add_slot(143): invalid argument: null
pointer E (487) sdmmc_periph: sdmmc_host_init_slot(145): failed to add new SD
slot E (497) vfs_fat_sdmmc: slot init failed (0x102). E (497) vfs_fat_sdmmc:
esp_vfs_fat_sdmmc_sdcard_init failed (0x102).

*/