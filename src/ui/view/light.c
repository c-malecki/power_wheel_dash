#include "light.h"
#include "data_types.h"
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
        .action_data = VIEW_HOME_ID,
        .col_pos = 1,
        .row_pos = 0,
        .color = 0xFFC107,
        .name = "Bodylight",
        .symbol = LV_SYMBOL_DRIVE,
        .style = &STYLE_NAV_BUTTON,
    },
};

DATA_TYPE_UI_ViewDesc_t const VIEW_LIGHT = {
    .view_id = VIEW_LIGHTS_ID,
    .layout_id = UI_LAYOUT_GRID,
    .layout_cols = STYLE_LAYOUT_COLS_2,
    .layout_rows = STYLE_LAYOUT_ROWS_1,
    .inputs_total = 2,
    .inputs = light_inputs,
};
