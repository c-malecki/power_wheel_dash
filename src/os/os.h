#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "ui.h"
#include "light.h"

extern SemaphoreHandle_t OS_STATE_MUTEX;

typedef enum {
    OS_EVENT_NAVIGATE,
    OS_EVENT_LIGHT_CHANGE,
    OS_EVENT_SPEED_UPDATE,
} OS_Event_Type_t;

typedef struct
{
    OS_Event_Type_t type;
    union {
        UI_View_IDs view_id;
        // todo: check for lvgl deduplication of my
        // const declarations for colors
        Light_Colors color;
    } data;
} OS_Event_t;

esp_err_t OS_Init(void);
void OS_PostEvent(OS_Event_t event);

#endif // __OS_H_