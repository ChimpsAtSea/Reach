#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_xaudio_xenon_3d_voice.cpp"
/* ---------- headers */

#include "omaha\sound\sound_xaudio_xenon_3d_voice.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\platform_sound.h"
#include "omaha\sound\sound_math.h"
#include "omaha\sound\sound_xaudio_xenon_mix_master.h"
#include <xtl.h>
#include <x3daudio.h>
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void copy_to_xaudio_vector(struct _D3DVECTOR &, union vector3d const &);
// void copy_to_xaudio_position(struct _D3DVECTOR &, union real_point3d const &);
// public: void c_xaudio_voice_speaker_datum::calculate(unsigned char const (&)[20], struct X3DAUDIO_LISTENER const *, struct s_platform_sound_voice_update_definition const *, float);
// double bend_to_octaves(double);
// void apply_crossbleed_with_equal_power(float *, float *, float, float);
// public: void c_xaudio_voice_speaker_datum::get_platform_output(struct s_xaudio_voice_mix_state const *, struct s_xaudio_voice_setup const *, struct s_xaudio_platform_output *, float *);
// public: float * s_static_array<float, 6>::get_elements(void);
// void xchg<float>(float &, float &);

void copy_to_xaudio_vector(_D3DVECTOR & out_vector, vector3d const & vector)
{
    mangled_ppc("?copy_to_xaudio_vector@@YAXAAU_D3DVECTOR@@ABTvector3d@@@Z");

    out_vector.x = vector.i;
    out_vector.y = vector.j;
    out_vector.z = vector.k;
};

void copy_to_xaudio_position(_D3DVECTOR & out_position, real_point3d const & point)
{
    mangled_ppc("?copy_to_xaudio_position@@YAXAAU_D3DVECTOR@@ABTreal_point3d@@@Z");

    out_position.x = point.x;
    out_position.y = point.y;
    out_position.z = point.z;
};

void c_xaudio_voice_speaker_datum::calculate(unsigned char const (&x3d_audio_object)[20], X3DAUDIO_LISTENER const * listener, s_platform_sound_voice_update_definition const * voice_update, float doppler_scale)
{
    mangled_ppc("?calculate@c_xaudio_voice_speaker_datum@@QAAXAAY0BE@$$CBEPBUX3DAUDIO_LISTENER@@PBUs_platform_sound_voice_update_definition@@M@Z");

    X3DAUDIO_EMITTER emitter = {};
    copy_to_xaudio_vector(emitter.OrientFront, voice_update->forward);
    copy_to_xaudio_vector(emitter.OrientTop, voice_update->up);
    copy_to_xaudio_position(emitter.Position, voice_update->position);
    copy_to_xaudio_vector(emitter.Velocity, voice_update->velocity);

    float azimuths[k_number_of_xaudio_output_speakers] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    emitter.ChannelCount = 1;
    emitter.ChannelRadius = 0.0f;
    emitter.pChannelAzimuths = azimuths;

    X3DAUDIO_DISTANCE_CURVE_POINT flat_volume_curve_points[2] = { { 0.0f, 1.0f }, { 1.0f, 1.0f } };
    X3DAUDIO_DISTANCE_CURVE flat_volume_curve = { flat_volume_curve_points, 2 };
    X3DAUDIO_DISTANCE_CURVE_POINT zero_volume_curve_points[2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f } };
    X3DAUDIO_DISTANCE_CURVE zero_volume_curve = { zero_volume_curve_points, 2 };
    emitter.pVolumeCurve = &flat_volume_curve;

    unsigned long flags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB | X3DAUDIO_CALCULATE_REVERB | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_ZEROCENTER;
    if (TEST_BIT(voice_update->flags, 0) || TEST_BIT(voice_update->flags, 1))
    {
        flags |= X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;
        emitter.pLFECurve = &flat_volume_curve;
    }
    else
    {
        emitter.pLFECurve = &zero_volume_curve;
    }

    if (TEST_BIT(voice_update->flags, 0))
    {
        emitter.pLPFDirectCurve = &zero_volume_curve;
        emitter.pReverbCurve = &zero_volume_curve;
    }
    else
    {
        emitter.pReverbCurve = &flat_volume_curve;
    }
    emitter.CurveDistanceScaler = FLT_MAX;

    X3DAUDIO_DSP_SETTINGS dsp_settings = {};
    dsp_settings.pMatrixCoefficients = m_speaker_gains.get_elements();
    dsp_settings.SrcChannelCount = emitter.ChannelCount;
    dsp_settings.DstChannelCount = k_number_of_xaudio_output_speakers;
    X3DAudioCalculate(x3d_audio_object, listener, &emitter, flags, &dsp_settings);

    xchg(m_speaker_gains[_xaudio_output_front_left], m_speaker_gains[_xaudio_output_front_right]);
    xchg(m_speaker_gains[_xaudio_output_back_left], m_speaker_gains[_xaudio_output_back_right]);

    m_reverb_level = dsp_settings.ReverbLevel;
    m_emitter_to_listener_distance = dsp_settings.EmitterToListenerDistance;
    m_doppler_frequency_shift = dsp_settings.DopplerFactor;
    assert_tag_debug_untracked_jul_11_2011(159, m_doppler_frequency_shift>0.0f);
};

