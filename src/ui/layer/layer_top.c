#include "layer_top.h"
#include "core/lv_observer.h"
#include "misc/lv_event.h"
#include "model.h"
#include "types.h"
#include "ui.h"

static void layer_top_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  Sys_Screen_ID screen_id =
      (Sys_Screen_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  SYS_MODEL_SET_PROP(SYSTEM_MODEL_PROP_PENDING_SCREEN_ID, screen_id);
}

void Layer_Top_Init(void) {
  lv_obj_t *container = lv_obj_create(lv_layer_top());

  lv_obj_set_style_height(container, 40, 0);
  lv_obj_set_style_width(container, lv_pct(100), 0);
  lv_obj_set_style_layout(container, LV_LAYOUT_FLEX, 0);
  lv_obj_set_align(container, LV_ALIGN_BOTTOM_MID);

  lv_obj_t *home_button = UI_Create_Button(
      container, UI_STYLE_ELEMENT_SYS_BUTTON, G_COLOR_GRAY, LV_SYMBOL_HOME);
  lv_obj_add_event_cb(home_button, layer_top_touch_cb, LV_EVENT_CLICKED,
                      (void *)UI_SCREEN_HOME);
  lv_obj_set_align(home_button, LV_ALIGN_BOTTOM_LEFT);
}