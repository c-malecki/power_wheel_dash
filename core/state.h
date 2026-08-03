#ifndef __STATE_H_
#define __STATE_H_

typedef enum {
    STATE_SCREEN_HOME = 0,
    STATE_SCREEN_LIGHTS,
} State_Screens;

typedef enum {
    STATE_LIGHT_HL_L = 0,
    STATE_LIGHT_HL_R,
    STATE_LIGHT_BODY,
} State_Lights;

// REFERENCE: peripherals/light.c
// maps to Light_Color_t consts
typedef enum {
    STATE_LIGHT_COLOR_NONE = 0,
    STATE_LIGHT_COLOR_RED,
    STATE_LIGHT_COLOR_GREEN,
    STATE_LIGHT_COLOR_BLUE,
    STATE_LIGHT_COLOR_PURPLE,
} State_Lights_Colors;

typedef struct
{
    bool is_on;
    State_Lights_Colors color;
    // animation?
} State_Lights_Section_t;

typedef struct
{
    bool screens_pending;
    State_Screens screens_current;
    State_Lights_Section_t lights_hl_l;
    State_Lights_Section_t lights_hl_r;
    State_Lights_Section_t lights_body;
} State_t;

#endif // __STATE_H_