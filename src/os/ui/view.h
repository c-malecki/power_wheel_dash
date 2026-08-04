#ifndef __VIEW_H_
#define __VIEW_H_

#include "lvgl.h"
#include <stdint.h>

typedef enum {
    UI_VIEW_LAYOUT_FLEX = 0,
    UI_VIEW_LAYOUT_GRID
} UI_Layouts;

typedef enum {
    UI_INPUT_TYPE_BUTTON = 0,
    UI_INPUT_TYPE_COLOR,
} UI_Input_Types;

typedef enum {
    UI_VIEW_ACTION_NAVIGATE = 0,
    UI_VIEW_ACTION_SET_VALUE,
    UI_VIEW_ACTION_TRIGGER,
} UI_Action_Types;

typedef enum {
    UI_VIEW_ACTION_TRIGGER_COLORPICKER = 0,
} UI_Action_Triggers;

typedef struct
{
    UI_Input_Types input_type;
    UI_Action_Types action_type;
    uint32_t action_data;
    const char *name;
    int col_pos;
    int row_pos;
    uint32_t color;
    char *symbol;
    lv_style_t style;
} UI_Input_t;

typedef enum {
    UI_VIEW_HOME = 0,
    UI_VIEW_LIGHT,
    UI_VIEW_SOUND,
    UI_VIEW_SETTINGS,
} UI_View_IDs;

typedef struct
{
    UI_View_IDs view_id;
    UI_Layouts layout_style;
    const int32_t *layout_cols;
    const int32_t *layout_rows;
    int inputs_total;
    const UI_Input_t *inputs;
} UI_View_t;

extern const lv_style_t style_layout;
extern const lv_style_t style_button;
extern const lv_style_t style_button_icon;

extern const lv_style_t style_home_button;
extern const lv_style_t style_home_button_icon;

extern UI_Input_t const home_button;

extern UI_View_t const views_home;
extern UI_View_t const views_light;

#endif // __View_H_