#include "ui_manager.h"
#include "input.h"
#include "os.h"
#include "style.h"

static void button_touch_event_cb(lv_event_t *event) {
  if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
    lv_obj_t *target = lv_event_get_target(event);
    UI_Button_t *button = lv_obj_get_user_data(target);

    OS_Event_t os_event = {0};
    bool post_event = false;

    if (button->action_type == UI_INPUT_ACTION_NAVIGATE) {
      os_event.type = OS_EVENT_NAVIGATE;
      os_event.data.screen_id = (OS_Screen_IDs)button->action_data;
      post_event = true;
    } else if (button->action_type == UI_INPUT_ACTION_SET_VALUE) {
      os_event.type = OS_EVENT_LIGHT_CHANGE;
      os_event.data.color = (OS_Light_Colors)button->action_data;
      post_event = true;
    }

    if (post_event) {
      OS_PostEvent(os_event);
    }
  }
}

lv_obj_t *create_layout(lv_obj_t *cur_screen, const UI_View_t *new_view) {
  lv_obj_t *layout = lv_obj_create(cur_screen);

  lv_obj_add_style(layout, &style_screen, 0);

  if (new_view->layout == UI_LAYOUT_GRID) {
    lv_obj_set_layout(layout, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(layout, grid_col_dsc, grid_row_dsc);
  } else {
    lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_ROW_WRAP);
  }

  lv_obj_center(layout);

  return layout;
}

lv_obj_t *create_button(lv_obj_t *parent, const UI_Button_t *button) {
  lv_obj_t *target = lv_btn_create(parent);
  lv_obj_add_style(target, &style_button, 0);

  lv_obj_set_user_data(target, (void *)button);
  lv_obj_add_event_cb(target, button_touch_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(target);
  lv_obj_add_style(label, &style_button_icon, 0);

  lv_label_set_text(label, button->symbol ? button->symbol : "?");

  return target;
}

void populate_inputs(lv_obj_t *layout, const UI_View_t *new_view) {
  for (int i = 0; i < new_view->buttons_total; i++) {
    lv_obj_t *btn = create_button(layout, &new_view->buttons[i]);

    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_CENTER,
                         new_view->buttons[i].col_pos, 1, LV_GRID_ALIGN_CENTER,
                         new_view->buttons[i].row_pos, 1);
  }
}

void UI_Init(void) {
  lv_obj_t *screen = lv_obj_create(NULL);
  // initial load screen or splash or something
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x1a1a1a), 0);
  lv_screen_load(screen);
}

void UI_RenderView(const UI_View_t *new_view) {
  lv_obj_t *cur_view = lv_scr_act();
  lv_obj_clean(cur_view);

  lv_obj_t *layout = create_layout(cur_view, new_view);
  populate_inputs(layout, new_view);

  lv_scr_load(cur_view);
}