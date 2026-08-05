#include "home.h"
#include "home_button.h"
#include "nav_button.h"
#include "ui.h"

UI_Input_t const BUTTON_NAV_HOME = {
    .type_id = UI_INPUT_TYPE_BUTTON,
    .action_type_id = UI_INPUT_ACTION_NAVIGATE,
    .action_data = UI_VIEW_ID_HOME,
    .name = "home",
    .color = (0x607D8B),
    .symbol = LV_SYMBOL_HOME,
    .style = &STYLE_HOME_BUTTON,
};

static const UI_Input_t home_inputs[] = {
    {
        .type_id = UI_INPUT_TYPE_BUTTON,
        .action_type_id = UI_INPUT_ACTION_NAVIGATE,
        .action_data = UI_VIEW_ID_LIGHTS,
        .col_pos = 0,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "lights",
        .symbol = LV_SYMBOL_POWER,
        .style = &STYLE_NAV_BUTTON,
    },
    {
        .type_id = UI_INPUT_TYPE_BUTTON,
        .action_type_id = UI_INPUT_ACTION_NAVIGATE,
        .action_data = UI_VIEW_ID_LIGHTS,
        .col_pos = 1,
        .row_pos = 0,
        .color = 0x2196F3,
        .name = "sound",
        .symbol = LV_SYMBOL_AUDIO,
        .style = &STYLE_NAV_BUTTON,
    },
    {
        .type_id = UI_INPUT_TYPE_BUTTON,
        .action_type_id = UI_INPUT_ACTION_NAVIGATE,
        .action_data = UI_VIEW_ID_LIGHTS,
        .col_pos = 2,
        .row_pos = 0,
        .color = 0x607D8B,
        .name = "settings",
        .symbol = LV_SYMBOL_SETTINGS,
        .style = &STYLE_NAV_BUTTON,
    }};

UI_View_t const VIEW_HOME = {
    .view_id = UI_VIEW_ID_HOME,
    .layout_style_id = UI_VIEW_LAYOUT_GRID,
    .layout_cols = STYLE_LAYOUT_COLS_3,
    .layout_rows = STYLE_LAYOUT_ROWS_2,
    .inputs_total = 3,
    .inputs = home_inputs,
};