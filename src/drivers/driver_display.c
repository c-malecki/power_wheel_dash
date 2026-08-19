#include "driver_display.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch_xpt2046.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "global.h"
#include "lvgl.h"
#include <stdint.h>

static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

static lv_display_t *disp = NULL;
static lv_indev_t *indev = NULL;

esp_err_t init_panel(void);
esp_err_t init_touch(void);
void init_lvgl(void);

/* INTERFACE */

esp_err_t DisplayDriver_Init() {
  spi_bus_config_t spi_bus_lcd = {
      .sclk_io_num = LCD_PIN_SPI_CLK,
      .mosi_io_num = LCD_PIN_SPI_MOSI,
      .miso_io_num = LCD_PIN_SPI_MISO,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  esp_err_t err = spi_bus_initialize(SPI2_HOST, &spi_bus_lcd, SPI_DMA_CH_AUTO);
  if (err != ESP_OK) {
    return err;
  }
  ESP_LOGI("DISPLAY DRIVER", "lcd spi bus initialized");

  err = init_panel();
  if (err != ESP_OK) {
    return err;
  }

  err = init_touch();
  if (err != ESP_OK) {
    return err;
  }

  init_lvgl();

  LV_FONT_DECLARE(icon_lightbulb);
  LV_FONT_DECLARE(icon_sun);

  return ESP_OK;
}

/* SETUP */

static void lvgl_tick_cb(void *arg) { lv_tick_inc(2); }

static void touchpad_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
  esp_lcd_touch_point_data_t point;
  uint8_t point_count = 0;

  esp_err_t err = esp_lcd_touch_read_data(touch_handle);
  if (err != ESP_OK) {
    data->state = LV_INDEV_STATE_RELEASED;
    return;
  }

  bool pressed =
      esp_lcd_touch_get_data(touch_handle, &point, &point_count, 1) == ESP_OK &&
      point_count > 0;
  if (pressed) {
    data->point.x = point.x;
    data->point.y = point.y;
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

static bool flush_ready_cb(esp_lcd_panel_io_handle_t panel_io,
                           esp_lcd_panel_io_event_data_t *edata,
                           void *user_ctx) {
  lv_display_t *disp = (lv_display_t *)user_ctx;
  lv_display_flush_ready(disp);
  return false;
}

static void flush_exec_cb(lv_display_t *disp, const lv_area_t *area,
                          uint8_t *px_map) {
  esp_lcd_panel_handle_t panel =
      (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);

  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);
  lv_draw_sw_rgb565_swap(px_map, w * h);

  esp_lcd_panel_draw_bitmap(panel, area->x1, area->y1, area->x2 + 1,
                            area->y2 + 1, (uint16_t *)px_map);
}

esp_err_t init_panel(void) {
  gpio_config_t bk_gpio_config = {.mode = GPIO_MODE_OUTPUT,
                                  .pin_bit_mask = (1ULL << LCD_PIN_LED)};
  esp_err_t err = gpio_config(&bk_gpio_config);
  if (err != ESP_OK) {
    return err;
  }

  err = gpio_set_level(LCD_PIN_LED, 1);
  if (err != ESP_OK) {
    return err;
  }

  esp_lcd_panel_io_spi_config_t io_config = {
      .dc_gpio_num = LCD_PIN_DC,
      .cs_gpio_num = LCD_PIN_CS,
      .pclk_hz = 20 * 1000 * 1000,
      .lcd_cmd_bits = 8,
      .lcd_param_bits = 8,
      .spi_mode = 0,
      .trans_queue_depth = 10,
  };
  err = esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST,
                                 &io_config, &io_handle);
  if (err != ESP_OK) {
    return err;
  }

  esp_lcd_panel_dev_config_t panel_config = {
      .reset_gpio_num = LCD_PIN_RST,
      .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
      .bits_per_pixel = 16,
  };

  err = esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle);
  if (err != ESP_OK) {
    return err;
  }

  err = esp_lcd_panel_reset(panel_handle);
  if (err != ESP_OK) {
    return err;
  }

  err = esp_lcd_panel_init(panel_handle);
  if (err != ESP_OK) {
    return err;
  }

  err = esp_lcd_panel_swap_xy(panel_handle, true);
  if (err != ESP_OK) {
    return err;
  }

  return esp_lcd_panel_disp_on_off(panel_handle, true);
}

esp_err_t init_touch(void) {
  esp_lcd_panel_io_handle_t touch_io_handle = NULL;
  esp_lcd_panel_io_spi_config_t touch_io_config =
      ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(LCD_PIN_T_CS);
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST,
                                           &touch_io_config, &touch_io_handle));

  esp_lcd_touch_config_t touch_config = {
      .x_max = 240,
      .y_max = 320,
      .rst_gpio_num = GPIO_NUM_NC,
      .int_gpio_num = LCD_PIN_T_IRQ,
      .flags =
          {
              .swap_xy = 1,
              .mirror_x = 1,
              .mirror_y = 1,
          },
  };

  return esp_lcd_touch_new_spi_xpt2046(touch_io_handle, &touch_config,
                                       &touch_handle);
}

void init_lvgl(void) {
  lv_init();

  disp = lv_display_create(320, 240);

  static lv_color_t buf1[320 * 20];
  lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_display_set_flush_cb(disp, flush_exec_cb);
  lv_display_set_user_data(disp, panel_handle);

  esp_lcd_panel_io_callbacks_t iccbs = {.on_color_trans_done = flush_ready_cb};
  esp_lcd_panel_io_register_event_callbacks(io_handle, &iccbs, disp);

  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchpad_read_cb);
  lv_indev_set_display(indev, disp);

  const esp_timer_create_args_t lvgl_tick_timer_args = {
      .callback = &lvgl_tick_cb, .name = "lvgl_tick"};
  esp_timer_handle_t lvgl_tick_timer = NULL;
  ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, 2000));
}