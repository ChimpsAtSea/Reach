#pragma once
#ifndef __GEOMETRY_DEFINITIONS_H__
#define __GEOMETRY_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_resource_runtime.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_vertex_buffer_usage
{
    _vertex_buffer_usage_standard = 0,
    _vertex_buffer_usage_lightmap_uv,
    _vertex_buffer_usage_vert_color,
    _vertex_buffer_usage_prt,
    _vertex_buffer_usage_instances,
    _vertex_buffer_usage_indices,
    _vertex_buffer_usage_water_indices,
    _vertex_buffer_usage_water_vertex,

    k_number_of_vertex_buffer_usages
};

enum e_compression_flags
{
    _compression_info_compressed_position_bit = 0,
    _compression_info_compressed_texcoord_bit,
    _compression_info_compression_optimized_bit,

    k_number_of_compression_flags
};

/* ---------- definitions */

struct s_tag_resource_definition;
class c_rasterizer_vertex_buffer;

struct s_mesh
{
    s_tag_block parts; // 0x0
    s_tag_block subparts; // 0xC
    unsigned short vertex_buffer_indices[k_number_of_vertex_buffer_usages]; // 0x18
    short index_buffer_index; // 0x28
    short index_buffer_index_tessellation; // 0x2A
    unsigned short flags; // 0x2C
    char rigid_node_index; // 0x2E
    char vertex_type; // 0x2F
    char prt_vertex_type; // 0x30
    char lighting_policy; // 0x31
    char index_buffer_type; // 0x32
    unsigned char pad; // 0x33
    s_tag_block instance_buckets; // 0x34
    s_tag_block water_indices_start; // 0x40
    real runtime_bounding_radius; // 0x4C
    real_point3d runtime_bounding_offset; // 0x50
};
static_assert(sizeof(s_mesh) == 0x5C, "s_mesh");

struct s_compression_info
{
    unsigned short compression_flags; // 0x0
    unsigned short pad; // 0x2
    real_rectangle3d position_bounds; // 0x4
    real_rectangle2d texcoord_bounds; // 0x1C
    real unused0; // 0x2C
    real unused1; // 0x30
};
static_assert(sizeof(s_compression_info) == 0x34, "s_compression_info");

struct s_raw_vertex
{
    real_point3d position; // 0x0
    real_point2d texcoord; // 0xC
    real_point3d normal; // 0x14
    real_point3d binormal; // 0x20
    real_point3d tangent; // 0x2C
    real_point2d lightmap_texcoord; // 0x38
    unsigned char node_indices[4]; // 0x40
    real node_weights[4]; // 0x44
    real_point3d vertex_color; // 0x54
};
static_assert(sizeof(s_raw_vertex) == 0x60, "s_raw_vertex");

struct s_per_mesh_raw_data
{
    s_tag_block raw_vertices; // 0x0
    s_tag_block raw_indices; // 0xC
    s_tag_block raw_indices32; // 0x18
    s_tag_block raw_water_data; // 0x24
    s_tag_block raw_imposter_data; // 0x30
    s_tag_block raw_instance_imposter_verts; // 0x3C
    long per_vertex_lighting_vertex_size; // 0x48
    short parameterized_texture_width; // 0x4C
    short parameterized_texture_height; // 0x4E
    unsigned long flags; // 0x50
};
static_assert(sizeof(s_per_mesh_raw_data) == 0x54, "s_per_mesh_raw_data");

struct s_render_geometry
{
    unsigned long flags; // 0x0
    s_tag_block meshes; // 0x4
    s_tag_block compression_infos; // 0x10
    s_tag_block part_sorting_positions; // 0x1C
    s_tag_block user_data; // 0x28
    s_tag_block per_mesh_temporary; // 0x34
    unsigned char pad3[0xC]; // 0x40
    s_tag_block per_mesh_node_map; // 0x4C
    s_tag_block per_mesh_subpart_visibility; // 0x58
    s_tag_block per_mesh_prt_data; // 0x64
    s_tag_block per_instance_lightmap_texcoords; // 0x70
    s_tag_block per_instance_lightmap_texcoords_vertex_buffer; // 0x7C
    s_tag_block water_bounding_boxes; // 0x88
    s_tag_resource api_resource; // 0x94
};
static_assert(sizeof(s_render_geometry) == 0x9C, "s_render_geometry");

/* ---------- prototypes */

c_rasterizer_vertex_buffer const * mesh_get_vertex_buffer(s_render_geometry const * render_geometry, s_mesh const * mesh, e_vertex_buffer_usage usage);

/* ---------- globals */

extern s_tag_resource_definition render_geometry_api_resource_definition;

/* ---------- public code */

#endif // __GEOMETRY_DEFINITIONS_H__

