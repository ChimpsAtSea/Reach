#pragma once
#ifndef __CHARACTER_PHYSICS_DEFINITIONS_H__
#define __CHARACTER_PHYSICS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\materials.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_character_physics_flying_definition
{
    float flying_bank_amount; // 0x0
    float flying_bank_apply_time; // 0x4
    float flying_bank_decay_time; // 0x8
    float flying_pitch_amount; // 0xC
    float flying_velocity; // 0x10
    float flying_sidestep_velocity; // 0x14
    float flying_acceleration; // 0x18
    float flying_deceleration; // 0x1C
    float flying_angular_velocity; // 0x20
    float flying_angular_acceleration; // 0x24
    float flying_crouch_velocity_modifier; // 0x28
    long flying_flags; // 0x2C
};
static_assert(sizeof(s_character_physics_flying_definition) == 0x30, "s_character_physics_flying_definition");

struct s_character_physics_ground_definition
{
    float maximum_slope_angle; // 0x0
    float downhill_falloff_angle; // 0x4
    float downhill_cutoff_angle; // 0x8
    float uphill_falloff_angle; // 0xC
    float uphill_cutoff_angle; // 0x10
    float downhill_velocity_scale; // 0x14
    float uphill_velocity_scale; // 0x18
    float runtime_minimum_normal_k; // 0x1C
    float runtime_downhill_k0; // 0x20
    float runtime_downhill_k1; // 0x24
    float runtime_uphill_k0; // 0x28
    float runtime_uphill_k1; // 0x2C
    float climb_inflection_angle; // 0x30
    float airborne_reaction_time_scale; // 0x34
    float ground_adhesion_velocity_scale; // 0x38
    float gravity_scale; // 0x3C
    float airborne_acceleration_scale; // 0x40
};
static_assert(sizeof(s_character_physics_ground_definition) == 0x44, "s_character_physics_ground_definition");

struct s_character_physics_definition
{
    unsigned long flags; // 0x0 c_flags<e_flag, unsigned long, k_flag_count>
    float collision_height_standing; // 0x4
    float collision_height_crouching; // 0x8
    float collision_radius; // 0xC
    float collision_mass; // 0x10
    long collision_global_material_name; // 0x14 string_id
    long dead_collision_global_material_name; // 0x18 string_id
    c_global_material_type collision_global_material_type; // 0x1C
    c_global_material_type dead_collision_global_material_type; // 0x1E
    s_tag_block dead_spheres; // 0x20
    s_tag_block pills; // 0x2C
    s_tag_block spheres; // 0x38
    s_character_physics_ground_definition ground; // 0x44
    s_character_physics_flying_definition flying; // 0x88
};
static_assert(sizeof(s_character_physics_definition) == 0xB8, "s_character_physics_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CHARACTER_PHYSICS_DEFINITIONS_H__
