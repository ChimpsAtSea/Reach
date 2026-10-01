#pragma once
#ifndef __DAMAGE_INFO_DEFINITIONS_H__
#define __DAMAGE_INFO_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\game\materials.h"
#include "omaha\math\function_definitions.h"
#include "omaha\animations\animation_graph.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// order from animation_usage_enumeration "damage root *" entries
enum e_damage_part
{
    _damage_part_gut = 0,
    _damage_part_chest,
    _damage_part_head,
    _damage_part_left_shoulder,
    _damage_part_left_arm,
    _damage_part_left_leg,
    _damage_part_left_foot,
    _damage_part_right_shoulder,
    _damage_part_right_arm,
    _damage_part_right_leg,
    _damage_part_right_foot,

    k_damage_part_count
};

long const k_maximum_damage_part_names = 8;

/* ---------- definitions */

struct s_region_transition
{
    long region_name; // 0x0
    short new_state; // 0x4
    short runtime_region_index; // 0x6
};
static_assert(sizeof(s_region_transition) == 0x8, "s_region_transition");

struct s_instantaneous_damage_response
{
    short damage_response_type; // 0x0
    short constraint_damage_type; // 0x2
    long constraint_name_or_group_name; // 0x4
    unsigned long response_flags; // 0x8
    float damage_threshold; // 0xC
    unsigned long body_threshold_flags; // 0x10
    float body_damage_threshold; // 0x14
    s_tag_reference transition_effect_generic; // 0x18
    s_tag_reference transition_effect_specific; // 0x28
    s_tag_reference transition_damage_effect; // 0x38
    s_region_transition transition_region_swap; // 0x48
    s_region_transition transition_secondary_region_swap; // 0x50
    short destroy_instance_group_index; // 0x58
    short custom_response_behavior; // 0x5A
    long custom_response_label; // 0x5C
    long transition_effect_marker_name; // 0x60
    long transition_damage_effect_marker_name; // 0x64
    float response_delay_seconds; // 0x68
    s_tag_reference response_delay_effect; // 0x6C
    long response_delay_effect_marker_name; // 0x7C
    long ejecting_seat_name; // 0x80
    float skip_fraction; // 0x84
    long destroyed_child_object_marker_name; // 0x88
    float total_damage_threshold; // 0x8C
};
static_assert(sizeof(s_instantaneous_damage_response) == 0x90, "s_instantaneous_damage_response");

struct s_damage_section_recharge_speed_multiplier_curve
{
    c_function_definition mapping; // 0x0
};
static_assert(sizeof(s_damage_section_recharge_speed_multiplier_curve) == 0x14, "s_damage_section_recharge_speed_multiplier_curve");

struct s_damage_node
{
    short damage_part; // 0x0
    unsigned short pad; // 0x2
    long unused[3]; // 0x4
};
static_assert(sizeof(s_damage_node) == 0x10, "s_damage_node");

struct s_damage_body_parameters
{
    float maximum_vitality; // 0x0
    float minimum_stun_damage; // 0x4
    float stun_time; // 0x8
    float recharge_time; // 0xC
    float recharge_fraction; // 0x10
};
static_assert(sizeof(s_damage_body_parameters) == 0x14, "s_damage_body_parameters");

struct s_damage_shield_parameters
{
    float maximum_shield_vitality; // 0x0
    long global_shield_material_name; // 0x4
    float minimum_stun_damage; // 0x8
    float stun_time; // 0xC
    float recharge_time; // 0x10
    float shield_overcharge_fraction; // 0x14
    float shield_overcharge_time; // 0x18
    float shield_damaged_threshold; // 0x1C
    s_tag_reference shield_damaged_effect; // 0x20
    s_tag_reference shield_depleted_effect; // 0x30
    s_tag_reference shield_recharging_effect; // 0x40
};
static_assert(sizeof(s_damage_shield_parameters) == 0x50, "s_damage_shield_parameters");

