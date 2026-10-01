/* ---------- headers */

#include "omaha\visibility\visibility_test.h"
#include "omaha\visibility\visibility.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    _vertex_out_left_bit = 0,
    _vertex_out_right_bit,
    _vertex_out_bottom_bit,
    _vertex_out_top_bit,
    _vertex_out_near_bit,
    _vertex_out_far_bit,

    NUMBER_OF_CLIPPING_FLAGS,

    _vertex_out_no_bits = 0,
    _vertex_out_all_bits = FLAG(NUMBER_OF_CLIPPING_FLAGS) - 1
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long visibility_volume_test_point(struct visibility_volume const *, union real_point3d const *);
// long visibility_volume_build_vertex_flags(struct visibility_volume const *, union real_point3d const *, bool);
// long visibility_volume_test_box(struct visibility_volume const *, union real_rectangle3d const *, bool);
// long visibility_volume_test_triangle(struct visibility_volume const *, union real_point3d const *, union real_point3d const *, union real_point3d const *);
// long visibility_volume_test_sphere_old(struct visibility_volume const *, union real_point3d const *, float);

long visibility_volume_test_point(visibility_volume const * volume, real_point3d const * point)
{
    mangled_ppc("?visibility_volume_test_point@@YAJPBUvisibility_volume@@PBTreal_point3d@@@Z");

    long vertex_flags = visibility_volume_build_vertex_flags(volume, point, true);
    if (vertex_flags != _vertex_out_no_bits)
    {
        return 0;
    }
    else
    {
        return 2;
    }
};

long visibility_volume_build_vertex_flags(visibility_volume const * volume, real_point3d const * point, bool test_against_all_planes)
{
    mangled_ppc("?visibility_volume_build_vertex_flags@@YAJPBUvisibility_volume@@PBTreal_point3d@@_N@Z");

    long out_flags = plane3d_distance_to_point(&volume->world_planes[0], point) > 0.0f ? FLAG(_vertex_out_left_bit) : _vertex_out_no_bits;
    out_flags |= plane3d_distance_to_point(&volume->world_planes[1], point) > 0.0f ? FLAG(_vertex_out_right_bit) : _vertex_out_no_bits;
    out_flags |= plane3d_distance_to_point(&volume->world_planes[2], point) > 0.0f ? FLAG(_vertex_out_top_bit) : _vertex_out_no_bits;
    out_flags |= plane3d_distance_to_point(&volume->world_planes[3], point) > 0.0f ? FLAG(_vertex_out_bottom_bit) : _vertex_out_no_bits;

    if (test_against_all_planes)
    {
        out_flags |= plane3d_distance_to_point(&volume->world_planes[4], point) > 0.0f ? FLAG(_vertex_out_near_bit) : _vertex_out_no_bits;
        out_flags |= plane3d_distance_to_point(&volume->world_planes[5], point) > 0.0f ? FLAG(_vertex_out_far_bit) : _vertex_out_no_bits;
    }

    return out_flags;
};

long visibility_volume_test_box(visibility_volume const * volume, real_rectangle3d const * bounds, bool test_frustum_against_cube)
{
    mangled_ppc("?visibility_volume_test_box@@YAJPBUvisibility_volume@@PBTreal_rectangle3d@@_N@Z");

    if (volume->world_bounds.x1 < bounds->x0)
    {
        return 0;
    }
    if (volume->world_bounds.y1 < bounds->y0)
    {
        return 0;
    }
    if (volume->world_bounds.z1 < bounds->z0)
    {
        return 0;
    }
    if (volume->world_bounds.x0 > bounds->x1)
    {
        return 0;
    }
    if (volume->world_bounds.y0 > bounds->y1)
    {
        return 0;
    }
    if (volume->world_bounds.z0 > bounds->z1)
    {
        return 0;
    }

    {
        long vertex_index;
        real_point3d bounding_vertices[8];
        long and_flags = _vertex_out_all_bits;
        long or_flags = _vertex_out_no_bits;

        bounding_vertices[0].x = bounding_vertices[2].x = bounding_vertices[4].x = bounding_vertices[6].x = bounds->x0;
        bounding_vertices[1].x = bounding_vertices[3].x = bounding_vertices[5].x = bounding_vertices[7].x = bounds->x1;
        bounding_vertices[0].y = bounding_vertices[1].y = bounding_vertices[4].y = bounding_vertices[5].y = bounds->y0;
        bounding_vertices[2].y = bounding_vertices[3].y = bounding_vertices[6].y = bounding_vertices[7].y = bounds->y1;
        bounding_vertices[0].z = bounding_vertices[1].z = bounding_vertices[2].z = bounding_vertices[3].z = bounds->z0;
        bounding_vertices[4].z = bounding_vertices[5].z = bounding_vertices[6].z = bounding_vertices[7].z = bounds->z1;

        for (vertex_index = 0; vertex_index < static_cast<long>(NUMBEROF(bounding_vertices)); vertex_index++)
        {
            long vertex_flags = visibility_volume_build_vertex_flags(volume, &bounding_vertices[vertex_index], false);

            and_flags &= vertex_flags;
            or_flags |= vertex_flags;
        }

        if (or_flags == _vertex_out_no_bits)
        {
            return 2;
        }
        if (and_flags != _vertex_out_no_bits)
        {
            return 0;
        }
    }

    if (test_frustum_against_cube)
    {
        long vertex_index;
        long and_flags = _vertex_out_all_bits;

        for (vertex_index = 0; vertex_index < static_cast<long>(NUMBEROF(volume->world_vertices)); vertex_index++)
        {
            long out_flags;
            real_point3d const * wv = &volume->world_vertices[vertex_index];

            out_flags = wv->x <= bounds->x0 ? FLAG(_vertex_out_left_bit) : _vertex_out_no_bits;
            out_flags |= wv->x >= bounds->x1 ? FLAG(_vertex_out_right_bit) : _vertex_out_no_bits;
            out_flags |= wv->y <= bounds->y0 ? FLAG(_vertex_out_top_bit) : _vertex_out_no_bits;
            out_flags |= wv->y >= bounds->y1 ? FLAG(_vertex_out_bottom_bit) : _vertex_out_no_bits;
            out_flags |= wv->z <= bounds->z0 ? FLAG(_vertex_out_near_bit) : _vertex_out_no_bits;
            out_flags |= wv->z >= bounds->z1 ? FLAG(_vertex_out_far_bit) : _vertex_out_no_bits;

            and_flags &= out_flags;
        }

        if (and_flags != _vertex_out_no_bits)
        {
            return 0;
        }
    }

    return 1;
};

