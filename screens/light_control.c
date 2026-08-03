#include "light_control.h"
#include "ui.h"

UI_Button_t const light_control_button_hl_l = {
    .background_color = (0xFFC107),
    .icon_symbol = LV_SYMBOL_LEFT,
    .navigate_screen_id = UI_SCREEN_ID_HOME,
    .touch_event_name = "Headlight Left",
    .col_pos = 0,
    .row_pos = 0,
};

UI_Button_t const light_control_button_hl_r = {
    .background_color = (0xFFC107),
    .icon_symbol = LV_SYMBOL_RIGHT,
    .navigate_screen_id = UI_SCREEN_ID_HOME,
    .touch_event_name = "Headlight Right",
    .col_pos = 1,
    .row_pos = 0,
};

UI_Button_t const light_control_button_body = {
    .background_color = (0xFFC107),
    .icon_symbol = LV_SYMBOL_DRIVE,
    .navigate_screen_id = UI_SCREEN_ID_HOME,
    .touch_event_name = "Bodylight",
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

// on/off and color picker

void Screen_Lights_Settings(void) {
  lv_obj_t *screen = lv_scr_act();
  lv_obj_clean(screen);

  lv_obj_t *colors = lv_colorwheel_create(screen, NULL);
  lv_obj_set_size(colors, 200, 200);
  // lv_obj_align(colors, NULL, LV_ALIGN_CENTER, 0, 0);
}