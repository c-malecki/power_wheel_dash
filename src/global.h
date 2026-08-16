#ifndef __UI_TYPES_H_
#define __UI_TYPES_H_

#include <stdint.h>

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

#endif // __UI_TYPES_H_