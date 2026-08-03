#ifndef __UI_H_
#define __UI_H_

#include <stdint.h>

typedef enum {
    UI_SCREEN_ID_HOME = 0,
    UI_SCREEN_ID_LIGHT_CONTROL
} UI_Screen_IDs;

typedef struct
{
    uint32_t background_color;
    char *icon_symbol;
    UI_Screen_IDs navigate_screen_id;
    const char *touch_event_name;
    int col_pos;
    int row_pos;
} UI_Button_t;

typedef enum {
    UI_SCREEN_LAYOUT_3x1 = 0,
    UI_SCREEN_LAYOUT_3x2,
} UI_Screen_Layouts;

typedef struct
{
    UI_Screen_IDs screen_id;
    UI_Screen_Layouts layout;
    int buttons_total;
    UI_Button_t buttons[];
} UI_Screen_t;

#endif // __UI_H_