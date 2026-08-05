#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "ui.h"
#include <stdbool.h>
#include "car_manager.h"

extern SemaphoreHandle_t OS_STATE_MUTEX;

typedef enum {
    OS_EVENT_UPDATE_VIEW,
    OS_EVENT_UPDATE_LED,
} OS_Event_Type_IDs;

typedef struct
{
    OS_Event_Type_IDs type_id;
    union {
        UI_View_IDs view_id;
        Car_Light_IDs car_light_id;
        Car_Light_Color_IDs car_light_color_id;
        bool car_light_on;
    } data;
} OS_Event_t;

esp_err_t OS_Init(void);
void OS_PostEvent(OS_Event_t event);

#endif // __OS_H_