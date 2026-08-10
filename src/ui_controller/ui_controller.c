#include "ui_controller.h"
#include "core/lv_obj.h"
#include "esp_log.h"
#include "lvgl.h"
#include "os_event.h"
#include "ui_definitions.h"
#include <stdbool.h>

/*
  Current control flow:

  UI_Controller

  1. Screen element triggers touch_cb
  2. touch_cb gets element_id (UI_Element_ID) from user_data
  3. gets trigger from table by element_id
  4. constructs os_event (OS_Event_t)
  5. sends os_event to os_event_queue

  OS_Manager

  6. receives event and reroutes by rx_controller_id
  7. X_Controller_RX processes event

  In UI_Controller_RX:
  Currently only building full screens, so there is not
  any further control logic yet

  TRIGGER:
  element_id, trigger_id, rx_controller_id, payload

  payload currently is always a screen ID
*/

static UI_Screen_ID current_screen_id = UI_SCREEN_HOME;
static lv_subject_t current_screen_is_home;

void render(const UI_Screen_t *screen_desc);
static void touch_cb(lv_event_t *lv_event);

bool find_screen_by_screen_id(UI_Screen_ID screen_id, UI_Screen_t *screen);
bool find_trigger_by_element_id(UI_Element_ID element_id,
                                UI_Trigger_t *trigger);

/* INTERFACE */

void UI_Controller_Init(void) {
  lv_obj_t *main_screen = lv_scr_act();
  lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xf7ffff), 0);

  lv_obj_t *home_button = lv_obj_create(lv_layer_top());
  lv_obj_add_style(home_button, &ui_style_home_button, 0);

  lv_obj_set_pos(home_button, 20, 20);
  lv_obj_add_event_cb(home_button, touch_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(home_button);
  lv_obj_add_style(label, &ui_style_home_button_icon, 0);
  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_obj_set_user_data(home_button, (void *)UI_TRIGGER_NAVIGATE);

  lv_subject_init_int(&current_screen_is_home, 0);
  lv_obj_bind_flag_if_eq(home_button, &current_screen_is_home,
                         LV_OBJ_FLAG_HIDDEN, 1);

  UI_Screen_t home;
  bool found = find_screen_by_screen_id(UI_SCREEN_HOME, &home);
  if (!found) {
    //
  }

  render(&home);
}

void UI_Controller_RX(OS_Event_t *os_event) {
  ESP_LOGI("UI_Controller", "UI_Controller_RX");

  // currently just defaulting to only rendering a whole screen
  // so no other possible ways to handle it for now
  const UI_Screen_t *screen_desc = NULL;
  for (size_t i = 0; i < UI_SCREEN_TABLE_SIZE; i++) {
    if (ui_screen_table[i].screen_id == os_event->payload) {
      screen_desc = &ui_screen_table[i];
    }
  }

  if (screen_desc == NULL) {
    ESP_LOGI("UI_Controller_RX", "failed to find screen %d", os_event->payload);
    return;
    // fallback or something?
  }

  ESP_LOGI("UI_Controller_RX", "navigate to screen: %d",
           screen_desc->screen_id);
  render(screen_desc);
}

/* UTIL */

bool find_screen_by_screen_id(UI_Screen_ID screen_id, UI_Screen_t *screen) {
  bool found = false;

  for (size_t i = 0; i < UI_SCREEN_TABLE_SIZE; i++) {
    if (ui_screen_table[i].screen_id == screen_id) {
      *screen = ui_screen_table[i];
      found = true;
      break;
    }
  }

  return found;
}

bool find_trigger_by_element_id(UI_Element_ID element_id,
                                UI_Trigger_t *trigger) {
  bool found = false;

  for (size_t i = 0; i < UI_TRIGGER_TABLE_SIZE; i++) {
    if (ui_trigger_table[i].element_id == element_id) {
      *trigger = ui_trigger_table[i];
      found = true;
      break;
    }
  }

  return found;
}

/*
 ****
 */

static void touch_cb(lv_event_t *lv_event) {
  lv_obj_t *obj = lv_event_get_target(lv_event);
  ESP_LOGI("UI_CONTROLLER", "touch_cb: called");

  UI_Element_ID element_id = (UI_Element_ID)lv_obj_get_user_data(obj);

  UI_Trigger_t trigger;
  bool found = find_trigger_by_element_id(element_id, &trigger);
  if (!found) {
    ESP_LOGW("UI_CONTROLLER",
             "Unmapped Trigger <-> Element_ID received: Element_ID %d",
             element_id);
    return;
  }

  OS_Event_t os_event;
  os_event.payload = trigger.payload;
  os_event.rx_controller_id = trigger.rx_controller_id;

  ESP_LOGI("UI_CONTROLLER", "touch_cb: sending event to queue");
  xQueueSend(os_event_queue, &os_event, 0);
}

/*
 ****
 */

lv_obj_t *create_layout(lv_obj_t *screen, const UI_Screen_t *screen_desc) {

  lv_obj_t *layout = lv_obj_create(screen);
  lv_obj_add_style(layout, &ui_style_layout_grid, 0);

  switch (screen_desc->grid) {
  case UI_GRID_2x1:
    lv_obj_set_grid_dsc_array(layout, UI_STYLE_LAYOUT_COLS_2,
                              UI_STYLE_LAYOUT_ROWS_1);
    break;

  case UI_GRID_3x2:
    lv_obj_set_grid_dsc_array(layout, UI_STYLE_LAYOUT_COLS_3,
                              UI_STYLE_LAYOUT_ROWS_2);
    break;

  case UI_GRID_NONE:

    break;
  }

  lv_obj_center(layout);

  return layout;
}

lv_obj_t *create_element(lv_obj_t *layout, UI_Element_t element) {
  lv_obj_t *new_element = lv_btn_create(layout);

  lv_obj_add_style(new_element, element.element_style, 0);
  lv_obj_set_style_bg_color(new_element, element.bg_color, 0);

  lv_obj_add_event_cb(new_element, touch_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_user_data(new_element, (void *)element.element_id);

  if (element.icon != NULL) {
    lv_obj_t *label = lv_label_create(new_element);
    lv_obj_add_style(label, element.icon->icon_style, 0);

    lv_label_set_text(label, element.icon->icon_symbol);
  }

  return new_element;
}

void render(const UI_Screen_t *screen_desc) {
  lv_obj_t *main_screen = lv_scr_act();
  lv_obj_clean(main_screen);

  lv_obj_t *layout = create_layout(main_screen, screen_desc);

  int pop_row = 0;
  for (int i = 0; i < screen_desc->element_ct; i++) {
    if (i == 3) {
      pop_row = 1;
    }

    lv_obj_t *new_element = create_element(layout, screen_desc->elements[i]);

    lv_obj_set_grid_cell(new_element, LV_GRID_ALIGN_CENTER, i, 1,
                         LV_GRID_ALIGN_CENTER, pop_row, 1);
  }

  // toggle home button visibility
  if (screen_desc->screen_id == UI_SCREEN_HOME) {
    lv_subject_set_int(&current_screen_is_home, 1);
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_subject_set_int(&current_screen_is_home, 0);
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
  }

  current_screen_id = screen_desc->screen_id;
}
