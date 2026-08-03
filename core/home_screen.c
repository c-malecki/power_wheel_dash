#include "home_screen.h"

static Homescreen_Button_t const btn_light = {
    .background_color = (0xFFC107),
    .icon_symbol = LV_SYMBOL_POWER,
    .btn_name = "Lights",
};

static Homescreen_Button_t const btn_sound = {
    .background_color = (0x2196F3),
    .icon_symbol = LV_SYMBOL_AUDIO,
    .btn_name = "Sound",
};

static Homescreen_Button_t const btn_settings = {
    .background_color = (0x607D8B),
    .icon_symbol = LV_SYMBOL_SETTINGS,
    .btn_name = "Settings",
};

void Home_Screen_Create(void) {
  lv_obj_t *screen = lv_scr_act();

  static const int16_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                    LV_GRID_TEMPLATE_LAST};
  static const int16_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                    LV_GRID_TEMPLATE_LAST};

  lv_obj_t *container = lv_obj_create(screen);
  lv_obj_set_size(container, 320, 240);
  lv_obj_set_layout(container, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);

  lv_obj_set_style_flex_main_place(screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_cross_place(screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_track_place(screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_pad_row(screen, 8, 0);

  lv_obj_t *lights =
      Display_CreateIcon(container, lv_color_hex(btn_light.background_color),
                         btn_light.icon_symbol, btn_light.btn_name);
  lv_obj_set_grid_cell(lights, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER,
                       0, 1);

  lv_obj_t *sound =
      Display_CreateIcon(container, lv_color_hex(btn_sound.background_color),
                         btn_sound.icon_symbol, btn_sound.btn_name);
  lv_obj_set_grid_cell(sound, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER,
                       0, 1);

  lv_obj_t *settings =
      Display_CreateIcon(container, lv_color_hex(btn_settings.background_color),
                         btn_settings.icon_symbol, btn_settings.btn_name);
  lv_obj_set_grid_cell(settings, LV_GRID_ALIGN_CENTER, 2, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_t *ph1 =
      Display_CreateIcon(container, lv_color_hex(btn_settings.background_color),
                         btn_settings.icon_symbol, btn_settings.btn_name);
  lv_obj_set_grid_cell(ph1, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1,
                       1);

  lv_obj_t *ph2 =
      Display_CreateIcon(container, lv_color_hex(btn_settings.background_color),
                         btn_settings.icon_symbol, btn_settings.btn_name);
  lv_obj_set_grid_cell(ph2, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 1,
                       1);

  lv_obj_t *ph3 =
      Display_CreateIcon(container, lv_color_hex(btn_settings.background_color),
                         btn_settings.icon_symbol, btn_settings.btn_name);
  lv_obj_set_grid_cell(ph3, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 1,
                       1);

  lv_scr_load(screen);
}