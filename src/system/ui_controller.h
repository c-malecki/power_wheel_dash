#ifndef __UI_CONTROLLER_H_
#define __UI_CONTROLLER_H_

#include "system_definitions.h"
#include "lvgl.h"

void UI_Controller_Init(void);
void UI_Controller_HandleSystemEvent(System_Event_t *system_event);

#endif // __UI_CONTROLLER_H_