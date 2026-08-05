#ifndef __DATA_TYPES_H_
#define __DATA_TYPES_H_

#include "misc/lv_style.h"
#include <stdint.h>
#include <stdbool.h>

#define UI_INPUT_HOME_BUTTON_NAME "home"

/*
    Hardware
*/

typedef enum {
    LED_STRIP_NONE_ID = 0,
    LED_STRIP_HL_L_ID,
    LED_STRIP_HL_R_ID,
    LED_STRIP_BODY_ID,
} DT_LED_Strip_ID;

typedef enum {
    LED_COLOR_NONE_ID = 0,
    LED_COLOR_RED_ID,
    LED_COLOR_GREEN_ID,
    LED_COLOR_BLUE_ID,
    LED_COLOR_PURPLE_ID,
} DT_LED_Color_ID;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} DT_LED_Color_t;

// split headlights into 8, top 3 are turn signal and all are lights

extern const DT_LED_Color_t LED_COLOR_NONE;
extern const DT_LED_Color_t LED_COLOR_RED;
extern const DT_LED_Color_t LED_COLOR_GREEN;
extern const DT_LED_Color_t LED_COLOR_BLUE;
extern const DT_LED_Color_t LED_COLOR_PURPLE;

/*
    UI
*/

extern const lv_style_t STYLE_LAYOUT;

extern const int32_t STYLE_LAYOUT_COLS_2[];
extern const int32_t STYLE_LAYOUT_ROWS_1[];

extern const int32_t STYLE_LAYOUT_COLS_3[];
extern const int32_t STYLE_LAYOUT_ROWS_2[];

typedef enum {
    UI_INPUT_TYPE_NAV_BUTTON = 0,
    UI_INPUT_TYPE_BUTTON_MATRIX,
} DT_UI_Input_TypeID;

// typedef enum {
//     UI_INPUT_ACTION_NONE = 0,
//     UI_INPUT_ACTION_NAVIGATE,
//     UI_INPUT_ACTION_SET_VALUE,
// } DT_UI_Input_Action_TypeID;

typedef enum {
    OSMANAGER_CAR_ID = 0,
    OSMANAGER_MEDIA_ID,
    OSMANAGER_VIEW_ID,
} DT_OS_Manager_ID;

typedef struct
{
    DT_UI_Input_TypeID type_id;
    DT_OS_Manager_ID to_manager_id;
    // DT_UI_Input_Action_TypeID action_type_id;
    uint32_t action_data;
    const char *name;
    int col_pos;
    int row_pos;
    uint32_t color;
    char *symbol;
    const lv_style_t *style;
    const char **button_matrix_map;
} DT_UI_Input_t;

typedef enum {
    VIEW_HOME_ID = 0,
    VIEW_LIGHT_MENU_ID,
    VIEW_LIGHT_CONTROL_ID,
    VIEW_MEDIA_ID,
    VIEW_SETTINGS_ID,
} DT_UI_ViewDesc_ID;

typedef struct
{
    DT_UI_ViewDesc_ID view_desc_id;
    lv_layout_t layout_id;
    const int32_t *layout_cols;
    const int32_t *layout_rows;
    int inputs_total;
    const DT_UI_Input_t *inputs;
} DT_UI_ViewDesc_t;

/* OS */

typedef enum {
    OSEVENT_NONE_ID = 0,
    OSEVENT_LED_UPDATE_ID,
} DT_OS_Event_ID;

typedef struct
{
    DT_UI_Input_t *from_input;
    DT_OS_Event_ID event_id;
    union {
        DT_UI_ViewDesc_ID view_id;
        DT_LED_Strip_ID led_strip_id;
        DT_LED_Color_ID led_color_id;
        bool led_strip_on;
    } data;
} DT_OS_Event_t;

#endif // __DATA_TYPES_H_