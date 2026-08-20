#ifndef __CONTROLLER_STORAGE_H_
#define __CONTROLLER_STORAGE_H_

#include "state.h"

extern SemaphoreHandle_t ui_controller_mutex;

void Storage_Controller_Init(void);
void Storage_Controller_RX(G_Event_t *g_event);

#endif // __CONTROLLER_STORAGE_H_