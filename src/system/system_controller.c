#include "system_controller.h"
#include "display.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "led.h"
#include "system_definitions.h"
#include "ui_controller.h"

#define SPI_MOSI_PIN 11
#define SPI_CLK_PIN 12
#define SPI_MISO_PIN 13

QueueHandle_t system_event_queue = NULL;
SemaphoreHandle_t system_mutex = NULL;

static void system_task(void *arg) {
  System_Event_t system_event;
  while (1) {
    if (xQueueReceive(system_event_queue, &system_event, portMAX_DELAY)) {
      xSemaphoreTake(system_mutex, portMAX_DELAY);
      ESP_LOGI("TOUCH TRIGGER", "system_task queue");

      switch (system_event.destination) {
      case SYSTEM_CONTROLLER_UI:
        UI_Controller_HandleSystemEvent(&system_event);
        break;

      case SYSTEM_CONTROLLER_LIGHT:

        break;

      case SYSTEM_CONTROLLER_NONE:

        break;
      }

      xSemaphoreGive(system_mutex);
    }
  }
}

esp_err_t System_Controller_Init(void) {
  system_event_queue = xQueueCreate(10, sizeof(System_Event_t));
  system_mutex = xSemaphoreCreateMutex();

  spi_bus_config_t buscfg = {
      .sclk_io_num = SPI_CLK_PIN,
      .mosi_io_num = SPI_MOSI_PIN,
      .miso_io_num = SPI_MISO_PIN,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 240 * 320 * sizeof(uint16_t),
  };
  esp_err_t err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
  if (err != ESP_OK) {
    return err;
  }

  // display controller init
  // touch controller init

  // drivers
  err = Display_Init();
  if (err != ESP_OK) {
    return err;
  }

  err = LED_Init();
  if (err != ESP_OK) {
    return err;
  }

  // higher level systems
  UI_Controller_Init();

  xTaskCreatePinnedToCore(system_task, "system_task", 4096, NULL, 10, NULL, 0);

  Display_TaskRun();

  return ESP_OK;
}