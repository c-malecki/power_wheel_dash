#include "ui.h"

UI_Button_t const light_control_button_hl_l = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_LIGHT_COLORPICKER,
    .color = (0xFFC107),
    .symbol = LV_SYMBOL_LEFT,
    .name = "Headlight Left",
    .col_pos = 0,
    .row_pos = 0,
};

UI_Button_t const light_control_button_hl_r = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_LIGHT_COLORPICKER,
    .color = (0xFFC107),
    .symbol = LV_SYMBOL_RIGHT,
    .name = "Headlight Right",
    .col_pos = 1,
    .row_pos = 0,
};

UI_Button_t const light_control_button_body = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_LIGHT_COLORPICKER,
    .color = (0xFFC107),
    .symbol = LV_SYMBOL_DRIVE,
    .name = "Bodylight",
    .col_pos = 2,
    .row_pos = 0,
};

UI_Screen_t const screens_light_control = {
    .screen_id = UI_SCREEN_ID_LIGHT_CONTROL,
    .layout = UI_SCREEN_LAYOUT_3x1,
    .buttons =
        {
            light_control_button_hl_l,
            light_control_button_hl_r,
            light_control_button_body,
        },
    .buttons_total = 3,
};