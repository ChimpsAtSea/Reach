#pragma once
#ifndef __UNIT_DEFINITIONS_H__
#define __UNIT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\objects\object_definitions.h"

/* ---------- constants */

enum
{
    UNIT_DEFINITION_TAG = 'unit',
};

enum e_unit_camera_flags
{
    _unit_camera_pitch_bounds_absolute_space_bit = 0,
    _unit_camera_only_collides_with_environment_bit,
    _unit_camera_hides_player_unit_from_camera_bit,
    _unit_camera_use_aiming_vector_instead_of_marker_forward_bit,

    k_unit_camera_flags_count
};

// names from unit_seat_flags (haloreach_tagtest_x360.json); count from c_flags_no_init<e_unit_seat_flags, unsigned long, 32>
enum e_unit_seat_flags
{
    _unit_seat_is_invisible_bit = 0,
    _unit_seat_is_locked_bit,
    _unit_seat_is_driver_bit,
    _unit_seat_is_gunner_bit,
    // $TODO remaining bits

    k_unit_seat_flags_count = 32
};

/* ---------- definitions */

// layout from unit_camera_struct (haloreach_tagtest_x360.json)
struct s_unit_camera_obstruction
{
    float cylinder_fraction; // 0x0
    float obstruction_test_angle; // 0x4
    float obstruction_max_inward_acceleration; // 0x8
    float obstruction_max_outward_acceleration; // 0xC
    float obstruction_max_velocity; // 0x10
    float obstruction_return_delay; // 0x14
};
static_assert(sizeof(s_unit_camera_obstruction) == 0x18, "s_unit_camera_obstruction");

struct s_unit_camera
{
    unsigned short flags; // 0x0
    unsigned short pad; // 0x2
    long camera_marker_name; // 0x4 $TODO c_old_string_id
    float pitch_auto_level; // 0x8
    float pitch_range_lower; // 0xC
    float pitch_range_upper; // 0x10
    s_tag_block camera_tracks; // 0x14
    float pitch_minimum_spring; // 0x20
    float pitch_maximum_spring; // 0x24
    float spring_velocity; // 0x28
    float look_acceleration; // 0x2C
    float look_deceleration; // 0x30
    float look_acceleration_smoothing_fraction; // 0x34
    float override_field_of_view; // 0x38
    s_unit_camera_obstruction camera_obstruction; // 0x3C
    s_tag_block camera_acceleration; // 0x54
    s_tag_block move_stick_overrides; // 0x60
    s_tag_block look_stick_overrides; // 0x6C
};
static_assert(sizeof(s_unit_camera) == 0x78, "s_unit_camera");

// layout from unit_trick_definition_block (haloreach_tagtest_x360.json)
struct s_unit_trick_definition
{
    long animation_name; // 0x0 $TODO c_string_id
    char activation_type; // 0x4
    char velocity_preservation; // 0x5
    unsigned char flags; // 0x6
    unsigned char pad; // 0x7
    float camera_interpolation_time; // 0x8
    float trick_exit_time; // 0xC
    float trick_exit_camera_interpolation_time_lower; // 0x10 $TODO real_bounds
    float trick_exit_camera_interpolation_time_upper; // 0x14
    float trick_exit_displacement_reference; // 0x18
    float cooldown_time; // 0x1C
};
static_assert(sizeof(s_unit_trick_definition) == 0x20, "s_unit_trick_definition");

// layout from unit_seat_block (haloreach_tagtest_x360.json, 316 bytes); only the leading fields are reversed
struct unit_seat
{
    c_flags_no_init<e_unit_seat_flags, unsigned long, k_unit_seat_flags_count> flags; // 0x0
    c_old_string_id label; // 0x4
    unsigned char unknown8[0x13C - 0x8]; // 0x8
};
static_assert(sizeof(unit_seat) == 0x13C, "unit_seat");

// unit_boost_struct (haloreach_tagtest_x360.json, 64 bytes)
struct s_unit_boost
{
    s_tag_reference boost_collision_damage; // 0x0
    unsigned long flags; // 0x10
    float boost_peak_power; // 0x14 (boat_engine_update)
    float boost_rise_time; // 0x18
    float boost_fall_time; // 0x1C
    float boost_power_per_second; // 0x20
    float recharge_rate; // 0x24
    float recharge_delay; // 0x28
    unsigned char trigger_to_boost[0x14]; // 0x2C $TODO mapping_function (c_function_definition)
};
static_assert(sizeof(s_unit_boost) == 0x40, "s_unit_boost");

// $TODO: layout only partially reversed. In Reach sizeof(_unit_definition) == 1304 and it begins with the object struct (tag json structure_size_string)
struct _unit_definition
{
    _object_definition object; // 0x0
    unsigned char unknown178[0x34]; // 0x178
    s_unit_camera unit_camera; // 0x1AC
    unsigned char unknown224[0x488 - 0x224]; // 0x224
    s_tag_block seats; // 0x488 (hs_match_unit_seat_internal)
    unsigned char unknown494[0x4B0 - 0x494]; // 0x494
    s_unit_boost boost; // 0x4B0 (boat_engine_update reads boost.boost_peak_power at 0x4C4)
    unsigned char unknown4F0[0x518 - 0x4F0]; // 0x4F0
};
static_assert(sizeof(_unit_definition) == 0x518, "_unit_definition");

// $TODO: the anonymous struct keeps the older flat accessors (unit_definition->unit_camera) compiling; migrate them to unit.*
struct unit_definition
{
    union
    {
        struct
        {
            unsigned char object[0x178]; // 0x0 $TODO _object_definition
            unsigned char unknown178[0x34]; // 0x178
            s_unit_camera unit_camera; // 0x1AC
            unsigned char unknown224[0x518 - 0x224]; // 0x224
        };
        _unit_definition unit; // 0x0
    };
};
static_assert(sizeof(unit_definition) == 0x518, "unit_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __UNIT_DEFINITIONS_H__

