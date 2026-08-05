#ifndef __VIEW_MANAGER_H_
#define __VIEW_MANAGER_H_

#include "data_types.h"
#include "lvgl.h"

void View_Manager_Init(lv_event_cb_t touch_cb);
void View_Manager_HandleOSEvent(DT_OS_Event_t os_event);
void View_Manager_Navigate(DT_UI_ViewDesc_ID new_view_id);
void View_Manager_RenderView(const DT_UI_ViewDesc_t *new_view);

#endif // __VIEW_MANAGER_H_