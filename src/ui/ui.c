#include "ui.h"
#include "os.h"

lv_obj_t *create_button(lv_obj_t *parent, const UI_Button_t *button);

const int32_t col_dsc_3x2[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                               LV_GRID_TEMPLATE_LAST};
const int32_t row_dsc_3x2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                               LV_GRID_TEMPLATE_LAST};

void UI_Create_Screen(const UI_Screen_t *target_screen) {
  lv_obj_t *cur_screen = lv_scr_act();
  lv_obj_clean(cur_screen);

  lv_obj_t *container = lv_obj_create(cur_screen);
  lv_obj_set_size(container, 320, 240);
  lv_obj_set_layout(container, LV_LAYOUT_GRID);

  switch (target_screen->layout) {
  case UI_SCREEN_LAYOUT_3x1:
    lv_obj_set_grid_dsc_array(container, col_dsc_3x2, row_dsc_3x2);
    break;

  case UI_SCREEN_LAYOUT_3x2:
    lv_obj_set_grid_dsc_array(container, col_dsc_3x2, row_dsc_3x2);
    break;
  }

  lv_obj_set_style_flex_main_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_cross_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_track_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_pad_row(cur_screen, 8, 0);

  for (int i = 0; i < target_screen->buttons_total; i++) {
    lv_obj_t *button = create_button(container, &target_screen->buttons[i]);
    lv_obj_set_grid_cell(
        button, LV_GRID_ALIGN_CENTER, target_screen->buttons[i].col_pos, 1,
        LV_GRID_ALIGN_CENTER, target_screen->buttons[i].row_pos, 1);
  }

  lv_scr_load(cur_screen);
}

/* BUTTON */

static void button_touch_event_cb(lv_event_t *event) {
  if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
    lv_obj_t *target = lv_event_get_target(event);
    UI_Button_t *button = lv_obj_get_user_data(target);

    OS_Event_t os_event = {0};
    bool post_event = false;

    if (button->action_type == UI_ACTION_NAVIGATE) {
      os_event.type = OS_EVENT_NAVIGATE;
      os_event.data.screen_id = (OS_Screen_IDs)button->action_data;
      post_event = true;
    } else if (button->action_type == UI_ACTION_SET_VALUE) {
      os_event.type = OS_EVENT_LIGHT_CHANGE;
      os_event.data.color = (OS_Light_Colors)button->action_data;
      post_event = true;
    }

    if (post_event) {
      OS_PostEvent(os_event);
    }
  }
}

lv_obj_t *create_button(lv_obj_t *parent, const UI_Button_t *button) {

  lv_obj_t *target = lv_btn_create(parent);

  lv_obj_set_size(target, 70, 70);
  lv_obj_set_style_radius(target, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(target, lv_color_hex(button->color), 0);

  lv_obj_add_event_cb(target, button_touch_event_cb, LV_EVENT_CLICKED,
                      (void *)button);

  lv_obj_t *label = lv_label_create(target);

  if (button->symbol != NULL && (uintptr_t)button->symbol > 0xFFFF) {
    lv_label_set_text(label, button->symbol);
  } else {
    lv_label_set_text(label, "?");
  }

  lv_obj_set_style_text_color(label, lv_color_white(), 0);
  lv_obj_set_style_text_opa(label, LV_OPA_80, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
  lv_obj_center(label);

  lv_obj_set_user_data(target, (void *)button);

  return target;
}

/* COLORPICKER */

// static lv_obj_t *colors_wheel;
// static color_picker_confirmed_cb_t app_confirm_callback = NULL;

// static void green_btn_cb(lv_event_t *e) {
//   lv_event_code_t code = lv_event_get_code(e);
//   if (code == LV_EVENT_CLICKED) {
//     // 1. Get the color from the internal wheel object
//     lv_color_t final_color = lv_colorwheel_get_rgb(colors_wheel);

//     // 2. Safely push the data out to the application layer if registered
//     if (app_confirm_callback != NULL) {
//       app_confirm_callback(final_color);
//     }
//   }
// }

// static void red_btn_cb(lv_event_t *e) {
//   if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
//     // Optional: Call a cancel callback if you add one to your header
//   }
// }

// void create_color_picker(color_picker_confirmed_cb_t on_confirm_cb) {
//   // Save the application callback for later execution
//   app_confirm_callback = on_confirm_cb;

//   lv_obj_t *cur_screen = lv_scr_act();
//   lv_obj_clean(cur_screen);

//   // Main layout container (Horizontal Row)
//   lv_obj_t *main_container = lv_obj_create(cur_screen);
//   lv_obj_set_size(main_container, 320, 240);
//   lv_obj_center(main_container);
//   lv_obj_set_layout(main_container, LV_LAYOUT_FLEX);
//   lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_ROW);
//   lv_obj_set_flex_align(main_container, LV_FLEX_ALIGN_CENTER,
//                         LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//   lv_obj_clear_flag(main_container, LV_OBJ_FLAG_SCROLLABLE);

//   // Color Wheel
//   colors_wheel = lv_colorwheel_create(main_container, true);
//   lv_obj_set_size(colors_wheel, 180, 180);

//   // Buttons Container (Vertical Column)
//   lv_obj_t *btn_container = lv_obj_create(main_container);
//   lv_obj_set_size(btn_container, 80, 180);
//   lv_obj_set_layout(btn_container, LV_LAYOUT_FLEX);
//   lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_COLUMN);
//   lv_obj_set_flex_align(btn_container, LV_FLEX_ALIGN_SPACE_EVENLY,
//                         LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//   lv_obj_set_style_pad_all(btn_container, 0, LV_PART_MAIN);
//   lv_obj_set_style_border_width(btn_container, 0, LV_PART_MAIN);
//   lv_obj_set_style_bg_opa(btn_container, LV_OPA_TRANSP, LV_PART_MAIN);

//   // Confirm Button
//   lv_obj_t *green_btn = lv_btn_create(btn_container);
//   lv_obj_set_size(green_btn, 50, 50);
//   lv_obj_set_style_bg_color(green_btn, lv_color_make(0, 180, 0),
//   LV_PART_MAIN); lv_obj_add_event_cb(green_btn, green_btn_cb,
//   LV_EVENT_CLICKED, NULL);

//   lv_obj_t *green_label = lv_label_create(green_btn);
//   lv_label_set_text(green_label, LV_SYMBOL_OK);
//   lv_obj_center(green_label);

//   // Cancel Button
//   lv_obj_t *red_btn = lv_btn_create(btn_container);
//   lv_obj_set_size(red_btn, 50, 50);
//   lv_obj_set_style_bg_color(red_btn, lv_color_make(220, 0, 0), LV_PART_MAIN);
//   lv_obj_add_event_cb(red_btn, red_btn_cb, LV_EVENT_CLICKED, NULL);

//   lv_obj_t *red_label = lv_label_create(red_btn);
//   lv_label_set_text(red_label, LV_SYMBOL_CLOSE);
//   lv_obj_center(red_label);

//   lv_scr_load(cur_screen);
// }