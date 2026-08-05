#ifndef __MEDIA_MANAGER_H_
#define __MEDIA_MANAGER_H_

#include "data_types.h"

void Media_Manager_Init(void);
void Media_Manager_HandleOSEvent(DT_OS_Event_t os_event);

#endif // __MEDIA_MANAGER_H_