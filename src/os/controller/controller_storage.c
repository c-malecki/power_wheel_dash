#include "controller_storage.h"
#include "driver_storage.h"
#include "esp_log.h"
#include "state.h"
#include "types.h"

void Storage_Controller_Init(void) {
  /*
   */
}

void Storage_Controller_RX(OS_Event_t *os_event) {
  //   ESP_LOGI("STORAGE_CONTROLLER", "event received");

  switch (os_event->event_id) {

  case OS_EVENT_FS_FILE_REQ: {
    G_FS_File_ID file_id = (G_FS_File_ID)os_event->payload;
    const char *path = Global_Filepath_Lookup(file_id);

    FILE *f = Storage_Driver_FileRead(path);
    if (f == NULL) {
      break;
    }

    OS_Event_t new_os_event = {
        .tx_controller_id = OS_CONTROLLER_STORAGE,
        .rx_controller_id = OS_CONTROLLER_SOUND,
        .event_id = OS_EVENT_SFX_PLAY,
        .payload_data = (void *)f,
    };

    if (xQueueSend(os_event_queue, &new_os_event, pdMS_TO_TICKS(50)) !=
        pdTRUE) {
      ESP_LOGW("STORAGE_CONTROLLER", "event queue full, dropped event id=%d",
               new_os_event.event_id);
      fclose(f);
    }

    break;
  }

  default:
    break;
  }
};