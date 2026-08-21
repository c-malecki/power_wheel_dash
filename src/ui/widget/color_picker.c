#include "color_picker.h"
#include "lvgl.h"

static color_picker_cb event_cb = NULL;
static const color_picker_map_table_t *color_table = NULL;
static size_t color_table_len = 0;

static void draw_cb(lv_event_t *lv_event) {
  lv_draw_task_t *draw_task = lv_event_get_draw_task(lv_event);
  lv_draw_dsc_base_t *draw_base = lv_draw_task_get_draw_dsc(draw_task);

  if (draw_base->part != LV_PART_ITEMS) {
    return;
  }
  // id1 should be the idx of the btn in the map
  if (draw_base->id1 >= color_table_len) {
    return;
  }

  lv_draw_fill_dsc_t *fill = lv_draw_task_get_fill_dsc(draw_task);
  if (!fill) {
    return;
  }

  Sys_Color_t c = Sys_Color_Lookup(color_table[draw_base->id1].color_id);
  fill->color = lv_color_make(c.r, c.g, c.b);
}

lv_obj_t *Color_Picker_Create(lv_obj_t *parent, const char *map[],
                              const color_picker_map_table_t *table,
                              size_t table_len) {
  color_table = table;
  color_table_len = table_len;

  lv_obj_t *bm = lv_buttonmatrix_create(parent);
  lv_obj_set_size(bm, 320, 240);
  lv_buttonmatrix_set_map(bm, map);

  lv_obj_set_style_text_opa(bm, LV_OPA_TRANSP, LV_PART_ITEMS);
  lv_obj_set_style_border_width(bm, 2, LV_PART_ITEMS);
  lv_obj_set_style_border_color(bm, lv_color_black(), LV_PART_ITEMS);

  lv_obj_add_flag(bm, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_add_event_cb(bm, draw_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_event_cb(bm, event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  return bm;
}

void Color_Picker_Register_CB(color_picker_cb cb) { event_cb = cb; }