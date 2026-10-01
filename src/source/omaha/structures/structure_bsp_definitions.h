#ifndef __STRUCTURE_BSP_DEFINITIONS_H__
#define __STRUCTURE_BSP_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    STRUCTURE_BSP_TAG = 'sbsp',
};

/* ---------- definitions */

struct s_tag_resource_definition;

// $TODO: layout only partially reversed; size per scenario_structure_bsp_block_struct (Reach tag layout)
struct structure_bsp
{
    unsigned char unknown0[0x11C]; // 0x0
    s_tag_block cluster_portals; // 0x11C (per game_portals)
    s_tag_block detail_objects; // 0x128
    s_tag_block clusters; // 0x134 structure_cluster
    unsigned char unknown140[0x51C - 0x140]; // 0x140
};
static_assert(sizeof(structure_bsp) == 0x51C, "structure_bsp");

// $TODO: layout only partially reversed; per structure_bsp_cluster_block_struct (Reach tag layout)
struct structure_cluster
{
    real bounds_x[2]; // 0x0
    real bounds_y[2]; // 0x8
    real bounds_z[2]; // 0x10
    char scenario_sky_index; // 0x18
    char atmosphere_index; // 0x19
    char camera_fx_index; // 0x1A
    char weather_index; // 0x1B
    unsigned char unknown1C[0x34 - 0x1C]; // 0x1C
    s_tag_block portals; // 0x34 short (structure_bsp_cluster_portal_index_block)
    unsigned char unknown40[0x8C - 0x40]; // 0x40
};
static_assert(sizeof(structure_cluster) == 0x8C, "structure_cluster");

// per structure_bsp_cluster_portal_block (Reach tag layout)
struct cluster_portal
{
    unsigned char oriented_bounds[0x28]; // 0x0 structure_bsp_cluster_portal_oriented_bounds_block
    short cluster_indices[2]; // 0x28 back, front
    long plane_index; // 0x2C
    real_point3d centroid; // 0x30
    real bounding_radius; // 0x3C
    long flags; // 0x40
    s_tag_block vertices; // 0x44 real_point3d
};
static_assert(sizeof(cluster_portal) == 0x50, "cluster_portal");

/* ---------- prototypes */

void structure_bsp_fixup(long structure_bsp_definition_index);
long structure_bsp_get_import_version();

/* ---------- globals */

extern s_tag_resource_definition structure_bsp_tag_resources;
extern s_tag_resource_definition structure_bsp_cache_file_tag_resources;

/* ---------- public code */

#endif // __STRUCTURE_BSP_DEFINITIONS_H__

