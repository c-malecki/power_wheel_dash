#include "ui.h"

UI_Button_t const home_button_light_control = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_LIGHT_CONTROL,
    .color = (0xFFC107),
    .symbol = LV_SYMBOL_POWER,
    .name = "lights",
    .col_pos = 0,
    .row_pos = 0,
};

UI_Button_t const home_button_sound = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_SOUND_CONTROL,
    .color = (0x2196F3),
    .symbol = LV_SYMBOL_AUDIO,
    .name = "sound",
    .col_pos = 1,
    .row_pos = 0,
};

UI_Button_t const home_button_settings = {
    .action_type = UI_ACTION_NAVIGATE,
    .action_data = UI_SCREEN_ID_SETTINGS,
    .color = (0x607D8B),
    .symbol = LV_SYMBOL_SETTINGS,
    .name = "settings",
    .col_pos = 2,
    .row_pos = 0,
};

UI_Screen_t const screens_home = {.screen_id = UI_SCREEN_ID_HOME,
                                  .layout = UI_SCREEN_LAYOUT_3x2,
                                  .buttons =
                                      {
                                          home_button_light_control,
                                          home_button_sound,
                                          home_button_settings,
                                      },
                                  .buttons_total = 3};