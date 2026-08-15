#include "led.h"
#include "led_strip.h"
#include "led_strip_types.h"
#include <stdint.h>

// todo: create separation from application dependency
// callback to register strips

static led_strip_handle_t strip_hll_handle;
static led_strip_handle_t strip_hlr_handle;
static led_strip_handle_t strip_body_handle;

static const LED_Color_t color_none = {0, 0, 0};
static const LED_Color_t color_white = {255, 255, 255};
static const LED_Color_t color_red = {255, 0, 0};
static const LED_Color_t color_orange = {255, 128, 0};
static const LED_Color_t color_yellow = {255, 255, 0};
static const LED_Color_t color_green = {0, 255, 0};
static const LED_Color_t color_blue = {0, 255, 0};
static const LED_Color_t color_violet = {128, 0, 255};

static const led_strip_config_t hll_config = {
    .strip_gpio_num = LED_HLL_DC_PIN,
    .max_leds = LED_HL_MAX_LEDS,
    .led_model = LED_MODEL_WS2812,
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
    .flags.invert_out = false,
};

static const led_strip_config_t hlr_config = {
    .strip_gpio_num = LED_HLR_DC_PIN,
    .max_leds = LED_HL_MAX_LEDS,
    .led_model = LED_MODEL_WS2812,
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
    .flags.invert_out = false,
};

static const led_strip_config_t body_config = {
    .strip_gpio_num = LED_BODY_DC_PIN,
    .max_leds = LED_HL_MAX_LEDS,
    .led_model = LED_MODEL_WS2812,
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
    .flags.invert_out = false,
};

static const led_strip_rmt_config_t rmt_config = {
    .clk_src = RMT_CLK_SRC_DEFAULT,
    .resolution_hz = 10 * 1000 * 1000, // 10MHz
    .flags.with_dma = false,
};

void set_color(led_strip_handle_t strip, uint8_t i, LED_Color_ID color_id) {
  switch (color_id) {
  case LED_COLOR_WHITE:
    led_strip_set_pixel(strip, i, color_white.r, color_white.g, color_white.b);
    break;

  case LED_COLOR_RED:
    led_strip_set_pixel(strip, i, color_red.r, color_red.g, color_red.b);
    break;

  case LED_COLOR_ORANGE:
    led_strip_set_pixel(strip, i, color_orange.r, color_orange.g,
                        color_orange.b);
    break;

  case LED_COLOR_YELLOW:
    led_strip_set_pixel(strip, i, color_yellow.r, color_yellow.g,
                        color_yellow.b);
    break;

  case LED_COLOR_GREEN:
    led_strip_set_pixel(strip, i, color_green.r, color_green.g, color_green.b);
    break;

  case LED_COLOR_BLUE:
    led_strip_set_pixel(strip, i, color_blue.r, color_blue.g, color_blue.b);
    break;

  case LED_COLOR_VIOLET:
    led_strip_set_pixel(strip, i, color_violet.r, color_violet.g,
                        color_violet.b);
    break;

  case LED_COLOR_NONE:
    led_strip_set_pixel(strip, i, color_none.r, color_none.g, color_none.b);
    break;
  }
}

void strip_set_color(LED_Strip_ID strip_id, LED_Color_ID color_id) {
  switch (strip_id) {
  case LED_STRIP_HEADLIGHT:
    led_strip_clear(strip_hll_handle);
    led_strip_clear(strip_hlr_handle);
    for (uint8_t i = 0; i < LED_HL_MAX_LEDS; i++) {
      set_color(strip_hll_handle, i, color_id);
      set_color(strip_hlr_handle, i, color_id);
    }
    led_strip_refresh(strip_hll_handle);
    led_strip_refresh(strip_hlr_handle);
    break;

  case LED_STRIP_BODYLIGHT:
    led_strip_clear(strip_hlr_handle);
    for (uint8_t i = 0; i < LED_HL_MAX_LEDS; i++) {
      set_color(strip_body_handle, i, color_id);
    }
    led_strip_refresh(strip_hlr_handle);
    break;

  case LED_STRIP_NONE:
    break;

  default:
    break;
  }
}

esp_err_t LED_Init(void) {
  esp_err_t err =
      led_strip_new_rmt_device(&hll_config, &rmt_config, &strip_hll_handle);
  if (err != ESP_OK) {
    return err;
  }

  err = led_strip_new_rmt_device(&hlr_config, &rmt_config, &strip_hlr_handle);
  if (err != ESP_OK) {
    return err;
  }

  return led_strip_new_rmt_device(&body_config, &rmt_config,
                                  &strip_body_handle);
}

void LED_SetHeadlights(LED_Color_ID color_id) {
  strip_set_color(LED_STRIP_HEADLIGHT, color_id);
}

void LED_SetBodylights(LED_Color_ID color_id) {
  strip_set_color(LED_STRIP_BODYLIGHT, color_id);
}

// const DT_LED_Color_t *color_from_id(DT_LED_Color_ID led_color_id) {
//   switch (led_color_id) {
//   case LED_COLOR_NONE_ID:
//     return &LED_COLOR_NONE;

//   case LED_COLOR_RED_ID:
//     return &LED_COLOR_RED;

//   case LED_COLOR_GREEN_ID:
//     return &LED_COLOR_GREEN;

//   case LED_COLOR_BLUE_ID:
//     return &LED_COLOR_BLUE;

//   case LED_COLOR_PURPLE_ID:
//     return &LED_COLOR_PURPLE;
//   }

//   return &LED_COLOR_NONE;
// }

// void LED_SetColor(DT_LED_Strip_ID led_strip_id, DT_LED_Color_ID color_id) {
//   strip_set_color(led_strip_id, color_from_id(color_id));
// }

/* */