/* ---------- headers */

#include "omaha\physics\bsp2d.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

template<typename t_types>
long bsp2d_test_point_node_offset_internal(typename t_types::t_bsp2d const * bsp, real_point2d const * point, long root_index);

template<typename t_types>
long bsp2d_test_point_internal(typename t_types::t_bsp2d const * bsp, real_point2d const * point, long child_index);

template<> long bsp2d_test_point_node_offset_internal<s_small_bsp2d_types>(bsp2d const * bsp, real_point2d const * point, long root_index);
template<> long bsp2d_test_point_node_offset_internal<s_large_bsp2d_types>(large_bsp2d const * bsp, real_point2d const * point, long root_index);
template<> long bsp2d_test_point_internal<s_small_bsp2d_types>(bsp2d const * bsp, real_point2d const * point, long child_index);
template<> long bsp2d_test_point_internal<s_large_bsp2d_types>(large_bsp2d const * bsp, real_point2d const * point, long child_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long bsp2d_test_point_node_offset(struct bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point_node_offset(struct large_bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point(struct bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point(struct large_bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point_node_offset_internal<struct s_small_bsp2d_types>(struct bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point_node_offset_internal<struct s_large_bsp2d_types>(struct large_bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point_internal<struct s_small_bsp2d_types>(struct bsp2d const *, union real_point2d const *, long);
// long bsp2d_test_point_internal<struct s_large_bsp2d_types>(struct large_bsp2d const *, union real_point2d const *, long);

long bsp2d_test_point_node_offset(bsp2d const * bsp, real_point2d const * point, long root_index)
{
    mangled_ppc("?bsp2d_test_point_node_offset@@YAJPBUbsp2d@@PBTreal_point2d@@J@Z");

    return bsp2d_test_point_node_offset_internal<s_small_bsp2d_types>(bsp, point, root_index);
};

long bsp2d_test_point_node_offset(large_bsp2d const * bsp, real_point2d const * point, long root_index)
{
    mangled_ppc("?bsp2d_test_point_node_offset@@YAJPBUlarge_bsp2d@@PBTreal_point2d@@J@Z");

    return bsp2d_test_point_node_offset_internal<s_large_bsp2d_types>(bsp, point, root_index);
};

long bsp2d_test_point(bsp2d const * bsp, real_point2d const * point, long child_index)
{
    mangled_ppc("?bsp2d_test_point@@YAJPBUbsp2d@@PBTreal_point2d@@J@Z");

    return bsp2d_test_point_internal<s_small_bsp2d_types>(bsp, point, child_index);
};

long bsp2d_test_point(large_bsp2d const * bsp, real_point2d const * point, long child_index)
{
    mangled_ppc("?bsp2d_test_point@@YAJPBUlarge_bsp2d@@PBTreal_point2d@@J@Z");

    return bsp2d_test_point_internal<s_large_bsp2d_types>(bsp, point, child_index);
};

template<>
long bsp2d_test_point_node_offset_internal<s_small_bsp2d_types>(bsp2d const * bsp, real_point2d const * point, long root_index)
{
    mangled_ppc("??$bsp2d_test_point_node_offset_internal@Us_small_bsp2d_types@@@@YAJPBUbsp2d@@PBTreal_point2d@@J@Z");

    if (s_small_bsp2d_types::bsp2d_child_index_is_node(root_index))
    {
        long root_node_index = s_small_bsp2d_types::bsp2d_node_index_from_child_index(root_index);
        long child_index = 0;
        do
        {
            root_node_index += s_small_bsp2d_types::bsp2d_node_index_from_child_index(child_index);
            bsp2d_node const * node = s_small_bsp2d_types::bsp2d_get_node(bsp, root_node_index);
            real distance = plane2d_distance_to_point(&node->plane, point);
            child_index = node->child_indices[distance >= 0.0f];
        }
        while (s_small_bsp2d_types::bsp2d_child_index_is_node(child_index));

        return child_index != NONE ? s_small_bsp2d_types::bsp2d_leaf_index_from_child_index(child_index) : NONE;
    }
    else
    {
        return root_index != NONE ? s_small_bsp2d_types::bsp2d_leaf_index_from_child_index(root_index) : NONE;
    }
};

template<>
long bsp2d_test_point_node_offset_internal<s_large_bsp2d_types>(large_bsp2d const * bsp, real_point2d const * point, long root_index)
{
    mangled_ppc("??$bsp2d_test_point_node_offset_internal@Us_large_bsp2d_types@@@@YAJPBUlarge_bsp2d@@PBTreal_point2d@@J@Z");

    if (s_large_bsp2d_types::bsp2d_child_index_is_node(root_index))
    {
        long root_node_index = s_large_bsp2d_types::bsp2d_node_index_from_child_index(root_index);
        long child_index = 0;
        do
        {
            root_node_index += s_large_bsp2d_types::bsp2d_node_index_from_child_index(child_index);
            large_bsp2d_node const * node = s_large_bsp2d_types::bsp2d_get_node(bsp, root_node_index);
            real distance = plane2d_distance_to_point(&node->plane, point);
            child_index = node->child_indices[distance >= 0.0f];
        }
        while (s_large_bsp2d_types::bsp2d_child_index_is_node(child_index));

        return child_index != NONE ? s_large_bsp2d_types::bsp2d_leaf_index_from_child_index(child_index) : NONE;
    }
    else
    {
        return root_index != NONE ? s_large_bsp2d_types::bsp2d_leaf_index_from_child_index(root_index) : NONE;
    }
};

template<>
long bsp2d_test_point_internal<s_small_bsp2d_types>(bsp2d const * bsp, real_point2d const * point, long child_index)
{
    mangled_ppc("??$bsp2d_test_point_internal@Us_small_bsp2d_types@@@@YAJPBUbsp2d@@PBTreal_point2d@@J@Z");

    while (s_small_bsp2d_types::bsp2d_child_index_is_node(child_index))
    {
        bsp2d_node const * node = s_small_bsp2d_types::bsp2d_get_node(bsp, s_small_bsp2d_types::bsp2d_node_index_from_child_index(child_index));
        real distance = plane2d_distance_to_point(&node->plane, point);
        child_index = node->child_indices[distance >= 0.0f];
    }

    return child_index != NONE ? s_small_bsp2d_types::bsp2d_leaf_index_from_child_index(child_index) : NONE;
};

template<>
long bsp2d_test_point_internal<s_large_bsp2d_types>(large_bsp2d const * bsp, real_point2d const * point, long child_index)
{
    mangled_ppc("??$bsp2d_test_point_internal@Us_large_bsp2d_types@@@@YAJPBUlarge_bsp2d@@PBTreal_point2d@@J@Z");

    while (s_large_bsp2d_types::bsp2d_child_index_is_node(child_index))
    {
        large_bsp2d_node const * node = s_large_bsp2d_types::bsp2d_get_node(bsp, s_large_bsp2d_types::bsp2d_node_index_from_child_index(child_index));
        real distance = plane2d_distance_to_point(&node->plane, point);
        child_index = node->child_indices[distance >= 0.0f];
    }

    return child_index != NONE ? s_large_bsp2d_types::bsp2d_leaf_index_from_child_index(child_index) : NONE;
};

