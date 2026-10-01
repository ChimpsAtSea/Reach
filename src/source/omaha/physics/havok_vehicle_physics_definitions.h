#pragma once
#ifndef __HAVOK_VEHICLE_PHYSICS_DEFINITIONS_H__
#define __HAVOK_VEHICLE_PHYSICS_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\game\materials.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    _anti_gravity_point_definition_gets_damage_from_region_bit = 0,
    _anti_gravity_point_definition_only_active_on_water_bit,

    k_anti_gravity_point_definition_flags_count
};

enum
{
    _friction_point_definition_gets_damage_from_region_bit = 0,
    _friction_point_definition_powered_bit,
    _friction_point_definition_front_turning_bit,
    _friction_point_definition_rear_turning_bit,
    _friction_point_definition_ai_force_rear_turning_bit,
    _friction_point_definition_attached_to_e_brake_bit,
    _friction_point_definition_can_be_destroyed_bit,

    k_friction_point_definition_flags_count
};

enum
{
    _havok_vehicle_physics_definition_has_suspension_bit = 0,

    k_havok_vehicle_physics_definition_flags_count
};

/* ---------- definitions */

// anti_gravity_point_definition_block
struct s_anti_gravity_point_definition
{
    long marker_name; // 0x0
    unsigned long flags; // 0x4
    long damping; // 0x8
    float antigrav_strength; // 0xC
    float antigrav_height; // 0x10
    float antigrav_compression_damping; // 0x14
    float antigrav_extension_damping; // 0x18
    float antigrav_normal_k1; // 0x1C
    float antigrav_normal_k0; // 0x20
    float radius; // 0x24
    long collision_global_material_name; // 0x28
    c_global_material_type collision_global_material_type; // 0x2C
    short runtime_damage_source_region_index; // 0x2E
    long damage_source_region_name; // 0x30
    float damage_error[5]; // 0x34
};
static_assert(sizeof(s_anti_gravity_point_definition) == 0x48, "s_anti_gravity_point_definition");

// friction_point_definition_block
struct s_friction_point_definition
{
    long marker_name; // 0x0
    unsigned long flags; // 0x4
    float fraction_of_total_vehicle_mass; // 0x8
    float radius; // 0xC
    float damaged_radius; // 0x10
    float moving_friction_velocity_difference; // 0x14
    float emergency_brake_moving_friction; // 0x18
    float emergency_brake_friction; // 0x1C
    float emergency_braking_moving_friction_velocity_difference; // 0x20
    long collision_global_material_name; // 0x24
    c_global_material_type collision_global_material_type; // 0x28
    short model_state_friction_point_destroyed; // 0x2A
    long destroyed_region_name; // 0x2C
    long destroyed_runtime_region_index; // 0x30
};
static_assert(sizeof(s_friction_point_definition) == 0x34, "s_friction_point_definition");

// boat_physics_definition_struct
struct s_boat_physics_definition
{
    float ground_vertical_extrusion; // 0x0
};
static_assert(sizeof(s_boat_physics_definition) == 0x4, "s_boat_physics_definition");

// havok_vehicle_physics_struct
struct s_havok_vehicle_physics_definition
{
    long flags; // 0x0
    float ground_friction; // 0x4
    float ground_depth; // 0x8
    float ground_damp_fraction; // 0xC
    float ground_moving_friction; // 0x10
    float ground_plane_minimum_k0; // 0x14 ground maximum slope 0 (degrees), cosine after postprocess
    float ground_plane_minimum_k1; // 0x18 ground maximum slope 1 (degrees), cosine after postprocess
    float maximum_normal_force_friction_contribution; // 0x1C
    float anti_gravity_bank_lift; // 0x20
    float steering_bank_reaction_scale; // 0x24
    float gravity_scale; // 0x28
    short maximum_update_period_ticks; // 0x2C
    short maximum_remote_update_period_ticks; // 0x2E
    long iteration_count; // 0x30
    long suspension_count; // 0x34
    s_tag_block anti_gravity_points; // 0x38 s_anti_gravity_point_definition
    s_tag_block friction_points; // 0x44 s_friction_point_definition
    s_boat_physics_definition boat_physics; // 0x50
};
static_assert(sizeof(s_havok_vehicle_physics_definition) == 0x54, "s_havok_vehicle_physics_definition");

/* ---------- prototypes */

extern void havok_vehicle_physics_postprocess(long vehicle_definition_index);
extern void havok_vehicle_shape_phantom_postprocess(long vehicle_definition_index);
extern void model_postprocess_vehicle_anti_gravity_points(s_havok_vehicle_physics_definition * physics, long model_definition_index);

extern bool havok_vehicle_physics_has_suspension(s_havok_vehicle_physics_definition const * physics);
extern void havok_vehicle_physics_definition_fixup(s_havok_vehicle_physics_definition * physics);
extern void havok_vehicle_physics_definition_teardown(s_havok_vehicle_physics_definition * physics);

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_VEHICLE_PHYSICS_DEFINITIONS_H__

