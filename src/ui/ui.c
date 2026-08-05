#include "ui.h"

const lv_style_const_prop_t STYLE_LAYOUT_props[] = {
    LV_STYLE_CONST_WIDTH(320), LV_STYLE_CONST_HEIGHT(240),
    LV_STYLE_CONST_BG_OPA(0), LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_PROPS_END};

LV_STYLE_CONST_INIT(STYLE_LAYOUT, STYLE_LAYOUT_props);

const int32_t STYLE_LAYOUT_COLS_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                       LV_GRID_TEMPLATE_LAST};
const int32_t STYLE_LAYOUT_ROWS_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

const int32_t STYLE_LAYOUT_COLS_3[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                       LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t STYLE_LAYOUT_ROWS_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                       LV_GRID_TEMPLATE_LAST};