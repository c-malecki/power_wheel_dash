#ifndef __CAR_MANAGER_H_
#define __CAR_MANAGER_H_

#include <stdbool.h>
#include "data_types.h"

// todo: X_is_on for OE on/off switch, not LED_COLOR_NONE_ID

typedef struct
{
    DATA_TYPE_ID_LEDStrips hll_strip_id;
    bool hll_is_on;
    DATA_TYPE_ID_LEDColors hll_strip_color_id;

    DATA_TYPE_ID_LEDStrips hlr_strip_id;
    bool hlr_is_on;
    DATA_TYPE_ID_LEDColors hlr_strip_color_id;

    DATA_TYPE_ID_LEDStrips body_strip_id;
    bool body_is_on;
    DATA_TYPE_ID_LEDColors body_strip_color_id;
} Car_Manager_t;

void Car_Manager_Init(void);
void Car_Manager_SetLED(DATA_TYPE_ID_LEDStrips led_strip_id, DATA_TYPE_ID_LEDColors led_color_id,
                        bool led_strip_on);

#endif // __CAR_MANAGER_H_