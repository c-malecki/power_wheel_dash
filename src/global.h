#ifndef __UI_TYPES_H_
#define __UI_TYPES_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdint.h>

/* system */

extern QueueHandle_t g_event_queue;

typedef enum {
  G_CONTROLLER_NONE = 0,
  G_CONTROLLER_UI,
  G_CONTROLLER_LIGHT,
  G_CONTROLLER_SOUND,
} G_Controller_ID;

typedef enum {
  G_EVENT_NONE = 0,
  G_EVENT_NAVIGATE,
  G_EVENT_LIGHT_SELECT,
  G_EVENT_SFX_SELECT,
  G_EVENT_SFX_PLAY,
} G_Event_ID;

typedef struct {
  G_Controller_ID tx_controller_id;
  G_Controller_ID rx_controller_id;
  G_Event_ID event_id;
  uint32_t payload;
} G_Event_t;

typedef void (*g_event_ui_intercept_cb)(G_Event_t *g_event);

void G_Event_Queue_Init(void);

G_Event_t G_Event_Create(G_Controller_ID tx_controller_id,
                         G_Controller_ID rx_controller_id, G_Event_ID event_id,
                         uint32_t payload);

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
  const char *path;
} G_Sfx_t;

G_Sfx_t Global_Sfx_Lookup(G_Sfx_ID sfx_id);

#endif // __UI_TYPES_H_