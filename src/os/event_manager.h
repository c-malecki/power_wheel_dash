#ifndef __EVENT_MANAGER_H_
#define __EVENT_MANAGER_H_

#include "data_types.h"
#include "lvgl.h"

void Event_Manager_Init(void);
lv_event_cb_t Event_Manager_GetTouchHandler(void);

#endif // __EVENT_MANAGER_H_