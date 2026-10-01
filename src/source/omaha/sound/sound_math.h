#ifndef __SOUND_MATH_H__
#define __SOUND_MATH_H__
#pragma once

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

enum e_sound_speaker
{
    _speaker_front_left = 0,
    _speaker_front_right,
    _speaker_back_left,
    _speaker_back_right,
    k_number_of_positional_speakers,

    _speaker_center = k_number_of_positional_speakers,
    k_number_of_positional_speakers_plus_center,

    _speaker_lfe = k_number_of_positional_speakers_plus_center,
    k_number_of_speakers
};

/* ---------- definitions */

union vector3d;
struct s_sound_transmission_envelope;

/* ---------- prototypes */

float calculate_individual_positional_speaker_gain(vector3d const * localized_and_normalized_sound_position, e_sound_speaker speaker_index, bool use_linear_speaker_gain);
float calculate_individual_positional_speaker_gain_vap(vector3d const * localized_and_normalized_sound_position, e_sound_speaker speaker_index);
void calculate_positional_speaker_gain(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers> * out_speaker_gains, bool use_linear_speaker_gain);
void calculate_positional_plus_center_speaker_gain(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers_plus_center> * out_speaker_gains, bool use_linear_speaker_gain);
float calculate_distance_attenuation(s_sound_transmission_envelope const & envelope, float distance);
void calculate_positional_speaker_gain_internal(vector3d const * localized_and_normalized_sound_position, s_static_array<float, k_number_of_positional_speakers_plus_center> * out_speaker_gains, bool use_linear_speaker_gain, long speaker_count);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_MATH_H__

