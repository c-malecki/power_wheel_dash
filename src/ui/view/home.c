#include "home.h"
#include "data_types.h"
#include "home_button.h"
#include "nav_button.h"

DT_UI_Input_t const BUTTON_NAV_HOME_CONST = {
    .type_id = UI_INPUT_TYPE_NAV_BUTTON,
    .to_manager_id = OSMANAGER_VIEW_ID,
    .action_data = VIEW_HOME_ID,
    .name = UI_INPUT_HOME_BUTTON_NAME,
    .color = (0x607D8B),
    .symbol = LV_SYMBOL_HOME,
    .style = &STYLE_HOME_BUTTON,
};

static const DT_UI_Input_t inputs[] = {{
                                           .type_id = UI_INPUT_TYPE_NAV_BUTTON,
                                           .to_manager_id = OSMANAGER_VIEW_ID,
                                           .action_data = VIEW_LIGHT_CONTROL_ID,
                                           .col_pos = 0,
                                           .row_pos = 0,
                                           .color = 0xFFC107,
                                           .name = "lights",
                                           .symbol = LV_SYMBOL_POWER,
                                           .style = &STYLE_NAV_BUTTON,
                                       },
                                       {
                                           .type_id = UI_INPUT_TYPE_NAV_BUTTON,
                                           .to_manager_id = OSMANAGER_VIEW_ID,
                                           .action_data = VIEW_LIGHT_CONTROL_ID,
                                           .col_pos = 1,
                                           .row_pos = 0,
                                           .color = (0x2196F3),
                                           .name = "sound",
                                           .symbol = LV_SYMBOL_AUDIO,
                                           .style = &STYLE_NAV_BUTTON,
                                       },
                                       {
                                           .type_id = UI_INPUT_TYPE_NAV_BUTTON,
                                           .to_manager_id = OSMANAGER_VIEW_ID,
                                           .action_data = VIEW_LIGHT_CONTROL_ID,
                                           .col_pos = 2,
                                           .row_pos = 0,
                                           .color = (0x607D8B),
                                           .name = "settings",
                                           .symbol = LV_SYMBOL_SETTINGS,
                                           .style = &STYLE_NAV_BUTTON,
                                       }};

DT_UI_ViewDesc_t const VIEW_HOME_CONST = {
    .view_desc_id = VIEW_HOME_ID,
    .layout_id = LV_LAYOUT_GRID,
    .layout_cols = STYLE_LAYOUT_COLS_3,
    .layout_rows = STYLE_LAYOUT_ROWS_2,
    .inputs_total = 3,
    .inputs = inputs,
};