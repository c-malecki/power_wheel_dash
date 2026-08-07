#ifndef __UI_DEFINITIONS_H_
#define __UI_DEFINITIONS_H_

#include "lvgl.h"
#include <stdint.h>
#include "system_definitions.h"

/* UI */

#define UI_INPUT_HOME_BUTTON_NAME "home"
#define UI_ICON_HEADLIGHT "\xEF\x83\xAB"

/*
 ***********************
 *******  TYPES  *******
 ***********************
 */

typedef enum {
    UI_SCREEN_NONE = 0,
    UI_SCREEN_HOME,
    UI_SCREEN_LIGHT,
    UI_SCREEN_LIGHT_SELECT,
} UI_Screen_e;

typedef enum {
    UI_TRIGGER_NONE = 0,
    UI_TRIGGER_NAVIGATE_HOME,
    UI_TRIGGER_NAVIGATE_LIGHT,
    //
    UI_TRIGGER_SELECT_LIGHT,
    UI_TRIGGER_SELECT_LIGHT_COLOR,
    UI_TRIGGER_CONFIRM_LIGHT_COLOR,
    UI_TRIGGER_CANCEL_LIGHT_COLOR,
    //
} UI_Trigger_e;

typedef struct
{
    UI_Trigger_e trigger;
    System_Controller_e destination;
    System_Action_e action;
    uint32_t default_payload;
} UI_Trigger_Desc_t;

typedef enum {
    UI_ELEMENT_NONE = 0,
    UI_ELEMENT_NAV
} UI_Element_e;

// todo: still needs color, symbol for icon, and styles
typedef struct
{
    UI_Element_e element;
    UI_Trigger_e trigger;
} UI_Element_Desc_t;

typedef struct
{
    UI_Screen_e screen;
    const UI_Element_Desc_t *elements;
    uint8_t element_count;
} UI_Screen_Desc_t;

/*
 ***********************
 *******  STYLES *******
 ***********************
 */

const lv_style_const_prop_t STYLE_LAYOUT_props[] = {
    LV_STYLE_CONST_WIDTH(320), LV_STYLE_CONST_HEIGHT(240), LV_STYLE_CONST_BG_OPA(0),
    LV_STYLE_CONST_BORDER_WIDTH(0), LV_STYLE_CONST_PROPS_END
};

LV_STYLE_CONST_INIT(STYLE_LAYOUT, STYLE_LAYOUT_props);

const lv_style_const_prop_t STYLE_HOME_BUTTON_props[] = {
    LV_STYLE_CONST_WIDTH(50), LV_STYLE_CONST_HEIGHT(50), LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
    LV_STYLE_CONST_BORDER_WIDTH(0), LV_STYLE_CONST_PROPS_END
};

const lv_style_const_prop_t STYLE_HOME_BUTTON_ICON_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_14), LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)), LV_STYLE_CONST_PROPS_END
};

LV_STYLE_CONST_INIT(STYLE_HOME_BUTTON, STYLE_HOME_BUTTON_props);
LV_STYLE_CONST_INIT(STYLE_HOME_BUTTON_ICON, STYLE_HOME_BUTTON_ICON_props);

const lv_style_const_prop_t STYLE_NAV_BUTTON_props[] = {
    LV_STYLE_CONST_WIDTH(70), LV_STYLE_CONST_HEIGHT(70), LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
    LV_STYLE_CONST_BORDER_WIDTH(0), LV_STYLE_CONST_PROPS_END
};

const lv_style_const_prop_t STYLE_NAV_BUTTON_ICON_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_28), LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)), LV_STYLE_CONST_PROPS_END
};

LV_STYLE_CONST_INIT(STYLE_NAV_BUTTON, STYLE_NAV_BUTTON_props);
LV_STYLE_CONST_INIT(STYLE_NAV_BUTTON_ICON, STYLE_NAV_BUTTON_ICON_props);

const int32_t STYLE_LAYOUT_COLS_2[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
const int32_t STYLE_LAYOUT_ROWS_1[] = { LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

const int32_t STYLE_LAYOUT_COLS_3[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                        LV_GRID_TEMPLATE_LAST };
const int32_t STYLE_LAYOUT_ROWS_2[] = { LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

/*
 ***********************
 ******* SCREENS *******
 ***********************
 */

// HOME
const UI_Element_Desc_t ui_screen_home_elements[] = {
    {
        .element = UI_ELEMENT_NAV,
        .trigger = UI_TRIGGER_NAVIGATE_LIGHT,
    },
};

#define UI_SCREEN_HOME_ELEMENT_SIZE                                                                \
    (sizeof(ui_screen_home_elements) / sizeof(ui_screen_home_elements[0]))

const UI_Screen_Desc_t ui_screen_home = {
    .screen = UI_SCREEN_HOME,
    .elements = ui_screen_home_elements,
    .element_count = UI_SCREEN_HOME_ELEMENT_SIZE,
};

// LIGHT
const UI_Element_Desc_t ui_screen_light_elements[] = {
    {
        .element = UI_ELEMENT_NAV,
        .trigger = UI_TRIGGER_NAVIGATE_HOME,
    },
    {
        .element = UI_ELEMENT_NAV,
        .trigger = UI_TRIGGER_NAVIGATE_HOME,
    },
};

#define UI_SCREEN_LIGHT_ELEMENT_SIZE                                                               \
    (sizeof(ui_screen_light_elements) / sizeof(ui_screen_light_elements[0]))

const UI_Screen_Desc_t ui_screen_light = {
    .screen = UI_SCREEN_LIGHT,
    .elements = ui_screen_light_elements,
    .element_count = UI_SCREEN_LIGHT_ELEMENT_SIZE,
};

/*
 ***********************
 *******  TABLES *******
 ***********************
 */

extern const UI_Trigger_Desc_t ui_trigger_table[];
UI_Trigger_Desc_t const ui_trigger_table[] = {
    { UI_TRIGGER_NAVIGATE_HOME, SYSTEM_CONTROLLER_UI, SYSTEM_ACTION_UI_UPDATE, UI_SCREEN_HOME },
    { UI_TRIGGER_NAVIGATE_LIGHT, SYSTEM_CONTROLLER_UI, SYSTEM_ACTION_UI_UPDATE, UI_SCREEN_LIGHT },
};

#define UI_TRIGGER_TABLE_SIZE (sizeof(ui_trigger_table) / sizeof(ui_trigger_table[0]))

extern const UI_Screen_Desc_t ui_screen_table[];
UI_Screen_Desc_t const ui_screen_table[] = {
    ui_screen_home,
    ui_screen_light,
};

#define UI_SCREEN_TABLE_SIZE (sizeof(ui_screen_table) / sizeof(ui_screen_table[0]))

#endif // __UI_DEFINITIONS_H_
