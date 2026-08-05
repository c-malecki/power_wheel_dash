#ifndef __CAR_MANAGER_H_
#define __CAR_MANAGER_H_

#include <stdbool.h>
#include "data_types.h"

// todo: X_is_on for OE on/off switch, not LED_COLOR_NONE_ID

typedef struct
{
    DT_LED_Strip_ID hll_strip_id;
    bool hll_is_on;
    DT_LED_Color_ID hll_strip_color_id;

    DT_LED_Strip_ID hlr_strip_id;
    bool hlr_is_on;
    DT_LED_Color_ID hlr_strip_color_id;

    DT_LED_Strip_ID body_strip_id;
    bool body_is_on;
    DT_LED_Color_ID body_strip_color_id;
} Car_Manager_t;

void Car_Manager_Init(void);
void Car_Manager_HandleOSEvent(DT_OS_Event_t os_event);
void Car_Manager_SetLED(DT_LED_Strip_ID led_strip_id, DT_LED_Color_ID led_color_id,
                        bool led_strip_on);

#endif // __CAR_MANAGER_H_