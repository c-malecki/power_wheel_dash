#include "led.h"

static led_strip_handle_t strip_hll_handle;
static led_strip_handle_t strip_hlr_handle;
static led_strip_handle_t strip_body_handle;

// split headlights into 8, top 3 are turn signal and all are lights

const LED_Color_t LED_COLOR_NONE = {.b = 0, .r = 0, .g = 0};
const LED_Color_t LED_COLOR_RED = {.b = 0, .r = 150, .g = 0};
const LED_Color_t LED_COLOR_GREEN = {.b = 0, .r = 0, .g = 150};
const LED_Color_t LED_COLOR_BLUE = {.b = 150, .r = 0, .g = 0};
const LED_Color_t LED_COLOR_PURPLE = {.b = 150, .r = 150, .g = 0};

void strip_set_color(LED_Strip_IDs strip_id, const LED_Color_t *color);

/* */

esp_err_t LED_Init(void) {
  led_strip_config_t hll_config = {
      .strip_gpio_num = LED_HLL_DC_PIN,
      .max_leds = LED_HL_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t hlr_config = {
      .strip_gpio_num = LED_HLR_DC_PIN,
      .max_leds = LED_HL_MAX_LEDS,
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  led_strip_config_t body_config = {
      .strip_gpio_num = LED_BODY_DC_PIN,
      .max_leds = LED_BODY_MAX_LEDS,
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

const LED_Color_t *color_from_id(LED_Color_IDs color_id) {
  switch (color_id) {
  case LED_COLOR_ID_NONE:
    return &LED_COLOR_NONE;

  case LED_COLOR_ID_RED:
    return &LED_COLOR_RED;

  case LED_COLOR_ID_GREEN:
    return &LED_COLOR_GREEN;

  case LED_COLOR_ID_BLUE:
    return &LED_COLOR_BLUE;

  case LED_COLOR_ID_PURPLE:
    return &LED_COLOR_PURPLE;
  }

  return &LED_COLOR_NONE;
}

void LED_SetColor(LED_Strip_IDs strip_id, LED_Color_IDs color_id) {
  strip_set_color(strip_id, color_from_id(color_id));
}

/* */

void strip_set_color(LED_Strip_IDs strip_id, const LED_Color_t *color) {
  switch (strip_id) {
  case LED_SECTION_HL_L:
    led_strip_clear(strip_hll_handle);
    for (uint8_t i = 0; i < LED_HL_MAX_LEDS; i++) {
      led_strip_set_pixel(strip_hll_handle, i, color->r, color->g, color->b);
    }
    led_strip_refresh(strip_hll_handle);
    break;

  case LED_SECTION_HL_R:
    led_strip_clear(strip_hlr_handle);
    for (uint8_t i = 0; i < LED_HL_MAX_LEDS; i++) {
      led_strip_set_pixel(strip_hlr_handle, i, color->r, color->g, color->b);
    }
    led_strip_refresh(strip_hlr_handle);
    break;

  case LED_SECTION_BODY:
    led_strip_clear(strip_body_handle);
    for (uint8_t i = 0; i < LED_BODY_MAX_LEDS; i++) {
      led_strip_set_pixel(strip_body_handle, i, color->r, color->g, color->b);
    }
    led_strip_refresh(strip_body_handle);
    break;
  }
}