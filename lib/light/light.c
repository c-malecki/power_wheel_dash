#include "light.h"
#include <stdint.h>

/* */

static led_strip_handle_t strip_hl_l;
static led_strip_handle_t strip_hl_r;
static led_strip_handle_t strip_body;

/* */

// split headlights into 8, top 3 are turn signal and all are lights

const Light_Color_t light_color_none = {.b = 0, .r = 0, .g = 0};
const Light_Color_t light_color_red = {.b = 0, .r = 150, .g = 0};
const Light_Color_t light_color_green = {.b = 0, .r = 0, .g = 150};
const Light_Color_t light_color_blue = {.b = 150, .r = 0, .g = 0};
const Light_Color_t light_color_purple = {.b = 150, .r = 150, .g = 0};

void strip_set_color(led_strip_handle_t strip, uint8_t len,
                     Light_Color_t color);

/* */

esp_err_t Light_Control_Init(Light_Control_t *ctrl) {
  ctrl->headlight_l.is_on = false;
  ctrl->headlight_r.is_on = false;
  ctrl->bodylight.is_on = false;
  ctrl->headlight_l.color = light_color_none;
  ctrl->headlight_r.color = light_color_none;
  ctrl->bodylight.color = light_color_none;

  led_strip_config_t hll_config = {
      .strip_gpio_num = LIGHT_HEADLIGHT_L_DC_PIN,
      .max_leds = LIGHT_HEADLIGHT_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t hlr_config = {
      .strip_gpio_num = LIGHT_HEADLIGHT_R_DC_PIN,
      .max_leds = LIGHT_HEADLIGHT_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t body_config = {
      .strip_gpio_num = LIGHT_BODYLIGHT_DC_PIN,
      .max_leds = LIGHT_BODYLIGHT_MAX_LEDS,
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

void Light_SetColor(Light_Sections section, Light_Color_t color) {
  switch (section) {
  case LIGHT_SECTION_HL_L:
    strip_set_color(strip_hl_l, LIGHT_HEADLIGHT_MAX_LEDS, color);
    break;

  case LIGHT_SECTION_HL_R:
    strip_set_color(strip_hl_r, LIGHT_HEADLIGHT_MAX_LEDS, color);
    break;

  case LIGHT_SECTION_BODY:
    strip_set_color(strip_body, LIGHT_BODYLIGHT_MAX_LEDS, color);
    break;
  }
}

/* */

void strip_set_color(led_strip_handle_t strip, uint8_t len,
                     Light_Color_t color) {
  led_strip_clear(strip);

  for (uint8_t i = 0; i < len; i++) {
    led_strip_set_pixel(strip, i, color.r, color.g, color.b);
  }

  led_strip_refresh(strip);
}