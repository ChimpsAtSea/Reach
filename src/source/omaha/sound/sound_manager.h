#pragma once
#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_stack.h"

/* ---------- constants */

/* ---------- definitions */

struct s_sound_transmission_envelope
{
    struct envelope_point
    {
        float distance; // 0x0
        float gain; // 0x4
    };

    static long const k_max_envelope_points = 6;

    s_sound_transmission_envelope(void);

    c_static_stack<envelope_point, k_max_envelope_points> points; // 0x0
};
static_assert(sizeof(s_sound_transmission_envelope) == 0x34, "s_sound_transmission_envelope");

enum e_sound_volume_type;
union real_point3d;
struct real32_quaternion;
union argb_color;

// size from sound_manager_set_global_effects (memcpy 0x44); field names after 0x0 unverified
struct s_platform_sound_effect_properties
{
    // ??0s_platform_sound_effect_properties@@QAA@XZ is f i (sound_manager.obj): constructs the unnamed radio
    // member (which constructs s_sound_radio_settings at +0x8) then calls clear(); body not reversed yet
    s_platform_sound_effect_properties(void);
    void clear(void);

    long effect_type; // 0x0 (0 = no effect)
    unsigned char radio[0x28]; // 0x4 <unnamed-type-radio>: long + s_sound_radio_settings
    long lowpass_type; // 0x2C
    float lowpass_amount; // 0x30
    float lowpass_time; // 0x34
    unsigned long lowpass_parameters[2]; // 0x38
    long oscillator_index; // 0x40
};
static_assert(sizeof(s_platform_sound_effect_properties) == 0x44, "s_platform_sound_effect_properties");

struct s_platform_sound_effect_input_parameters;

/* ---------- prototypes */

void sound_build_sound_effect_properties(long listener_index, long playback_designator, s_platform_sound_effect_input_parameters const * input_parameters, s_platform_sound_effect_properties * properties);
void sound_manager_set_global_effects(s_platform_sound_effect_properties const * properties);

bool sound_manager_allocate_hardware_voice_explicit(short hardware_voice_index);
void sound_manager_free_hardware_voice(short hardware_voice_index);
void sound_render_deferred_wait(bool block);
void sound_stop_all(long game_state_proc_flags);
void sound_manager_prepare_for_language_change(void);
void sound_manager_handle_language_change(void);
void render_debug_sound_at_point(e_sound_volume_type volume_type, real_point3d const * position, real32_quaternion const * orientation, float cylinder_height, float minimum_distance, float maximum_distance, float inner_cone_angle, float outer_cone_angle, argb_color const * override_min_color, argb_color const * override_max_color);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_MANAGER_H__

