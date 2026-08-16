#include "ui_definitions.h"
#include "global.h"
#include "misc/lv_color.h"

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

void UI_Set_Element_BG_Color(lv_obj_t *element, G_Color_ID color_id) {
  lv_color_t color;

  switch (color_id) {
  case G_COLOR_WHITE:
    color = lv_color_make(g_color_white.r, g_color_white.g, g_color_white.b);
    break;

  case G_COLOR_RED:
    color = lv_color_make(g_color_red.r, g_color_red.g, g_color_red.b);
    break;

  case G_COLOR_ORANGE:
    color = lv_color_make(g_color_orange.r, g_color_orange.g, g_color_orange.b);
    break;

  case G_COLOR_YELLOW:
    color = lv_color_make(g_color_yellow.r, g_color_yellow.g, g_color_yellow.b);
    break;

  case G_COLOR_GREEN:
    color = lv_color_make(g_color_green.r, g_color_green.g, g_color_green.b);
    break;

  case G_COLOR_BLUE:
    color = lv_color_make(g_color_blue.r, g_color_blue.g, g_color_blue.b);
    break;

  case G_COLOR_VIOLET:
    color = lv_color_make(g_color_violet.r, g_color_violet.g, g_color_violet.b);
    break;

  case G_COLOR_GRAY:
    color = lv_color_make(g_color_gray.r, g_color_gray.g, g_color_gray.b);
    break;

  case G_COLOR_NONE:
    color = lv_color_make(g_color_none.r, g_color_none.g, g_color_none.b);
    break;
  }

  lv_obj_set_style_bg_color(element, color, 0);
}
