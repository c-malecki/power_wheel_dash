#include "types.h"

const Sys_Color_t g_color_none = {0, 0, 0};
const Sys_Color_t g_color_white = {255, 255, 255}; // 127, 127, 127
const Sys_Color_t g_color_red = {255, 0, 0};       // 127, 0, 0
const Sys_Color_t g_color_orange = {255, 128, 0};  // 127, 64, 0
const Sys_Color_t g_color_yellow = {255, 255, 0};  // 127, 127, 0
const Sys_Color_t g_color_green = {0, 255, 0};     // 0, 127, 0
const Sys_Color_t g_color_blue = {0, 0, 255};      // 0, 0, 127
const Sys_Color_t g_color_violet = {128, 0, 255};  // 64, 0, 127,
const Sys_Color_t g_color_gray = {96, 125, 139};   // 48, 75, 70

Sys_Color_t Sys_Color_Lookup(Sys_Color_ID color_id) {
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

const G_FS_File_t g_fs_file_none = {.file_id = G_FS_FILE_NONE, .path = "/sfx"};

const G_FS_File_t g_fs_file_car_start = {.file_id = G_FS_FILE_CAR_START,
                                         .path = "/sfx/car_start.wav"};

const char *Global_Filepath_Lookup(G_FS_File_ID file_id) {
  switch (file_id) {
  case G_SFX_CAR_START:
    return g_fs_file_car_start.path;
  default:
    return g_fs_file_none.path;
  }
}

const G_Sfx_t g_sfx_none = {
    .sfx_id = G_SFX_NONE,
    .file_id = G_FS_FILE_NONE,
};

const G_Sfx_t g_sfx_car_start = {
    .sfx_id = G_SFX_CAR_START,
    .file_id = G_FS_FILE_CAR_START,
};

G_FS_File_ID Global_Sfx_File_ID_Lookup(G_Sfx_ID sfx_id) {
  switch (sfx_id) {
  case G_SFX_CAR_START: {
    return g_sfx_car_start.file_id;
  }

  default:
    return g_sfx_none.file_id;
  }
}

// const G_Sfx_t g_sfx_table[] = {
//     // car power on sound
//     {
//         .sfx_id = G_SFX_CAR_START,
//         .file_id = G_FS_FILE_CAR_START,
//     },
// };
// const size_t g_sfx_table_size =
//     sizeof(g_sfx_table) / sizeof(g_sfx_table[0]);
