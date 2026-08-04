#ifndef __VIEW_H_
#define __VIEW_H_

#include "input.h"
#include "layout.h"

typedef enum {
    UI_VIEW_HOME = 0,
    UI_VIEW_LIGHT_CONTROL,
    UI_VIEW_LIGHT_COLORPICKER,
    UI_VIEW_SOUND_CONTROL,
    UI_VIEW_SETTINGS,
} UI_View_IDs;

typedef struct
{
    UI_View_IDs view_id;
    UI_Layout_Types layout;
    UI_Layout_Dimensions dimensions;
    int buttons_total;
    UI_Button_t buttons[];
} UI_View_t;

extern UI_View_t const views_home;
extern UI_View_t const views_light_control;

#endif // __View_H_