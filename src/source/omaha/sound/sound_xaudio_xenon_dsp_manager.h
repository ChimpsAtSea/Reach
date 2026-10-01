#pragma once
#ifndef __SOUND_XAUDIO_XENON_DSP_MANAGER_H__
#define __SOUND_XAUDIO_XENON_DSP_MANAGER_H__

/* ---------- headers */

#include "xdk\xaudiod\xaudio.h"

/* ---------- constants */

// indices into the global dsp submix voice array (c_xenon_audio_dsp_manager +0x90, s_static_array<IXAudioSubmixVoice *, 6>)
// names inferred from c_xenon_audio_dsp_manager::initialize
enum e_sound_xaudio_dsp_effect
{
    _sound_xaudio_dsp_effect_headset = 0, // 4 channel, voice headset ring buffer output
    _sound_xaudio_dsp_effect_mix, // 6 channel "mix_l360"
    _sound_xaudio_dsp_effect_obstruction_reverb,
    _sound_xaudio_dsp_effect_obstruction, // "obstr_qn"
    _sound_xaudio_dsp_effect_radio, // 1 channel, look up table distortion
    _sound_xaudio_dsp_effect_radio_equalizer, // 1 channel, waves q3

    k_number_of_sound_xaudio_dsp_effects
};

/* ---------- definitions */

// $TODO data layout not reversed yet (size 0x160 in the target, global dsp effect voices at +0x90)
class c_xenon_audio_dsp_manager
{
public:
    IXAudioVoice * get_global_dsp_effect(e_sound_xaudio_dsp_effect effect);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_DSP_MANAGER_H__

