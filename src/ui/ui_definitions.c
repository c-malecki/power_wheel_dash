#include "ui_definitions.h"

/*
LV_STYLE_CONST_WIDTH
LV_STYLE_CONST_HEIGHT
LV_STYLE_CONST_BG_COLOR
LV_STYLE_CONST_BG_OPA

LV_STYLE_CONST_BORDER_WIDTH
LV_STYLE_CONST_BORDER_COLOR
LV_STYLE_CONST_BORDER_OPA

LV_STYLE_CONST_LAYOUT
LV_STYLE_CONST_ALIGN

LV_STYLE_X
LV_STYLE_Y

LV_STYLE_CONST_RADIUS
LV_STYLE_CONST_PAD_TOP (BOTTOM, LEFT, RIGHT)

*/

/*
  STYLES
*/

const lv_style_const_prop_t ui_style_layout_grid_props[] = {
    LV_STYLE_CONST_WIDTH(320),
    LV_STYLE_CONST_HEIGHT(240),
    LV_STYLE_CONST_BG_OPA(0),
    LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_LAYOUT(LV_LAYOUT_GRID),
};
LV_STYLE_CONST_INIT(ui_style_layout_grid, ui_style_layout_grid_props);

const lv_style_const_prop_t ui_style_sys_button_props[] = {
    LV_STYLE_CONST_WIDTH(40),
    LV_STYLE_CONST_HEIGHT(40),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
    LV_STYLE_CONST_BORDER_WIDTH(0),
};
LV_STYLE_CONST_INIT(ui_style_sys_button, ui_style_sys_button_props);

const lv_style_const_prop_t ui_style_sys_button_icon_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_14),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    // LV_STYLE_CONST_TEXT_COLOR()
};
LV_STYLE_CONST_INIT(ui_style_sys_button_icon, ui_style_sys_button_icon_props);

const lv_style_const_prop_t ui_style_nav_button_props[] = {
    LV_STYLE_CONST_WIDTH(70),
    LV_STYLE_CONST_HEIGHT(70),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
    LV_STYLE_CONST_BORDER_WIDTH(0),
};
LV_STYLE_CONST_INIT(ui_style_nav_button, ui_style_nav_button_props);

const lv_style_const_prop_t ui_style_nav_button_icon_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_28),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
};
LV_STYLE_CONST_INIT(ui_style_nav_button_icon, ui_style_nav_button_icon_props);

const int32_t ui_style_layout_cols_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t ui_style_layout_cols_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_TEMPLATE_LAST};
const int32_t ui_style_layout_cols_3[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

const int32_t ui_style_layout_rows_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t ui_style_layout_rows_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_TEMPLATE_LAST};

const lv_color_t ui_style_color_gray = LV_COLOR_MAKE(0x60, 0x7D, 0x8B);
const lv_color_t ui_style_color_yellow = LV_COLOR_MAKE(0xFF, 0xC1, 0x07);
const lv_color_t ui_style_color_blue = LV_COLOR_MAKE(0xFF, 0xC1, 0x07);

lv_obj_t *UI_Create_Grid_2x1(lv_obj_t *screen) {
  lv_obj_t *layout = lv_obj_create(screen);
  lv_obj_add_style(layout, &ui_style_layout_grid, 0);
  lv_obj_set_grid_dsc_array(layout, ui_style_layout_cols_2,
                            ui_style_layout_rows_1);
  return layout;
}

lv_obj_t *UI_Create_Grid_3x2(lv_obj_t *screen) {
  lv_obj_t *layout = lv_obj_create(screen);
  lv_obj_add_style(layout, &ui_style_layout_grid, 0);
  lv_obj_set_grid_dsc_array(layout, ui_style_layout_cols_3,
                            ui_style_layout_rows_2);
  return layout;
}

// todo: global mapping for colors for reference between setting LEDs and
// setting colors for UI styles
void UI_Set_Element_BG_Color(lv_obj_t *element, UI_Style_Color_ID color_id) {
  // switch (color_id) {
  // case UI_STYLE_COLOR_YELLOW:
  //   lv_obj_set_style_bg_color(element, ui_style_color_yellow, 0);
  //   break;

  // case UI_STYLE_COLOR_BLUE:
  //   lv_obj_set_style_bg_color(element, ui_style_color_blue, 0);
  //   break;

  // case UI_STYLE_COLOR_GRAY:
  //   lv_obj_set_style_bg_color(element, ui_style_color_gray, 0);
  //   break;

  // case UI_STYLE_COLOR_NONE:
  //   break;
  // }
}
