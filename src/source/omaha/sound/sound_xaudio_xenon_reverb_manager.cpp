#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_xaudio_xenon_reverb_manager.cpp"
/* ---------- headers */

#include "omaha\sound\sound_xaudio_xenon_reverb_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\platform_sound.h"
#include "omaha\sound\sound_dsp_settings_definitions.h"
#include "omaha\sound\sound_xaudio_xenon_3d_voice.h"
#include "omaha\sound\sound_xaudio_xenon_dsp_manager.h"
#include "xdk\xaudiod\xaudio.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

typedef float s_speaker_ranges[3][2];

/* ---------- prototypes */

/* ---------- globals */

static real k_full_circle = k_2pi;
static real k_eighth_circle = k_quarter_pi;

// each speaker covers a half-circle of azimuth, spelled as up to three wrapped intervals over [-2pi, 2pi]
static s_speaker_ranges const k_front_left_ranges =
{
    { -k_eighth_circle, 3.0f * k_eighth_circle },
    { k_full_circle - k_eighth_circle, k_full_circle },
    { -k_full_circle, 3.0f * k_eighth_circle - k_full_circle },
};

static s_speaker_ranges const k_front_right_ranges =
{
    { -3.0f * k_eighth_circle, k_eighth_circle },
    { k_full_circle - 3.0f * k_eighth_circle, k_full_circle },
    { -k_full_circle, -k_full_circle + k_eighth_circle },
};

static s_speaker_ranges const k_back_left_ranges =
{
    { k_eighth_circle, 5.0f * k_eighth_circle },
    { -k_full_circle + k_eighth_circle, -k_full_circle + 5.0f * k_eighth_circle },
    { 0.0f, 0.0f },
};

static s_speaker_ranges const k_back_right_ranges =
{
    { 3.0f * k_eighth_circle, 7.0f * k_eighth_circle },
    { -k_full_circle + 3.0f * k_eighth_circle, -k_full_circle + 7.0f * k_eighth_circle },
    { 0.0f, 0.0f },
};

