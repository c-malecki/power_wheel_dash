#ifndef __OS_H_
#define __OS_H_

#include "light.h"
#include "display.h"
#include "storage.h"
#include "sound.h"

typedef struct
{
    Display_Control_t display;
    Light_Control_t lights;
    Storage_Control_t storage;

} OS_t;

#endif // __OS_H_