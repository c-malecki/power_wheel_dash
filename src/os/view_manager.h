#ifndef __VIEW_MANAGER_H_
#define __VIEW_MANAGER_H_

#include "data_types.h"

void View_Manager_Init(void);
void View_Manager_Navigate(DATA_TYPE_ID_UIViews new_view_id);
void View_Manager_RenderView(const DATA_TYPE_UI_ViewDesc_t *new_view);

#endif // __VIEW_MANAGER_H_