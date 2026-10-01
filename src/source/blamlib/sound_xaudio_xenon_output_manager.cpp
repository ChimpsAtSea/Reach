/* ---------- headers */

#include "blamlib\sound_xaudio_xenon_output_manager.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_xaudio_xenon_dsp_manager.h"
#include "omaha\sound\sound_xaudio_xenon_reverb_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

// $TODO storage names other than k_mono_channel_map_entry_storage are guesses (the target keeps them static)

// source channel -> speaker, used by _xenon_audio_source_output_mix / _xenon_audio_source_output_obstruction
static XAUDIOCHANNELMAPENTRY k_mono_channel_map_entry_storage[] =
{
    { 0, 0, k_one_over_root2 },
    { 0, 1, k_one_over_root2 },
    { 0, 2, 0.0f },
    { 0, 3, 0.0f },
    { 0, 4, 0.0f },
    { 0, 5, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_stereo_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 1.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f },
    { 0, 4, 0.0f }, { 1, 4, 0.0f },
    { 0, 5, 0.0f }, { 1, 5, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_quad_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 1.0f }, { 2, 1, 0.0f }, { 3, 1, 0.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f }, { 2, 2, 0.0f }, { 3, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f }, { 2, 3, 0.0f }, { 3, 3, 0.0f },
    { 0, 4, 0.0f }, { 1, 4, 0.0f }, { 2, 4, 1.0f }, { 3, 4, 0.0f },
    { 0, 5, 0.0f }, { 1, 5, 0.0f }, { 2, 5, 0.0f }, { 3, 5, 1.0f },
};

static XAUDIOCHANNELMAPENTRY k_5_dot_1_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f }, { 4, 0, 0.0f }, { 5, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 1.0f }, { 2, 1, 0.0f }, { 3, 1, 0.0f }, { 4, 1, 0.0f }, { 5, 1, 0.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f }, { 2, 2, 0.0f }, { 3, 2, 0.0f }, { 4, 2, 1.0f }, { 5, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f }, { 2, 3, 0.0f }, { 3, 3, 0.0f }, { 4, 3, 0.0f }, { 5, 3, 1.0f },
    { 0, 4, 0.0f }, { 1, 4, 0.0f }, { 2, 4, 1.0f }, { 3, 4, 0.0f }, { 4, 4, 0.0f }, { 5, 4, 0.0f },
    { 0, 5, 0.0f }, { 1, 5, 0.0f }, { 2, 5, 0.0f }, { 3, 5, 1.0f }, { 4, 5, 0.0f }, { 5, 5, 0.0f },
};

// source channel -> mono, used by the reverb outputs
static XAUDIOCHANNELMAPENTRY k_mono_to_mono_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f },
};

static XAUDIOCHANNELMAPENTRY k_stereo_to_mono_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 1.0f },
};

static XAUDIOCHANNELMAPENTRY k_quad_to_mono_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 1.0f }, { 2, 0, 1.0f }, { 3, 0, 1.0f },
};

static XAUDIOCHANNELMAPENTRY k_5_dot_1_to_mono_channel_map_entry_storage[] =
{
    { 0, 0, 1.0f }, { 1, 0, 1.0f }, { 2, 0, 1.0f }, { 3, 0, 1.0f }, { 4, 0, 1.0f }, { 5, 0, 1.0f },
};

// source channel -> 4 channel headset output (silent)
static XAUDIOCHANNELMAPENTRY k_mono_headset_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f },
    { 0, 1, 0.0f },
    { 0, 2, 0.0f },
    { 0, 3, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_stereo_headset_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 0.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_quad_headset_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 0.0f }, { 2, 1, 0.0f }, { 3, 1, 0.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f }, { 2, 2, 0.0f }, { 3, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f }, { 2, 3, 0.0f }, { 3, 3, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_5_dot_1_headset_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f }, { 4, 0, 0.0f }, { 5, 0, 0.0f },
    { 0, 1, 0.0f }, { 1, 1, 0.0f }, { 2, 1, 0.0f }, { 3, 1, 0.0f }, { 4, 1, 0.0f }, { 5, 1, 0.0f },
    { 0, 2, 0.0f }, { 1, 2, 0.0f }, { 2, 2, 0.0f }, { 3, 2, 0.0f }, { 4, 2, 0.0f }, { 5, 2, 0.0f },
    { 0, 3, 0.0f }, { 1, 3, 0.0f }, { 2, 3, 0.0f }, { 3, 3, 0.0f }, { 4, 3, 0.0f }, { 5, 3, 0.0f },
};

