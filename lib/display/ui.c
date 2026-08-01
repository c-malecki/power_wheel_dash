#include "ui.h"

static void icon_touch_event_cb(lv_event_t *event) {
  const char *name = (const char *)lv_event_get_user_data(event);
  ESP_LOGI("BTN", "%s pressed", name);
  // TODO: lv_scr_load_anim(target_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0,
  // false);
}

void UI_CreateIcon(lv_obj_t *parent, lv_color_t color, const char *symbol,
                   const char *name) {
  lv_obj_t *btn = lv_btn_create(parent);
  lv_obj_set_size(btn, 70, 70);
  lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(btn, color, 0);
  lv_obj_add_event_cb(btn, icon_touch_event_cb, LV_EVENT_CLICKED, (void *)name);

  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, symbol);
  lv_obj_set_style_text_color(label, lv_color_white(), 0);
  lv_obj_set_style_text_opa(label, LV_OPA_80, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
  // lv_label_set_text(label, name);
  lv_obj_center(label);
}