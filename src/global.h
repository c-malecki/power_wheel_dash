#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdint.h>

#ifdef DEVELOPMENT
/* Development Configuration */
#define LED_STRIP_MAX_LEDS (1)
#define LOG_LEVEL LOG_LEVEL_INFO
// Macro to execute a block of development-only code
#define DEV_ONLY(code)                                                         \
  do {                                                                         \
    code;                                                                      \
  } while (0)
#else
/* Production Configuration */
#define LED_STRIP_MAX_LEDS (10)
#define LOG_LEVEL LOG_LEVEL_ERROR
// Compiles out completely in production
#define DEV_ONLY(code)                                                         \
  do {                                                                         \
  } while (0)
#endif

/* *** HARDWARE *** */

// avoid GPIO 0, 46, 45, 35, 36, 37

/*
  LCD
*/
#define LCD_PIN_SPI_MOSI (11)
#define LCD_PIN_SPI_CLK (12)
#define LCD_PIN_SPI_MISO (13)
#define LCD_PIN_DC (8)
#define LCD_PIN_RST (9)
#define LCD_PIN_CS (10)
#define LCD_PIN_LED (18)
#define LCD_PIN_T_IRQ (16)
#define LCD_PIN_T_CS (17)

/*
  MicroSD Card
  https://docs.espressif.com/projects/esp-idf/en/release-v6.1/esp32s3/api-reference/peripherals/sdmmc_host.html
*/
#define MICROSD_PIN_SPI_MOSI (37)
#define MICROSD_PIN_SPI_CLK (36)
#define MICROSD_PIN_SPI_MISO (35)
#define MICROSD_PIN_SPI_CS (38)
#define MICROSD_MAX_FREQ (10000)
#define MICROSD_MOUNT_POINT "/sdcard"

/*
  WS2812 LEDs
*/
#define LED_PIN_HLL_DC (1)
#define LED_PIN_HLR_DC (2)
#define LED_PIN_BLL_DC (41)
#define LED_PIN_BLR_DC (42)

/*
  MAX98357a Class D Audio Amplifier
*/

#define AUDIO_AMP_PIN_LRC (15)
#define AUDIO_AMP_PIN_BCLK (7)
#define AUDIO_AMP_PIN_DIN (6)

/* SYSTEM GLOBALS */

extern QueueHandle_t g_event_queue;

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

typedef struct {
  G_Controller_ID tx_controller_id;
  G_Controller_ID rx_controller_id;
  G_Event_ID event_id;
  uint32_t payload;
  void *payload_data;
} G_Event_t;

typedef void (*g_event_ui_intercept_cb)(G_Event_t *g_event);

void G_Event_Queue_Init(void);

G_Event_t G_Event_Create(G_Controller_ID tx_controller_id,
                         G_Controller_ID rx_controller_id, G_Event_ID event_id,
                         uint32_t payload);

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