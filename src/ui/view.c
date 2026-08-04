#include "view.h"

UI_View_t const views_home = {
    .view_id = UI_VIEW_HOME,
    .layout = UI_LAYOUT_GRID,
    .dimensions = UI_LAYOUT_DIMENSION_3x2,
    .buttons_total = 3,
    .buttons =
        {
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_LIGHT_CONTROL,
                .color = (0xFFC107),
                .symbol = LV_SYMBOL_POWER,
                .name = "lights",
                .col_pos = 0,
                .row_pos = 0,
            },
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_SOUND_CONTROL,
                .color = (0x2196F3),
                .symbol = LV_SYMBOL_AUDIO,
                .name = "sound",
                .col_pos = 1,
                .row_pos = 0,
            },
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_SETTINGS,
                .color = (0x607D8B),
                .symbol = LV_SYMBOL_SETTINGS,
                .name = "settings",
                .col_pos = 2,
                .row_pos = 0,
            },
        },
};

UI_View_t const views_light_control = {
    .view_id = UI_VIEW_LIGHT_CONTROL,
    .layout = UI_LAYOUT_FLEX,
    .dimensions = UI_LAYOUT_DIMENSION_3x2,
    .buttons_total = 3,
    .buttons =
        {
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_LIGHT_COLORPICKER,
                .color = (0xFFC107),
                .symbol = LV_SYMBOL_LEFT,
                .name = "Headlight Left",
                .col_pos = 0,
                .row_pos = 0,
            },
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_LIGHT_COLORPICKER,
                .color = (0xFFC107),
                .symbol = LV_SYMBOL_RIGHT,
                .name = "Headlight Right",
                .col_pos = 1,
                .row_pos = 0,
            },
            {
                .action_type = UI_INPUT_ACTION_NAVIGATE,
                .action_data = UI_VIEW_LIGHT_COLORPICKER,
                .color = (0xFFC107),
                .symbol = LV_SYMBOL_DRIVE,
                .name = "Bodylight",
                .col_pos = 2,
                .row_pos = 0,
            },
        },
};