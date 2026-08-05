#include "light_menu.h"
#include "data_types.h"
#include "nav_button.h"

static const DT_UI_Input_t inputs[] = {
    {
        .type_id = UI_INPUT_TYPE_NAV_BUTTON,
        .to_manager_id = OSMANAGER_VIEW_ID,
        .action_data = VIEW_LIGHT_CONTROL_ID,
        .col_pos = 0,
        .row_pos = 0,
        .color = (0xFFC107),
        .name = "Headlight Left",
        .symbol = LV_SYMBOL_LEFT,
        .style = &STYLE_NAV_BUTTON,
    },
    {
        .type_id = UI_INPUT_TYPE_NAV_BUTTON,
        .to_manager_id = OSMANAGER_VIEW_ID,
        .action_data = VIEW_LIGHT_CONTROL_ID,
        .col_pos = 1,
        .row_pos = 0,
        .color = (0xFFC107),
        .name = "Bodylight",
        .symbol = LV_SYMBOL_DRIVE,
        .style = &STYLE_NAV_BUTTON,
    },
};

DT_UI_ViewDesc_t const VIEW_LIGHT_MENU_CONST = {
    .view_desc_id = VIEW_LIGHT_MENU_ID,
    .layout_id = LV_LAYOUT_GRID,
    .layout_cols = STYLE_LAYOUT_COLS_2,
    .layout_rows = STYLE_LAYOUT_ROWS_1,
    .inputs_total = 2,
    .inputs = inputs,
};
