#include "light_control.h"
#include "data_types.h"
#include "lvgl.h"

static DT_LED_Strip_ID cur_strip;
static DT_LED_Color_t cur_color;

static const char *btnm_map[9] = {"RED", "BLUE", "GREEN", "\n", "PURPLE",
                                  "\n",  "STOP", "GO",    ""};

static const DT_UI_Input_t inputs[] = {{.type_id = UI_INPUT_TYPE_BUTTON_MATRIX,
                                        .name = "led button matrix",
                                        .button_matrix_map = btnm_map}};

DT_UI_ViewDesc_t const VIEW_LIGHT_CONTROL_CONST = {
    .view_desc_id = VIEW_LIGHT_CONTROL_ID,
    .layout_id = LV_LAYOUT_FLEX,
    .inputs_total = 1,
    .inputs = inputs,
};

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    uint32_t id = lv_buttonmatrix_get_selected_button(obj);
    const char *txt = lv_buttonmatrix_get_button_text(obj, id);
    LV_UNUSED(txt);
    LV_LOG_USER("%s was pressed\n", txt);
  }
}

void Light_Control_Render() {
  lv_obj_t *btnm1 = lv_buttonmatrix_create(lv_screen_active());
  lv_buttonmatrix_set_map(btnm1, btnm_map);
  lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
}