// source channel -> mono radio output (silent)
static XAUDIOCHANNELMAPENTRY k_mono_radio_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_stereo_radio_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_quad_radio_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f },
};

static XAUDIOCHANNELMAPENTRY k_5_dot_1_radio_channel_map_entry_storage[] =
{
    { 0, 0, 0.0f }, { 1, 0, 0.0f }, { 2, 0, 0.0f }, { 3, 0, 0.0f }, { 4, 0, 0.0f }, { 5, 0, 0.0f },
};

static XAUDIOCHANNELMAP k_speaker_channel_maps[k_number_of_sound_channel_source_types] =
{
    { NUMBEROF(k_mono_channel_map_entry_storage), k_mono_channel_map_entry_storage },
    { NUMBEROF(k_stereo_channel_map_entry_storage), k_stereo_channel_map_entry_storage },
    { NUMBEROF(k_quad_channel_map_entry_storage), k_quad_channel_map_entry_storage },
    { NUMBEROF(k_5_dot_1_channel_map_entry_storage), k_5_dot_1_channel_map_entry_storage },
    { 0, NULL },
};

// the target's quad and 5.1 reverb maps point at the speaker storage (its first 4 / 6 entries), not at the
// *_to_mono storage
static XAUDIOCHANNELMAP k_reverb_channel_maps[k_number_of_sound_channel_source_types] =
{
    { NUMBEROF(k_mono_to_mono_channel_map_entry_storage), k_mono_to_mono_channel_map_entry_storage },
    { NUMBEROF(k_stereo_to_mono_channel_map_entry_storage), k_stereo_to_mono_channel_map_entry_storage },
    { NUMBEROF(k_quad_to_mono_channel_map_entry_storage), k_quad_channel_map_entry_storage },
    { NUMBEROF(k_5_dot_1_to_mono_channel_map_entry_storage), k_5_dot_1_channel_map_entry_storage },
    { 0, NULL },
};

static XAUDIOCHANNELMAP k_headset_channel_maps[k_number_of_sound_channel_source_types] =
{
    { NUMBEROF(k_mono_headset_channel_map_entry_storage), k_mono_headset_channel_map_entry_storage },
    { NUMBEROF(k_stereo_headset_channel_map_entry_storage), k_stereo_headset_channel_map_entry_storage },
    { NUMBEROF(k_quad_headset_channel_map_entry_storage), k_quad_headset_channel_map_entry_storage },
    { NUMBEROF(k_5_dot_1_headset_channel_map_entry_storage), k_5_dot_1_headset_channel_map_entry_storage },
    { 0, NULL },
};

