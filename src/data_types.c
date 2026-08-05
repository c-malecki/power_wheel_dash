#include "data_types.h"

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

const DT_LED_Color_t LED_COLOR_NONE = {.b = 0, .r = 0, .g = 0};
const DT_LED_Color_t LED_COLOR_RED = {.b = 0, .r = 100, .g = 0};
const DT_LED_Color_t LED_COLOR_GREEN = {.b = 0, .r = 0, .g = 100};
const DT_LED_Color_t LED_COLOR_BLUE = {.b = 100, .r = 0, .g = 0};
const DT_LED_Color_t LED_COLOR_PURPLE = {.b = 100, .r = 100, .g = 0};