#include "os_event.h"

QueueHandle_t os_event_queue = NULL;

void OS_Event_Queue_Init(void) {
  os_event_queue = xQueueCreate(10, sizeof(OS_Event_t));
}