#include "ui_tables.h"
#include "screen_home.h"
#include "screen_light_select.h"

// screen_id, grid_id, element_ct
const UI_Screen_Entry_t ui_screen_table[] = {
    // home
    {
        .screen_id = UI_SCREEN_HOME,
        .render_fn = Home_Screen_Render,
    },
    // light control
    {
        .screen_id = UI_SCREEN_LIGHT_SELECT,
        .render_fn = Light_Select_Screen_Render,
    },
};

const size_t ui_screen_table_size =
    sizeof(ui_screen_table) / sizeof(ui_screen_table[0]);

/*

// screen_id, bg_color_id, icon, trigger_id, rx_controller_id, payload
const UI_Element_Entry_t ui_element_table[] = {
    // System: Nav Home Button
    {
        .element_id = UI_ELEMENT_SYS_HOME_BTN,
        .screen_id = UI_SCREEN_NONE,
        .row = 0,
        .col = 0,
        .element_style = ui_style_home_button,
        .bg_color_id = UI_STYLE_COLOR_GRAY,
        .icon_style = ui_style_home_button_ICON,
        .icon_symbol = LV_SYMBOL_HOME,
        .rx_controller_id = OS_CONTROLLER_UI,
        .payload = UI_SCREEN_HOME,
        .render_func = NULL,
    },
    // Home Screen: Light Control nav button
    {
        .element_id = UI_ELEMENT_HOME_SCREEN_LIGHTS,
        .screen_id = UI_SCREEN_HOME,
        .row = 0,
        .col = 0,
        .element_style = ui_style_nav_button,
        .bg_color_id = UI_STYLE_COLOR_YELLOW,
        .icon_style = ui_style_nav_button_ICON,
        .icon_symbol = LV_SYMBOL_POWER,
        .rx_controller_id = OS_CONTROLLER_UI,
        .payload = UI_SCREEN_LIGHT_SELECT,
        .render_func = NULL,
    },
    // Light Control Screen: Headlights select button
    {
        .element_id = UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
        .screen_id = UI_SCREEN_LIGHT_SELECT,
        .row = 0,
        .col = 0,
        .element_style = ui_style_nav_button,
        .bg_color_id = UI_STYLE_COLOR_YELLOW,
        .icon_style = ui_style_nav_button_ICON,
        .icon_symbol = LV_SYMBOL_LEFT,
        .rx_controller_id = OS_CONTROLLER_LIGHT,
        .payload = 0,
        .render_func = Color_Picker_Create,
    },
    // Light Control Screen: Bodylights select button
    {
        .element_id = UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
        .screen_id = UI_SCREEN_LIGHT_SELECT,
        .row = 0,
        .col = 1,
        .element_style = ui_style_nav_button,
        .bg_color_id = UI_STYLE_COLOR_YELLOW,
        .icon_style = ui_style_nav_button_ICON,
        .icon_symbol = LV_SYMBOL_DRIVE,
        .rx_controller_id = OS_CONTROLLER_LIGHT,
        .payload = 0,
        .render_func = Color_Picker_Create,
    },
};

const size_t ui_element_table_size =
    sizeof(ui_element_table) / sizeof(ui_element_table[0]);

    */