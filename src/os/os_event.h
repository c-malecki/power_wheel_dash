#ifndef __OS_STATE_H_
#define __OS_STATE_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include <stdint.h>

extern QueueHandle_t os_event_queue;

typedef enum {
    OS_CONTROLLER_NONE = 0,
    OS_CONTROLLER_UI,
    OS_CONTROLLER_LIGHT,
} OS_Controller_ID;

typedef struct
{
    OS_Controller_ID rx_controller_id;
    uint32_t payload;
} OS_Event_t;

void OS_Event_Queue_Init(void);

#endif // __OS_STATE_H_
