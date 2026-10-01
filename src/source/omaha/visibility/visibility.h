#ifndef __VISIBILITY_H__
#define __VISIBILITY_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\cseries\location.h"

/* ---------- constants */

/* ---------- definitions */

struct visibility_volume
{
    real vector_planes[6][4]; // 0x0 (__vector4 in the target)
    short projection_index; // 0x60
    short region_cluster_index; // 0x62
    long plane_index; // 0x64
    short plane_bsp_index; // 0x68
    short parent_volume_index; // 0x6A
    real_rectangle2d frustum_bounds; // 0x6C
    real portal_nearest_z; // 0x7C
    real_point3d world_vertices[5]; // 0x80
    real_rectangle3d world_bounds; // 0xBC
    real_plane3d world_planes[6]; // 0xD4
    vector3d world_edge_vectors[4]; // 0x134
    char pad0[12]; // 0x164
};
static_assert(sizeof(visibility_volume) == 0x170, "visibility_volume");

struct visibility_projection
{
    bool parallel_projection_flag; // 0x0
    bool pad0[3]; // 0x1
    real_matrix4x3 world_to_basis; // 0x4
    real_matrix4x3 basis_to_world; // 0x38
    bool near_bounded_flag; // 0x6C
    bool pad1[3]; // 0x6D
    real near_distance; // 0x70
    real_plane3d near_plane; // 0x74
    bool far_bounded_flag; // 0x84
    bool far_bounded_spherical_flag; // 0x85
    bool pad2[2]; // 0x86
    real far_distance; // 0x88
    bool volume_bounded_flag; // 0x8C
    bool pad3[3]; // 0x8D
    visibility_volume volume; // 0x90
    long convex_hull_point_count; // 0x200
    real_point2d convex_hull_points[4]; // 0x204
    char pad4[12]; // 0x224
};
static_assert(sizeof(visibility_projection) == 0x230, "visibility_projection");

// $TODO: Reach grew this from 26 to 30 bytes; only cluster_reference (0x4) is verified
struct visibility_cluster
{
    short unknown0[2]; // 0x0
    s_cluster_reference cluster_reference; // 0x4
    short volume_counts[6]; // 0x6
    short first_volume_indices[6]; // 0x12
};
static_assert(sizeof(visibility_cluster) == 0x1E, "visibility_cluster");

long const k_maximum_visibility_region_projections = 6;
long const k_maximum_visibility_region_clusters = 75; // derived from the 0xD32..0x1728 gap, unverified
long const k_maximum_visibility_region_volumes = 512; // H3 value, unverified

// offsets from the Reach target (c_visibility_collection_render::render_debug_visibility_region, render_region_cluster_portals)
struct s_visibility_region
{
    short projection_count; // 0x0
    unsigned char pad0[0xE]; // 0x2 (projections are __vector4 aligned in the target)
    visibility_projection projections[k_maximum_visibility_region_projections]; // 0x10
    short cluster_count; // 0xD30
    visibility_cluster clusters[k_maximum_visibility_region_clusters]; // 0xD32
    long cluster_remap_table[k_maximum_visibility_region_clusters]; // 0x15FC
    short volume_count; // 0x1728
    unsigned char pad1[0x6]; // 0x172A
    visibility_volume volumes[k_maximum_visibility_region_volumes]; // 0x1730
};
static_assert(OFFSETOF(s_visibility_region, cluster_count) == 0xD30, "s_visibility_region");
static_assert(OFFSETOF(s_visibility_region, volumes) == 0x1730, "s_visibility_region");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __VISIBILITY_H__

