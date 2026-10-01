#pragma once
#ifndef __MULTIPLAYER_GAME_OBJECTS_H__
#define __MULTIPLAYER_GAME_OBJECTS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\game_constants.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_multiplayer_object_boundary_shape
{
    _shape_unused = 0,
    _shape_sphere,
    _shape_cylinder,
    _shape_box,

    k_multiplayer_object_boundary_count
};

/* ---------- definitions */

struct s_multiplayer_object_boundary_shape_string_resolver;

// $TODO: offsets 0x0-0x10 verified in location_names_get_name_index_for_point; size assumed from s_multiplayer_object_boundary_geometry_data
struct s_multiplayer_object_boundary
{
    s_multiplayer_object_boundary()
    {
    };

    real width_or_radius; // 0x0
    real box_length; // 0x4
    real positive_height; // 0x8
    real negative_height; // 0xC
    c_enum<e_multiplayer_object_boundary_shape, char, _shape_unused, k_multiplayer_object_boundary_count, s_multiplayer_object_boundary_shape_string_resolver> shape; // 0x10
};
static_assert(sizeof(s_multiplayer_object_boundary) == 0x14, "s_multiplayer_object_boundary");

// $TODO: fields after the base follow H3 (shader index, transform, bounding radius); only the base fields are verified
struct s_multiplayer_object_boundary_geometry_data :
    public s_multiplayer_object_boundary
{
    s_multiplayer_object_boundary_geometry_data()
    {
    };

    long shader_definition_index; // 0x14
    real_matrix4x3 boundary_transform; // 0x18
    real bounding_sphere_radius; // 0x4C
};
static_assert(sizeof(s_multiplayer_object_boundary_geometry_data) == 0x50, "s_multiplayer_object_boundary_geometry_data");

// $TODO: only the fields used so far are reversed; total size unknown
struct s_multiplayer_object_properties
{
    // f i (simulation_game_objects.obj): returns the team designator byte at 0x19; body not written yet
    c_enum<e_multiplayer_team_designator, char, _multiplayer_team_designator_none, k_multiplayer_team_designator_count, s_multiplayer_team_designator_string_resolver> get_team_designator(void) const;

    unsigned char __unknown0[0x1A]; // 0x0
    char spawn_order; // 0x1A (area_set_compare_by_order_index)
    unsigned char __unknown1B[0x1D - 0x1B]; // 0x1B
    unsigned char location_name_index; // 0x1D (location_names_get_name_index_for_point)
};

/* ---------- prototypes */

bool point_in_multiplayer_object_boundary(real_point3d const * point, s_multiplayer_object_boundary_geometry_data const * geometry_data);
bool player_in_multiplayer_object_boundary(long player_index, s_multiplayer_object_boundary_geometry_data const * geometry_data);
void multiplayer_object_calculate_boundary_geometry(long object_index, s_multiplayer_object_boundary_geometry_data * out_geometry_data, bool use_opaque_shader);
void multiplayer_object_submit_boundary(s_multiplayer_object_boundary_geometry_data const * geometry_data, union argb_color const * color, long object_index, unsigned long flags);

/* ---------- globals */

/* ---------- public code */

#endif // __MULTIPLAYER_GAME_OBJECTS_H__

