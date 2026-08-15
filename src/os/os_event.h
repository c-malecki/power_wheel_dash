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

typedef enum {
  OS_EVENT_NONE = 0,
  OS_EVENT_NAVIGATE,
  OS_EVENT_LIGHT_SELECT,
} OS_Event_ID;

typedef struct {
  OS_Controller_ID tx_controller_id;
  OS_Controller_ID rx_controller_id;
  OS_Event_ID event_id;
  uint32_t payload;
} OS_Event_t;

typedef void (*os_event_ui_intercept_cb)(OS_Event_t *os_event);

void OS_Event_Queue_Init(void);

OS_Event_t OS_Event_Create(OS_Controller_ID tx_controller_id,
                           OS_Controller_ID rx_controller_id,
                           OS_Event_ID event_id, uint32_t payload);

#endif // __OS_STATE_H_
