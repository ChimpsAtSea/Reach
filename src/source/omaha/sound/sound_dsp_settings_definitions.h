#pragma once
#ifndef __SOUND_DSP_SETTINGS_DEFINITIONS_H__
#define __SOUND_DSP_SETTINGS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\sound\game_sound_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_sound_reverb_settings
{
    real_decibel room_intensity_db; // 0x0
    real_decibel room_intensity_hf_db; // 0x4
    float room_rolloff_factor; // 0x8
    float decay_time; // 0xC
    float decay_hf_ratio; // 0x10
    real_decibel reflections_intensity_db; // 0x14
    float reflections_delay; // 0x18
    real_decibel reverb_intensity_db; // 0x1C
    float reverb_delay; // 0x20
    float diffusion; // 0x24
    float density; // 0x28
    float hf_reference; // 0x2C
};
static_assert(sizeof(s_sound_reverb_settings) == 0x30, "s_sound_reverb_settings");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_DSP_SETTINGS_DEFINITIONS_H__

