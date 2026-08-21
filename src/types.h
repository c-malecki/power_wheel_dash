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
  UI_STYLE_LAYOUT_GRID_NONE = 0,
  UI_STYLE_LAYOUT_GRID_2x1,
  UI_STYLE_LAYOUT_GRID_3x2,
  UI_STYLE_LAYOUT_GRID_5x3,
} UI_Style_Layout_Grid_ID;

typedef enum {
  UI_STYLE_ELEMENT_NONE = 0,
  // global buttons
  UI_STYLE_ELEMENT_SYS_BUTTON,
  // navigation buttons/icons
  UI_STYLE_ELEMENT_NAV_BUTTON,
} UI_Style_Element_ID;

typedef enum {
  UI_ELEMENT_NONE = 0,
  // global back to home button
  UI_ELEMENT_SYS_HOME_BTN,
  // home
  UI_ELEMENT_HOME_LIGHT_NAV,
  UI_ELEMENT_HOME_SOUND_NAV,
  UI_ELEMENT_HOME_SETTINGS_NAV,
  // lights
  UI_ELEMENT_LIGHT_SCREEN_HEADLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_BODYLIGHTS_BTN,
  UI_ELEMENT_LIGHT_SCREEN_COLOR_PICKER,
  // sounds
  UI_ELEMENT_SOUND_SCREEN_SOUND_PICKER,
  UI_ELEMENT_SOUND_SCREEN_IGNITION_BTN,
} UI_Element_ID;

typedef enum {
  UI_SCREEN_NONE = 0,
  UI_SCREEN_HOME,
  UI_SCREEN_LIGHT,
  UI_SCREEN_SOUND,
} UI_Screen_ID;

typedef enum {
  OS_CONTROLLER_NONE = 0,
  OS_CONTROLLER_UI,
  OS_CONTROLLER_LIGHT,
  OS_CONTROLLER_SOUND,
  OS_CONTROLLER_STORAGE,
} OS_Controller_ID;

typedef enum {
  OS_EVENT_NONE = 0,
  OS_EVENT_NAVIGATE,
  OS_EVENT_LIGHT_SELECT,
  OS_EVENT_SFX_SELECT,
  OS_EVENT_SFX_PLAY,
  OS_EVENT_FS_FILE_REQ,
} OS_Event_ID;

typedef struct {
  OS_Controller_ID tx_controller_id;
  OS_Controller_ID rx_controller_id;
  OS_Event_ID event_id;
  uint32_t payload;
  void *payload_data;
} OS_Event_t;

typedef void (*os_event_ui_intercept_cb)(OS_Event_t *os_event);

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

#endif // __TYPES_H_