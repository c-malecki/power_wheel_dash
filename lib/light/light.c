#include "light.h"

static led_strip_handle_t headlight_strip;
// static led_strip_handle_t body_strip;

const Light_Color_t light_color_red = {.b = 0, .r = 150, .g = 0};
const Light_Color_t light_color_green = {.b = 0, .r = 0, .g = 150};
const Light_Color_t light_color_blue = {.b = 150, .r = 0, .g = 0};
const Light_Color_t light_color_purple = {.b = 150, .r = 150, .g = 0};

esp_err_t Light_Init(void) {
  led_strip_config_t headlight_config = {
      .strip_gpio_num = LED_HEADLIGHT_DATA_PIN,
      .max_leds = 1, // 16
      .led_model = LED_MODEL_WS2812,
      .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
      .flags.invert_out = false,
  };

  // led_strip_config_t body_config = {
  //     .strip_gpio_num = LED_BODY_DATA_PIN,
  //     .max_leds = 16,
  //     .led_model = LED_MODEL_WS2812,
  //     .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
  //     .flags.invert_out = false,
  // };

  led_strip_rmt_config_t rmt_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT,
      .resolution_hz = 10 * 1000 * 1000, // 10MHz
      .flags.with_dma = false,
  };

  // esp_err_t err =
  //     led_strip_new_rmt_device(&body_config, &rmt_config, &body_strip);
  // if (err != ESP_OK) {
  //   return err;
  // }

  return led_strip_new_rmt_device(&headlight_config, &rmt_config,
                                  &headlight_strip);
}

void Headlight_SetColor(uint32_t index, Light_Color_t color) {
  led_strip_clear(headlight_strip);
  led_strip_set_pixel(headlight_strip, index, color.r, color.g, color.b);
  led_strip_refresh(headlight_strip);
}