#include "os.h"
#include "display.h"

esp_err_t OS_Init(OS_t *OS) {
  OS->current_screen = OS_SCREEN_HOME;

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

  Home_Screen_Create();

  Display_Control_TaskRun();

  return Light_Control_Init(&OS->lights);
}

void OS_SetScreen(OS_Screens screen) {
  switch (screen) {
  case OS_SCREEN_HOME:
    Home_Screen_Create();
    break;

  case OS_SCREEN_LIGHTS:

    break;
  }
}