#pragma once
#ifndef __SOUND_XAUDIO_XENON_3D_VOICE_H__
#define __SOUND_XAUDIO_XENON_3D_VOICE_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

enum e_xaudio_output_speaker
{
    _xaudio_output_front_left = 0,
    _xaudio_output_front_right,
    _xaudio_output_center,
    _xaudio_output_lfe,
    _xaudio_output_back_left,
    _xaudio_output_back_right,
    k_number_of_xaudio_output_speakers
};

/* ---------- definitions */

struct X3DAUDIO_LISTENER;
struct s_platform_sound_voice_update_definition;
struct s_xaudio_voice_mix_state;
struct s_xaudio_voice_setup;
struct s_xaudio_platform_output;

class c_xaudio_voice_speaker_datum
{
public:
    void calculate(unsigned char const (&x3d_audio_object)[20], X3DAUDIO_LISTENER const * listener, s_platform_sound_voice_update_definition const * voice_update, float doppler_scale);
    void get_platform_output(s_xaudio_voice_mix_state const * mix_state, s_xaudio_voice_setup const * voice_setup, s_xaudio_platform_output * in_out_platform_output, float * out_distance_orientation_scale);

    s_static_array<float, k_number_of_xaudio_output_speakers> m_speaker_gains; // 0x0
    float m_doppler_frequency_shift; // 0x18
    float m_reverb_level; // 0x1C
    float m_emitter_to_listener_distance; // 0x20
};
static_assert(sizeof(c_xaudio_voice_speaker_datum) == 0x24, "c_xaudio_voice_speaker_datum");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_3D_VOICE_H__

