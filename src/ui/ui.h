#ifndef __UI_H_
#define __UI_H_

#include "lvgl.h"
#include "types.h"

typedef enum {
  UI_STYLE_LAYOUT_GRID_NONE = 0,
  UI_STYLE_LAYOUT_GRID_2x1,
  UI_STYLE_LAYOUT_GRID_3x2,
  UI_STYLE_LAYOUT_GRID_5x3,
} UI_Style_Layout_Grid_ID;

typedef enum {
  UI_STYLE_ELEMENT_NONE = 0,
  // global buttons
  UI_STYLE_ELEMENT_SYS_BUTTON,
  // navigation buttons/icons
  UI_STYLE_ELEMENT_NAV_BUTTON,
} UI_Style_Element_ID;

lv_obj_t *UI_Create_Grid(lv_obj_t *screen, UI_Style_Layout_Grid_ID grid_id);
lv_obj_t *UI_Create_Button(lv_obj_t *parent, UI_Style_Element_ID style_id,
                           Sys_Color_ID color_id, const char *label);

#endif // __UI_H_