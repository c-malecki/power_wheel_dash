#include "layer_os.h"
#include "state.h"
#include "ui_definitions.h"

static void os_layer_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }
}

void Layer_OS_Init(void) {
  lv_obj_t *container = lv_obj_create(lv_layer_top());

  lv_obj_set_style_height(container, 40, 0);
  lv_obj_set_style_width(container, lv_pct(100), 0);
  lv_obj_set_style_layout(container, LV_LAYOUT_FLEX, 0);
  lv_obj_set_align(container, LV_ALIGN_BOTTOM_MID);

  lv_obj_t *back_button = UI_Create_Button(
      container, UI_STYLE_ELEMENT_SYS_BUTTON, G_COLOR_GRAY, LV_SYMBOL_HOME);
  lv_obj_add_event_cb(back_button, os_layer_touch_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_align(back_button, LV_ALIGN_BOTTOM_LEFT);
}