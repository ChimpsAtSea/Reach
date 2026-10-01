#pragma once
#ifndef __CHARACTER_PHYSICS_H__
#define __CHARACTER_PHYSICS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_character_physics_definition;
class c_animation_manager;
class hkShape;

struct s_character_physics_update_input_datum
{
    struct s_flying
    {
        real bank; // 0x0
    };
    static_assert(sizeof(s_flying) == 0x4, "s_character_physics_update_input_datum::s_flying");

    struct s_sentinel
    {
        real_point3d position; // 0x0
        real_point3d animation_position; // 0xC
        vector3d desired_velocity; // 0x18
        long animation_id; // 0x24 c_animation_id
    };
    static_assert(sizeof(s_sentinel) == 0x28, "s_character_physics_update_input_datum::s_sentinel");

    struct s_ground
    {
        long last_support_havok_component_index; // 0x0
        long last_support_rigid_body_index; // 0x4
        real_matrix4x3 last_support_havok_component_matrix; // 0x8
        vector3d ground_plane; // 0x3C
        real stun_fraction; // 0x48
        vector3d movement_forward; // 0x4C
        real adhesion_velocity_scale; // 0x58
        bool effected_by_phantom_this_tick; // 0x5C
    };
    static_assert(sizeof(s_ground) == 0x60, "s_character_physics_update_input_datum::s_ground");

    struct s_dead
    {
        vector3d resting_surface_normal; // 0x0
        bool update_size; // 0xC
        bool in_relaxation_state; // 0xD
    };
    static_assert(sizeof(s_dead) == 0x10, "s_character_physics_update_input_datum::s_dead");

    struct s_melee
    {
        bool has_target; // 0x0
        real physics_radius; // 0x4
        real target_physics_radius; // 0x8
        real_point3d target_position; // 0xC
        vector3d target_velocity; // 0x18
        real target_distance; // 0x24
    };
    static_assert(sizeof(s_melee) == 0x28, "s_character_physics_update_input_datum::s_melee");

    long mode; // 0x0 c_character_physics_component::e_mode
    bool sub_initialized; // 0x4
    s_character_physics_definition const * character_physics_definition; // 0x8
    unsigned long flags; // 0xC
    long early_mover_object_index; // 0x10
    long accepted_early_mover_object_index; // 0x14
    long havok_component_index; // 0x18
    c_animation_manager const * animation_manager; // 0x1C
    real movement_scale; // 0x20
    long havok_group; // 0x24 e_havok_group
    s_flying flying; // 0x28
    s_sentinel sentinel; // 0x2C
    s_ground ground; // 0x54
    s_dead dead; // 0xB4
    s_melee melee; // 0xC4
    vector3d throttle; // 0xEC
    real_point3d position; // 0xF8
    vector3d forward; // 0x104
    vector3d up; // 0x110
    vector3d desired_facing_vector; // 0x11C
    vector3d aiming; // 0x128
    vector3d velocity; // 0x134
    vector3d early_mover_localized_velocity; // 0x140
    real gravity; // 0x14C
    real boost_power; // 0x150
    vector3d desired_movement_speed; // 0x154
    real acceleration_maximum; // 0x160
    real airborne_acceleration_maximum; // 0x164
    hkShape const * shape_switch_request; // 0x168
};
static_assert(sizeof(s_character_physics_update_input_datum) == 0x16C, "s_character_physics_update_input_datum");

struct s_character_physics_update_output_datum
{
    enum e_animation_state
    {
        _state_idle = 0,
        _state_move_front,
        _state_move_back,
        _state_move_left,
        _state_move_right,
    };

    struct s_sentinel
    {
        bool is_origin_translated_flag; // 0x0
        real_point3d translated_origin; // 0x4
    };
    static_assert(sizeof(s_sentinel) == 0x10, "s_character_physics_update_output_datum::s_sentinel");

    struct s_ground
    {
        vector3d surface_velocity; // 0x0
    };
    static_assert(sizeof(s_ground) == 0xC, "s_character_physics_update_output_datum::s_ground");

    unsigned long flags; // 0x0
    e_animation_state animation_state; // 0x4
    bool animation_state_urgent; // 0x8
    vector3d new_velocity; // 0xC
    vector3d forward; // 0x18
    vector3d up; // 0x24
    matrix3x3 local_space_rotation; // 0x30
    s_sentinel sentinel; // 0x54
    s_ground ground; // 0x64
};
static_assert(sizeof(s_character_physics_update_output_datum) == 0x70, "s_character_physics_update_output_datum");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CHARACTER_PHYSICS_H__

