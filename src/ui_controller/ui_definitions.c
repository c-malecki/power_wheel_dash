#include "ui_definitions.h"
#include "layouts/lv_layout.h"
#include "misc/lv_style.h"
#include "misc/lv_style_gen.h"

const lv_color_t ui_color_gray = LV_COLOR_MAKE(0x60, 0x7D, 0x8B);
const lv_color_t ui_color_yellow = LV_COLOR_MAKE(0xFF, 0xC1, 0x07);
const lv_color_t ui_color_blue = LV_COLOR_MAKE(0xFF, 0xC1, 0x07);

const int32_t UI_STYLE_LAYOUT_COLS_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t UI_STYLE_LAYOUT_COLS_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_TEMPLATE_LAST};
const int32_t UI_STYLE_LAYOUT_COLS_3[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

const int32_t UI_STYLE_LAYOUT_ROWS_1[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
const int32_t UI_STYLE_LAYOUT_ROWS_2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                          LV_GRID_TEMPLATE_LAST};

// layout
lv_style_t ui_style_layout_grid;

void init_layout_grid_style(void) {
  lv_style_init(&ui_style_layout_grid);
  lv_style_set_width(&ui_style_layout_grid, 320);
  lv_style_set_height(&ui_style_layout_grid, 240);
  lv_style_set_bg_opa(&ui_style_layout_grid, 0);
  lv_style_set_border_width(&ui_style_layout_grid, 0);
  lv_style_set_layout(&ui_style_layout_grid, LV_LAYOUT_GRID);
}

lv_style_t ui_style_home_button;
lv_style_t ui_style_home_button_icon;

void init_home_button_style(void) {
  lv_style_init(&ui_style_home_button);
  lv_style_set_width(&ui_style_home_button, 50);
  lv_style_set_height(&ui_style_home_button, 50);
  lv_style_set_radius(&ui_style_home_button, LV_RADIUS_CIRCLE);
  lv_style_set_border_width(&ui_style_home_button, 0);
  lv_style_set_bg_color(&ui_style_home_button, ui_color_gray);

  lv_style_init(&ui_style_home_button_icon);
  lv_style_set_text_font(&ui_style_home_button_icon, &lv_font_montserrat_14);
  lv_style_set_align(&ui_style_home_button_icon, LV_ALIGN_CENTER);
  lv_style_set_text_color(&ui_style_home_button_icon, lv_color_hex(0xFFFFFF));
}

lv_style_t ui_style_nav_button;
lv_style_t ui_style_nav_button_icon;

void init_nav_button_style(void) {
  lv_style_init(&ui_style_nav_button);
  lv_style_set_width(&ui_style_nav_button, 70);
  lv_style_set_height(&ui_style_nav_button, 70);
  lv_style_set_radius(&ui_style_nav_button, LV_RADIUS_CIRCLE);
  lv_style_set_border_width(&ui_style_nav_button, 0);

  lv_style_init(&ui_style_nav_button_icon);
  lv_style_set_text_font(&ui_style_nav_button_icon, &lv_font_montserrat_28);
  lv_style_set_align(&ui_style_nav_button_icon, LV_ALIGN_CENTER);
  lv_style_set_text_color(&ui_style_nav_button_icon, lv_color_hex(0xFFFFFF));
}

void UI_Styles_Init(void) {
  init_layout_grid_style();
  init_home_button_style();
  init_nav_button_style();
}

/*
  TRIGGER TABLE
*/

const UI_Trigger_t ui_trigger_table[] = {
    {UI_ELEMENT_SYS_HOME_BTN, UI_TRIGGER_NAVIGATE, OS_CONTROLLER_UI,
     UI_SCREEN_HOME},
    {UI_ELEMENT_HOME_SCREEN_LIGHTS, UI_TRIGGER_NAVIGATE, OS_CONTROLLER_UI,
     UI_SCREEN_LIGHT},
    // placeholder test nav instead of changing lights
    {UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN, UI_TRIGGER_NAVIGATE,
     OS_CONTROLLER_UI, UI_SCREEN_HOME},
    {UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN, UI_TRIGGER_NAVIGATE,
     OS_CONTROLLER_UI, UI_SCREEN_HOME},
};
const size_t UI_TRIGGER_TABLE_SIZE =
    sizeof(ui_trigger_table) / sizeof(ui_trigger_table[0]);

/*
  SCREEN DEFS
*/

/* HOME */
const UI_Element_Icon_t screen_home_light_nav_icon = {
    .icon_style = &ui_style_nav_button_icon,
    .icon_symbol = LV_SYMBOL_POWER,
};

const UI_Element_t screen_home_elements[] = {
    {
        .element_id = UI_ELEMENT_HOME_SCREEN_LIGHTS,
        .element_style = &ui_style_nav_button,
        .bg_color = ui_color_yellow,
        .icon = &screen_home_light_nav_icon,
    },
};

/* LIGHT */
const UI_Element_Icon_t screen_light_headlights_icon = {
    .icon_style = &ui_style_nav_button_icon,
    .icon_symbol = "L",
};

const UI_Element_Icon_t screen_light_bodylights_icon = {
    .icon_style = &ui_style_nav_button_icon,
    .icon_symbol = LV_SYMBOL_DRIVE,
};

// UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
// UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
const UI_Element_t screen_light_elements[] = {
    {
        .element_id = UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
        .element_style = &ui_style_nav_button,
        .bg_color = ui_color_yellow,
        .icon = &screen_light_headlights_icon,
    },
    {
        .element_id = UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
        .element_style = &ui_style_nav_button,
        .bg_color = ui_color_yellow,
        .icon = &screen_light_bodylights_icon,
    },
};

/*
  SCREEN TABLE
*/

const UI_Screen_t ui_screen_table[] = {
    {UI_SCREEN_HOME, UI_GRID_3x2, screen_home_elements,
     sizeof(screen_home_elements) / sizeof(screen_home_elements[0])},
    {UI_SCREEN_LIGHT, UI_GRID_2x1, screen_light_elements,
     sizeof(screen_light_elements) / sizeof(screen_light_elements[0])},
};
const size_t UI_SCREEN_TABLE_SIZE =
    sizeof(ui_screen_table) / sizeof(ui_screen_table[0]);