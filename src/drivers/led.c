#include "led.h"

static led_strip_handle_t strip_hl_l;
static led_strip_handle_t strip_hl_r;
static led_strip_handle_t strip_body;

// split headlights into 8, top 3 are turn signal and all are lights

const LED_Color_t lED_color_none = {.b = 0, .r = 0, .g = 0};
const LED_Color_t lED_color_red = {.b = 0, .r = 150, .g = 0};
const LED_Color_t lED_color_green = {.b = 0, .r = 0, .g = 150};
const LED_Color_t lED_color_blue = {.b = 150, .r = 0, .g = 0};
const LED_Color_t lED_color_purple = {.b = 150, .r = 150, .g = 0};

void strip_set_color(led_strip_handle_t strip, uint8_t len, LED_Color_t color);

/* */

esp_err_t LED_Init(void) {
  led_strip_config_t hll_config = {
      .strip_gpio_num = LED_HEADLED_L_DC_PIN,
      .max_leds = LED_HEADLED_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t hlr_config = {
      .strip_gpio_num = LED_HEADLED_R_DC_PIN,
      .max_leds = LED_HEADLED_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t body_config = {
      .strip_gpio_num = LED_BODYLED_DC_PIN,
      .max_leds = LED_BODYLED_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_rmt_config_t rmt_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT,
      .resolution_hz = 10 * 1000 * 1000, // 10MHz
      .flags.with_dma = false,
  };

  esp_err_t err =
      led_strip_new_rmt_device(&hll_config, &rmt_config, &strip_hl_l);
  if (err != ESP_OK) {
    return err;
  }

  err = led_strip_new_rmt_device(&hlr_config, &rmt_config, &strip_hl_r);
  if (err != ESP_OK) {
    return err;
  }

  return led_strip_new_rmt_device(&body_config, &rmt_config, &strip_body);
}

void LED_SetColor(LED_Sections section, LED_Color_t color) {
  switch (section) {
  case LED_SECTION_HL_L:
    strip_set_color(strip_hl_l, LED_HEADLED_MAX_LEDS, color);
    break;

  case LED_SECTION_HL_R:
    strip_set_color(strip_hl_r, LED_HEADLED_MAX_LEDS, color);
    break;

  case LED_SECTION_BODY:
    strip_set_color(strip_body, LED_BODYLED_MAX_LEDS, color);
    break;
  }
}

/* */

void strip_set_color(led_strip_handle_t strip, uint8_t len, LED_Color_t color) {
  led_strip_clear(strip);

  for (uint8_t i = 0; i < len; i++) {
    led_strip_set_pixel(strip, i, color.r, color.g, color.b);
  }

  led_strip_refresh(strip);
}