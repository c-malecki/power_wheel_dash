#include "light.h"
#include "nav_button.h"
#include "ui.h"

static const UI_Input_t light_inputs[] = {
    {
        .type_id = UI_INPUT_TYPE_BUTTON,
        .action_type_id = UI_INPUT_ACTION_TRIGGER,
        .action_data = UI_INPUT_ACTION_TRIGGER_COLORPICKER,
        .col_pos = 0,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "Headlight Left",
        .symbol = LV_SYMBOL_LEFT,
        .style = &STYLE_NAV_BUTTON,
    },
    {
        .type_id = UI_INPUT_TYPE_BUTTON,
        .action_type_id = UI_INPUT_ACTION_NAVIGATE,
        .action_data = UI_VIEW_ID_HOME,
        .col_pos = 1,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "Bodylight",
        .symbol = LV_SYMBOL_DRIVE,
        .style = &STYLE_NAV_BUTTON,
    },
};

UI_View_t const VIEW_LIGHT = {
    .view_id = UI_VIEW_ID_LIGHTS,
    .layout_style_id = UI_VIEW_LAYOUT_GRID,
    .layout_cols = STYLE_LAYOUT_COLS_2,
    .layout_rows = STYLE_LAYOUT_ROWS_1,
    .inputs_total = 2,
    .inputs = light_inputs,
};
