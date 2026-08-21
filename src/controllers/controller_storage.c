#include "controller_storage.h"
#include "driver_storage.h"
#include "esp_log.h"
#include "model.h"
#include "types.h"

void Storage_Controller_Init(void) {
  /*
   */
}

void Storage_Controller_RX(Sys_Event_t *sys_event) {
  //   ESP_LOGI("STORAGE_CONTROLLER", "event received");

  switch (sys_event->event_id) {

  case SYS_EVENT_FS_FILE_REQ: {
    G_FS_File_ID file_id = (G_FS_File_ID)sys_event->payload;
    const char *path = Global_Filepath_Lookup(file_id);

    FILE *f = Storage_Driver_FileRead(path);
    if (f == NULL) {
      break;
    }

    Sys_Event_t new_sys_event = {
        .tx_controller_id = SYS_CONTROLLER_STORAGE,
        .rx_controller_id = SYS_CONTROLLER_SOUND,
        .event_id = SYS_EVENT_SFX_PLAY,
        .payload_data = (void *)f,
    };

    if (xQueueSend(SYS_EVENT_QUEUE, &new_sys_event, pdMS_TO_TICKS(50)) !=
        pdTRUE) {
      ESP_LOGW("STORAGE_CONTROLLER", "event queue full, dropped event id=%d",
               new_sys_event.event_id);
      fclose(f);
    }

    break;
  }

  default:
    break;
  }
};