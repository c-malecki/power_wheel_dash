
#include "storage.h"
#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>

sdmmc_card_t *sd_card = NULL;

esp_err_t Storage_Init(void) {
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
  ESP_LOGI("STORAGE DRIVER", "lcd spi bus initialized");

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024,
  };

  sdmmc_card_t *card;
  const char mount_point[] = MOUNT_POINT;

  // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
  // For setting a specific frequency, use host.max_freq_khz (range 400kHz -
  // 40MHz for SDMMC) Example: for fixed frequency of 10MHz, use
  // host.max_freq_khz = 10000;
  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  host.slot = SPI3_HOST;
  host.unaligned_multi_block_rw_max_chunk_size = 8;
  host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;

  // This initializes the slot without card detect (CD) and write protect (WP)
  // signals. Modify slot_config.gpio_cd and slot_config.gpio_wp if your board
  // has these signals.
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

  slot_config.clk = SPI_CLK_PIN_MSD;
  slot_config.cmd = SPI_MOSI_PIN_MSD;
  slot_config.d0 = SPI_MISO_PIN_MSD;

  err = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config,
                                &card);
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("STORAGE DRIVER", "file system initialized");

  // Card has been initialized, print its properties
  sdmmc_card_print_info(stdout, card);

  return ESP_OK;
}