#include "view_manager.h"
#include "car_manager.h"
#include "data_types.h"
#include "home.h"
#include "light.h"
#include "os.h"
#include "ui.h"

static lv_subject_t subject_is_home;

static void input_touch_event_cb(lv_event_t *event) {
  if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
    lv_obj_t *event_target = lv_event_get_target(event);
    UI_Input_t *ui_input = lv_obj_get_user_data(event_target);

    DATA_TYPE_OSEvent_t os_event = {0};
    bool post_event = false;

    switch (ui_input->action_type_id) {
    case UI_INPUT_ACTION_NAVIGATE:
      os_event.event_id = OSEVENT_VIEW_UPDATE_ID;
      os_event.data.view_id = (DATA_TYPE_ID_UIViews)ui_input->action_data;
      post_event = true;
      break;

    case UI_INPUT_ACTION_TRIGGER:

      post_event = true;
      break;

    case UI_INPUT_ACTION_SET_VALUE:
      os_event.event_id = OSEVENT_LED_UPDATE_ID;
      os_event.data.led_strip_id =
          (DATA_TYPE_ID_LEDStrips)ui_input->action_data;
      os_event.data.led_color_id =
          (DATA_TYPE_ID_LEDColors)ui_input->action_data;
      os_event.data.led_strip_on = (bool)ui_input->action_data;
      post_event = true;
      break;
    }

    if (post_event) {
      OS_PostEvent(os_event);
    }
  }
}

lv_obj_t *create_input(lv_obj_t *parent, const UI_Input_t *new_input);
void populate_inputs(lv_obj_t *layout, const DATA_TYPE_UI_ViewDesc_t *new_view);
lv_obj_t *create_layout(lv_obj_t *cur_screen,
                        const DATA_TYPE_UI_ViewDesc_t *new_view);
void render_view(const DATA_TYPE_UI_ViewDesc_t *new_view);

/* */

void View_Manager_Navigate(DATA_TYPE_ID_UIViews new_view_id) {
  switch (new_view_id) {
  case VIEW_HOME_ID:
    render_view(&VIEW_HOME);
    break;

  case VIEW_LIGHTS_ID:
    render_view(&VIEW_LIGHT);
    break;

  default:
    break;
  }
}

void View_Manager_Init(void) {
  lv_obj_t *screen = lv_scr_act();
  lv_obj_set_style_bg_color(screen, lv_color_hex(0xf7ffff), 0);

  // lv_obj_t *screen = lv_obj_create(NULL);
  // lv_obj_set_style_bg_color(screen, lv_color_hex(0xf7ffff), 0);
  // initial load screen or splash or something

  /*
    home button setup so that it is always present
    but hidden when on the home screen itself
  */

  lv_obj_t *home_button = lv_obj_create(lv_layer_top());
  lv_obj_add_style(home_button, &STYLE_HOME_BUTTON, 0);
  lv_obj_set_style_bg_color(home_button, lv_color_hex(0x607D8B), 0);
  lv_obj_set_pos(home_button, 20, 20);
  lv_obj_add_event_cb(home_button, input_touch_event_cb, LV_EVENT_CLICKED,
                      NULL);

  lv_obj_t *label = lv_label_create(home_button);
  lv_obj_add_style(label, &STYLE_HOME_BUTTON_ICON, 0);
  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_obj_set_user_data(home_button, (void *)&BUTTON_NAV_HOME);

  lv_subject_init_int(&subject_is_home, 0);
  lv_obj_bind_flag_if_eq(home_button, &subject_is_home, LV_OBJ_FLAG_HIDDEN, 1);

  /*
    finish home button setup
  */

  render_view(&VIEW_HOME);
}

/* */

lv_obj_t *create_input(lv_obj_t *parent, const UI_Input_t *new_input) {
  lv_obj_t *target = lv_btn_create(parent);

  switch (new_input->type_id) {
  case UI_INPUT_TYPE_BUTTON:
    lv_obj_add_style(target, new_input->style, 0);
    lv_obj_set_style_bg_color(target, lv_color_hex(new_input->color), 0);

    lv_obj_add_event_cb(target, input_touch_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label = lv_label_create(target);
    lv_obj_add_style(label, &STYLE_NAV_BUTTON_ICON, 0);

    lv_label_set_text(label, new_input->symbol ? new_input->symbol : "?");
    break;

  case UI_INPUT_TYPE_COLOR:

    break;
  }

  lv_obj_set_user_data(target, (void *)new_input);

  return target;
}

void populate_inputs(lv_obj_t *layout,
                     const DATA_TYPE_UI_ViewDesc_t *new_view) {
  for (int i = 0; i < new_view->inputs_total; i++) {
    lv_obj_t *btn = create_input(layout, &new_view->inputs[i]);

    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_CENTER, new_view->inputs[i].col_pos,
                         1, LV_GRID_ALIGN_CENTER, new_view->inputs[i].row_pos,
                         1);
  }
}

lv_obj_t *create_layout(lv_obj_t *cur_screen,
                        const DATA_TYPE_UI_ViewDesc_t *new_view) {
  lv_obj_t *layout = lv_obj_create(cur_screen);

  lv_obj_add_style(layout, &STYLE_LAYOUT, 0);

  if (new_view->layout_id == UI_LAYOUT_GRID) {
    lv_obj_set_layout(layout, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(layout, new_view->layout_cols,
                              new_view->layout_rows);
  } else {
    lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_ROW_WRAP);
  }

  lv_obj_center(layout);

  if (new_view->view_id == VIEW_HOME_ID) {
    lv_subject_set_int(&subject_is_home, 1);
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_subject_set_int(&subject_is_home, 0);
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  }

  return layout;
}

void render_view(const DATA_TYPE_UI_ViewDesc_t *new_view) {
  lv_obj_t *cur_view = lv_scr_act();
  lv_obj_clean(cur_view);

  lv_obj_t *layout = create_layout(cur_view, new_view);
  populate_inputs(layout, new_view);
}