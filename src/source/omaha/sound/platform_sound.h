#pragma once
#ifndef __PLATFORM_SOUND_H__
#define __PLATFORM_SOUND_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_dsp_settings_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_platform_sound_voice_update_definition
{
    long listener_index; // 0x0
    unsigned long flags; // 0x4
    real_point3d position; // 0x8
    vector3d velocity; // 0x14
    vector3d forward; // 0x20
    vector3d up; // 0x2C
    float occlusion; // 0x38
    float obstruction; // 0x3C
    real_decibel reverb_gain_db; // 0x40
    float occlusion_interpolation_speed; // 0x44
    float obstruction_interpolation_speed; // 0x48
};
static_assert(sizeof(s_platform_sound_voice_update_definition) == 0x4C, "s_platform_sound_voice_update_definition");

struct s_platform_sound_listener
{
    real_point3d position; // 0x0
    vector3d velocity; // 0xC
    vector3d forward; // 0x18
    vector3d up; // 0x24
};
static_assert(sizeof(s_platform_sound_listener) == 0x30, "s_platform_sound_listener");

// Reach layout from c_xenon_audio_source_manager::update_source_status / c_xenon_audio_voice_manager::update_voice_status
struct s_platform_sound_status
{
    c_big_flags_typed_no_init<long, 196> available_sources; // 0x0
    s_static_array<long, 5> source_first_indices; // 0x1C
    s_static_array<long, 5> source_one_past_last_indices; // 0x30
    c_big_flags_typed_no_init<long, 212> available_voices; // 0x44
};
static_assert(sizeof(s_platform_sound_status) == 0x60, "s_platform_sound_status");

struct s_platform_sound_listener_reverb
{
    s_sound_reverb_settings const * reverb_settings; // 0x0
    s_sound_azimuth_image azimuth_image; // 0x4
    float gain; // 0x14
};
static_assert(sizeof(s_platform_sound_listener_reverb) == 0x18, "s_platform_sound_listener_reverb");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PLATFORM_SOUND_H__
