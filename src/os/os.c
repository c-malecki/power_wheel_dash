#include "os.h"
#include "config.h"
#include "display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "light.h"
#include "ui_manager.h"

static QueueHandle_t OS_event_queue = NULL;
SemaphoreHandle_t OS_state_mutex = NULL;

/* INTERFACE */

void OS_Navigate(UI_View_IDs new_view_id) {
  switch (new_view_id) {
  case UI_VIEW_HOME:
    UI_Manager_RenderView(&views_home);
    break;

  case UI_VIEW_LIGHT:
    UI_Manager_RenderView(&views_light);
    break;

  default:
    break;
  }
}

void OS_PostEvent(OS_Event_t event) { xQueueSend(OS_event_queue, &event, 0); }

/* SETUP STUFF */

static void os_task(void *arg) {
  OS_Event_t event;
  while (1) {
    if (xQueueReceive(OS_event_queue, &event, portMAX_DELAY)) {
      xSemaphoreTake(OS_state_mutex, portMAX_DELAY);

      switch (event.type) {
      case OS_EVENT_NAVIGATE:
        OS_Navigate(event.data.view_id);
        break;
      case OS_EVENT_LIGHT_CHANGE:
        // OS_state.headlight_color = event.data.color;
        break;
      default:
        break;
      }

      xSemaphoreGive(OS_state_mutex);
    }
  }
}

esp_err_t OS_Init(void) {
  OS_state_mutex = xSemaphoreCreateMutex();
  OS_event_queue = xQueueCreate(10, sizeof(OS_Event_t));

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

  // drivers
  err = Display_Init();
  if (err != ESP_OK) {
    return err;
  }

  err = Light_Init();
  if (err != ESP_OK) {
    return err;
  }

  // higher level systems
  UI_Manager_Init();
  OS_Navigate(UI_VIEW_HOME);

  xTaskCreatePinnedToCore(os_task, "os_task", 4096, NULL, 10, NULL, 0);

  Display_TaskRun();

  return ESP_OK;
}