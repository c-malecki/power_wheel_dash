#ifndef __DATA_TYPES_H_
#define __DATA_TYPES_H_

#include "misc/lv_style.h"
#include <stdint.h>
#include <stdbool.h>

/*
    Hardware
*/

typedef enum {
    LED_STRIP_HL_L_ID = 0,
    LED_STRIP_HL_R_ID,
    LED_STRIP_BODY_ID,
} DATA_TYPE_ID_LEDStrips;

typedef enum {
    LED_COLOR_NONE_ID = 0,
    LED_COLOR_RED_ID,
    LED_COLOR_GREEN_ID,
    LED_COLOR_BLUE_ID,
    LED_COLOR_PURPLE_ID,
} DATA_TYPE_ID_LEDColors;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} DATA_TYPE_LED_Color_t;

// split headlights into 8, top 3 are turn signal and all are lights

extern const DATA_TYPE_LED_Color_t LED_COLOR_NONE;
extern const DATA_TYPE_LED_Color_t LED_COLOR_RED;
extern const DATA_TYPE_LED_Color_t LED_COLOR_GREEN;
extern const DATA_TYPE_LED_Color_t LED_COLOR_BLUE;
extern const DATA_TYPE_LED_Color_t LED_COLOR_PURPLE;

/*
    UI
*/

typedef enum {
    UI_INPUT_TYPE_BUTTON = 0,
    UI_INPUT_TYPE_COLOR,
} DATA_TYPE_ID_UIInputs;

typedef enum {
    UI_INPUT_ACTION_NAVIGATE = 0,
    UI_INPUT_ACTION_TRIGGER,
    UI_INPUT_ACTION_SET_VALUE,
} DATA_TYPE_ID_UI_InputActions;

typedef enum {
    UI_INPUT_ACTION_TRIGGER_COLORPICKER = 0,
} DATA_TYPE_ID_UI_InputActionTriggers;

typedef enum {
    UI_LAYOUT_FLEX = 0,
    UI_LAYOUT_GRID
} DATA_TYPE_ID_UILayouts;

typedef struct
{
    DATA_TYPE_ID_UIInputs type_id;
    DATA_TYPE_ID_UI_InputActions action_type_id;
    uint32_t action_data;
    const char *name;
    int col_pos;
    int row_pos;
    uint32_t color;
    char *symbol;
    const lv_style_t *style;
} UI_Input_t;

typedef enum {
    VIEW_HOME_ID = 0,
    VIEW_LIGHTS_ID,
    VIEW_MEDIA_ID,
    VIEW_SETTINGS_ID,
} DATA_TYPE_ID_UIViews;

typedef struct
{
    DATA_TYPE_ID_UIViews view_id;
    DATA_TYPE_ID_UILayouts layout_id;
    const int32_t *layout_cols;
    const int32_t *layout_rows;
    int inputs_total;
    const UI_Input_t *inputs;
} DATA_TYPE_UI_ViewDesc_t;

/* OS */

typedef enum {
    OSEVENT_VIEW_UPDATE_ID,
    OSEVENT_LED_UPDATE_ID,
} DATA_TYPE_ID_OSEvents;

typedef enum {
    OSMANAGER_CAR_ID = 0,
    OSMANAGER_MEDIA_ID,
    OSMANAGER_VIEW_ID,
} DATA_TYPE_ID_OSManagers;

typedef struct
{
    DATA_TYPE_ID_OSManagers manager_id;
    DATA_TYPE_ID_OSEvents event_id;
    union {
        DATA_TYPE_ID_UIViews view_id;
        DATA_TYPE_ID_LEDStrips led_strip_id;
        DATA_TYPE_ID_LEDColors led_color_id;
        bool led_strip_on;
    } data;
} DATA_TYPE_OSEvent_t;

#endif // __DATA_TYPES_H_