double bend_to_octaves(double bend)
{
    mangled_ppc("?bend_to_octaves@@YANN@Z");

    return log(bend) / k_ln2_gain;
};

void apply_crossbleed_with_equal_power(float * left_channel_gain, float * right_channel_gain, float same_channel_crossfade, float opposite_channel_crossfade)
{
    mangled_ppc("?apply_crossbleed_with_equal_power@@YAXPAM0MM@Z");

    float temp_left_channel_gain = *left_channel_gain;
    float temp_right_channel_gain = *right_channel_gain;
    float in_power = temp_left_channel_gain * temp_left_channel_gain + temp_right_channel_gain * temp_right_channel_gain;
    temp_left_channel_gain = temp_left_channel_gain * same_channel_crossfade + temp_right_channel_gain * opposite_channel_crossfade;
    temp_right_channel_gain = temp_right_channel_gain * same_channel_crossfade + temp_left_channel_gain * opposite_channel_crossfade;
    float out_power = temp_left_channel_gain * temp_left_channel_gain + temp_right_channel_gain * temp_right_channel_gain;
    if (out_power > 0.001f)
    {
        float power_ratio = square_root(in_power / out_power);
        temp_left_channel_gain *= power_ratio;
        temp_right_channel_gain *= power_ratio;
    }
    *left_channel_gain = temp_left_channel_gain;
    *right_channel_gain = temp_right_channel_gain;
};

void c_xaudio_voice_speaker_datum::get_platform_output(s_xaudio_voice_mix_state const * mix_state, s_xaudio_voice_setup const * voice_setup, s_xaudio_platform_output * in_out_platform_output, float * out_distance_orientation_scale)
{
    mangled_ppc("?get_platform_output@c_xaudio_voice_speaker_datum@@QAAXPBUs_xaudio_voice_mix_state@@PBUs_xaudio_voice_setup@@PAUs_xaudio_platform_output@@PAM@Z");

    assert_tag_debug_untracked_jul_11_2011(201, mix_state);
    assert_tag_debug_untracked_jul_11_2011(202, in_out_platform_output);

    float distance_scale = calculate_distance_attenuation(mix_state->transmission, m_emitter_to_listener_distance);
    float orientation_scale = mix_state->cone_rolloff_factor;
    if (out_distance_orientation_scale)
    {
        *out_distance_orientation_scale = distance_scale * orientation_scale;
    }

    in_out_platform_output->radio_send = static_cast<float>(1.0 - distance_scale * orientation_scale);
    in_out_platform_output->speaker_gains.resize(mix_state->channel_count * k_number_of_xaudio_output_speakers);
    in_out_platform_output->reverb_gain = m_reverb_level * distance_scale * orientation_scale;
    in_out_platform_output->pitch_in_octaves = static_cast<float>(bend_to_octaves(m_doppler_frequency_shift));
    in_out_platform_output->direct_obstruction = mix_state->direct_obstruction;
    in_out_platform_output->reverb_occlusion = mix_state->reverb_occlusion;
    m_speaker_gains[_xaudio_output_lfe] *= real_decibels_to_gain(mix_state->lfe_gain_db);

    for (long speaker_index = 0, speaker_count = in_out_platform_output->speaker_gains.count(); speaker_index < speaker_count; speaker_index++)
    {
        long channel_index = speaker_index / mix_state->channel_count;
        in_out_platform_output->speaker_gains[speaker_index] = m_speaker_gains[channel_index] * distance_scale * orientation_scale;
    }

    for (long channel_index = 0; channel_index < mix_state->channel_count; channel_index++)
    {
        apply_crossbleed_with_equal_power(
            &in_out_platform_output->speaker_gains[_xaudio_output_front_left * mix_state->channel_count + channel_index],
            &in_out_platform_output->speaker_gains[_xaudio_output_front_right * mix_state->channel_count + channel_index],
            voice_setup->same_channel_crossfade,
            voice_setup->opposite_channel_crossfade);
        apply_crossbleed_with_equal_power(
            &in_out_platform_output->speaker_gains[_xaudio_output_back_left * mix_state->channel_count + channel_index],
            &in_out_platform_output->speaker_gains[_xaudio_output_back_right * mix_state->channel_count + channel_index],
            voice_setup->same_channel_crossfade,
            voice_setup->opposite_channel_crossfade);
    }
};