static XAUDIOCHANNELMAP k_radio_channel_maps[k_number_of_sound_channel_source_types] =
{
    { NUMBEROF(k_mono_radio_channel_map_entry_storage), k_mono_radio_channel_map_entry_storage },
    { NUMBEROF(k_stereo_radio_channel_map_entry_storage), k_stereo_radio_channel_map_entry_storage },
    { NUMBEROF(k_quad_radio_channel_map_entry_storage), k_quad_radio_channel_map_entry_storage },
    { NUMBEROF(k_5_dot_1_radio_channel_map_entry_storage), k_5_dot_1_radio_channel_map_entry_storage },
    { 0, NULL },
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct XAUDIOVOICEOUTPUTENTRY make_xaudio_voice_output_entry(struct IXAudioVoice *, struct XAUDIOCHANNELMAP *);
// public: void c_xenon_audio_output_manager::initialize(class c_xenon_audio_reverb_manager *, class c_xenon_audio_dsp_manager *);
// public: class c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY> c_xenon_audio_output_manager::get_source_output(enum e_sound_channel_type);
// public: struct XAUDIOVOICEOUTPUTENTRY * s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::get_elements(void);
// public: static long s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::get_count(void);
// public: struct IXAudioSubmixVoice *& s_static_array<struct IXAudioSubmixVoice *, 2>::operator[]<int>(int);
// public: class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7> & s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::operator[]<long>(long);
// public: struct XAUDIOVOICEOUTPUTENTRY & s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::operator[]<enum e_xenon_audio_source_output>(enum e_xenon_audio_source_output);
// public: class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7> & s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::operator[]<enum e_sound_channel_type>(enum e_sound_channel_type);
// class c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY> make_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>(struct XAUDIOVOICEOUTPUTENTRY *, long);
// public: c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>::c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>(struct XAUDIOVOICEOUTPUTENTRY *, long);
// public: void c_wrapped_array_no_init<struct XAUDIOVOICEOUTPUTENTRY>::set_elements(struct XAUDIOVOICEOUTPUTENTRY *, long);
// public: static bool s_static_array<struct IXAudioSubmixVoice *, 2>::valid<int>(int);
// public: static bool s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::valid<long>(long);
// public: static bool s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::valid<enum e_xenon_audio_source_output>(enum e_xenon_audio_source_output);
// public: static bool s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::valid<enum e_sound_channel_type>(enum e_sound_channel_type);

XAUDIOVOICEOUTPUTENTRY make_xaudio_voice_output_entry(IXAudioVoice * voice, XAUDIOCHANNELMAP * channel_map)
{
    mangled_ppc("?make_xaudio_voice_output_entry@@YA?AUXAUDIOVOICEOUTPUTENTRY@@PAUIXAudioVoice@@PAUXAUDIOCHANNELMAP@@@Z");

    XAUDIOVOICEOUTPUTENTRY entry;
    entry.pDestVoice = voice;
    entry.pChannelMap = channel_map;

    return entry;
};

void c_xenon_audio_output_manager::initialize(c_xenon_audio_reverb_manager * reverb_manager, c_xenon_audio_dsp_manager * dsp_manager)
{
    mangled_ppc("?initialize@c_xenon_audio_output_manager@@QAAXPAVc_xenon_audio_reverb_manager@@PAVc_xenon_audio_dsp_manager@@@Z");

    IXAudioVoice * left_reverb_voice = reverb_manager->m_submix_voices[0];
    IXAudioVoice * right_reverb_voice = reverb_manager->m_submix_voices[1];
    IXAudioVoice * headset_voice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_headset);
    IXAudioVoice * obstruction_submix_voice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_obstruction);
    IXAudioVoice * obstruction_reverb_voice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_obstruction_reverb);
    IXAudioVoice * radio_submix_voice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_radio);
    IXAudioVoice * main_mix_voice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_mix);

    for (long channel_type = 0; channel_type < k_number_of_sound_channel_source_types; channel_type++)
    {
        m_source_outputs[channel_type][_xenon_audio_source_output_mix] = make_xaudio_voice_output_entry(main_mix_voice, &k_speaker_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_reverb_0] = make_xaudio_voice_output_entry(left_reverb_voice, &k_reverb_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_reverb_1] = make_xaudio_voice_output_entry(right_reverb_voice, &k_reverb_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_headset] = make_xaudio_voice_output_entry(headset_voice, &k_headset_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_obstruction] = make_xaudio_voice_output_entry(obstruction_submix_voice, &k_speaker_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_obstruction_reverb] = make_xaudio_voice_output_entry(obstruction_reverb_voice, &k_reverb_channel_maps[channel_type]);
        m_source_outputs[channel_type][_xenon_audio_source_output_radio] = make_xaudio_voice_output_entry(radio_submix_voice, &k_radio_channel_maps[channel_type]);
    }
};

