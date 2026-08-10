#ifndef __UI_DEFINITIONS_H_
#define __UI_DEFINITIONS_H_

#include "lvgl.h"
#include "os_event.h"
#include <stddef.h>

#define UI_INPUT_HOME_BUTTON_NAME "home"
#define UI_ICON_HEADLIGHT "\xEF\x83\xAB"

void UI_Styles_Init(void);
void UI_Styles_Init(void);

// element styles

extern lv_color_t const ui_color_gray;
extern lv_color_t const ui_color_yellow;
extern lv_color_t const ui_color_blue;

extern const int32_t UI_STYLE_LAYOUT_COLS_1[];
extern const int32_t UI_STYLE_LAYOUT_COLS_2[];
extern const int32_t UI_STYLE_LAYOUT_COLS_3[];

extern const int32_t UI_STYLE_LAYOUT_ROWS_1[];
extern const int32_t UI_STYLE_LAYOUT_ROWS_2[];

extern lv_style_t ui_style_layout_grid;

extern lv_style_t ui_style_home_button;
extern lv_style_t ui_style_home_button_icon;

extern lv_style_t ui_style_nav_button;
extern lv_style_t ui_style_nav_button_icon;

typedef enum {
    UI_GRID_NONE = 0,
    UI_GRID_2x1,
    UI_GRID_3x2,
} UI_Grid_ID;

typedef enum {
    UI_ELEMENT_NONE = 0,
    UI_ELEMENT_SYS_HOME_BTN,
    UI_ELEMENT_HOME_SCREEN_LIGHTS,
    UI_ELEMENT_HOME_SCREEN_SOUND,
    UI_ELEMENT_HOME_SCREEN_SETTINGS,
    UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
    UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
} UI_Element_ID;

typedef enum {
    UI_TRIGGER_NONE = 0,
    UI_TRIGGER_NAVIGATE,
    UI_TRIGGER_POPUP, // todo: popup table like screens
} UI_Trigger_ID;

typedef enum {
    UI_SCREEN_NONE = 0,
    UI_SCREEN_HOME,
    UI_SCREEN_LIGHT,
    UI_SCREEN_COLOR,
} UI_Screen_ID;

//

typedef struct
{
    UI_Element_ID element_id;
    UI_Trigger_ID trigger_id;
    OS_Controller_ID rx_controller_id;
    uint32_t payload;
} UI_Trigger_t;

typedef struct
{
    char *icon_symbol;
    lv_style_t *icon_style;
} UI_Element_Icon_t;

typedef struct
{
    UI_Element_ID element_id;
    lv_style_t *element_style;
    lv_color_t bg_color;
    const UI_Element_Icon_t *icon;
} UI_Element_t;

typedef struct
{
    UI_Screen_ID screen_id;
    UI_Grid_ID grid;
    const UI_Element_t *elements;
    uint8_t element_ct;
} UI_Screen_t;

// element_id = unique
// trigger_id = navigate (top level hierarchy)
// default_payload = id

// trigger_id <-> controller_id mapping

extern const UI_Trigger_t ui_trigger_table[];
extern const size_t UI_TRIGGER_TABLE_SIZE;

extern const UI_Screen_t ui_screen_table[];
extern const size_t UI_SCREEN_TABLE_SIZE;

#endif // __UI_DEFINITIONS_H_