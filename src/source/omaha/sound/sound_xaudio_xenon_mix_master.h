#pragma once
#ifndef __SOUND_XAUDIO_XENON_MIX_MASTER_H__
#define __SOUND_XAUDIO_XENON_MIX_MASTER_H__

/* ---------- headers */

#include "omaha\memory\wrapped_arrays.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_manager.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO layouts only partially known (from c_xaudio_voice_speaker_datum::get_platform_output); sizes unverified
struct s_xaudio_voice_mix_state
{
    s_xaudio_voice_mix_state(void);

    long channel_count; // 0x0
    s_sound_transmission_envelope transmission; // 0x4
    float cone_rolloff_factor; // 0x38
    float direct_obstruction; // 0x3C
    float reverb_occlusion; // 0x40
    real_decibel lfe_gain_db; // 0x44
};

struct s_xaudio_voice_setup
{
    float same_channel_crossfade; // 0x0
    float opposite_channel_crossfade; // 0x4
};

struct s_xaudio_platform_output
{
    s_xaudio_platform_output(void);

    c_static_sized_dynamic_array<float, 36> speaker_gains; // 0x0
    unsigned long unknown94; // 0x94
    float reverb_gain; // 0x98
    float pitch_in_octaves; // 0x9C
    float direct_obstruction; // 0xA0
    float reverb_occlusion; // 0xA4
    float radio_send; // 0xA8
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_MIX_MASTER_H__

