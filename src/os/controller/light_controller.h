#ifndef __LIGHT_CONTROLLER_H_
#define __LIGHT_CONTROLLER_H_

#include "os_event.h"

void Light_Controller_Init(void);
void Light_Controller_RX(OS_Event_t *os_event);

#endif // __LIGHT_CONTROLLER_H_