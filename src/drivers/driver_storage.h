#ifndef __DRIVER_STORAGE_H_
#define __DRIVER_STORAGE_H_

#include "esp_err.h"

/*
https://docs.espressif.com/projects/esp-idf/en/release-v6.1/esp32s3/api-reference/peripherals/sdmmc_host.html
*/

#define SPI_MOSI_PIN_MSD (37)
#define SPI_CLK_PIN_MSD (36)
#define SPI_MISO_PIN_MSD (35)

#define MSD_CS_PIN (38)
#define MSD_MAX_FREQ (10000)

#define MOUNT_POINT "/sdcard"

esp_err_t StorageDriver_Init(void);

#endif // __DRIVER_STORAGE_H_