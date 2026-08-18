#include "screen_light.h"
#include "color_picker.h"
#include "esp_log.h"
#include "ui_definitions.h"
#include <stdint.h>
#include <string.h>

static g_event_ui_intercept_cb ui_controller_intercept_cb = NULL;
static lv_subject_t btn_is_selected;
static UI_Element_ID selected_btn = UI_ELEMENT_NONE;

// config vars for color picker
const char *color_picker_map[] = {"NONE",   "WHITE", "RED",  "ORANGE", "\n",
                                  "YELLOW", "GREEN", "BLUE", "VIOLET", ""};

static const color_picker_map_table_t color_picker_lookup_table[] = {
    {"NONE", G_COLOR_NONE},     {"WHITE", G_COLOR_WHITE},
    {"RED", G_COLOR_RED},       {"ORANGE", G_COLOR_ORANGE},
    {"YELLOW", G_COLOR_YELLOW}, {"GREEN", G_COLOR_GREEN},
    {"BLUE", G_COLOR_BLUE},     {"VIOLET", G_COLOR_VIOLET},
};

// local scope/not injected elsewhere
static void light_select_btn_event_cb(lv_event_t *lv_event);
static G_Color_ID get_mapped_color_id(const char *map_entry);

// callback given to the color picker so that it doesn't hold state
// on a file level
static void color_picker_injection_cb(lv_event_t *lv_event) {
  assert(ui_controller_intercept_cb != NULL);

  lv_obj_t *bm = lv_event_get_target_obj(lv_event);
  uint32_t id = lv_buttonmatrix_get_selected_button(bm);
  const char *text = lv_buttonmatrix_get_button_text(bm, id);

  G_Color_ID color_id = get_mapped_color_id(text);

  G_Event_t g_event = G_Event_Create(G_CONTROLLER_UI, G_CONTROLLER_LIGHT,
                                     G_EVENT_LIGHT_SELECT, color_id);

  selected_btn = UI_ELEMENT_NONE;
  lv_subject_set_int(&btn_is_selected, 0);

  ui_controller_intercept_cb(&g_event);
  ESP_LOGI("SCREEN_LIGHT_SELECT", "sending g_event with color_id: %s", text);
}

// use current value from light to fill back selected

void Light_Select_Screen_Render(lv_obj_t *screen,
                                g_event_ui_intercept_cb ui_injection_cb) {
  assert(ui_injection_cb != NULL);

  ui_controller_intercept_cb = ui_injection_cb;

  lv_obj_t *layout = UI_Create_Grid_2x1(screen);

  // create color picker and hide it
  lv_obj_t *color_picker = Color_Picker_Create(lv_layer_top(), color_picker_map,
                                               color_picker_lookup_table, 8,
                                               color_picker_injection_cb);
  lv_subject_init_int(&btn_is_selected, 0);
  lv_obj_bind_flag_if_eq(color_picker, &btn_is_selected, LV_OBJ_FLAG_HIDDEN, 0);

  // todo: eventually set text color and bg color based on states like
  // current active color on LEDs for light control buttons
  //  todo: make abstraction for button

  // headlights button
  lv_obj_t *headlight_btn = lv_button_create(layout);
  lv_obj_add_style(headlight_btn, &ui_style_nav_button, 0);
  UI_Set_Element_BG_Color(headlight_btn, G_COLOR_YELLOW);
  lv_obj_add_event_cb(headlight_btn, light_select_btn_event_cb,
                      LV_EVENT_CLICKED,
                      (void *)UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN);

  lv_obj_t *hl_label = lv_label_create(headlight_btn);
  lv_obj_add_style(hl_label, &ui_style_nav_button_icon, 0);
  lv_label_set_text(hl_label, LV_SYMBOL_LEFT);

  lv_obj_set_grid_cell(headlight_btn, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  // bodylights button
  lv_obj_t *bodylight_btn = lv_button_create(layout);
  lv_obj_add_style(bodylight_btn, &ui_style_nav_button, 0);
  UI_Set_Element_BG_Color(bodylight_btn, G_COLOR_YELLOW);
  lv_obj_add_event_cb(bodylight_btn, light_select_btn_event_cb,
                      LV_EVENT_CLICKED,
                      (void *)UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN);

  lv_obj_t *bl_label = lv_label_create(bodylight_btn);
  lv_obj_add_style(bl_label, &ui_style_nav_button_icon, 0);
  lv_label_set_text(bl_label, LV_SYMBOL_DRIVE);

  lv_obj_set_grid_cell(bodylight_btn, LV_GRID_ALIGN_CENTER, 1, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);
}

// local

static void light_select_btn_event_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  UI_Element_ID btn_id =
      (UI_Screen_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  if (btn_id == UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN) {
    selected_btn = selected_btn == UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN
                       ? UI_ELEMENT_NONE
                       : UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN;
  } else {
    selected_btn = selected_btn == UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN
                       ? UI_ELEMENT_NONE
                       : UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN;
  }

  if (selected_btn != UI_ELEMENT_NONE) {
    lv_subject_set_int(&btn_is_selected, 1);
  } else {
    lv_subject_set_int(&btn_is_selected, 0);
  }
}

static G_Color_ID get_mapped_color_id(const char *map_entry) {
  for (uint8_t i = 0; i < 8; i++) {
    if (strcmp(map_entry, color_picker_lookup_table[i].entry) == 0) {
      return color_picker_lookup_table[i].color_id;
    }
  }
  return G_COLOR_NONE;
}