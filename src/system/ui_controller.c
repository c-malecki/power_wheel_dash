#include "ui_controller.h"
#include "esp_log.h"
#include "lvgl.h"
#include "system_controller.h"
#include "system_definitions.h"
#include "ui_definitions.h"

/*
  touch_cb -> sends system_event to system_event_queue -> system_controller
  routes back to ui_controller with different entry point
  Render_Controller_HandleSystemEvent -> finds screen from table and renders
*/

extern QueueHandle_t system_event_queue;
static UI_Screen_e current_screen = UI_SCREEN_HOME;
static lv_subject_t screen_is_home;

void render(UI_Screen_Desc_t screen_desc);
static void touch_cb(lv_event_t *lv_event);

void UI_Controller_Init(void) {
  lv_obj_t *main_screen = lv_scr_act();
  lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xf7ffff), 0);

  lv_obj_t *home_button = lv_obj_create(lv_layer_top());
  lv_obj_add_style(home_button, &STYLE_HOME_BUTTON, 0);
  lv_obj_set_style_bg_color(home_button, lv_color_hex(0x607D8B), 0);
  lv_obj_set_pos(home_button, 20, 20);
  lv_obj_add_event_cb(home_button, touch_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(home_button);
  lv_obj_add_style(label, &STYLE_HOME_BUTTON_ICON, 0);
  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_obj_set_user_data(home_button, (void *)UI_TRIGGER_NAVIGATE_HOME);

  lv_subject_init_int(&screen_is_home, 0);
  lv_obj_bind_flag_if_eq(home_button, &screen_is_home, LV_OBJ_FLAG_HIDDEN, 1);

  render(ui_screen_home);
}

void UI_Controller_HandleSystemEvent(System_Event_t *system_event) {
  // action: SYSTEM_ACTION_UI_UPDATE
  // payload: 1 home screen id, 2 light screen id
  ESP_LOGI("UI_Controller_HandleSystemEvent", "received event");
  switch (system_event->action) {
  case SYSTEM_ACTION_UI_UPDATE:
    UI_Screen_Desc_t screen_desc = {0};
    for (size_t i = 0; i < UI_SCREEN_TABLE_SIZE; i++) {
      if (ui_screen_table[i].screen == system_event->payload) {
        screen_desc = ui_screen_table[i];
        ESP_LOGI("UI_Controller_HandleSystemEvent", "navigate to screen: %d",
                 ui_screen_table[i].screen);
      }
    }
    // fallback or something?
    render(screen_desc);
    break;

  default:
    break;
  }
}

/*
 ****
 */

static void touch_cb(lv_event_t *lv_event) {
  lv_obj_t *obj = lv_event_get_target(lv_event);

  UI_Trigger_e trigger = (UI_Trigger_e)lv_obj_get_user_data(obj);

  for (size_t i = 0; i < UI_TRIGGER_TABLE_SIZE; i++) {
    if (ui_trigger_table[i].trigger == trigger) {

      System_Event_t system_event;
      system_event.destination = ui_trigger_table[i].destination;
      system_event.action = ui_trigger_table[i].action;
      system_event.payload = ui_trigger_table[i].default_payload;

      // system_event.payload = (dynamic_payload != 0)
      //                            ? dynamic_payload
      //                            : ui_trigger_table[i].default_payload;

      ESP_LOGI("touch_cb", "sending event to queue");
      xQueueSend(system_event_queue, &system_event, 0);
      return;
    }
  }
  ESP_LOGW("UI_CONTROLLER", "Unmapped UI Trigger received: %d", trigger);
}

/*
 ****
 */

lv_obj_t *create_input(lv_obj_t *parent, const UI_Element_Desc_t *element) {
  lv_obj_t *target = lv_btn_create(parent);

  switch (element->element) {
  case UI_ELEMENT_NAV:
    // todo: still needs color and styles
    lv_obj_add_style(target, &STYLE_NAV_BUTTON, 0);
    // lv_obj_set_style_bg_color(target, lv_color_hex(element->color), 0);

    lv_obj_add_event_cb(target, touch_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_user_data(target, (void *)UI_TRIGGER_NAVIGATE_LIGHT);

    lv_obj_t *label = lv_label_create(target);
    lv_obj_add_style(label, &STYLE_NAV_BUTTON_ICON, 0);

    lv_label_set_text(label, "icon");

    break;

  // case UI_INPUT_TYPE_BUTTON_MATRIX:

  //   break;
  default:
    break;
  }

  return target;
}

void render(UI_Screen_Desc_t screen_desc) {
  // todo: screen arg
  lv_obj_t *main_screen = lv_scr_act();
  lv_obj_clean(main_screen);

  // todo: layout arg

  lv_obj_t *layout = lv_obj_create(main_screen);

  lv_obj_add_style(layout, &STYLE_LAYOUT, 0);
  lv_obj_set_layout(layout, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(layout, STYLE_LAYOUT_COLS_3, STYLE_LAYOUT_ROWS_2);

  lv_obj_center(layout);

  // toggle home button visibility
  if (screen_desc.screen == UI_SCREEN_HOME) {
    lv_subject_set_int(&screen_is_home, 1);
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_subject_set_int(&screen_is_home, 0);
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  }

  // populate inputs
  int pop_row = 0;
  for (int i = 0; i < screen_desc.element_count; i++) {
    if (i == 3) {
      pop_row = 1;
    }

    lv_obj_t *new_element = lv_btn_create(layout);

    switch (screen_desc.elements[i].element) {
    case UI_ELEMENT_NAV:
      // todo: still needs color and styles
      lv_obj_add_style(new_element, &STYLE_NAV_BUTTON, 0);
      // lv_obj_set_style_bg_color(new_element, lv_color_hex(el_desc.color),
      // 0);

      lv_obj_add_event_cb(new_element, touch_cb, LV_EVENT_CLICKED, NULL);
      lv_obj_set_user_data(new_element, (void *)UI_TRIGGER_NAVIGATE_LIGHT);

      lv_obj_t *label = lv_label_create(new_element);
      lv_obj_add_style(label, &STYLE_NAV_BUTTON_ICON, 0);

      lv_label_set_text(label, "icon");

      break;

    // case UI_INPUT_TYPE_BUTTON_MATRIX:

    //   break;
    default:
      break;
    }

    lv_obj_set_grid_cell(new_element, LV_GRID_ALIGN_CENTER, i, 1,
                         LV_GRID_ALIGN_CENTER, pop_row, 1);
  }

  current_screen = screen_desc.screen;
}
