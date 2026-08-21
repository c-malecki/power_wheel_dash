#ifndef __DRIVER_SOUND_H_
#define __DRIVER_SOUND_H_

#include "esp_err.h"
#include "types.h"
#include <stdio.h>

#define DRIVER_SOUND_VOL_0 0
#define DRIVER_SOUND_VOL_1 ? // 1_3dB
#define DRIVER_SOUND_VOL_2 ? // 1_6dB
#define DRIVER_SOUND_VOL_3 ? // 1_9dB
#define DRIVER_SOUND_VOL_4 ? // 1_12dB
#define DRIVER_SOUND_VOL_5 ? // 15db

esp_err_t SoundDriver_Init(void);
void SoundDriver_Play(FILE *wav_file);

#endif // __DRIVER_SOUND_H_