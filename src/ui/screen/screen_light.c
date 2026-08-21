#include "screen_light.h"
#include "state.h"
#include "types.h"
#include "ui_helpers.h"

static lv_obj_t *screen_obj;

static void screen_light_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  // show color picker
}

static void screen_light_observer_cb(lv_observer_t *observer,
                                     lv_subject_t *subject) {
  UI_Screen_ID active_screen_id = (UI_Screen_ID)lv_subject_get_int(subject);
  lv_obj_t *new_screen = lv_observer_get_target_obj(observer);

  if (active_screen_id == UI_SCREEN_LIGHT) {
    if (lv_screen_active() != new_screen) {
      lv_scr_load_anim(screen_obj, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
    }
  }
}

void Light_Screen_Init(void) {
  screen_obj = lv_obj_create(NULL);
  lv_obj_t *layout = UI_Create_Grid(screen_obj, UI_STYLE_LAYOUT_GRID_2x1);

  lv_obj_t *headlight_btn = UI_Create_Button(
      layout, UI_STYLE_ELEMENT_NAV_BUTTON, G_COLOR_YELLOW, LV_SYMBOL_LEFT);
  lv_obj_set_grid_cell(headlight_btn, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_add_event_cb(headlight_btn, screen_light_touch_cb, LV_EVENT_CLICKED,
                      (void *)UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN);

  lv_obj_t *bodylight_btn = UI_Create_Button(
      layout, UI_STYLE_ELEMENT_NAV_BUTTON, G_COLOR_YELLOW, LV_SYMBOL_DRIVE);
  lv_obj_set_grid_cell(bodylight_btn, LV_GRID_ALIGN_CENTER, 1, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_add_event_cb(bodylight_btn, screen_light_touch_cb, LV_EVENT_CLICKED,
                      (void *)UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN);

  lv_subject_add_observer_obj(&state_active_screen_id, screen_light_observer_cb,
                              screen_obj, NULL);
}

/*
  // create color picker and hide it
  lv_obj_t *color_picker = Color_Picker_Create(lv_layer_top(), color_picker_map,
                                               color_picker_lookup_table, 8);

  lv_subject_init_int(&btn_is_selected, 0);
  lv_obj_bind_flag_if_eq(color_picker, &btn_is_selected, LV_OBJ_FLAG_HIDDEN, 0);

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
static void screen_light_touch_cb(lv_event_t *lv_event);
static G_Color_ID get_mapped_color_id(const char *map_entry);

// callback given to the color picker so that it doesn't hold state
// on a file level
static void color_picker_injection_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  lv_obj_t *bm = lv_event_get_target_obj(lv_event);
  uint32_t id = lv_buttonmatrix_get_selected_button(bm);
  const char *text = lv_buttonmatrix_get_button_text(bm, id);

  G_Color_ID color_id = get_mapped_color_id(text);

  G_Event_t g_event = G_Event_Create(G_CONTROLLER_UI, G_CONTROLLER_LIGHT,
                                     G_EVENT_LIGHT_SELECT, color_id);

  selected_btn = UI_ELEMENT_NONE;
  lv_subject_set_int(&btn_is_selected, 0);

  ESP_LOGI("SCREEN_LIGHT_SELECT", "sending g_event with color_id: %s", text);
}
*/

// static void screen_light_touch_cb(lv_event_t *lv_event) {
//   lv_event_code_t code = lv_event_get_code(lv_event);
//   if (code != LV_EVENT_CLICKED) {
//     return;
//   }

//   UI_Element_ID btn_id =
//       (UI_Screen_ID)(uintptr_t)lv_event_get_user_data(lv_event);

//   if (btn_id == UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN) {
//     selected_btn = selected_btn == UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN
//                        ? UI_ELEMENT_NONE
//                        : UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN;
//   } else {
//     selected_btn = selected_btn == UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN
//                        ? UI_ELEMENT_NONE
//                        : UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN;
//   }

//   if (selected_btn != UI_ELEMENT_NONE) {
//     lv_subject_set_int(&btn_is_selected, 1);
//   } else {
//     lv_subject_set_int(&btn_is_selected, 0);
//   }
// }

// static G_Color_ID get_mapped_color_id(const char *map_entry) {
//   for (uint8_t i = 0; i < 8; i++) {
//     if (strcmp(map_entry, color_picker_lookup_table[i].entry) == 0) {
//       return color_picker_lookup_table[i].color_id;
//     }
//   }
//   return G_COLOR_NONE;
// }