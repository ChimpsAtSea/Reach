#pragma once
#ifndef __BIPEDS_H__
#define __BIPEDS_H__

/* ---------- headers */

#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// H3 names; only _biped_falling_to_his_death_bit (4, c_dead_camera::update) and the count
// (17, c_flags_no_init<e_biped_flag, unsigned long, 17>) are verified for Reach
enum e_biped_flag
{
    _biped_player_accept_melee_aiming_from_unit_bit = 0,
    _biped_ejected_from_seat_bit,
    _biped_effected_by_phantom_this_tick_bit,
    _biped_pathfinding_ground_collision_valid_bit,
    _biped_falling_to_his_death_bit,

    k_biped_flag_count = 17
};

/* ---------- definitions */

// $TODO: layout not reversed; offsets are from the start of the datum
struct biped_datum
{
    unsigned char __unknown0[0x9B8];
    c_flags_no_init<e_biped_flag, unsigned long, k_biped_flag_count> flags; // 0x9B8 (c_dead_camera::update)
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BIPEDS_H__

