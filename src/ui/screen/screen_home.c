#include "screen_home.h"
#include "model.h"
#include "types.h"
#include "ui.h"

static lv_obj_t *screen_obj;

static void screen_home_touch_cb(lv_event_t *lv_event) {
  lv_event_code_t code = lv_event_get_code(lv_event);
  if (code != LV_EVENT_CLICKED) {
    return;
  }

  Sys_Screen_ID screen_id =
      (Sys_Screen_ID)(uintptr_t)lv_event_get_user_data(lv_event);

  SYS_MODEL_SET_PROP(SYSTEM_MODEL_PROP_PENDING_SCREEN_ID, screen_id);
}

static void screen_home_observer_cb(lv_observer_t *observer,
                                    lv_subject_t *subject) {
  Sys_Screen_ID active_screen_id = (Sys_Screen_ID)lv_subject_get_int(subject);
  lv_obj_t *new_screen = lv_observer_get_target_obj(observer);

  if (active_screen_id == UI_SCREEN_HOME) {
    if (lv_screen_active() != new_screen) {
      lv_scr_load_anim(screen_obj, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
    }
  }
}

void Home_Screen_Init(void) {
  screen_obj = lv_obj_create(NULL);
  lv_obj_t *layout = UI_Create_Grid(screen_obj, UI_STYLE_LAYOUT_GRID_3x2);

  lv_obj_t *light_button = UI_Create_Button(layout, UI_STYLE_ELEMENT_NAV_BUTTON,
                                            G_COLOR_YELLOW, LV_SYMBOL_POWER);
  lv_obj_set_grid_cell(light_button, LV_GRID_ALIGN_CENTER, 0, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_add_event_cb(light_button, screen_home_touch_cb, LV_EVENT_CLICKED,
                      (void *)UI_SCREEN_LIGHT);

  lv_obj_t *sound_button = UI_Create_Button(layout, UI_STYLE_ELEMENT_NAV_BUTTON,
                                            G_COLOR_BLUE, LV_SYMBOL_AUDIO);
  lv_obj_set_grid_cell(sound_button, LV_GRID_ALIGN_CENTER, 1, 1,
                       LV_GRID_ALIGN_CENTER, 0, 1);

  lv_obj_add_event_cb(sound_button, screen_home_touch_cb, LV_EVENT_CLICKED,
                      (void *)UI_SCREEN_SOUND);

  lv_subject_add_observer_obj(&SYS_MODEL.active_screen_id,
                              screen_home_observer_cb, screen_obj, NULL);
}