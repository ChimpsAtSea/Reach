#ifndef __ANIMATION_CONSTANTS_H__
#define __ANIMATION_CONSTANTS_H__
#pragma once

/* ---------- headers */

#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// Reach: 18 bits (c_flags<e_animation_playback_flags, unsigned long, 18>); bits 0..15 named per H3 e_animation_playback_flag_bits
// (bit 15 tested by c_auxilary_channel::apply_node_orientations, as in H3)
enum e_animation_playback_flags
{
    _animation_playback_autoplay_bit = 0,
    _animation_playback_loop_bit,
    _animation_playback_allow_random_start,
    _animation_playback_allow_random_speed,
    _animation_playback_allow_random_variation,
    _animation_playback_no_random_variation_on_loop,
    _animation_playback_force_subframe_interpolation,
    _animation_playback_ignore_frame_events,
    _animation_playback_ignore_sound_events,
    _animation_playback_ignore_effect_events,
    _animation_playback_right_arm_only,
    _animation_playback_left_arm_only,
    _animation_playback_right_arm_sounds_allowed,
    _animation_playback_left_arm_sounds_allowed,
    _animation_playback_custom_animation_bit,
    _animation_playback_acceleration_screen_bit,
    _animation_playback_unknown16_bit, // $TODO name
    _animation_playback_unknown17_bit, // $TODO name

    k_number_of_animation_playback_flags
};

// Reach: c_enum<e_animation_graph_location, char, 0, 9> (channel_base.obj); names past H3's 7 unknown
enum e_animation_graph_location
{
    _animation_graph_unknown_location = 0,
    _animation_graph_action,
    _animation_graph_overlay,
    _animation_graph_death_and_damage,
    _animation_graph_transition,
    _animation_graph_vehicle_suspension,
    _animation_graph_object_overlay,
    _animation_graph_location_unknown7, // $TODO name
    _animation_graph_location_unknown8, // $TODO name

    k_number_of_animation_graph_locations
};

/* ---------- definitions */

typedef c_flags<e_animation_playback_flags, unsigned long, k_number_of_animation_playback_flags> c_animation_playback_flags;
typedef c_enum<e_animation_graph_location, char, _animation_graph_unknown_location, k_number_of_animation_graph_locations> c_animation_graph_location;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ANIMATION_CONSTANTS_H__

