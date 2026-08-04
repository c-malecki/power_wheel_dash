#include "ui_manager.h"
#include "core/lv_observer.h"
#include "os.h"
#include "view.h"

static lv_subject_t subject_is_home;

static void input_touch_event_cb(lv_event_t *event) {
  if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
    lv_obj_t *target = lv_event_get_target(event);
    UI_Input_t *input = lv_obj_get_user_data(target);

    OS_Event_t os_event = {0};
    bool post_event = false;

    if (input->action_type == UI_VIEW_ACTION_NAVIGATE) {
      os_event.type = OS_EVENT_NAVIGATE;
      os_event.data.view_id = (UI_View_IDs)input->action_data;
      post_event = true;
    } else if (input->action_type == UI_VIEW_ACTION_SET_VALUE) {
      os_event.type = OS_EVENT_LIGHT_CHANGE;
      os_event.data.color = (Light_Colors)input->action_data;
      post_event = true;
    }

    if (post_event) {
      OS_PostEvent(os_event);
    }
  }
}

lv_obj_t *Create_Input(lv_obj_t *parent, const UI_Input_t *input) {
  lv_obj_t *target = lv_btn_create(parent);

  switch (input->input_type) {
  case UI_INPUT_TYPE_BUTTON:
    lv_obj_add_style(target, &input->style, 0);
    lv_obj_set_style_bg_color(target, lv_color_hex(input->color), 0);

    lv_obj_add_event_cb(target, input_touch_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label = lv_label_create(target);
    lv_obj_add_style(label, &style_button_icon, 0);

    lv_label_set_text(label, input->symbol ? input->symbol : "?");
    break;

  case UI_INPUT_TYPE_COLOR:

    break;
  }

  lv_obj_set_user_data(target, (void *)input);

  return target;
}

void Populate_Inputs(lv_obj_t *layout, const UI_View_t *new_view) {
  for (int i = 0; i < new_view->inputs_total; i++) {
    lv_obj_t *btn = Create_Input(layout, &new_view->inputs[i]);

    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_CENTER, new_view->inputs[i].col_pos,
                         1, LV_GRID_ALIGN_CENTER, new_view->inputs[i].row_pos,
                         1);
  }
}

lv_obj_t *Create_Layout(lv_obj_t *cur_screen, const UI_View_t *new_view) {
  lv_obj_t *layout = lv_obj_create(cur_screen);

  lv_obj_add_style(layout, &style_layout, 0);

  if (new_view->layout_style == UI_VIEW_LAYOUT_GRID) {
    lv_obj_set_layout(layout, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(layout, new_view->layout_cols,
                              new_view->layout_rows);
  } else {
    lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_ROW_WRAP);
  }

  lv_obj_center(layout);

  if (new_view->view_id == UI_VIEW_HOME) {
    lv_subject_set_int(&subject_is_home, 1);
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_subject_set_int(&subject_is_home, 0);
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  }

  return layout;
}

void UI_Manager_Init(void) {
  lv_obj_t *screen = lv_obj_create(NULL);
  // initial load screen or splash or something
  lv_obj_set_style_bg_color(screen, lv_color_hex(0xf7ffff), 0);

  // home btn

  lv_obj_t *home_btn = lv_obj_create(lv_layer_top());

  lv_obj_add_style(home_btn, &style_home_button, 0);
  lv_obj_set_style_bg_color(home_btn, lv_color_hex(0x607D8B), 0);
  lv_obj_set_pos(home_btn, 20, 20);

  lv_obj_add_event_cb(home_btn, input_touch_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(home_btn);
  lv_obj_add_style(label, &style_home_button_icon, 0);

  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_obj_set_user_data(home_btn, (void *)&home_button);

  //

  lv_subject_init_int(&subject_is_home, 0);
  lv_obj_bind_flag_if_eq(home_btn, &subject_is_home, LV_OBJ_FLAG_HIDDEN, 1);

  //

  lv_screen_load(screen);
}

void UI_Manager_RenderView(const UI_View_t *new_view) {
  lv_obj_t *cur_view = lv_scr_act();
  lv_obj_clean(cur_view);

  lv_obj_t *layout = Create_Layout(cur_view, new_view);
  Populate_Inputs(layout, new_view);

  lv_scr_load(cur_view);
}