long visibility_volume_test_triangle(visibility_volume const * volume, real_point3d const * p0, real_point3d const * p1, real_point3d const * p2)
{
    mangled_ppc("?visibility_volume_test_triangle@@YAJPBUvisibility_volume@@PBTreal_point3d@@11@Z");

    long and_flags = _vertex_out_all_bits;
    long vertex_flags;

    vertex_flags = visibility_volume_build_vertex_flags(volume, p0, false);
    if (vertex_flags == _vertex_out_no_bits)
    {
        return 1;
    }
    and_flags &= vertex_flags;

    vertex_flags = visibility_volume_build_vertex_flags(volume, p1, false);
    if (vertex_flags == _vertex_out_no_bits)
    {
        return 1;
    }
    and_flags &= vertex_flags;

    vertex_flags = visibility_volume_build_vertex_flags(volume, p2, false);
    if (vertex_flags == _vertex_out_no_bits)
    {
        return 1;
    }
    and_flags &= vertex_flags;

    if (and_flags != _vertex_out_no_bits)
    {
        return 0;
    }

    return 1;
};

long visibility_volume_test_sphere_old(visibility_volume const * volume, real_point3d const * point, real radius)
{
    mangled_ppc("?visibility_volume_test_sphere_old@@YAJPBUvisibility_volume@@PBTreal_point3d@@M@Z");

    if (volume->world_bounds.x1 < point->x - radius)
    {
        return 0;
    }
    if (volume->world_bounds.y1 < point->y - radius)
    {
        return 0;
    }
    if (volume->world_bounds.z1 < point->z - radius)
    {
        return 0;
    }
    if (volume->world_bounds.x0 > point->x + radius)
    {
        return 0;
    }
    if (volume->world_bounds.y0 > point->y + radius)
    {
        return 0;
    }
    if (volume->world_bounds.z0 > point->z + radius)
    {
        return 0;
    }

    real dist_x0 = plane3d_distance_to_point(&volume->world_planes[0], point);
    if (dist_x0 > radius)
    {
        return 0;
    }
    real dist_x1 = plane3d_distance_to_point(&volume->world_planes[1], point);
    if (dist_x1 > radius)
    {
        return 0;
    }
    real dist_y0 = plane3d_distance_to_point(&volume->world_planes[2], point);
    if (dist_y0 > radius)
    {
        return 0;
    }
    real dist_y1 = plane3d_distance_to_point(&volume->world_planes[3], point);
    if (dist_y1 > radius)
    {
        return 0;
    }
    real dist_z0 = plane3d_distance_to_point(&volume->world_planes[4], point);
    if (dist_z0 > radius)
    {
        return 0;
    }
    real dist_z1 = plane3d_distance_to_point(&volume->world_planes[5], point);
    if (dist_z1 > radius)
    {
        return 0;
    }

    // $note dist_z0 is never tested against the far side of the sphere
    if (dist_x0 < -radius && dist_x1 < -radius && dist_y0 < -radius && dist_y1 < -radius && dist_z1 < -radius)
    {
        return 2;
    }

    return 1;
};