static float const (* const k_speaker_ranges[k_number_of_reverb_speakers])[2] =
{
    k_front_left_ranges, // _reverb_front_left
    k_front_right_ranges, // _reverb_front_right
    k_back_left_ranges, // _reverb_back_left
    k_back_right_ranges, // _reverb_back_right
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_xenon_audio_reverb_manager::initialize(class c_xenon_audio_dsp_manager *);
// public: void c_xenon_audio_reverb_manager::dispose(void);
// float azimuth_intersection(float, float, float, float);
// float reverb_calculate_speaker_volume(enum e_reverb_speaker, struct s_sound_azimuth_image const *);
// private: void c_xenon_audio_reverb_manager::update_reverb(long, struct s_platform_sound_listener_reverb const *);
// public: void c_xenon_audio_reverb_manager::update_reverbs(long, struct s_platform_sound_listener_reverb const *);
// public: struct IXAudioSubmixVoice *& s_static_array<struct IXAudioSubmixVoice *, 2>::operator[]<long>(long);
// public: struct s_sound_reverb_settings & s_static_array<struct s_sound_reverb_settings, 2>::operator[]<long>(long);
// public: float & s_static_array<float, 2>::operator[]<long>(long);
// public: static bool s_static_array<struct IXAudioSubmixVoice *, 2>::valid<long>(long);
// public: static bool s_static_array<struct s_sound_reverb_settings, 2>::valid<long>(long);
// public: static bool s_static_array<float, 2>::valid<long>(long);
// public: long IXAudioVoice::SetVoiceOutputVolume(struct XAUDIOVOICEOUTPUTVOLUME const *);

void c_xenon_audio_reverb_manager::initialize(c_xenon_audio_dsp_manager * dsp_manager)
{
    mangled_ppc("?initialize@c_xenon_audio_reverb_manager@@QAAXPAVc_xenon_audio_dsp_manager@@@Z");

    // local names reproduce the target's /Od stack slot order (this compiler orders a scope's locals by identifier hash)
    XAUDIOFXINIT fx_init = { 3, NULL };
    XAUDIOFXINIT const * fx_list[] = { &fx_init };
    XAUDIOVOICEFXCHAIN chain = { NUMBEROF(fx_list), fx_list };
    XAUDIOCHANNELMAPENTRY map_entries[] =
    {
        { _xaudio_output_front_left, _xaudio_output_front_left, 1.0f },
        { _xaudio_output_front_right, _xaudio_output_front_right, 1.0f },
        { _xaudio_output_center, _xaudio_output_center, 0.0f },
        { _xaudio_output_lfe, _xaudio_output_lfe, 1.0f },
        { _xaudio_output_back_left, _xaudio_output_back_left, 1.0f },
        { _xaudio_output_back_right, _xaudio_output_back_right, 1.0f },
    };
    XAUDIOVOICEOUTPUT output;
    XAUDIOVOICEOUTPUTENTRY output_entry;
    XAUDIOCHANNELMAP map;
    output.OutputCount = 1;
    output.paOutputs = &output_entry;
    output_entry.pDestVoice = dsp_manager->get_global_dsp_effect(_sound_xaudio_dsp_effect_mix);
    output_entry.pChannelMap = &map;
    map.EntryCount = NUMBEROF(map_entries);
    map.paEntries = map_entries;
    XAUDIOSUBMIXVOICEINIT voice_init = { 0 };
    voice_init.pEffectChain = &chain;
    voice_init.MaxChannelMapEntryCount = k_number_of_xaudio_output_speakers;
    voice_init.SampleType = XAUDIOSAMPLETYPE_NATIVE;
    voice_init.SampleRate = 48000;
    voice_init.ChannelCount = 1;
    voice_init.pVoiceOutput = &output;
    voice_init.SubmixStage = 2;

    for (long reverb_index = 0; reverb_index < m_xaudio_reverbs.get_count(); reverb_index++)
    {
        long hr = XAudioCreateSubmixVoice(&voice_init, &m_xaudio_reverbs[reverb_index]);
        assert_tag_debug_untracked_jul_11_2011(68, SUCCEEDED(hr));
    }

    m_force_dirty = true;
};

void c_xenon_audio_reverb_manager::dispose(void)
{
    mangled_ppc("?dispose@c_xenon_audio_reverb_manager@@QAAXXZ");

    for (long reverb_index = 0; reverb_index < m_xaudio_reverbs.get_count(); reverb_index++)
    {
        m_xaudio_reverbs[reverb_index]->Release();
    }
};

float azimuth_intersection(float start_a, float end_a, float start_b, float end_b)
{
    mangled_ppc("?azimuth_intersection@@YAMMMMM@Z");

    float intersection = (end_a > end_b ? end_b : end_a) - MAX(start_a, start_b);
    return MAX(intersection, 0.0f);
};

float reverb_calculate_speaker_volume(e_reverb_speaker speaker_index, s_sound_azimuth_image const * reverb_azimuth_image)
{
    mangled_ppc("?reverb_calculate_speaker_volume@@YAMW4e_reverb_speaker@@PBUs_sound_azimuth_image@@@Z");

    float azimuth_gain = azimuth_intersection(reverb_azimuth_image->start_angle, reverb_azimuth_image->end_angle, k_speaker_ranges[speaker_index][0][0], k_speaker_ranges[speaker_index][0][1])
        + azimuth_intersection(reverb_azimuth_image->start_angle, reverb_azimuth_image->end_angle, k_speaker_ranges[speaker_index][1][0], k_speaker_ranges[speaker_index][1][1])
        + azimuth_intersection(reverb_azimuth_image->start_angle, reverb_azimuth_image->end_angle, k_speaker_ranges[speaker_index][2][0], k_speaker_ranges[speaker_index][2][1]);
    azimuth_gain /= k_pi;
    azimuth_gain = interpolate_linear(reverb_azimuth_image->gain_fraction, azimuth_gain, reverb_azimuth_image->pitch_factor);
    return azimuth_gain;
};

void c_xenon_audio_reverb_manager::update_reverb(long reverb_index, s_platform_sound_listener_reverb const * reverb)
{
    mangled_ppc("?update_reverb@c_xenon_audio_reverb_manager@@AAAXJPBUs_platform_sound_listener_reverb@@@Z");

    bool reverb_settings_dirty = reverb->reverb_settings != NULL && (m_force_dirty || memcmp(&m_reverb_settings[reverb_index], reverb->reverb_settings, sizeof(s_sound_reverb_settings)) != 0);
    if (reverb_settings_dirty)
    {
        s_sound_reverb_settings const * settings = reverb->reverb_settings;

        XAUDIOREVERBI3DL2SETTINGS i3dl2_settings;
        i3dl2_settings.lRoom = static_cast<long>(settings->room_intensity_db.to_real() * 100.0f);
        i3dl2_settings.lRoomHF = static_cast<long>(settings->room_intensity_hf_db.to_real() * 100.0f);
        i3dl2_settings.flRoomRolloffFactor = settings->room_rolloff_factor;
        i3dl2_settings.flDecayTime = settings->decay_time;
        i3dl2_settings.flDecayHFRatio = settings->decay_hf_ratio;
        i3dl2_settings.lReflections = static_cast<long>(settings->reflections_intensity_db.to_real() * 100.0f);
        i3dl2_settings.flReflectionsDelay = settings->reflections_delay;
        i3dl2_settings.lReverb = static_cast<long>(settings->reverb_intensity_db.to_real() * 100.0f);
        i3dl2_settings.flReverbDelay = settings->reverb_delay;
        i3dl2_settings.flDiffusion = 100.0f * settings->diffusion;
        i3dl2_settings.flDensity = 100.0f * settings->density;
        i3dl2_settings.flHFReference = settings->hf_reference;

        XAUDIOFXPARAM effect_param;
        effect_param.Buffer.pBuffer = &i3dl2_settings;
        effect_param.Buffer.BufferSize = sizeof(i3dl2_settings);
        m_xaudio_reverbs[reverb_index]->SetEffectParam(0, 1, 3, &effect_param);
        m_reverb_settings[reverb_index] = *reverb->reverb_settings;
    }

    // local names and the block reproduce the target's /Od stack slot order
    {
        XAUDIOCHANNELVOLUMEENTRY channel_volume_entries[] =
        {
            { _xaudio_output_front_left, reverb->gain * reverb_calculate_speaker_volume(_reverb_front_left, &reverb->azimuth_image) },
            { _xaudio_output_front_right, reverb->gain * reverb_calculate_speaker_volume(_reverb_front_right, &reverb->azimuth_image) },
            { _xaudio_output_back_left, reverb->gain * reverb_calculate_speaker_volume(_reverb_back_left, &reverb->azimuth_image) },
            { _xaudio_output_back_right, reverb->gain * reverb_calculate_speaker_volume(_reverb_back_right, &reverb->azimuth_image) },
            { _xaudio_output_lfe, reverb->gain },
        };
        XAUDIOCHANNELVOLUME volume = { NUMBEROF(channel_volume_entries), channel_volume_entries };
        XAUDIOVOICEOUTPUTVOLUMEENTRY output_entry = { 0, &volume };
        XAUDIOVOICEOUTPUTVOLUME output_volume = { 1, &output_entry };
        m_xaudio_reverbs[reverb_index]->SetVoiceOutputVolume(&output_volume);
    }
    m_reverb_gains[reverb_index] = reverb->gain;
};

void c_xenon_audio_reverb_manager::update_reverbs(long reverb_count, s_platform_sound_listener_reverb const * reverbs)
{
    mangled_ppc("?update_reverbs@c_xenon_audio_reverb_manager@@QAAXJPBUs_platform_sound_listener_reverb@@@Z");

    assert_tag_debug_untracked_jul_11_2011(260, reverb_count==m_xaudio_reverbs.get_count());

    for (long reverb_index = 0; reverb_index < m_xaudio_reverbs.get_count(); reverb_index++)
    {
        update_reverb(reverb_index, &reverbs[reverb_index]);
    }

    m_force_dirty = false;
};
