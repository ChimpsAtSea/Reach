#pragma once
#ifndef __SOUND_XAUDIO_XENON_VOICE_MANAGER_H__
#define __SOUND_XAUDIO_XENON_VOICE_MANAGER_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\sound\sound_xaudio_xenon_3d_voice.h"
#include <xtl.h>
#include <x3daudio.h>

/* ---------- constants */

enum
{
    k_maximum_xaudio_listeners = 4,
    k_maximum_xaudio_voices = 212,
};

/* ---------- definitions */

class c_xenon_audio_source_manager;
struct s_platform_sound_listener;
struct s_platform_sound_status;
struct s_platform_sound_voice_update_definition;
struct s_xaudio_voice_mix_state;
struct s_xaudio_voice_setup;
struct s_xaudio_platform_output;

class c_xenon_audio_voice_manager
{
public:
    void initialize(c_xenon_audio_source_manager * source_manager, float speed_of_sound);
    void dispose(void);
    void update_listeners(s_platform_sound_listener const * new_listeners, c_flags<long, unsigned long, 4> valid_listeners);
    static void update_voice_status(s_platform_sound_status * out_platform_status);
    static bool voice_is_idle_async(long voice_index);
    static void voice_initialize_properties(long voice_index);
    void voice_update_properties(long voice_index, s_platform_sound_voice_update_definition const * voice_update, float doppler_scale);
    void voice_get_platform_output(long voice_index, s_xaudio_voice_mix_state const * mix_state, s_xaudio_voice_setup const * voice_setup, s_xaudio_platform_output * in_out_platform_output, float * out_distance_orientation_scale);

private:
    c_xenon_audio_source_manager * m_source_manager; // 0x0
    s_static_array<X3DAUDIO_LISTENER, k_maximum_xaudio_listeners> m_listeners; // 0x4
    c_flags<long, unsigned long, 4> m_valid_listeners; // 0xD4
    s_static_array<c_xaudio_voice_speaker_datum, k_maximum_xaudio_voices> m_voice_data; // 0xD8
    X3DAUDIO_HANDLE m_x3d_audio_object; // 0x1EA8
};
static_assert(sizeof(c_xenon_audio_voice_manager) == 0x1EBC, "c_xenon_audio_voice_manager");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_VOICE_MANAGER_H__

