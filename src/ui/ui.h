#ifndef __UI_H_
#define __UI_H_

#include <stdint.h>
#include "lvgl.h"

typedef void (*color_picker_confirmed_cb_t)(lv_color_t color);

extern const int16_t col_dsc_3x2[];
extern const int16_t row_dsc_3x2[];

typedef enum {
    UI_SCREEN_ID_HOME = 0,
    UI_SCREEN_ID_LIGHT_CONTROL,
    UI_SCREEN_ID_LIGHT_COLORPICKER,
    UI_SCREEN_ID_SOUND_CONTROL,
    UI_SCREEN_ID_SETTINGS,
} UI_Screen_IDs;

typedef enum {
    UI_ACTION_NAVIGATE = 0,
    UI_ACTION_SET_VALUE,
    UI_ACTION_TRIGGER,
} UI_Action_Type_t;

typedef struct
{
    UI_Action_Type_t action_type;
    uint32_t action_data;
    uint32_t color;
    char *symbol;
    const char *name;
    int col_pos;
    int row_pos;
} UI_Button_t;

typedef enum {
    UI_SCREEN_LAYOUT_3x1 = 0,
    UI_SCREEN_LAYOUT_3x2,
} UI_Screen_Layouts;

typedef struct
{
    UI_Screen_IDs screen_id;
    UI_Screen_Layouts layout;
    int buttons_total;
    UI_Button_t buttons[];
} UI_Screen_t;

void UI_Create_Screen(const UI_Screen_t *target_screen);

void create_color_picker(color_picker_confirmed_cb_t on_confirm_cb);

extern UI_Screen_t const screens_home;
extern UI_Screen_t const screens_light_control;

#endif // __UI_H_