#ifndef __STORAGE_H_
#define __STORAGE_H_

#include "esp_err.h"

#define SPI_MOSI_PIN_MSD (37)
#define SPI_CLK_PIN_MSD (36)
#define SPI_MISO_PIN_MSD (35)

#define MSD_CS_PIN (38)

#define MOUNT_POINT "/sdcard"

esp_err_t Storage_Init(void);

#endif // __STORAGE_H_