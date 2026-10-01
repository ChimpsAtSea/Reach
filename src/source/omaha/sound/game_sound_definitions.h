#pragma once
#ifndef __GAME_SOUND_DEFINITIONS_H__
#define __GAME_SOUND_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include <math.h>

/* ---------- constants */

const float k_speed_of_sound = 111.548553f;
const float k_ln2_gain = 0.6931472f; // ln(2)

enum e_sound_volume_type
{
    _sound_volume_sphere = 0,
    _sound_volume_cylinder,
    _sound_volume_pill,

    k_number_of_sound_volume_types
};

enum e_sound_gain_scale_type
{
    _sound_gain_scale_linear = 0,
    _sound_gain_scale_intensity,
    _sound_gain_scale_power,
    _sound_gain_scale_inverse_power,
    _sound_gain_scale_ease_in_out,
    k_number_of_sound_gain_scale_types
};

/* ---------- definitions */

struct s_sound_location
{
    real_point3d position; // 0x0
    real32_quaternion orientation; // 0xC
    vector3d translational_velocity; // 0x1C
    unsigned long game_location; // 0x28 $TODO s_location
};
static_assert(sizeof(s_sound_location) == 0x2C, "s_sound_location");

struct s_sound_azimuth_image
{
    float start_angle; // 0x0
    float end_angle; // 0x4
    float pitch_factor; // 0x8
    float gain_fraction; // 0xC
};
static_assert(sizeof(s_sound_azimuth_image) == 0x10, "s_sound_azimuth_image");

struct s_sound_playback_parameter
{
    float scale_lower_bound; // 0x0
    float scale_upper_bound; // 0x4
    float random_base; // 0x8
    float random_variance; // 0xC
};
static_assert(sizeof(s_sound_playback_parameter) == 0x10, "s_sound_playback_parameter");

struct real_decibel
{
    float db; // 0x0

    bool operator<(real_decibel const & rhs) const
    {
        mangled_ppc("??Mreal_decibel@@QBA_NABU0@@Z");

        return db < rhs.db;
    };

    bool operator>(real_decibel const & rhs) const
    {
        mangled_ppc("??Oreal_decibel@@QBA_NABU0@@Z");

        return rhs.db < db;
    };

    float to_real() const
    {
        mangled_ppc("?to_real@real_decibel@@QBAMXZ");

        return db;
    };
};
static_assert(sizeof(real_decibel) == 0x4, "real_decibel");

// each translation unit that reads these gets its own private copy
static real_decibel const k_maximum_sound_gain_db = { 0.0f };
static real_decibel const k_minimum_sound_gain_db = { -64.0f };

/* ---------- prototypes */

inline float power_10(float exponent)
{
    mangled_ppc("?power_10@@YAMM@Z");

    return exp(exponent * 2.3025851f);
};

float real_decibels_to_gain(real_decibel gain_db);
real_decibel convert_real_to_decibels_direct(float gain_in_decibels);
real_decibel pin_gain_db(real_decibel gain_db);
real_decibel real_decibel_interpolate(e_sound_gain_scale_type scale_type, real_decibel start_gain, real_decibel end_gain, float t);
real_decibel scale_real_decibel(e_sound_gain_scale_type scale_type, real_decibel gain_db, float scale);
real_decibel real_decibel_difference(real_decibel start, real_decibel end);
real_decibel real_gain_to_decibels(float gain);
float sound_playback_parameter_get_value(s_sound_playback_parameter const * parameter, unsigned long * in_out_random_seed, float scale);
void sound_location_set_forward(s_sound_location * sound_location, vector3d const * forward);
void sound_location_set_identity_forward(s_sound_location * sound_location);

/* ---------- globals */

static s_sound_azimuth_image k_indentity_azimuth_image = { 0.0f, k_2pi, 1.0f, 0.0f };

/* ---------- public code */

#endif // __GAME_SOUND_DEFINITIONS_H__

