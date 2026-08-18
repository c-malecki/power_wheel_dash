#ifndef __DRIVER_SOUND_H_
#define __DRIVER_SOUND_H_

#include "esp_err.h"
#include "global.h"

#define SOUND_AMP_LRC_PIN (15)
#define SOUND_AMP_BCLK_PIN (7)
#define SOUND_AMP_DIN_PIN (6)

#define SOUND_VOL_0 0
#define SOUND_VOL_1 ? // 1_3dB
#define SOUND_VOL_2 ? // 1_6dB
#define SOUND_VOL_3 ? // 1_9dB
#define SOUND_VOL_4 ? // 1_12dB
#define SOUND_VOL_5 ? // 15db

esp_err_t SoundDriver_Init(void);
// void SoundDriver_Play(FILE *wav_file);

#endif // __DRIVER_SOUND_H_