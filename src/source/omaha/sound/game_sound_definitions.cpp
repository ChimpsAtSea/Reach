#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\game_sound_definitions.cpp"
/* ---------- headers */

#include "omaha\sound\game_sound_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\random_math.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition sound_playback_parameter_definition; // "?sound_playback_parameter_definition@@3Us_tag_struct_definition@@A"

// float real_decibels_to_gain(struct real_decibel);
// float power_10(float);
// struct real_decibel convert_real_to_decibels_direct(float);
// struct real_decibel pin_gain_db(struct real_decibel);
// struct real_decibel real_decibel_interpolate(enum e_sound_gain_scale_type, struct real_decibel, struct real_decibel, float);
// struct real_decibel scale_real_decibel(enum e_sound_gain_scale_type, struct real_decibel, float);
// struct real_decibel real_decibel_difference(struct real_decibel, struct real_decibel);
// struct real_decibel real_gain_to_decibels(float);
// float sound_playback_parameter_get_value(struct s_sound_playback_parameter const *, unsigned long *, float);
// void sound_location_set_forward(struct s_sound_location *, union vector3d const *);
// void sound_location_set_identity_forward(struct s_sound_location *);

float real_decibels_to_gain(real_decibel gain_db)
{
    mangled_ppc("?real_decibels_to_gain@@YAMUreal_decibel@@@Z");

    return power_10(gain_db.to_real() / 20.0f);
};

real_decibel convert_real_to_decibels_direct(float gain_in_decibels)
{
    mangled_ppc("?convert_real_to_decibels_direct@@YA?AUreal_decibel@@M@Z");

    real_decibel db;
    db.db = gain_in_decibels;
    return db;
};

real_decibel pin_gain_db(real_decibel gain_db)
{
    mangled_ppc("?pin_gain_db@@YA?AUreal_decibel@@U1@@Z");

    return MIN(MAX(gain_db, k_minimum_sound_gain_db), k_maximum_sound_gain_db);
};

real_decibel real_decibel_interpolate(e_sound_gain_scale_type scale_type, real_decibel start_gain, real_decibel end_gain, float t)
{
    mangled_ppc("?real_decibel_interpolate@@YA?AUreal_decibel@@W4e_sound_gain_scale_type@@U1@1M@Z");

    real_decibel scaled_gain_db = end_gain;
    switch (scale_type)
    {
    case _sound_gain_scale_linear:
    {
        scaled_gain_db.db = interpolate_linear(start_gain.to_real(), end_gain.to_real(), t);
    }
    break;
    case _sound_gain_scale_power:
    {
        float start_amplitude = real_decibels_to_gain(start_gain);
        float end_amplitude = real_decibels_to_gain(end_gain);
        float scale = start_amplitude < end_amplitude ? square_root(t) : 1.0f - square_root(1.0f - t);
        float gain = interpolate_linear(start_amplitude, end_amplitude, scale);
        scaled_gain_db = real_gain_to_decibels(gain);
    }
    break;
    case _sound_gain_scale_inverse_power:
    {
        float start_amplitude = real_decibels_to_gain(start_gain);
        float end_amplitude = real_decibels_to_gain(end_gain);
        float scale = start_amplitude < end_amplitude ? 1.0f - square_root(1.0f - t) : square_root(t);
        float gain = interpolate_linear(start_amplitude, end_amplitude, scale);
        scaled_gain_db = real_gain_to_decibels(gain);
    }
    break;
    case _sound_gain_scale_intensity:
    {
        float start_amplitude = real_decibels_to_gain(start_gain);
        float end_amplitude = real_decibels_to_gain(end_gain);
        float gain = interpolate_linear(start_amplitude, end_amplitude, t);
        scaled_gain_db = real_gain_to_decibels(gain);
    }
    break;
    case _sound_gain_scale_ease_in_out:
    {
        float start_amplitude = real_decibels_to_gain(start_gain);
        float end_amplitude = real_decibels_to_gain(end_gain);
        float gain = interpolate_linear(start_amplitude, end_amplitude, ease_in_ease_out(t));
        scaled_gain_db = real_gain_to_decibels(gain);
    }
    break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(96, false, "halt()");
        break;
    }

    return scaled_gain_db;
};

real_decibel scale_real_decibel(e_sound_gain_scale_type scale_type, real_decibel gain_db, float scale)
{
    mangled_ppc("?scale_real_decibel@@YA?AUreal_decibel@@W4e_sound_gain_scale_type@@U1@M@Z");

    scale = MIN(MAX(scale, 0.0f), 1.0f);
    return real_decibel_interpolate(scale_type, k_minimum_sound_gain_db, gain_db, scale);
};

real_decibel real_decibel_difference(real_decibel start, real_decibel end)
{
    mangled_ppc("?real_decibel_difference@@YA?AUreal_decibel@@U1@0@Z");

    real_decibel difference = end;
    difference.db -= start.db;
    return difference;
};

real_decibel real_gain_to_decibels(float gain)
{
    mangled_ppc("?real_gain_to_decibels@@YA?AUreal_decibel@@M@Z");

    float true_gain = MIN(MAX(gain, 0.0f), 1.0f);
    float decibels;
    if (gain > 0.0f)
    {
        decibels = 20.0f * log10(true_gain);
        decibels = MIN(MAX(decibels, k_minimum_sound_gain_db.to_real()), k_maximum_sound_gain_db.to_real());
    }
    else
    {
        decibels = k_minimum_sound_gain_db.to_real();
    }

    real_decibel gain_db;
    gain_db.db = decibels;
    return pin_gain_db(gain_db);
};

float sound_playback_parameter_get_value(s_sound_playback_parameter const * parameter, unsigned long * in_out_random_seed, float scale)
{
    mangled_ppc("?sound_playback_parameter_get_value@@YAMPBUs_sound_playback_parameter@@PAKM@Z");

    assert_tag_debug_untracked_jul_11_2011(146, parameter);
    assert_tag_debug_untracked_jul_11_2011(147, in_out_random_seed);

    float scale_value = interpolate_linear(parameter->scale_lower_bound, parameter->scale_upper_bound, scale);
    float random_value = parameter->random_base + _real_random_range(in_out_random_seed, NULL, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 150, -parameter->random_variance, parameter->random_variance);
    return scale_value + random_value;
};

void sound_location_set_forward(s_sound_location * sound_location, vector3d const * forward)
{
    mangled_ppc("?sound_location_set_forward@@YAXPAUs_sound_location@@PBTvector3d@@@Z");

    matrix3x3 matrix;
    vector3d normalized_forward = *forward;
    normalize3d_with_default(&normalized_forward, global_forward3d);
    quaternion_from_unit_vectors(&sound_location->orientation, global_forward3d, &normalized_forward);

    matrix3x3_rotation_from_quaternion(&matrix, &sound_location->orientation);
    float cos_angle = dot_product3d(&normalized_forward, &matrix.forward);
    assert_tag_debug_untracked_jul_11_2011(170, _realcmp(cos_angle, 1.0f, k_valid_real_epsilon));
};

void sound_location_set_identity_forward(s_sound_location * sound_location)
{
    mangled_ppc("?sound_location_set_identity_forward@@YAXPAUs_sound_location@@@Z");

    assert_tag_debug_untracked_jul_11_2011(179, sound_location);

    sound_location->orientation = *global_identity_quaternion;
};
