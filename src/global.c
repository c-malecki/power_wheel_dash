#include "global.h"

const G_Color_t g_color_none = {0, 0, 0};
const G_Color_t g_color_white = {255, 255, 255}; // 127, 127, 127
const G_Color_t g_color_red = {255, 0, 0};       // 127, 0, 0
const G_Color_t g_color_orange = {255, 128, 0};  // 127, 64, 0
const G_Color_t g_color_yellow = {255, 255, 0};  // 127, 127, 0
const G_Color_t g_color_green = {0, 255, 0};     // 0, 127, 0
const G_Color_t g_color_blue = {0, 0, 255};      // 0, 0, 127
const G_Color_t g_color_violet = {128, 0, 255};  // 64, 0, 127,
const G_Color_t g_color_gray = {96, 125, 139};   // 48, 75, 70

G_Color_t Global_Color_Lookup(G_Color_ID color_id) {
  switch (color_id) {
  case G_COLOR_WHITE:
    return g_color_white;
  case G_COLOR_RED:
    return g_color_red;
  case G_COLOR_ORANGE:
    return g_color_orange;
  case G_COLOR_YELLOW:
    return g_color_yellow;
  case G_COLOR_GREEN:
    return g_color_green;
  case G_COLOR_BLUE:
    return g_color_blue;
  case G_COLOR_VIOLET:
    return g_color_violet;
  case G_COLOR_GRAY:
    return g_color_gray;
  default:
    return g_color_none;
  }
}