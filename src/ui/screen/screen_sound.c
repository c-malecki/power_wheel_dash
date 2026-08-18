#include "screen_sound.h"
#include "esp_log.h"
#include "global.h"
#include "ui_definitions.h"
#include <assert.h>
#include <stdint.h>

static g_event_ui_intercept_cb ui_controller_intercept_cb = NULL;

static void sfx_btn_event_cb(lv_event_t *lv_event) {
  assert(ui_controller_intercept_cb != NULL);

  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  G_Sfx_ID sfx_id = (G_Sfx_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  assert(sfx_id == G_SFX_CAR_START);

  G_Event_t g_event = G_Event_Create(G_CONTROLLER_UI, G_CONTROLLER_SOUND,
                                     G_EVENT_SFX_SELECT, G_SFX_CAR_START);

  ui_controller_intercept_cb(&g_event);
  ESP_LOGI("SCREEN_SOUND_SELECT", "sending g_event with sfx_id: %s",
           "CAR START");
}

void Sound_Screen_Render(lv_obj_t *screen,
                         g_event_ui_intercept_cb ui_injection_cb) {
  assert(ui_injection_cb != NULL);

  ui_controller_intercept_cb = ui_injection_cb;

  lv_obj_t *layout = UI_Create_Grid_3x2(screen);

  // test button to trigger single sfx from sdcard
  lv_obj_t *test_sfx_btn = lv_button_create(layout);
  lv_obj_add_style(test_sfx_btn, &ui_style_nav_button, 0);
  UI_Set_Element_BG_Color(test_sfx_btn, G_COLOR_VIOLET);
  lv_obj_add_event_cb(test_sfx_btn, sfx_btn_event_cb, LV_EVENT_CLICKED,
                      (void *)G_SFX_CAR_START);

  lv_obj_t *test_sfx_label = lv_label_create(test_sfx_btn);
  lv_obj_add_style(test_sfx_label, &ui_style_nav_button_icon, 0);
  lv_label_set_text(test_sfx_label, LV_SYMBOL_PLAY);

  lv_obj_set_grid_cell(test_sfx_btn, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);
}