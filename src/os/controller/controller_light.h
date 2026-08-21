#ifndef __CONTROLLER_LIGHT_H_
#define __CONTROLLER_LIGHT_H_

#include "types.h"

void Light_Controller_Init(void);
void Light_Controller_RX(OS_Event_t *os_event);

#endif // __CONTROLLER_LIGHT_H_