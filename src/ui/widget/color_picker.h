#ifndef __UI_COLOR_PICKER_H_
#define __UI_COLOR_PICKER_H_

#include "misc/lv_types.h"
#include "types.h"

typedef void (*color_picker_cb)(lv_event_t *event);

typedef struct {
  const char *entry;
  Sys_Color_ID color_id;
} color_picker_map_table_t;

lv_obj_t *Color_Picker_Create(lv_obj_t *parent, const char *map[],
                              const color_picker_map_table_t *table,
                              size_t table_len);
void Color_Picker_Register_CB(color_picker_cb cb);

#endif // __UI_COLOR_PICKER_H_