#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "view.h"
#include "light.h"

extern SemaphoreHandle_t OS_state_mutex;

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
        // todo: move light into some sort of OS module
        Light_Colors color;
    } data;
} OS_Event_t;

esp_err_t OS_Init(void);
void OS_Navigate(UI_View_IDs new_view_id);
void OS_PostEvent(OS_Event_t event);

#endif // __OS_H_