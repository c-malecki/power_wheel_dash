#ifndef __OS_MANAGER_H_
#define __OS_MANAGER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

extern QueueHandle_t os_event_queue;
extern SemaphoreHandle_t os_mutex;

esp_err_t OS_Manager_Init(void);

#endif // __OS_MANAGER_H_
