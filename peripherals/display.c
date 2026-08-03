#include "display.h"
#include "core/lv_event.h"
#include "core/lv_obj.h"
#include "ui.h"

/* */

static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;

static esp_lcd_touch_handle_t touch_handle = NULL;
static lv_indev_drv_t indev_drv;

// layouts

static const int16_t col_dsc_3x2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                      LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
static const int16_t row_dsc_3x2[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                      LV_GRID_TEMPLATE_LAST};

lv_obj_t *create_button(lv_obj_t *parent, lv_color_t color, const char *symbol,
                        const char *name, UI_Screen_IDs navigate_screen_id);
void create_screen(const UI_Screen_t *new_screen);

/* */

esp_err_t init_panel(void);
esp_err_t init_touch(void);
void init_lvgl(void);

static void display_task(void *arg) {
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(10));
    lv_timer_handler();
  }
}

/* PRIMARY FUNCTIONS */

esp_err_t Display_Control_Init() {
  esp_err_t err = init_panel();
  if (err != ESP_OK) {
    return err;
  }

  err = init_touch();
  if (err != ESP_OK) {
    return err;
  }

  init_lvgl();

  lv_obj_t *screen = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x1a1a1a), 0);

  return ESP_OK;
}

void Display_Control_TaskRun(void) {
  xTaskCreatePinnedToCore(display_task, "display task", 4096, NULL, 5, NULL, 1);
}

void Display_Navigate(UI_Screen_IDs ui_screen_id) {
  switch (ui_screen_id) {
  case UI_SCREEN_ID_HOME:
    create_screen(&screens_home);
    break;

  case UI_SCREEN_ID_LIGHT_CONTROL:
    create_screen(&screens_light_control);
    break;
  }
}

/* CALLBACKS */

static void button_touch_event_cb(lv_event_t *event) {
  lv_event_code_t code = lv_event_get_code(event);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_t *btn = lv_event_get_target(event);

    UI_Screen_IDs target_screen =
        (UI_Screen_IDs)(uintptr_t)lv_obj_get_user_data(btn);

    Display_Navigate((UI_Screen_IDs)target_screen);
  }
}

static void lvgl_tick_cb(void *arg) { lv_tick_inc(2); }

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

/* INIT SUB-FUNCTIONS */

esp_err_t init_panel(void) {
  gpio_config_t bk_gpio_config = {
      .mode = GPIO_MODE_OUTPUT, .pin_bit_mask = (1ULL << DISPLAY_LCD_LED_PIN)};
  esp_err_t err = gpio_config(&bk_gpio_config);
  if (err != ESP_OK) {
    return err;
  }

  err = gpio_set_level(DISPLAY_LCD_LED_PIN, 1);
  if (err != ESP_OK) {
    return err;
  }

  esp_lcd_panel_io_spi_config_t io_config = {
      .dc_gpio_num = DISPLAY_LCD_DC_PIN,
      .cs_gpio_num = DISPLAY_LCD_CS_PIN,
      .pclk_hz = 20 * 1000 * 1000,
      .lcd_cmd_bits = 8,
      .lcd_param_bits = 8,
      .spi_mode = 0,
      .trans_queue_depth = 10,
  };
  err = esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_HOST_PIN,
                                 &io_config, &io_handle);
  if (err != ESP_OK) {
    return err;
  }

  esp_lcd_panel_dev_config_t panel_config = {
      .reset_gpio_num = DISPLAY_LCD_RST_PIN,
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
      ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(DISPLAY_LCD_T_CS_PIN);
  ESP_ERROR_CHECK(
      esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_HOST_PIN,
                               &touch_io_config, &touch_io_handle));

  esp_lcd_touch_config_t touch_config = {
      .x_max = 240,
      .y_max = 320,
      .rst_gpio_num = GPIO_NUM_NC,
      .int_gpio_num = DISPLAY_LCD_T_IRQ_PIN,
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

  const esp_timer_create_args_t lvgl_tick_timer_args = {
      .callback = &lvgl_tick_cb, .name = "lvgl_tick"};

  esp_timer_handle_t lvgl_tick_timer = NULL;
  ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));

  ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, 2000));
}

/* */

lv_obj_t *create_button(lv_obj_t *parent, lv_color_t color, const char *symbol,
                        const char *name, UI_Screen_IDs navigate_screen_id) {

  lv_obj_t *btn = lv_btn_create(parent);

  lv_obj_set_size(btn, 70, 70);
  lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(btn, color, 0);

  lv_obj_add_event_cb(btn, button_touch_event_cb, LV_EVENT_CLICKED,
                      (void *)name);

  lv_obj_t *label = lv_label_create(btn);

  if (symbol != NULL && (uintptr_t)symbol > 0xFFFF) {
    lv_label_set_text(label, symbol);
  } else {
    lv_label_set_text(label, "?");
  }

  lv_obj_set_style_text_color(label, lv_color_white(), 0);
  lv_obj_set_style_text_opa(label, LV_OPA_80, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
  lv_obj_center(label);

  lv_obj_set_user_data(btn, (void *)(uintptr_t)navigate_screen_id);

  return btn;
}

void create_screen(const UI_Screen_t *target_screen) {
  lv_obj_t *cur_screen = lv_scr_act();
  lv_obj_clean(cur_screen);

  lv_obj_t *container = lv_obj_create(cur_screen);
  lv_obj_set_size(container, 320, 240);
  lv_obj_set_layout(container, LV_LAYOUT_GRID);

  switch (target_screen->layout) {
  case UI_SCREEN_LAYOUT_3x1:
    lv_obj_set_grid_dsc_array(container, col_dsc_3x2, row_dsc_3x2);
    break;

  case UI_SCREEN_LAYOUT_3x2:
    lv_obj_set_grid_dsc_array(container, col_dsc_3x2, row_dsc_3x2);
    break;
  }

  lv_obj_set_grid_dsc_array(container, col_dsc_3x2, row_dsc_3x2);

  lv_obj_set_style_flex_main_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_cross_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_flex_track_place(cur_screen, LV_FLEX_ALIGN_CENTER, 0);
  lv_obj_set_style_pad_row(cur_screen, 8, 0);

  for (int i = 0; i < target_screen->buttons_total; i++) {
    lv_obj_t *button = create_button(
        container, lv_color_hex(target_screen->buttons[i].background_color),
        target_screen->buttons[i].icon_symbol,
        target_screen->buttons[i].touch_event_name,
        target_screen->buttons[i].navigate_screen_id);
    lv_obj_set_grid_cell(
        button, LV_GRID_ALIGN_CENTER, target_screen->buttons[i].col_pos, 1,
        LV_GRID_ALIGN_CENTER, target_screen->buttons[i].row_pos, 1);
  }

  lv_scr_load(cur_screen);
}