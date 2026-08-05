#ifndef __VIEW_MANAGER_H_
#define __VIEW_MANAGER_H_

#include "ui.h"

void View_Manager_Init(void);
void View_Manager_Navigate(UI_View_IDs new_view_id);
void View_Manager_RenderView(const UI_View_t *new_view);

#endif // __VIEW_MANAGER_H_