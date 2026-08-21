#ifndef __TYPES_H_
#define __TYPES_H_

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
  UI_SCREEN_NONE = 0,
  UI_SCREEN_HOME,
  UI_SCREEN_LIGHT,
  UI_SCREEN_SOUND,
} Sys_Screen_ID;

typedef enum {
  SYS_CONTROLLER_NONE = 0,
  SYS_CONTROLLER_UI,
  SYS_CONTROLLER_LIGHT,
  SYS_CONTROLLER_SOUND,
  SYS_CONTROLLER_STORAGE,
} Sys_Controller_ID;

typedef enum {
  SYS_EVENT_NONE = 0,
  SYS_EVENT_NAVIGATE,
  SYS_EVENT_LIGHT_SELECT,
  SYS_EVENT_SFX_SELECT,
  SYS_EVENT_SFX_PLAY,
  SYS_EVENT_FS_FILE_REQ,
} Sys_Event_ID;

typedef struct {
  Sys_Controller_ID tx_controller_id;
  Sys_Controller_ID rx_controller_id;
  Sys_Event_ID event_id;
  uint32_t payload;
  void *payload_data;
} Sys_Event_t;

typedef void (*sys_event_ui_intercept_cb)(Sys_Event_t *sys_event);

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
} Sys_Color_ID;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Sys_Color_t;

extern const Sys_Color_t g_color_none;
extern const Sys_Color_t g_color_white;
extern const Sys_Color_t g_color_red;
extern const Sys_Color_t g_color_orange;
extern const Sys_Color_t g_color_yellow;
extern const Sys_Color_t g_color_green;
extern const Sys_Color_t g_color_blue;
extern const Sys_Color_t g_color_violet;
extern const Sys_Color_t g_color_gray;

Sys_Color_t Sys_Color_Lookup(Sys_Color_ID color_id);

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

#endif // __TYPES_H_