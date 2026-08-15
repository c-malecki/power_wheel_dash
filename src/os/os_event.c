#include "os_event.h"

QueueHandle_t os_event_queue = NULL;

void OS_Event_Queue_Init(void) {
  os_event_queue = xQueueCreate(10, sizeof(OS_Event_t));
}

OS_Event_t OS_Event_Create(OS_Controller_ID tx_controller_id,
                           OS_Controller_ID rx_controller_id,
                           OS_Event_ID event_id, uint32_t payload) {
  return (OS_Event_t){
      .tx_controller_id = tx_controller_id,
      .rx_controller_id = rx_controller_id,
      .event_id = event_id,
      .payload = payload,
  };
}