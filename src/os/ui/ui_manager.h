#ifndef __UI_MANAGER_H_
#define __UI_MANAGER_H_

#include "view.h"

typedef struct
{

} UI_Manager_t;

void UI_Manager_Init(void);
void UI_Manager_RenderView(const UI_View_t *new_view);

#endif // __UI_MANAGER_H_