#include "home.h"
#include "ui.h"

UI_Button_t const home_button_light_control = {
    .background_color = (0xFFC107),
    .icon_symbol = LV_SYMBOL_POWER,
    .navigate_screen_id = UI_SCREEN_ID_LIGHT_CONTROL,
    .touch_event_name = "lights",
    .col_pos = 0,
    .row_pos = 0,
};

UI_Button_t const home_button_sound = {
    .background_color = (0x2196F3),
    .icon_symbol = LV_SYMBOL_AUDIO,
    .navigate_screen_id = UI_SCREEN_ID_HOME,
    .touch_event_name = "sound",
    .col_pos = 1,
    .row_pos = 0,
};

UI_Button_t const home_button_settings = {
    .background_color = (0x607D8B),
    .icon_symbol = LV_SYMBOL_SETTINGS,
    .navigate_screen_id = UI_SCREEN_ID_HOME,
    .touch_event_name = "settings",
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