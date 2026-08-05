#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdbool.h>
#include "data_types.h"

extern SemaphoreHandle_t OS_STATE_MUTEX;

esp_err_t OS_Init(void);
void OS_PostEvent(DATA_TYPE_OSEvent_t os_event);

#endif // __OS_H_