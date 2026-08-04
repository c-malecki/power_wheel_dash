#ifndef __VIEW_H_
#define __VIEW_H_

#include <stdint.h>

typedef enum {
    UI_VIEW_LAYOUT_FLEX = 0,
    UI_VIEW_LAYOUT_GRID
} UI_View_Layouts;

typedef enum {
    UI_VIEW_TYPE_BUTTON = 0,
    UI_VIEW_TYPE_COLOR,
} UI_View_Types;

typedef enum {
    UI_VIEW_ACTION_NAVIGATE = 0,
    UI_VIEW_ACTION_SET_VALUE,
    UI_VIEW_ACTION_TRIGGER,
} UI_View_Action_Types;

typedef enum {
    UI_VIEW_HOME = 0,
    UI_VIEW_LIGHT_CONTROL,
    UI_VIEW_LIGHT_COLORPICKER,
    UI_VIEW_SOUND_CONTROL,
    UI_VIEW_SETTINGS,
} UI_View_IDs;

typedef struct
{
    UI_View_Action_Types action_type;
    uint32_t action_data;
    uint32_t color;
    char *symbol;
    const char *name;
    int col_pos;
    int row_pos;
} UI_View_Button_t;

typedef struct
{
    UI_View_Action_Types action_type;
    uint32_t action_data;
    uint32_t color;
    int col_pos;
    int row_pos;
    union {

    } data;
} UI_View_Input_t;

typedef struct
{
    UI_View_IDs view_id;
    UI_View_Layouts layout;
    int buttons_total;
    UI_View_Button_t buttons[];
} UI_View_t;

extern UI_View_t const views_home;
extern UI_View_t const views_light_control;

#endif // __View_H_