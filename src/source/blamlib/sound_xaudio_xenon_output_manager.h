#pragma once
#ifndef __SOUND_XAUDIO_XENON_OUTPUT_MANAGER_H__
#define __SOUND_XAUDIO_XENON_OUTPUT_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\sound\sound_preferences.h"
#include "xdk\xaudiod\xaudio.h"

/* ---------- constants */

// names inferred from the voices c_xenon_audio_output_manager::initialize routes each output to
enum e_xenon_audio_source_output
{
    _xenon_audio_source_output_mix = 0, // _sound_xaudio_dsp_effect_mix
    _xenon_audio_source_output_reverb_0, // reverb submix voice 0
    _xenon_audio_source_output_reverb_1, // reverb submix voice 1
    _xenon_audio_source_output_headset, // _sound_xaudio_dsp_effect_headset
    _xenon_audio_source_output_obstruction, // _sound_xaudio_dsp_effect_obstruction
    _xenon_audio_source_output_obstruction_reverb, // _sound_xaudio_dsp_effect_obstruction_reverb
    _xenon_audio_source_output_radio, // _sound_xaudio_dsp_effect_radio

    k_number_of_xenon_audio_source_outputs
};

/* ---------- definitions */

class c_xenon_audio_reverb_manager;
class c_xenon_audio_dsp_manager;

class c_xenon_audio_output_manager
{
public:
    void initialize(c_xenon_audio_reverb_manager * reverb_manager, c_xenon_audio_dsp_manager * dsp_manager);
    c_wrapped_array<XAUDIOVOICEOUTPUTENTRY> get_source_output(e_sound_channel_type channel_type);

private:
    s_static_array<s_static_array<XAUDIOVOICEOUTPUTENTRY, k_number_of_xenon_audio_source_outputs>, k_number_of_sound_channel_source_types> m_source_outputs; // 0x0
};
static_assert(sizeof(c_xenon_audio_output_manager) == 0x118, "c_xenon_audio_output_manager");

/* ---------- prototypes */

XAUDIOVOICEOUTPUTENTRY make_xaudio_voice_output_entry(IXAudioVoice * voice, XAUDIOCHANNELMAP * channel_map);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_OUTPUT_MANAGER_H__
