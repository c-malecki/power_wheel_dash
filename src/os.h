#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "lvgl.h"

typedef enum {
    OS_SCREEN_HOME = 0,
    OS_SCREEN_LIGHT_CONTROL,
    OS_SCREEN_LIGHT_COLOR,
} OS_Screen_IDs;

typedef enum {
    OS_LIGHT_COLOR_NONE = 0,
    OS_LIGHT_COLOR_RED,
    OS_LIGHT_COLOR_GREEN,
    OS_LIGHT_COLOR_BLUE,
    OS_LIGHT_COLOR_PURPLE,
} OS_Light_Colors;

typedef enum {
    OS_EVENT_NAVIGATE,
    OS_EVENT_LIGHT_CHANGE,
    OS_EVENT_SPEED_UPDATE,
} OS_Event_Type_t;

typedef struct
{
    OS_Event_Type_t type;
    union {
        OS_Screen_IDs screen_id;
        OS_Light_Colors color;
    } data;
} OS_Event_t;

typedef struct
{
    OS_Screen_IDs current_screen;
    OS_Light_Colors light_hll_color;
    OS_Light_Colors light_hlr_color;
    OS_Light_Colors light_body_color;
} OS_State_t;

esp_err_t OS_Init(void);
void OS_PostEvent(OS_Event_t event);
OS_State_t OS_GetState(void);

#endif // __OS_H_