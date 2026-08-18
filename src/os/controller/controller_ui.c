#include "controller_ui.h"
#include "esp_log.h"
#include "ui_definitions.h"
#include "ui_tables.h"
#include <stdbool.h>
#include <stddef.h>

static lv_obj_t *current_screen_obj = NULL;
static UI_Screen_ID current_screen_id = UI_SCREEN_HOME;
static lv_subject_t current_screen_is_home;

static void render(UI_Screen_ID screen_id);
static void sys_home_touch_cb(lv_event_t *lv_event);

static const UI_Screen_Entry_t *
find_screen_by_screen_id(UI_Screen_ID screen_id);

static void ui_controller_intercept(G_Event_t *g_event) {
  ESP_LOGI("UI_CONTROLLER", "ui_controller_intercept g_event");

  // handle local/ui changes and then pass up to OS manager
  if (g_event->event_id == G_EVENT_NAVIGATE) {
    UI_Screen_ID new_screen_id = g_event->payload;
    render(new_screen_id);
    return;
  }

  if (xQueueSend(g_event_queue, g_event, pdMS_TO_TICKS(50)) != pdTRUE) {
    ESP_LOGW("UI_CONTROLLER", "event queue full, dropped event id=%d",
             g_event->event_id);
  }
}

void UI_Controller_Init(void) {
  assert(ui_screen_table != NULL);

  lv_obj_t *home_button = lv_button_create(lv_layer_top());
  lv_obj_add_style(home_button, &ui_style_sys_button, 0);
  UI_Set_Element_BG_Color(home_button, G_COLOR_GRAY);
  lv_obj_set_pos(home_button, 10, 10);
  lv_obj_add_event_cb(home_button, sys_home_touch_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *label = lv_label_create(home_button);
  lv_obj_add_style(label, &ui_style_sys_button_icon, 0);
  lv_label_set_text(label, LV_SYMBOL_HOME);

  lv_subject_init_int(&current_screen_is_home, 1);
  lv_obj_bind_flag_if_eq(home_button, &current_screen_is_home,
                         LV_OBJ_FLAG_HIDDEN, 1);

  render(UI_SCREEN_HOME);
}

static const UI_Screen_Entry_t *
find_screen_by_screen_id(UI_Screen_ID screen_id) {
  const UI_Screen_Entry_t *screen = NULL;
  for (size_t i = 0; i < ui_screen_table_size; i++) {
    if (ui_screen_table[i].screen_id == screen_id) {
      screen = &ui_screen_table[i];

      break;
    }
  }

  return screen;
}

static void render(UI_Screen_ID new_screen_id) {
  const UI_Screen_Entry_t *new_screen = find_screen_by_screen_id(new_screen_id);
  assert(new_screen != NULL);

  if (current_screen_obj != NULL) {
    lv_obj_del(current_screen_obj);
    current_screen_obj = NULL;
  }

  current_screen_obj = lv_obj_create(NULL);
  new_screen->render_fn(current_screen_obj, ui_controller_intercept);

  if (new_screen_id == UI_SCREEN_HOME) {
    lv_subject_set_int(&current_screen_is_home, 1);
  } else {
    lv_subject_set_int(&current_screen_is_home, 0);
  }

  lv_screen_load(current_screen_obj);
  current_screen_id = new_screen_id;
}

static void sys_home_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  render(UI_SCREEN_HOME);
}

void UI_Controller_RX(G_Event_t *g_event) {}