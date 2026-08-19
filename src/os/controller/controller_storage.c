#include "controller_storage.h"
#include "driver_storage.h"
#include "esp_log.h"
#include "global.h"

void Storage_Controller_Init(void) {
  /*
   */
}

void Storage_Controller_RX(G_Event_t *g_event) {
  //   ESP_LOGI("STORAGE_CONTROLLER", "event received");

  switch (g_event->event_id) {

  case G_EVENT_FS_FILE_REQ: {
    G_FS_File_ID file_id = (G_FS_File_ID)g_event->payload;
    const char *path = Global_Filepath_Lookup(file_id);

    FILE *f = Storage_Driver_FileRead(path);
    if (f == NULL) {
      break;
    }

    G_Event_t new_g_event = {
        .tx_controller_id = G_CONTROLLER_STORAGE,
        .rx_controller_id = G_CONTROLLER_SOUND,
        .event_id = G_EVENT_SFX_PLAY,
        .payload_data = (void *)f,
    };

    if (xQueueSend(g_event_queue, &new_g_event, pdMS_TO_TICKS(50)) != pdTRUE) {
      ESP_LOGW("STORAGE_CONTROLLER", "event queue full, dropped event id=%d",
               new_g_event.event_id);
      fclose(f);
    }

    break;
  }

  default:
    break;
  }
};