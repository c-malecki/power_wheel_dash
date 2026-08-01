#include "display.h"

/* */

static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;

static esp_lcd_touch_handle_t touch_handle = NULL;
static lv_indev_drv_t indev_drv;

/* */

static bool flush_ready_cb(esp_lcd_panel_io_handle_t panel_io,
                           esp_lcd_panel_io_event_data_t *edata,
                           void *user_ctx) {
  lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
  lv_disp_flush_ready(disp_driver);
  return false;
}

static void flush_exec_cb(lv_disp_drv_t *drv, const lv_area_t *area,
                          lv_color_t *color_map) {
  esp_lcd_panel_handle_t panel = (esp_lcd_panel_handle_t)drv->user_data;
  esp_lcd_panel_draw_bitmap(panel, area->x1, area->y1, area->x2 + 1,
                            area->y2 + 1, color_map);
}

static void touchpad_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data) {
  ESP_LOGI("TOUCH", "read_cb called");
  esp_lcd_touch_point_data_t point;
  uint8_t point_count = 0;

  esp_err_t err = esp_lcd_touch_read_data(touch_handle);
  if (err != ESP_OK) {
    ESP_LOGW("TOUCH", "read_data failed: %s", esp_err_to_name(err));
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

esp_err_t Display_Init(void) {
  gpio_config_t bk_gpio_config = {.mode = GPIO_MODE_OUTPUT,
                                  .pin_bit_mask = 1ULL << DISPLAY_LCD_LED_PIN};
  gpio_config(&bk_gpio_config);
  gpio_set_level(DISPLAY_LCD_LED_PIN, 1);

  spi_bus_config_t buscfg = {
      .sclk_io_num = SPI_CLK_PIN,
      .mosi_io_num = SPI_MOSI_PIN,
      .miso_io_num = SPI_MISO_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  ESP_ERROR_CHECK(spi_bus_initialize(SPI_HOST_PIN, &buscfg, SPI_DMA_CH_AUTO));

  esp_lcd_panel_io_spi_config_t io_config = {
      .dc_gpio_num = DISPLAY_LCD_DC_PIN,
      .cs_gpio_num = DISPLAY_LCD_CS_PIN,
      .pclk_hz = 20 * 1000 * 1000,
      .lcd_cmd_bits = 8,
      .lcd_param_bits = 8,
      .spi_mode = 0,
      .trans_queue_depth = 10,
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
      (esp_lcd_spi_bus_handle_t)SPI_HOST_PIN, &io_config, &io_handle));

  esp_lcd_panel_dev_config_t panel_config = {
      .reset_gpio_num = DISPLAY_LCD_RST_PIN,
      .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
      .bits_per_pixel = 16,
  };
  ESP_ERROR_CHECK(
      esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));
  esp_lcd_panel_reset(panel_handle);
  esp_lcd_panel_init(panel_handle);
  esp_lcd_panel_swap_xy(panel_handle, true);
  esp_lcd_panel_disp_on_off(panel_handle, true);

  // touch setup
  esp_lcd_panel_io_handle_t touch_io_handle = NULL;
  esp_lcd_panel_io_spi_config_t touch_io_config =
      ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(DISPLAY_LCD_T_CS_PIN);
  ESP_ERROR_CHECK(
      esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_HOST_PIN,
                               &touch_io_config, &touch_io_handle));

  esp_lcd_touch_config_t touch_config = {
      .x_max = 240, // match your panel's native resolution, pre-swap
      .y_max = 320,
      .rst_gpio_num = GPIO_NUM_NC,
      .int_gpio_num = DISPLAY_LCD_T_IRQ_PIN,
      .flags =
          {
              .swap_xy = 1,  // match your display swap_xy setting
              .mirror_x = 0, // tune to match display mirror settings
              .mirror_y = 0,
          },
  };
  ESP_ERROR_CHECK(esp_lcd_touch_new_spi_xpt2046(touch_io_handle, &touch_config,
                                                &touch_handle));

  // end touch

  lv_init();
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf1[320 * 20];
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 20);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = flush_exec_cb;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.user_data = panel_handle;
  lv_disp_drv_register(&disp_drv);

  esp_lcd_panel_io_callbacks_t iccbs = {.on_color_trans_done = flush_ready_cb};
  esp_lcd_panel_io_register_event_callbacks(io_handle, &iccbs, &disp_drv);

  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = touchpad_read_cb;
  lv_indev_drv_register(&indev_drv);
  ESP_LOGI("TOUCH", "indev registered, touch_handle=%p", touch_handle);

  lv_obj_t *screen = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x1a1a1a), 0);

  xTaskCreatePinnedToCore(Display_Task, "Display Task", 4096, NULL, 5, NULL, 1);

  Home_Screen_Create(screen);

  return ESP_OK;
}

void Display_Task(void *arg) {
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_timer_handler();
  }
}

/* */

esp_lcd_touch_handle_t Display_GetTouchHandle(void) { return touch_handle; }