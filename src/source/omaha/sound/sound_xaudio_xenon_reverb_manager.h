#pragma once
#ifndef __SOUND_XAUDIO_XENON_REVERB_MANAGER_H__
#define __SOUND_XAUDIO_XENON_REVERB_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\platform_sound.h"
#include "omaha\sound\sound_dsp_settings_definitions.h"
#include "xdk\xaudiod\xaudio.h"

/* ---------- constants */

enum
{
    k_xaudio_reverb_submix_voice_count = 2,
};

enum e_reverb_speaker
{
    _reverb_front_left = 0,
    _reverb_front_right,
    _reverb_back_left,
    _reverb_back_right,

    k_number_of_reverb_speakers
};

/* ---------- definitions */

class c_xenon_audio_dsp_manager;

class c_xenon_audio_reverb_manager
{
public:
    void initialize(c_xenon_audio_dsp_manager * dsp_manager);
    void dispose(void);
    void update_reverbs(long reverb_count, s_platform_sound_listener_reverb const * reverbs);

private:
    void update_reverb(long reverb_index, s_platform_sound_listener_reverb const * reverb);

public:
    union
    {
        s_static_array<IXAudioSubmixVoice *, k_xaudio_reverb_submix_voice_count> m_xaudio_reverbs; // 0x0
        // older name, accessed directly by c_xenon_audio_output_manager::initialize
        s_static_array<IXAudioSubmixVoice *, k_xaudio_reverb_submix_voice_count> m_submix_voices; // 0x0
    };
    s_static_array<s_sound_reverb_settings, k_xaudio_reverb_submix_voice_count> m_reverb_settings; // 0x8
    s_static_array<float, k_xaudio_reverb_submix_voice_count> m_reverb_gains; // 0x68
    unsigned char unknown70[0x20]; // $TODO not reversed yet
    bool m_force_dirty; // 0x90 set by initialize, cleared by update_reverbs
};
static_assert(sizeof(c_xenon_audio_reverb_manager) == 0x94, "c_xenon_audio_reverb_manager");

/* ---------- prototypes */

float azimuth_intersection(float start_a, float end_a, float start_b, float end_b);
float reverb_calculate_speaker_volume(e_reverb_speaker speaker_index, s_sound_azimuth_image const * reverb_azimuth_image);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_REVERB_MANAGER_H__
