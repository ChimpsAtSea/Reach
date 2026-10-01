#pragma once
#ifndef __STRUCTURE_PHYSICS_DEFINITIONS_H__
#define __STRUCTURE_PHYSICS_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\color_math.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_structure_design_importer_version = 1,
    k_maximum_structure_soft_ceilings_count = 128,
    k_maximum_structure_soft_ceiling_triangles = 32767,
    k_maximum_structure_water_groups = 1024,
    k_maximum_structure_water_instances = 1024,
    k_maximum_structure_water_instance_planes = 1024,
    k_maximum_structure_water_instance_debug_triangles = 1024,
};

enum e_soft_ceiling_type
{
    _soft_ceiling_type_acceleration = 0,
    _soft_ceiling_type_soft_kill,
    _soft_ceiling_type_slip_surface,

    k_soft_ceiling_type_count
};

enum e_soft_surface_sink_class
{
    _soft_surface_sink_class_none = 0,
    _soft_surface_sink_class_biped,
    _soft_surface_sink_class_dead_biped,
    _soft_surface_sink_class_crates,
    _soft_surface_sink_class_debris,
    _soft_surface_sink_class_all,

    k_soft_surface_sink_class_count
};

/* ---------- definitions */

struct s_tag_field;

struct s_structure_physics
{
    s_tag_block mopp_code; // 0x0
    real pad; // 0xC
    real_point3d structure_bounds_min; // 0x10
    real_point3d structure_bounds_max; // 0x1C
    s_tag_block breakable_surface_mopp_code; // 0x28
    s_tag_block breakable_surface_key_table; // 0x34
};
static_assert(sizeof(s_structure_physics) == 0x40, "s_structure_physics");

struct s_structure_design_physics
{
    void clear();

    long import_version; // 0x0
    s_tag_block soft_ceiling_mopp_code; // 0x4
    s_tag_block soft_ceiling_block; // 0x10 s_structure_soft_ceiling
    s_tag_block water_mopp_code; // 0x1C
    s_tag_block water_groups_block; // 0x28
    s_tag_block water_instances_block; // 0x34 s_structure_physics_water_instance
};
static_assert(sizeof(s_structure_design_physics) == 0x40, "s_structure_design_physics");

struct s_structure_soft_ceiling
{
    long name; // 0x0 string_id
    short type; // 0x4 e_soft_ceiling_type
    short pad; // 0x6
    s_tag_block triangles; // 0x8 s_structure_soft_ceiling_triangle
};
static_assert(sizeof(s_structure_soft_ceiling) == 0x14, "s_structure_soft_ceiling");

struct s_structure_soft_ceiling_triangle
{
    plane3d plane; // 0x0
    real_point3d bounding_sphere_center; // 0x10
    real bounding_sphere_radius; // 0x1C
    real_point3d vertices[3]; // 0x20
};
static_assert(sizeof(s_structure_soft_ceiling_triangle) == 0x44, "s_structure_soft_ceiling_triangle");

struct s_structure_physics_water_instance_debug_triangle
{
    real_point3d vertices[3]; // 0x0
};
static_assert(sizeof(s_structure_physics_water_instance_debug_triangle) == 0x24, "s_structure_physics_water_instance_debug_triangle");

struct s_structure_physics_water_instance
{
    short group_index; // 0x0
    short pad; // 0x2
    vector3d flow_velocity; // 0x4
    argb_color fog_color; // 0x10
    real fog_murkiness; // 0x20
    s_tag_block planes; // 0x24
    s_tag_block debug_triangles; // 0x30 s_structure_physics_water_instance_debug_triangle
    real_rectangle3d bounds; // 0x3C
};
static_assert(sizeof(s_structure_physics_water_instance) == 0x54, "s_structure_physics_water_instance");

struct s_soft_surfaces_definition
{
    real sink_depths[k_soft_surface_sink_class_count]; // 0x0
};
static_assert(sizeof(s_soft_surfaces_definition) == 0x18, "s_soft_surfaces_definition");

/* ---------- prototypes */

void structure_physics_fixup(s_structure_physics * structure_physics);
void structure_physics_design_fixup(s_structure_design_physics * structure_physics_design);
bool structure_water_instance_postprocess(long block_index, void * element, bool for_editor);
bool load_old_structure_physics_v1(unsigned long old_version, s_tag_field const * old_fields, long old_size, long old_count, void * old_data, s_tag_field const * new_fields, long new_size, long new_count, void * new_data);
bool soft_surfaces_definition_postprocess(long block_index, void * element, bool for_editor);
bool structure_physics_postprocess(long block_index, void * element, bool for_editor);
bool scenario_soft_ceilings_plane_from_triangle(plane3d * plane, real_point3d const * point0, real_point3d const * point1, real_point3d const * point2);
bool scenario_soft_ceiling_triangle_postprocess(s_structure_soft_ceiling_triangle * triangle);
bool structure_physics_design_postprocess(long block_index, void * element, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __STRUCTURE_PHYSICS_DEFINITIONS_H__

