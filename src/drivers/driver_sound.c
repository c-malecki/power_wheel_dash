#include "driver_sound.h"
#include "driver/i2s_common.h"
#include "driver/i2s_std.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "global.h"
#include <stdio.h>
#include <wchar.h>

static i2s_chan_handle_t i2s_tx_chan;

esp_err_t SoundDriver_Init(void) {
  i2s_chan_config_t chan_cfg =
      I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
  esp_err_t ret = i2s_new_channel(&chan_cfg, &i2s_tx_chan, NULL);
  if (ret != ESP_OK)
    return ret;

  i2s_std_config_t std_cfg = {
      .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(44100),
      .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT,
                                                      I2S_SLOT_MODE_STEREO),
      .gpio_cfg =
          {
              .mclk = I2S_GPIO_UNUSED,
              .bclk = AUDIO_AMP_PIN_BCLK,
              .ws = AUDIO_AMP_PIN_LRC,
              .dout = I2S_GPIO_UNUSED,
              .din = AUDIO_AMP_PIN_DIN,
          },
  };
  ret = i2s_channel_init_std_mode(i2s_tx_chan, &std_cfg);
  if (ret != ESP_OK)
    return ret;

  return i2s_channel_enable(i2s_tx_chan);
}

// Minimal WAV playback: skips the 44-byte header, assumes 16-bit/44.1kHz/stereo
// PCM. Re-init i2s_channel_reconfig_std_clock() if a file's sample rate
// differs.
void SoundDriver_Play(FILE *wav_file) {
  fseek(wav_file, 44, SEEK_SET);

  uint8_t buf[1024];
  size_t bytes_read, bytes_written;
  while ((bytes_read = fread(buf, 1, sizeof(buf), wav_file)) > 0) {
    i2s_channel_write(i2s_tx_chan, buf, bytes_read, &bytes_written,
                      portMAX_DELAY);
  }
  fclose(wav_file);
}