c_wrapped_array<XAUDIOVOICEOUTPUTENTRY> c_xenon_audio_output_manager::get_source_output(e_sound_channel_type channel_type)
{
    mangled_ppc("?get_source_output@c_xenon_audio_output_manager@@QAA?AV?$c_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@W4e_sound_channel_type@@@Z");

    return make_wrapped_array(m_source_outputs[channel_type].get_elements(), m_source_outputs[channel_type].get_count());
};

//public: struct XAUDIOVOICEOUTPUTENTRY * s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::get_elements(void)
//{
//    mangled_ppc("?get_elements@?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@QAAPAUXAUDIOVOICEOUTPUTENTRY@@XZ");
//};

//public: static long s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::get_count(void)
//{
//    mangled_ppc("?get_count@?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@SAJXZ");
//};

//public: struct IXAudioSubmixVoice *& s_static_array<struct IXAudioSubmixVoice *, 2>::operator[]<int>(int)
//{
//    mangled_ppc("??$?AH@?$s_static_array@PAUIXAudioSubmixVoice@@$01@@QAAAAPAUIXAudioSubmixVoice@@H@Z");
//};

//public: class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7> & s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::operator[]<long>(long)
//{
//    mangled_ppc("??$?AJ@?$s_static_array@V?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@$04@@QAAAAV?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@J@Z");
//};

//public: struct XAUDIOVOICEOUTPUTENTRY & s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::operator[]<enum e_xenon_audio_source_output>(enum e_xenon_audio_source_output)
//{
//    mangled_ppc("??$?AW4e_xenon_audio_source_output@@@?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@QAAAAUXAUDIOVOICEOUTPUTENTRY@@W4e_xenon_audio_source_output@@@Z");
//};

//public: class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7> & s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::operator[]<enum e_sound_channel_type>(enum e_sound_channel_type)
//{
//    mangled_ppc("??$?AW4e_sound_channel_type@@@?$s_static_array@V?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@$04@@QAAAAV?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@W4e_sound_channel_type@@@Z");
//};

//class c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY> make_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>(struct XAUDIOVOICEOUTPUTENTRY *, long)
//{
//    mangled_ppc("??$make_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@YA?AV?$c_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@PAUXAUDIOVOICEOUTPUTENTRY@@J@Z");
//};

//public: c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>::c_wrapped_array<struct XAUDIOVOICEOUTPUTENTRY>(struct XAUDIOVOICEOUTPUTENTRY *, long)
//{
//    mangled_ppc("??0?$c_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@QAA@PAUXAUDIOVOICEOUTPUTENTRY@@J@Z");
//};

//public: void c_wrapped_array_no_init<struct XAUDIOVOICEOUTPUTENTRY>::set_elements(struct XAUDIOVOICEOUTPUTENTRY *, long)
//{
//    mangled_ppc("?set_elements@?$c_wrapped_array_no_init@UXAUDIOVOICEOUTPUTENTRY@@@@QAAXPAUXAUDIOVOICEOUTPUTENTRY@@J@Z");
//};

//public: static bool s_static_array<struct IXAudioSubmixVoice *, 2>::valid<int>(int)
//{
//    mangled_ppc("??$valid@H@?$s_static_array@PAUIXAudioSubmixVoice@@$01@@SA_NH@Z");
//};

//public: static bool s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::valid<long>(long)
//{
//    mangled_ppc("??$valid@J@?$s_static_array@V?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@$04@@SA_NJ@Z");
//};

//public: static bool s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>::valid<enum e_xenon_audio_source_output>(enum e_xenon_audio_source_output)
//{
//    mangled_ppc("??$valid@W4e_xenon_audio_source_output@@@?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@SA_NW4e_xenon_audio_source_output@@@Z");
//};

//public: static bool s_static_array<class s_static_array<struct XAUDIOVOICEOUTPUTENTRY, 7>, 5>::valid<enum e_sound_channel_type>(enum e_sound_channel_type)
//{
//    mangled_ppc("??$valid@W4e_sound_channel_type@@@?$s_static_array@V?$s_static_array@UXAUDIOVOICEOUTPUTENTRY@@$06@@$04@@SA_NW4e_sound_channel_type@@@Z");
//};

