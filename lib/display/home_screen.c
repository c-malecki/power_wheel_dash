#include "home_screen.h"

void Home_Screen_Create(lv_obj_t *screen) {
  lv_obj_t *container = lv_obj_create(screen);
  lv_obj_set_size(container, 320, 240);
  lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_pad_all(container, 0, 0);
  lv_obj_center(container);
  lv_obj_set_style_border_width(container, 0, 0);
  // lv_obj_set_style_border_color(container, lv_color_hex(0x000000), 0);
  lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_flex_align(container, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER);

  UI_CreateIcon(container, lv_color_hex(0xFFC107), LV_SYMBOL_POWER, "Lights");
  UI_CreateIcon(container, lv_color_hex(0x2196F3), LV_SYMBOL_AUDIO, "Music");
  UI_CreateIcon(container, lv_color_hex(0x607D8B), LV_SYMBOL_SETTINGS,
                "Settings");

  // UI_CreateIcon(container, lv_color_hex(0xE91E63), LV_SYMBOL_HOME, "PH1");
  // UI_CreateIcon(container, lv_color_hex(0x4CAF50), LV_SYMBOL_HOME,
  //               "PH2");
  // UI_CreateIcon(container, lv_color_hex(0x9C27B0), LV_SYMBOL_HOME,
  //               "PH3");

  lv_scr_load(screen);
}