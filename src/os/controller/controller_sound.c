#include "controller_sound.h"
#include "driver_sound.h"
#include "global.h"

static bool sfx_playing = false;
static G_Sfx_ID pending_sfx = G_SFX_NONE;
static G_Sfx_ID current_sfx = G_SFX_NONE;

void Sound_Controller_Init(void) { current_sfx = G_SFX_NONE; }

void Sound_Controller_RX(G_Event_t *g_event) {
  switch (g_event->event_id) {
  case G_EVENT_SFX_SELECT:
    pending_sfx = (G_Sfx_ID)g_event->payload;
    G_Sfx_t sfx = Global_Sfx_Lookup((G_Sfx_ID)g_event->payload);
    // OS_Manager_Request_File(const char* path);
    // request file from os
    // os goes to storage
    //
    // SoundDriver_Play(FILE *wav_file);
    break;

  case G_EVENT_SFX_PLAY:

    // FILE *sfx = Global_Sfx_Lookup((FILE *)g_event->payload);

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