#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_math.cpp"
/* ---------- headers */

#include "omaha\sound\sound_math.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\sound_manager.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static vector3d const k_speaker_positions[k_number_of_positional_speakers_plus_center] =
{
    { k_one_over_root2, k_one_over_root2, 0.0f }, // _speaker_front_left
    { k_one_over_root2, -k_one_over_root2, 0.0f }, // _speaker_front_right
    { -k_one_over_root2, k_one_over_root2, 0.0f }, // _speaker_back_left
    { -k_one_over_root2, -k_one_over_root2, 0.0f }, // _speaker_back_right
    { k_one_over_root2, 0.0f, 0.0f }, // _speaker_center
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float calculate_individual_positional_speaker_gain(union vector3d const *, enum e_sound_speaker, bool);
// float calculate_individual_positional_speaker_gain_vap(union vector3d const *, enum e_sound_speaker);
// void calculate_positional_speaker_gain(union vector3d const *, class s_static_array<float, 4> *, bool);
// void calculate_positional_plus_center_speaker_gain(union vector3d const *, class s_static_array<float, 5> *, bool);
// float calculate_distance_attenuation(struct s_sound_transmission_envelope const &, float);
// void calculate_positional_speaker_gain_internal(union vector3d const *, class s_static_array<float, 5> *, bool, long);
// public: bool c_static_stack<struct s_sound_transmission_envelope::envelope_point, 6>::empty(void) const;
// public: struct s_sound_transmission_envelope::envelope_point const & c_static_stack<struct s_sound_transmission_envelope::envelope_point, 6>::operator[](long) const;
// public: struct s_sound_transmission_envelope::envelope_point const * c_static_stack<struct s_sound_transmission_envelope::envelope_point, 6>::get_top(void) const;
// public: long c_static_stack<struct s_sound_transmission_envelope::envelope_point, 6>::top(void) const;
// public: struct s_sound_transmission_envelope::envelope_point const * c_static_stack<struct s_sound_transmission_envelope::envelope_point, 6>::get(long) const;
// public: float & s_static_array<float, 4>::operator[]<int>(int);
// public: float & s_static_array<float, 5>::operator[]<int>(int);
// public: float & s_static_array<float, 5>::operator[]<long>(long);
// public: static bool s_static_array<float, 4>::valid<int>(int);
// public: static bool s_static_array<float, 5>::valid<int>(int);
// public: static bool s_static_array<float, 5>::valid<long>(long);

float calculate_individual_positional_speaker_gain(vector3d const * localized_and_normalized_sound_position, e_sound_speaker speaker_index, bool use_linear_speaker_gain)
{
    mangled_ppc("?calculate_individual_positional_speaker_gain@@YAMPBTvector3d@@W4e_sound_speaker@@_N@Z");

    float speaker_factor = 0.0f;

    assert_tag_debug_untracked_jul_11_2011(31, VALID_INDEX(speaker_index, k_number_of_positional_speakers_plus_center));

    if (VALID_INDEX(speaker_index, k_number_of_positional_speakers_plus_center))
    {
        vector3d speaker_normal;
        float const k_spatialization_alpha = 0.2f;
        if (use_linear_speaker_gain)
        {
            speaker_normal.i = (localized_and_normalized_sound_position->i - k_speaker_positions[speaker_index].i) / 2.0f;
            speaker_normal.j = (localized_and_normalized_sound_position->j - k_speaker_positions[speaker_index].j) / 2.0f;
            speaker_normal.k = (localized_and_normalized_sound_position->k - k_speaker_positions[speaker_index].k) / 2.0f;
            speaker_factor = magnitude_squared3d(&speaker_normal);
            speaker_factor = PIN(speaker_factor, 0.0f, 1.0f);
        }
        else
        {
            speaker_normal.i = localized_and_normalized_sound_position->i - k_speaker_positions[speaker_index].i;
            speaker_normal.j = localized_and_normalized_sound_position->j - k_speaker_positions[speaker_index].j;
            speaker_normal.k = localized_and_normalized_sound_position->k - k_speaker_positions[speaker_index].k;
            speaker_factor = magnitude3d(&speaker_normal);
            speaker_factor = 1.0f - expf(-power(2.0f, speaker_factor) * k_spatialization_alpha);
        }
    }

    return 1.0f - speaker_factor;
};

float calculate_individual_positional_speaker_gain_vap(vector3d const * localized_and_normalized_sound_position, e_sound_speaker speaker_index)
{
    mangled_ppc("?calculate_individual_positional_speaker_gain_vap@@YAMPBTvector3d@@W4e_sound_speaker@@@Z");

    float speaker_gain = dot_product3d(localized_and_normalized_sound_position, &k_speaker_positions[speaker_index]);
    return PIN(speaker_gain, 0.0f, 1.0f);
};

void calculate_positional_speaker_gain(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers> * out_speaker_gains, bool use_linear_speaker_gain)
{
    mangled_ppc("?calculate_positional_speaker_gain@@YAXPBTvector3d@@PAV?$s_static_array@M$03@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(78, localized_and_normalized_sound_position);
    assert_tag_debug_untracked_jul_11_2011(79, out_speaker_gains);

    s_static_array<float, k_number_of_positional_speakers_plus_center> temp_gain;
    calculate_positional_speaker_gain_internal(localized_and_normalized_sound_position, &temp_gain, use_linear_speaker_gain, k_number_of_positional_speakers);
    (*out_speaker_gains)[0] = temp_gain[0];
    (*out_speaker_gains)[1] = temp_gain[1];
    (*out_speaker_gains)[2] = temp_gain[2];
    (*out_speaker_gains)[3] = temp_gain[3];
};

void calculate_positional_plus_center_speaker_gain(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers_plus_center> * out_speaker_gains, bool use_linear_speaker_gain)
{
    mangled_ppc("?calculate_positional_plus_center_speaker_gain@@YAXPBTvector3d@@PAV?$s_static_array@M$04@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(96, localized_and_normalized_sound_position);
    assert_tag_debug_untracked_jul_11_2011(97, out_speaker_gains);

    calculate_positional_speaker_gain_internal(localized_and_normalized_sound_position, out_speaker_gains, use_linear_speaker_gain, k_number_of_positional_speakers_plus_center);
};

// $TODO nonmatching: target evaluates previous distance first but subtracts point - previous
float calculate_distance_attenuation(s_sound_transmission_envelope const & envelope, float distance)
{
    mangled_ppc("?calculate_distance_attenuation@@YAMABUs_sound_transmission_envelope@@M@Z");

    float gain = envelope.points.empty() ? 1.0f : envelope.points.get_top()->gain;
    for (long point_index = 0, point_count = envelope.points.count(); point_index < point_count; point_index++)
    {
        s_sound_transmission_envelope::envelope_point const & point = envelope.points[point_index];
        if (distance < point.distance)
        {
            if (point_index == 0 || fabs(envelope.points[point_index - 1].distance - point.distance) < k_real_epsilon)
            {
                gain = point.gain;
            }
            else
            {
                s_sound_transmission_envelope::envelope_point const & previous_point = envelope.points[point_index - 1];
                float t = (previous_point.distance * (point.distance - distance)) / (distance * (point.distance - previous_point.distance));
                gain = point.gain + (previous_point.gain - point.gain) * t;
            }
            break;
        }
    }

    return gain;
};

void calculate_positional_speaker_gain_internal(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers_plus_center> * out_speaker_gains, bool use_linear_speaker_gain, long speaker_count)
{
    mangled_ppc("?calculate_positional_speaker_gain_internal@@YAXPBTvector3d@@PAV?$s_static_array@M$04@@_NJ@Z");

    assert_tag_debug_untracked_jul_11_2011(151, localized_and_normalized_sound_position);
    assert_tag_debug_untracked_jul_11_2011(152, out_speaker_gains);
    assert_tag_debug_untracked_jul_11_2011(153, speaker_count <= NUMBEROF(k_speaker_positions));

    for (long speaker_index = 0; speaker_index < speaker_count; speaker_index++)
    {
        (*out_speaker_gains)[speaker_index] = calculate_individual_positional_speaker_gain(localized_and_normalized_sound_position, static_cast<e_sound_speaker>(speaker_index), use_linear_speaker_gain);
    }
};












