#ifndef __CAR_MANAGER_H_
#define __CAR_MANAGER_H_

#include <stdbool.h>

typedef enum {
    CAR_LIGHT_ID_HLL = 0,
    CAR_LIGHT_ID_HLR,
    CAR_LIGHT_ID_BODY,
} Car_Light_IDs;

// todo: move stuff like this to a config where it can be shared?
typedef enum {
    CAR_LIGHT_COLOR_ID_NONE = 0,
    CAR_LIGHT_COLOR_ID_RED,
    CAR_LIGHT_COLOR_ID_GREEN,
    CAR_LIGHT_COLOR_ID_BLUE,
    CAR_LIGHT_COLOR_ID_PURPLE,
} Car_Light_Color_IDs;

typedef struct
{
    Car_Light_IDs light_id;
    bool is_on; // for OE on/off switch, not LED_COLOR_ID_NONE
    Car_Light_Color_IDs color_id; // LED_COLOR_ID_X
} Car_Light_t;

typedef struct
{
    Car_Light_t headlight_left;
    Car_Light_t headlight_right;
    Car_Light_t bodylight;
} Car_Manager_t;

void Car_Manager_Init(void);
void Car_Manager_SetLight(Car_Light_IDs car_light_id, Car_Light_Color_IDs car_light_color_id,
                          bool car_light_on);

#endif // __CAR_MANAGER_H_