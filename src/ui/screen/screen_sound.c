#include "screen_sound.h"
#include "state.h"
#include "types.h"
#include "ui_helpers.h"

static lv_obj_t *screen_obj;

static void screen_sound_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  //   G_Sfx_ID sfx_id = (G_Sfx_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  // assert(sfx_id == G_SFX_CAR_START);

  // os_Event_t os_event = os_Event_Create(G_CONTROLLER_UI, G_CONTROLLER_SOUND,
  //                                    os_EVENT_SFX_SELECT, G_SFX_CAR_START);

  // ref_ui_controller_intercept_cb(&os_event);
  // ESP_LOGI("SCREEN_SOUND_SELECT", "sending os_event with sfx_id: %s",
  //          "CAR START");
}

static void screen_sound_observer_cb(lv_observer_t *observer,
                                     lv_subject_t *subject) {
  UI_Screen_ID active_screen_id = (UI_Screen_ID)lv_subject_get_int(subject);
  lv_obj_t *new_screen = lv_observer_get_target_obj(observer);

  if (active_screen_id == UI_SCREEN_SOUND) {
    if (lv_screen_active() != new_screen) {
      lv_scr_load_anim(screen_obj, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
    }
  }
}

void Sound_Screen_Init(void) {
  screen_obj = lv_obj_create(NULL);
  lv_obj_t *layout = UI_Create_Grid(screen_obj, UI_STYLE_LAYOUT_GRID_3x2);

  lv_obj_t *test_sfx_btn = UI_Create_Button(layout, UI_STYLE_ELEMENT_NAV_BUTTON,
                                            G_COLOR_VIOLET, LV_SYMBOL_PLAY);
  lv_obj_set_grid_cell(test_sfx_btn, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_add_event_cb(test_sfx_btn, screen_sound_touch_cb, LV_EVENT_CLICKED,
                      (void *)G_SFX_CAR_START);

  lv_subject_add_observer_obj(&state_active_screen_id, screen_sound_observer_cb,
                              screen_obj, NULL);
}
