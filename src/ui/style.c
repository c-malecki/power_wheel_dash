#include "style.h"

const int32_t grid_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                LV_GRID_TEMPLATE_LAST};
const int32_t grid_row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                LV_GRID_TEMPLATE_LAST};

const lv_style_const_prop_t style_screen_props[] = {
    LV_STYLE_CONST_WIDTH(320),
    LV_STYLE_CONST_HEIGHT(240),
    LV_STYLE_CONST_BG_OPA(0),
    LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_BG_OPA(LV_OPA_TRANSP),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_button_props[] = {
    LV_STYLE_CONST_WIDTH(70), LV_STYLE_CONST_HEIGHT(70),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE), LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_PROPS_END};

const lv_style_const_prop_t style_button_icon_props[] = {
    LV_STYLE_CONST_TEXT_FONT(&lv_font_montserrat_28),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)),
    LV_STYLE_CONST_PROPS_END};

LV_STYLE_CONST_INIT(style_screen, style_screen_props);
LV_STYLE_CONST_INIT(style_button, style_button_props);
LV_STYLE_CONST_INIT(style_button_icon, style_button_icon_props);