#ifndef __LAYOUT_H_
#define __LAYOUT_H_

#include "lvgl.h"

typedef enum {
    UI_LAYOUT_FLEX = 0,
    UI_LAYOUT_GRID
} UI_Layout_Types;

typedef enum {
    UI_LAYOUT_DIMENSION_3x1 = 0,
    UI_LAYOUT_DIMENSION_3x2,
    UI_LAYOUT_DIMENSION_3x3
} UI_Layout_Dimensions;

#endif // __LAYOUT_H_