#ifndef __OS_H_
#define __OS_H_

#include "esp_err.h"
#include "config.h"
#include "light.h"
#include "storage.h"
#include "sound.h"
#include "home_screen.h"

typedef enum {
    OS_SCREEN_HOME = 0,
    OS_SCREEN_LIGHTS,
} OS_Screens;

typedef struct
{
    OS_Screens current_screen;
    Light_Control_t lights;
    Storage_Control_t storage;
} OS_t;

esp_err_t OS_Init(OS_t *OS);
void OS_SetScreen(OS_Screens screen);

#endif // __OS_H_