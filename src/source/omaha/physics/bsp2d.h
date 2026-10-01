#pragma once
#ifndef __BSP2D_H__
#define __BSP2D_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct bsp2d
{
    s_tag_block nodes; // 0x0
};
static_assert(sizeof(bsp2d) == 0xC, "bsp2d");

struct large_bsp2d
{
    s_tag_block nodes; // 0x0
};
static_assert(sizeof(large_bsp2d) == 0xC, "large_bsp2d");

struct bsp2d_node
{
    real_plane2d plane; // 0x0
    short child_indices[2]; // 0xC
};
static_assert(sizeof(bsp2d_node) == 0x10, "bsp2d_node");

struct large_bsp2d_node
{
    real_plane2d plane; // 0x0
    long child_indices[2]; // 0xC
};
static_assert(sizeof(large_bsp2d_node) == 0x14, "large_bsp2d_node");

struct s_small_bsp2d_types
{
    typedef bsp2d t_bsp2d;
    typedef bsp2d_node t_bsp2d_node;

    static bool bsp2d_child_index_is_node(long child_index)
    {
        return (child_index & 0x8000) == 0;
    };

    static long bsp2d_node_index_from_child_index(long child_index)
    {
        return child_index & 0x7FFF;
    };

    static long bsp2d_leaf_index_from_child_index(long child_index)
    {
        return child_index & 0x7FFF;
    };

    static bsp2d_node const * bsp2d_get_node(bsp2d const * bsp, long node_index)
    {
        return static_cast<bsp2d_node const *>(tag_block_get_element_with_size(&bsp->nodes, node_index, sizeof(bsp2d_node)));
    };
};

struct s_large_bsp2d_types
{
    typedef large_bsp2d t_bsp2d;
    typedef large_bsp2d_node t_bsp2d_node;

    static bool bsp2d_child_index_is_node(long child_index)
    {
        return (child_index & 0x80000000) == 0;
    };

    static long bsp2d_node_index_from_child_index(long child_index)
    {
        return child_index;
    };

    static long bsp2d_leaf_index_from_child_index(long child_index)
    {
        return child_index & 0x7FFFFFFF;
    };

    static large_bsp2d_node const * bsp2d_get_node(large_bsp2d const * bsp, long node_index)
    {
        return static_cast<large_bsp2d_node const *>(tag_block_get_element_with_size(&bsp->nodes, node_index, sizeof(large_bsp2d_node)));
    };
};

/* ---------- prototypes */

long bsp2d_test_point_node_offset(bsp2d const * bsp, real_point2d const * point, long root_index);
long bsp2d_test_point_node_offset(large_bsp2d const * bsp, real_point2d const * point, long root_index);
long bsp2d_test_point(bsp2d const * bsp, real_point2d const * point, long child_index);
long bsp2d_test_point(large_bsp2d const * bsp, real_point2d const * point, long child_index);

/* ---------- globals */

/* ---------- public code */

#endif // __BSP2D_H__

