#include "view_manager.h"
#include "data_types.h"
#include "esp_log.h"
#include "home.h"
#include "home_button.h"
#include "layouts/flex/lv_flex.h"
#include "light_control.h"
#include "light_menu.h"
#include "nav_button.h"

static lv_event_cb_t view_touch_cb = NULL;
static lv_subject_t view_is_home;

lv_obj_t *create_input(lv_obj_t *parent, const DT_UI_Input_t *new_input);
void populate_inputs(lv_obj_t *layout, const DT_UI_ViewDesc_t *new_view);
void assemble_view(lv_obj_t *cur_screen, const DT_UI_ViewDesc_t *new_view);
void render_view(const DT_UI_ViewDesc_t *new_view);

void View_Manager_Init(lv_event_cb_t touch_cb) {
  view_touch_cb = touch_cb;

  lv_obj_t *screen = lv_scr_act();
  lv_obj_set_style_bg_color(screen, lv_color_hex(0xf7ffff), 0);

  /*
    home button setup so that it is always present
    but hidden when on the home screen itself
  */

  lv_obj_t *home_button = lv_obj_create(lv_layer_top());
  lv_obj_add_style(home_button, &STYLE_HOME_BUTTON, 0);
  lv_obj_set_style_bg_color(home_button, lv_color_hex(0x607D8B), 0);
  lv_obj_set_pos(home_button, 20, 20);
  if (view_touch_cb != NULL) {
    lv_obj_add_event_cb(home_button, view_touch_cb, LV_EVENT_CLICKED, NULL);
  }

  lv_obj_t *label = lv_label_create(home_button);
  lv_obj_add_style(label, &STYLE_HOME_BUTTON_ICON, 0);
  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_obj_set_user_data(home_button, (void *)&BUTTON_NAV_HOME_CONST);

  lv_subject_init_int(&view_is_home, 0);
  lv_obj_bind_flag_if_eq(home_button, &view_is_home, LV_OBJ_FLAG_HIDDEN, 1);

  /*
    finish home button setup
  */

  render_view(&VIEW_HOME_CONST);
}

void navigate(DT_UI_ViewDesc_ID new_view_id) {
  switch (new_view_id) {
  case VIEW_HOME_ID:
    render_view(&VIEW_HOME_CONST);
    break;

  case VIEW_LIGHT_MENU_ID:
    render_view(&VIEW_LIGHT_MENU_CONST);
    break;

  case VIEW_LIGHT_CONTROL_ID:
    render_view(&VIEW_LIGHT_CONTROL_CONST);
    break;

  default:
    break;
  }
}

void View_Manager_HandleOSEvent(DT_OS_Event_t os_event) {
  // todo: sub specifiers for events when there is more than changing the whole
  // view
  ESP_LOGI("EVENT TRACE", "View_Manager_HandleOSEvent");
  navigate(os_event.data.view_id);
}

/* */

lv_obj_t *create_input(lv_obj_t *parent, const DT_UI_Input_t *new_input) {
  lv_obj_t *target = lv_btn_create(parent);

  switch (new_input->type_id) {
  case UI_INPUT_TYPE_NAV_BUTTON:
    lv_obj_add_style(target, new_input->style, 0);
    lv_obj_set_style_bg_color(target, lv_color_hex(new_input->color), 0);

    if (view_touch_cb != NULL) {
      lv_obj_add_event_cb(target, view_touch_cb, LV_EVENT_CLICKED, NULL);
    }

    lv_obj_t *label = lv_label_create(target);
    lv_obj_add_style(label, &STYLE_NAV_BUTTON_ICON, 0);

    lv_label_set_text(label, new_input->symbol ? new_input->symbol : "?");
    break;

  case UI_INPUT_TYPE_BUTTON_MATRIX:

    break;
  }

  lv_obj_set_user_data(target, (void *)new_input);

  return target;
}

void populate_inputs(lv_obj_t *layout, const DT_UI_ViewDesc_t *new_view) {
  for (int i = 0; i < new_view->inputs_total; i++) {
    lv_obj_t *input = create_input(layout, &new_view->inputs[i]);

    if (new_view->layout_id == LV_LAYOUT_GRID) {
      lv_obj_set_grid_cell(input, LV_GRID_ALIGN_CENTER,
                           new_view->inputs[i].col_pos, 1, LV_GRID_ALIGN_CENTER,
                           new_view->inputs[i].row_pos, 1);
    } else {
      // invoke render function?
      lv_obj_set_flex_align(input, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                            LV_FLEX_ALIGN_CENTER);
    }
  }
}

void assemble_view(lv_obj_t *cur_screen, const DT_UI_ViewDesc_t *new_view) {
  lv_obj_t *layout = lv_obj_create(cur_screen);

  lv_obj_add_style(layout, &STYLE_LAYOUT, 0);

  if (new_view->layout_id == LV_LAYOUT_GRID) {
    lv_obj_set_layout(layout, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(layout, new_view->layout_cols,
                              new_view->layout_rows);
  } else {
    lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_ROW_WRAP);
  }

  lv_obj_center(layout);

  if (new_view->view_desc_id == VIEW_HOME_ID) {
    lv_subject_set_int(&view_is_home, 1);
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_subject_set_int(&view_is_home, 0);
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  }

  populate_inputs(layout, new_view);
}

void render_view(const DT_UI_ViewDesc_t *new_view) {
  lv_obj_t *cur_view = lv_scr_act();
  lv_obj_clean(cur_view);
  assemble_view(cur_view, new_view);
}