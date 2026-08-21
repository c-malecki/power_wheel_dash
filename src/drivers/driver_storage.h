#ifndef __DRIVER_STORAGE_H_
#define __DRIVER_STORAGE_H_

#include "esp_err.h"
#include <stdio.h>

esp_err_t Driver_Storage_Init(void);
FILE *Storage_Driver_FileRead(const char *path);

#endif // __DRIVER_STORAGE_H_