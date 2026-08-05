#ifndef __UI_H_
#define __UI_H_

#include "lvgl.h"
#include <stdint.h>
#include "nav_button.h"
#include "home_button.h"

extern const lv_style_t STYLE_LAYOUT;

extern const int32_t STYLE_LAYOUT_COLS_2[];
extern const int32_t STYLE_LAYOUT_ROWS_1[];

extern const int32_t STYLE_LAYOUT_COLS_3[];
extern const int32_t STYLE_LAYOUT_ROWS_2[];

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
    const lv_style_t *style;
} UI_Input_t;

typedef enum {
    UI_VIEW_ID_HOME = 0,
    UI_VIEW_ID_LIGHTS,
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

#endif // __UI_H_