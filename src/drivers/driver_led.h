#ifndef __DRIVER_LED_H_
#define __DRIVER_LED_H_

#include "esp_err.h"
#include "types.h"
#include <stdbool.h>

esp_err_t LEDDriver_Init(void);
void LEDDriver_SetHeadlights(G_Color_ID color_id);
void LEDDriver_SetBodylights(G_Color_ID color_id);

#endif // __DRIVER_LED_H_