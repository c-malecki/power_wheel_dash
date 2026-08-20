#ifndef __CONTROLLER_LIGHT_H_
#define __CONTROLLER_LIGHT_H_

#include "state.h"

void Light_Controller_Init(void);
void Light_Controller_RX(G_Event_t *g_event);

#endif // __CONTROLLER_LIGHT_H_