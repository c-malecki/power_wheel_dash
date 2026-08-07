#ifndef __SYSTEM_DEFINITIONS_H_
#define __SYSTEM_DEFINITIONS_H_

#include <stdint.h>

typedef enum {
    SYSTEM_CONTROLLER_NONE = 0,
    SYSTEM_CONTROLLER_UI,
    SYSTEM_CONTROLLER_LIGHT,
} System_Controller_e;

typedef enum {
    SYSTEM_ACTION_NONE = 0,
    SYSTEM_ACTION_UI_UPDATE,
    SYSTEM_ACTION_LIGHT_UPDATE,
} System_Action_e;

typedef struct
{
    System_Controller_e destination;
    System_Action_e action;
    uint32_t payload;
} System_Event_t;

#endif // __SYSTEM_DEFINITIONS_H_