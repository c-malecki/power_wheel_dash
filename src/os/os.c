#include "os.h"
#include "car_manager.h"
#include "display.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "led.h"
#include "view_manager.h"

#define SPI_MOSI_PIN 11
#define SPI_CLK_PIN 12
#define SPI_MISO_PIN 13

static QueueHandle_t OS_event_queue = NULL;
SemaphoreHandle_t OS_STATE_MUTEX = NULL;

void OS_PostEvent(DATA_TYPE_OSEvent_t os_event) {
  xQueueSend(OS_event_queue, &os_event, 0);
}

/* SETUP STUFF */

static void os_task(void *arg) {
  DATA_TYPE_OSEvent_t os_event;
  while (1) {
    if (xQueueReceive(OS_event_queue, &os_event, portMAX_DELAY)) {
      xSemaphoreTake(OS_STATE_MUTEX, portMAX_DELAY);

      switch (os_event.event_id) {
      case OSEVENT_VIEW_UPDATE_ID:
        View_Manager_Navigate(os_event.data.view_id);
        break;
      case OSEVENT_LED_UPDATE_ID:
        Car_Manager_SetLED(os_event.data.led_strip_id,
                           os_event.data.led_color_id,
                           os_event.data.led_strip_on);
        break;
      default:
        break;
      }

      xSemaphoreGive(OS_STATE_MUTEX);
    }
  }
}

esp_err_t OS_Init(void) {
  OS_STATE_MUTEX = xSemaphoreCreateMutex();
  OS_event_queue = xQueueCreate(10, sizeof(DATA_TYPE_OSEvent_t));

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
  Car_Manager_Init();
  View_Manager_Init();

  xTaskCreatePinnedToCore(os_task, "os_task", 4096, NULL, 10, NULL, 0);

  Display_TaskRun();

  return ESP_OK;
}