#ifndef __INPUT_H_
#define __INPUT_H_

#include <stdint.h>

typedef enum {
    UI_INPUT_TYPE_BUTTON = 0,
    UI_INPUT_TYPE_COLOR,
} UI_Input_Types;

typedef enum {
    UI_INPUT_ACTION_NAVIGATE = 0,
    UI_INPUT_ACTION_SET_VALUE,
    UI_INPUT_ACTION_TRIGGER,
} UI_Input_Action_Types;

typedef struct
{
    UI_Input_Action_Types action_type;
    uint32_t action_data;
    uint32_t color;
    char *symbol;
    const char *name;
    int col_pos;
    int row_pos;
} UI_Button_t;

typedef struct
{
    UI_Input_Action_Types action_type;
    uint32_t action_data;
    uint32_t color;
    int col_pos;
    int row_pos;
    union {

    } data;
} UI_Input_t;

#endif // __INPUT_H_