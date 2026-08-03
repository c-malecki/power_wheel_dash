#ifndef __HOME_H_
#define __HOME_H_

#include "lvgl.h"
#include "ui.h"
#include <stdint.h>

typedef enum {
    HOMESCREEN_BUTTON_LIGHT,
    HOMESCREEN_BUTTON_SOUND,
    HOMESCREEN_BUTTON_SETTINGS,
    HOMESCREEN_BUTTON_PLACEHOLDER1,
    HOMESCREEN_BUTTON_PLACEHOLDER2,
    HOMESCREEN_BUTTON_PLACEHOLDER3,
} Homescreen_Buttons;

typedef struct
{
    uint32_t background_color;
    char *icon_symbol;
    char *btn_name;
} Homescreen_Button_t;

void Home_Screen_Create(void);

#endif // __HOME_H_