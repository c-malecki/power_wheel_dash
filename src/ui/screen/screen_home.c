#include "screen_home.h"
#include "esp_log.h"
#include "ui_definitions.h"
#include <assert.h>
#include <stdint.h>

static g_event_ui_intercept_cb ui_controller_intercept_cb = NULL;

static void home_nav_btn_event_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  UI_Screen_ID screen_id =
      (UI_Screen_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  G_Event_t g_event = G_Event_Create(G_CONTROLLER_UI, G_CONTROLLER_UI,
                                     G_EVENT_NAVIGATE, screen_id);

  if (ui_controller_intercept_cb != NULL) {
    ui_controller_intercept_cb(&g_event);
  }
}

void Home_Screen_Render(lv_obj_t *screen,
                        g_event_ui_intercept_cb ui_injection_cb) {
  assert(ui_injection_cb != NULL);

  ui_controller_intercept_cb = ui_injection_cb;

  lv_obj_t *layout = UI_Create_Grid_3x2(screen);

  // lights button
  lv_obj_t *light_select_btn = lv_button_create(layout);
  lv_obj_add_style(light_select_btn, &ui_style_nav_button, 0);
  UI_Set_Element_BG_Color(light_select_btn, G_COLOR_YELLOW);
  lv_obj_add_event_cb(light_select_btn, home_nav_btn_event_cb, LV_EVENT_CLICKED,
                      (void *)UI_SCREEN_LIGHT);

  lv_obj_t *light_select_label = lv_label_create(light_select_btn);
  lv_obj_add_style(light_select_label, &ui_style_nav_button_icon, 0);
  lv_label_set_text(light_select_label, LV_SYMBOL_POWER);

  lv_obj_set_grid_cell(light_select_btn, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  // sounds button
  lv_obj_t *sound_select_btn = lv_button_create(layout);
  lv_obj_add_style(sound_select_btn, &ui_style_nav_button, 0);
  UI_Set_Element_BG_Color(sound_select_btn, G_COLOR_YELLOW);
  lv_obj_add_event_cb(sound_select_btn, home_nav_btn_event_cb, LV_EVENT_CLICKED,
                      (void *)UI_SCREEN_SOUND);

  lv_obj_t *sound_select_label = lv_label_create(sound_select_btn);
  lv_obj_add_style(sound_select_label, &ui_style_nav_button_icon, 0);
  lv_label_set_text(sound_select_label, LV_SYMBOL_AUDIO);

  lv_obj_set_grid_cell(sound_select_btn, LV_GRID_ALIGN_CENTER, 1, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);
}