#include "os.h"
#include "config.h"
#include "display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "light.h"
#include "portmacro.h"

static OS_State_t OS_state;
static QueueHandle_t OS_event_queue = NULL;
static SemaphoreHandle_t OS_state_mutex = NULL;

static void os_task(void *arg) {
  OS_Event_t event;
  while (1) {
    if (xQueueReceive(OS_event_queue, &event, portMAX_DELAY)) {
      xSemaphoreTake(OS_state_mutex, portMAX_DELAY);

      switch (event.type) {
      case OS_EVENT_NAVIGATE:
        OS_state.current_screen = event.data.screen_id;
        Display_Navigate(OS_state.current_screen);
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

  err = Display_Init();
  if (err != ESP_OK) {
    return err;
  }

  err = Light_Init();
  if (err != ESP_OK) {
    return err;
  }

  lv_obj_clean(lv_scr_act());
  Display_Navigate(UI_SCREEN_ID_HOME);

  xTaskCreatePinnedToCore(os_task, "os_task", 4096, NULL, 10, NULL, 0);

  Display_TaskRun();

  return ESP_OK;
}

void OS_PostEvent(OS_Event_t event) { xQueueSend(OS_event_queue, &event, 0); }