// global_damage_info_block
struct s_model_damage_info
{
    unsigned long flags; // 0x0
    long global_indirect_material_name; // 0x4
    short indirect_damage_section; // 0x8
    unsigned char pad0[2]; // 0xA
    unsigned char pad1[4]; // 0xC
    char collision_damage_reporting_type; // 0x10
    char response_damage_reporting_type; // 0x11
    unsigned char pad2[2]; // 0x12
    unsigned char pad3[20]; // 0x14
    s_damage_body_parameters body; // 0x28
    unsigned char pad4[64]; // 0x3C
    s_damage_shield_parameters shield; // 0x7C
    s_tag_block damage_sections; // 0xCC
    s_tag_block nodes; // 0xD8
    c_global_material_type runtime_shield_material_type; // 0xE4
    c_global_material_type runtime_indirect_material_type; // 0xE6
    float runtime_shield_recharge_velocity; // 0xE8
    float runtime_overcharge_velocity; // 0xEC
    float runtime_health_recharge_velocity; // 0xF0
    s_tag_block damage_seats; // 0xF4
    s_tag_block damage_constraints; // 0x100
};
static_assert(sizeof(s_model_damage_info) == 0x10C, "s_model_damage_info");

// global_damage_info_block_fields_v1
struct s_model_damage_info_v1
{
    unsigned long flags; // 0x0
    long global_indirect_material_name; // 0x4
    float maximum_vitality; // 0x8
    float body_system_shock; // 0xC
    float friendly_damage_resistance; // 0x10
    s_tag_reference localized_damage_effect; // 0x14
    float area_damage_effect_threshold; // 0x24
    s_tag_reference area_damage_effect; // 0x28
    float body_damaged_threshold; // 0x38
    s_tag_reference body_damaged_effect; // 0x3C
    s_tag_reference body_depleted_effect; // 0x4C
    float body_destroyed_threshold; // 0x5C
    s_tag_reference body_destroyed_effect; // 0x60
    float maximum_shield_vitality; // 0x70
    long global_shield_material_name; // 0x74
    float minimum_stun_damage; // 0x78
    float stun_time; // 0x7C
    float recharge_time; // 0x80
    float shield_damaged_threshold; // 0x84
    s_tag_reference shield_damaged_effect; // 0x88
    s_tag_reference shield_depleted_effect; // 0x98
    s_tag_reference shield_recharging_effect; // 0xA8
    s_tag_block damage_sections; // 0xB8
    s_tag_block nodes; // 0xC4
    c_global_material_type runtime_shield_material_type; // 0xD0
    c_global_material_type runtime_indirect_material_type; // 0xD2
    float runtime_shield_recharge_velocity; // 0xD4
};
static_assert(sizeof(s_model_damage_info_v1) == 0xD8, "s_model_damage_info_v1");

// model_damage_info_struct
struct s_new_model_damage_info
{
    unsigned long flags; // 0x0
    float maximum_vitality; // 0x4
    long indirect_material_name; // 0x8
    short indirect_damage_section; // 0xC
    short shielded_state_damage_section; // 0xE
    char collision_damage_reporting_type; // 0x10
    char response_damage_reporting_type; // 0x11
    unsigned char pad0[2]; // 0x12
    s_tag_block damage_sections; // 0x14
    s_tag_block damage_constraints; // 0x20
    s_tag_block nodes; // 0x2C
    short runtime_indirect_material_type; // 0x38
    unsigned char pad1[2]; // 0x3A
};
static_assert(sizeof(s_new_model_damage_info) == 0x3C, "s_new_model_damage_info");

/* ---------- prototypes */

struct s_model_definition;
struct s_tag_field;

bool damage_info_build_nodes(s_model_definition const * model, s_tag_block * nodes_block);
short damage_part_name_match(char const * name);
void build_damage_root_node_map(s_model_definition const * model, short * const node_damage_parts);
short get_damage_part_for_node_usage_flag(e_animation_node_usage usage);
bool damage_info_conversion_func(unsigned long conversion_flags, s_tag_field const * old_fields, long old_version, long old_size, void * old_data, s_tag_field const * new_fields, long new_version, long new_size, void * new_data);

/* ---------- globals */

extern char const * model_state_enum_definition_strings[];

/* ---------- public code */

#endif // __DAMAGE_INFO_DEFINITIONS_H__
