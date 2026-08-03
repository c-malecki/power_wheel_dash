#include "os.h"
#include "config.h"
#include "display.h"
#include "light.h"

static State_t state;

esp_err_t OS_Init(void) {
  state.screens_current = STATE_SCREEN_HOME;

  spi_bus_config_t buscfg = {
      .sclk_io_num = SPI_CLK_PIN,
      .mosi_io_num = SPI_MOSI_PIN,
      .miso_io_num = SPI_MISO_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  esp_err_t err = spi_bus_initialize(SPI_HOST_PIN, &buscfg, SPI_DMA_CH_AUTO);
  if (err != ESP_OK) {
    return err;
  }

  err = Display_Control_Init();
  if (err != ESP_OK) {
    return err;
  }

  lv_obj_clean(lv_scr_act());

  Display_Navigate(UI_SCREEN_ID_HOME);

  Display_Control_TaskRun();

  return Light_Init();
}