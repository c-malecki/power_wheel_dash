#ifndef __SYSTEM_CONTROLLER_H_
#define __SYSTEM_CONTROLLER_H_

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

extern QueueHandle_t system_event_queue;
extern SemaphoreHandle_t system_mutex;

esp_err_t System_Controller_Init(void);

#endif // __SYSTEM_CONTROLLER_H_
