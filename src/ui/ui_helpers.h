#ifndef __UI_HELPERS_H_
#define __UI_HELPERS_H_

#include "lvgl.h"
#include "types.h"

const lv_style_t ui_style_layout_grid;

const int32_t ui_style_layout_cols_1[2];
const int32_t ui_style_layout_cols_2[3];
const int32_t ui_style_layout_cols_3[4];
const int32_t ui_style_layout_cols_4[5];
const int32_t ui_style_layout_cols_5[6];
const int32_t ui_style_layout_rows_1[2];
const int32_t ui_style_layout_rows_2[3];
const int32_t ui_style_layout_rows_3[4];
const int32_t ui_style_layout_rows_4[5];
const int32_t ui_style_layout_rows_5[6];

const lv_style_t ui_style_sys_button;
const lv_style_t ui_style_sys_button_icon;
const lv_style_t ui_style_nav_button;
const lv_style_t ui_style_nav_button_icon;

lv_obj_t *UI_Create_Grid(lv_obj_t *screen, UI_Style_Layout_Grid_ID grid_id);
lv_obj_t *UI_Create_Button(lv_obj_t *parent, UI_Style_Element_ID style_id,
                           G_Color_ID color_id, const char *label);

#endif // __UI_HELPERS_H_