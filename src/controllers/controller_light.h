#ifndef __CONTROLLER_LIGHT_H_
#define __CONTROLLER_LIGHT_H_

#include "types.h"

void Light_Controller_Init(void);
void Light_Controller_RX(Sys_Event_t *sys_event);

#endif // __CONTROLLER_LIGHT_H_