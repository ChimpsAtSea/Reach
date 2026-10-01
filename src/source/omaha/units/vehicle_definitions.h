#pragma once
#ifndef __VEHICLE_DEFINITIONS_H__
#define __VEHICLE_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\unit_definitions.h"
#include "omaha\physics\havok_vehicle_physics_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    VEHICLE_DEFINITION_TAG = 'vehi',
};

/* ---------- definitions */

// vehicle_physics_types_struct
struct s_vehicle_physics_types
{
    s_tag_block type_blocks[15]; // 0x0
};
static_assert(sizeof(s_vehicle_physics_types) == 0xB4, "s_vehicle_physics_types");

struct _vehicle_definition
{
    unsigned long flags; // 0x0
    s_vehicle_physics_types physics_types; // 0x4
    s_havok_vehicle_physics_definition havok_vehicle_physics; // 0xB8
    s_tag_block tricks; // 0x10C
    char player_training_vehicle_type; // 0x118
    char vehicle_size; // 0x119
    unsigned char pad[2]; // 0x11A
    float minimum_flipping_angular_velocity; // 0x11C
    float maximum_flipping_angular_velocity; // 0x120
    float crouch_transition_time; // 0x124
    float runtime_crouch_transition_velocity; // 0x128
    float seat_entrance_acceleration_scale; // 0x12C
    float seat_exit_acceleration_scale; // 0x130
    float blur_speed; // 0x134
    long flip_message; // 0x138
    s_tag_reference suspension_sound; // 0x13C
    s_tag_reference special_effect; // 0x14C
    s_tag_reference driver_boost_damage_effect_or_response; // 0x15C
    s_tag_reference rider_boost_damage_effect_or_response; // 0x16C
};
static_assert(sizeof(_vehicle_definition) == 0x17C, "_vehicle_definition");

// vehicle_group
struct vehicle_definition
{
    _unit_definition unit; // 0x0
    _vehicle_definition vehicle; // 0x518
};
static_assert(sizeof(vehicle_definition) == 0x694, "vehicle_definition");

/* ---------- prototypes */

void vehicle_definition_fixup(long vehicle_definition_index);
void vehicle_definition_teardown(long vehicle_definition_index);

/* ---------- globals */

/* ---------- public code */

#endif // __VEHICLE_DEFINITIONS_H__

