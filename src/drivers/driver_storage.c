
#include "driver_storage.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include <sys/stat.h>
#include <sys/unistd.h>

/*
https://docs.espressif.com/projects/esp-idf/en/release-v6.1/esp32s3/api-reference/peripherals/sdmmc_host.html

Of all the functions listed below, only the following ones will be used
directly by most applications:

sdmmc_host_init()

sdmmc_host_init_slot()

sdmmc_host_deinit()

*/

sdmmc_card_t *sd_card = NULL;

esp_err_t StorageDriver_Init(void) {
  spi_bus_config_t spi_bus_msd = {
      .sclk_io_num = SPI_CLK_PIN_MSD,
      .mosi_io_num = SPI_MOSI_PIN_MSD,
      .miso_io_num = SPI_MISO_PIN_MSD,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 4000,
  };
  esp_err_t err = spi_bus_initialize(SPI3_HOST, &spi_bus_msd, SPI_DMA_CH_AUTO);
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("STORAGE DRIVER", "msd spi bus initialized");

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024,
  };

  sdmmc_card_t *card;
  const char mount_point[] = MOUNT_POINT;

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  host.slot = SPI3_HOST;
  host.unaligned_multi_block_rw_max_chunk_size = 8;
  // HW-125 MicroSD module is not reliable without slower speed
  host.max_freq_khz = MSD_MAX_FREQ;

  sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
  slot_config.host_id = SPI3_HOST;
  slot_config.gpio_cs = MSD_CS_PIN;

  err = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config,
                                &card);
  if (err != ESP_OK) {
    ESP_LOGE("STORAGE DRIVER", "esp_vfs_fat_sdspi_mount error: 0x%x", err);
    return err;
  }
  ESP_LOGI("STORAGE DRIVER", "microsd card initialized via SPI");

  sd_card = card;
  sdmmc_card_print_info(stdout, sd_card);

  return ESP_OK;
}

/*

 sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.clk = SPI_CLK_PIN_MSD;
  slot_config.cmd = SPI_MOSI_PIN_MSD;
  slot_config.d0 = SPI_MISO_PIN_MSD;
  // HW-125 MicroSD module doesn't include CD or WP
  slot_config.gpio_cd = GPIO_NUM_NC;
  slot_config.gpio_wp = GPIO_NUM_NC;

*/