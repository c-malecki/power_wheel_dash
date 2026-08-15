#include "color_picker.h"
#include "lvgl.h"

static color_picker_cb event_cb = NULL;

lv_obj_t *Color_Picker_Create(lv_obj_t *parent, const char *map[],
                              color_picker_cb cb) {
  event_cb = cb;

  lv_obj_t *bm = lv_buttonmatrix_create(parent);
  lv_obj_set_size(bm, 320, 240);
  lv_buttonmatrix_set_map(bm, map);
  lv_obj_add_event_cb(bm, event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  return bm;
}