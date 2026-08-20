#ifndef __UI_DEFINITIONS_H_
#define __UI_DEFINITIONS_H_

#include "global.h"
#include "lvgl.h"
#include <stddef.h>

#define UI_INPUT_HOME_BUTTON_NAME "home"
#define UI_ICON_HEADLIGHT "\xEF\x83\xAB"

typedef enum {
  UI_STYLE_LAYOUT_GRID_NONE = 0,
  UI_STYLE_LAYOUT_GRID_2x1,
  UI_STYLE_LAYOUT_GRID_3x2,
} UI_Style_Layout_Grid_ID;

typedef enum {
  UI_STYLE_ELEMENT_NONE = 0,
  // global buttons
  UI_STYLE_ELEMENT_SYS_BUTTON,
  // navigation buttons/icons
  UI_STYLE_ELEMENT_NAV_BUTTON,
} UI_Style_Element_ID;

typedef enum {
  UI_ELEMENT_NONE = 0,
  // global back to home button
  UI_ELEMENT_SYS_HOME_BTN,
  // home
  UI_ELEMENT_HOME_LIGHT_NAV,
  UI_ELEMENT_HOME_SOUND_NAV,
  UI_ELEMENT_HOME_SETTINGS_NAV,
  // lights
  UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_COLOR_PICKER,
  // sounds
  UI_ELEMENT_SOUND_SCREEN_SOUND_PICKER,
  UI_ELEMENT_SOUND_SCREEN_IGNITION_BTN,
} UI_Element_ID;

typedef enum {
  UI_SCREEN_NONE = 0,
  UI_SCREEN_HOME,
  UI_SCREEN_LIGHT,
  UI_SCREEN_SOUND,
} UI_Screen_ID;

lv_obj_t *UI_Create_Grid(lv_obj_t *screen, UI_Style_Layout_Grid_ID grid_id);
lv_obj_t *UI_Create_Button(lv_obj_t *parent, UI_Style_Element_ID style_id,
                           G_Color_ID color_id, const char *label);

#endif // __UI_DEFINITIONS_H_