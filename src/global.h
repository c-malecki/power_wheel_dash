#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdint.h>

/* *** ENUM/IDs *** */

typedef enum {
  LED_STRIP_NONE = 0,
  LED_STRIP_HEADLIGHT,
  LED_STRIP_BODYLIGHT,
} LED_Strip_ID;

typedef enum {
  G_CONTROLLER_NONE = 0,
  G_CONTROLLER_UI,
  G_CONTROLLER_LIGHT,
  G_CONTROLLER_SOUND,
  G_CONTROLLER_STORAGE,
} G_Controller_ID;

typedef enum {
  G_EVENT_NONE = 0,
  G_EVENT_NAVIGATE,
  G_EVENT_LIGHT_SELECT,
  G_EVENT_SFX_SELECT,
  G_EVENT_SFX_PLAY,
  G_EVENT_FS_FILE_REQ,
} G_Event_ID;

typedef enum {
  G_FS_FILE_NONE = 0,
  G_FS_FILE_CAR_START,
} G_FS_File_ID;

typedef struct {
  G_FS_File_ID file_id;
  const char *path;
} G_FS_File_t;

const char *Global_Filepath_Lookup(G_FS_File_ID file_id);

/* styles */

typedef enum {
  G_COLOR_NONE = 0,
  G_COLOR_WHITE,
  G_COLOR_RED,
  G_COLOR_ORANGE,
  G_COLOR_YELLOW,
  G_COLOR_GREEN,
  G_COLOR_BLUE,
  G_COLOR_VIOLET,
  G_COLOR_GRAY,
} G_Color_ID;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} G_Color_t;

extern const G_Color_t g_color_none;
extern const G_Color_t g_color_white;
extern const G_Color_t g_color_red;
extern const G_Color_t g_color_orange;
extern const G_Color_t g_color_yellow;
extern const G_Color_t g_color_green;
extern const G_Color_t g_color_blue;
extern const G_Color_t g_color_violet;
extern const G_Color_t g_color_gray;

G_Color_t Global_Color_Lookup(G_Color_ID color_id);

/* sounds */

typedef enum {
  G_SFX_NONE = 0,
  G_SFX_CAR_START,
} G_Sfx_ID;

typedef struct {
  G_Sfx_ID sfx_id;
  G_FS_File_ID file_id;
} G_Sfx_t;

G_FS_File_ID Global_Sfx_File_ID_Lookup(G_Sfx_ID sfx_id);

/* tables */

// extern const G_Sfx_t g_sfx_table[];
// extern const size_t g_sfx_table_size;

#endif // __GLOBAL_H_