#include "controller_sound.h"
#include "driver_sound.h"
#include "esp_log.h"
#include "state.h"
#include "types.h"

// static bool sfx_playing = false;
static G_Sfx_ID pending_sfx = G_SFX_NONE;
static G_Sfx_ID current_sfx = G_SFX_NONE;

void Sound_Controller_Init(void) { current_sfx = G_SFX_NONE; }

void Sound_Controller_RX(OS_Event_t *os_event) {
  // ESP_LOGI("SOUND_CONTROLLER", "event received");

  switch (os_event->event_id) {
  case OS_EVENT_SFX_SELECT: {
    pending_sfx = (G_Sfx_ID)os_event->payload;
    // ESP_LOGI("SOUND_CTONROLLER", "rx event payload sfx_id=%d", pending_sfx);
    G_FS_File_ID sfx_file_id =
        Global_Sfx_File_ID_Lookup((G_Sfx_ID)os_event->payload);
    // ESP_LOGI("SOUND_CTONROLLER", "tx event payload sfx_file_id=%d",
    //          sfx_file_id);

    OS_Event_t new_os_event = {
        .tx_controller_id = OS_CONTROLLER_SOUND,
        .rx_controller_id = OS_CONTROLLER_STORAGE,
        .event_id = OS_EVENT_FS_FILE_REQ,
        .payload = sfx_file_id,
    };

    if (xQueueSend(os_event_queue, &new_os_event, pdMS_TO_TICKS(50)) !=
        pdTRUE) {
      ESP_LOGW("SOUND_CONTROLLER", "event queue full, dropped event id=%d",
               new_os_event.event_id);
    }

    break;
  }

  case OS_EVENT_SFX_PLAY: {
    FILE *f = (FILE *)os_event->payload_data;
    SoundDriver_Play(f);
    current_sfx = pending_sfx;
    pending_sfx = G_SFX_NONE;
    break;
  }

  default:
    break;
  }
}

// change volume
// playback controls
// current sfx meta data for display

// Minimal WAV playback: skips the 44-byte header, assumes 16-bit/44.1kHz/stereo
// PCM. Re-init i2s_channel_reconfig_std_clock() if a file's sample rate
// differs.
// void Sound_PlaySFX(G_Sfx_ID sfx_id) {
//   G_Sfx_t sfx = Global_Sfx_Lookup(sfx_id);

//   FILE *f = fopen(sfx.path, "rb");
//   if (!f) {
//     ESP_LOGE("SOUND DRIVER", "failed to open %s", sfx.path);
//     return;
//   }

//   fseek(f, 44, SEEK_SET);

//   uint8_t buf[1024];
//   size_t bytes_read, bytes_written;
//   while ((bytes_read = fread(buf, 1, sizeof(buf), f)) > 0) {
//     i2s_channel_write(i2s_tx_chan, buf, bytes_read, &bytes_written,
//                       portMAX_DELAY);
//   }
//   fclose(f);
// }