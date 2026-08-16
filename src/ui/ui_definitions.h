#ifndef __UI_DEFINITIONS_H_
#define __UI_DEFINITIONS_H_

#include "global.h"
#include "lvgl.h"
#include "os_event.h"
#include <stddef.h>
#include <stdint.h>

#define UI_INPUT_HOME_BUTTON_NAME "home"
#define UI_ICON_HEADLIGHT "\xEF\x83\xAB"

extern const lv_style_t ui_style_layout_grid;

extern const lv_style_t ui_style_sys_button;
extern const lv_style_t ui_style_sys_button_icon;

extern const lv_style_t ui_style_nav_button;
extern const lv_style_t ui_style_nav_button_icon;

extern const int32_t ui_style_layout_cols_1[];
extern const int32_t ui_style_layout_cols_2[];
extern const int32_t ui_style_layout_cols_3[];

extern const int32_t ui_style_layout_rows_1[];
extern const int32_t ui_style_layout_rows_2[];

/* ENUMS/IDs */

typedef enum {
  UI_STYLE_LAYOUT_GRID_NONE = 0,
  UI_STYLE_LAYOUT_GRID_2x1,
  UI_STYLE_LAYOUT_GRID_3x2,
} UI_Style_Layout_Grid_ID;

typedef enum {
  UI_ELEMENT_STYLE_NONE = 0,
  UI_ELEMENT_UI_STYLE_SYS_BUTTON,
  UI_ELEMENT_UI_STYLE_SYS_BUTTON_ICON,
  UI_ELEMENT_UI_STYLE_NAV_BUTTON,
  UI_ELEMENT_UI_STYLE_NAV_BUTTON_ICON,
} UI_Element_Style_ID;

typedef enum {
  UI_ELEMENT_NONE = 0,
  UI_ELEMENT_SYS_HOME_BTN,
  UI_ELEMENT_HOME_SCREEN_LIGHTS,
  UI_ELEMENT_HOME_SCREEN_SOUND,
  UI_ELEMENT_HOME_SCREEN_SETTINGS,
  UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_COLOR_PICKER,
} UI_Element_ID;

typedef enum {
  UI_SCREEN_NONE = 0,
  UI_SCREEN_HOME,
  UI_SCREEN_LIGHT_SELECT,
} UI_Screen_ID;

typedef void (*screen_render_fn)(lv_obj_t *screen,
                                 os_event_ui_intercept_cb ui_injection_cb);

typedef struct {
  UI_Screen_ID screen_id;
  screen_render_fn render_fn;
} UI_Screen_Entry_t;

extern const UI_Screen_Entry_t ui_screen_table[];
extern const size_t ui_screen_table_size;

lv_obj_t *UI_Create_Grid_2x1(lv_obj_t *screen);
lv_obj_t *UI_Create_Grid_3x2(lv_obj_t *screen);
void UI_Set_Element_BG_Color(lv_obj_t *element, G_Color_ID color_id);

#endif // __UI_DEFINITIONS_H_

/*

typedef struct {
  lv_obj_t *lv_obj;
  void (*ui_event_cb)(lv_event_t *event);
  void *ui_ctx;
} UI_Element_t;

typedef struct {
  UI_Element_ID element_id;
  UI_Screen_ID screen_id;
  uint8_t row;
  uint8_t col;
  const lv_style_t element_style;
  UI_Style_Color_ID bg_color_id;
  const lv_style_t icon_style;
  char *icon_symbol;
  OS_Controller_ID rx_controller_id;
  uint32_t payload;
  lv_obj_t *(*render_func)(lv_obj_t *parent);
  // const char *touch_event_name;
} UI_Element_Entry_t;

*/
