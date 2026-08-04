#include "view.h"
#include "font/lv_symbol_def.h"

const lv_style_const_prop_t style_layout_props[] = {
    LV_STYLE_CONST_WIDTH(320), LV_STYLE_CONST_HEIGHT(240),
    LV_STYLE_CONST_BG_OPA(0), LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_button_props[] = {
    LV_STYLE_CONST_WIDTH(70), LV_STYLE_CONST_HEIGHT(70),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE), LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_button_icon_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_28),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_home_button_props[] = {
    LV_STYLE_CONST_WIDTH(40), LV_STYLE_CONST_HEIGHT(40),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE), LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_home_button_icon_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_14),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)),
    LV_STYLE_CONST_PROPS_END};

LV_STYLE_CONST_INIT(style_layout, style_layout_props);
LV_STYLE_CONST_INIT(style_button, style_button_props);
LV_STYLE_CONST_INIT(style_button_icon, style_button_icon_props);
LV_STYLE_CONST_INIT(style_home_button, style_home_button_props);
LV_STYLE_CONST_INIT(style_home_button_icon, style_home_button_icon_props);

const int32_t col_2[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t row_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

const int32_t col_3[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                         LV_GRID_TEMPLATE_LAST};
const int32_t row_2[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

UI_Input_t const home_button = {
    .input_type = UI_INPUT_TYPE_BUTTON,
    .action_type = UI_VIEW_ACTION_NAVIGATE,
    .action_data = UI_VIEW_HOME,
    .name = "home",
    .color = (0x607D8B),
    .symbol = LV_SYMBOL_HOME,
    .style = style_home_button,
};

static const UI_Input_t home_inputs[] = {
    {
        .input_type = UI_INPUT_TYPE_BUTTON,
        .action_type = UI_VIEW_ACTION_NAVIGATE,
        .action_data = UI_VIEW_LIGHT,
        .col_pos = 0,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "lights",
        .symbol = LV_SYMBOL_POWER,
        .style = style_button,
    },
    {
        .input_type = UI_INPUT_TYPE_BUTTON,
        .action_type = UI_VIEW_ACTION_NAVIGATE,
        .action_data = UI_VIEW_LIGHT,
        .col_pos = 1,
        .row_pos = 0,
        .color = 0x2196F3,
        .name = "sound",
        .symbol = LV_SYMBOL_AUDIO,
        .style = style_button,
    },
    {
        .input_type = UI_INPUT_TYPE_BUTTON,
        .action_type = UI_VIEW_ACTION_NAVIGATE,
        .action_data = UI_VIEW_LIGHT,
        .col_pos = 2,
        .row_pos = 0,
        .color = 0x607D8B,
        .name = "settings",
        .symbol = LV_SYMBOL_SETTINGS,
        .style = style_button,
    }};

UI_View_t const views_home = {
    .view_id = UI_VIEW_HOME,
    .layout_style = UI_VIEW_LAYOUT_GRID,
    .layout_cols = col_3,
    .layout_rows = row_2,
    .inputs_total = 3,
    .inputs = home_inputs,
};

static const UI_Input_t light_inputs[] = {
    {
        .input_type = UI_INPUT_TYPE_BUTTON,
        .action_type = UI_VIEW_ACTION_TRIGGER,
        .action_data = UI_VIEW_ACTION_TRIGGER_COLORPICKER,
        .col_pos = 0,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "Headlight Left",
        .symbol = LV_SYMBOL_LEFT,
        .style = style_button,
    },
    {
        .input_type = UI_INPUT_TYPE_BUTTON,
        .action_type = UI_VIEW_ACTION_NAVIGATE,
        .action_data = UI_VIEW_HOME,
        .col_pos = 1,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "Bodylight",
        .symbol = LV_SYMBOL_DRIVE,
        .style = style_button,
    },
};

UI_View_t const views_light = {
    .view_id = UI_VIEW_LIGHT,
    .layout_style = UI_VIEW_LAYOUT_GRID,
    .layout_cols = col_2,
    .layout_rows = row_1,
    .inputs_total = 2,
    .inputs = light_inputs,
};
