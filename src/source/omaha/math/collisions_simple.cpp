#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\math\\collisions_simple.cpp"
/* ---------- headers */

#include "omaha\math\collisions_simple.h"
#include "omaha\math\real_math.h"
#include "omaha\math\matrix_math.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern real fabs(real x); // $TODO inline in the target (f i, render_mesh.obj)

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool collision_point_in_sphere(union real_point3d const *, union real_point3d const *, float);
// bool collision_point_in_cylinder(union real_point3d const *, struct real_matrix4x3const *, float, float, float *);
// bool collision_point_in_pill(union real_point3d const *, struct real_matrix4x3const *, float, float, float *);
// bool collision_point_in_box(union real_point3d const *, struct real_matrix4x3const *, float, float, float);
// bool collision_point_in_cone(union real_point3d const *, struct real_matrix4x3const *, union vector3d const *, float, float, float *, float *);

bool collision_point_in_sphere(real_point3d const * point, real_point3d const * sphere_center, real sphere_radius)
{
    mangled_ppc("?collision_point_in_sphere@@YA_NPBTreal_point3d@@0M@Z");

    assert_tag_debug_untracked_jul_11_2011(24, point!=NULL);
    assert_tag_debug_untracked_jul_11_2011(25, sphere_center!=NULL);

    bool collision;
    if (sphere_radius > k_real_epsilon)
    {
        collision = point_in_sphere(point, sphere_center, sphere_radius);
    }
    else
    {
        collision = false;
    }

    return collision;
};

bool collision_point_in_cylinder(real_point3d const * point, real_matrix4x3 const * cylinder_matrix, real cylinder_radius, real cylinder_height, real * out_distance_from_axis)
{
    mangled_ppc("?collision_point_in_cylinder@@YA_NPBTreal_point3d@@PBUreal_matrix4x3@@MMPAM@Z");

    bool collision = false;
    assert_tag_debug_untracked_jul_11_2011(48, point!=NULL);
    assert_tag_debug_untracked_jul_11_2011(49, cylinder_matrix!=NULL);

    if (cylinder_radius > k_real_epsilon && cylinder_height > k_real_epsilon)
    {
        vector3d normal = cylinder_matrix->up;
        plane3d xy_plane;
        plane3d_from_point_and_normal(&xy_plane, &cylinder_matrix->position, fast_normalize3d(&normal));
        real vertical_distance = fabs(plane3d_distance_to_point(&xy_plane, point));
        if (vertical_distance <= cylinder_height * 0.5)
        {
            vector3d height_vector = cylinder_matrix->up;
            fast_normalize3d(&height_vector);
            scale_vector3d(&height_vector, cylinder_height, &height_vector);

            real_point3d base;
            base.x = 0.0f;
            base.y = 0.0f;
            base.z = -0.5f * cylinder_height;
            matrix4x3_transform_point(cylinder_matrix, &base, &base);

            real radial_distance_squared = point_to_line_distance_squared3d(point, &base, &height_vector, NULL);
            if (radial_distance_squared <= cylinder_radius * cylinder_radius)
            {
                collision = true;
                if (out_distance_from_axis)
                {
                    *out_distance_from_axis = square_root(radial_distance_squared);
                }
            }
        }
    }

    return collision;
};

bool collision_point_in_pill(real_point3d const * point, real_matrix4x3 const * pill_matrix, real pill_radius, real height, real * out_distance_from_axis)
{
    mangled_ppc("?collision_point_in_pill@@YA_NPBTreal_point3d@@PBUreal_matrix4x3@@MMPAM@Z");

    bool collision = false;
    assert_tag_debug_untracked_jul_11_2011(95, point!=NULL);
    assert_tag_debug_untracked_jul_11_2011(96, pill_matrix!=NULL);

    if (pill_radius > k_real_epsilon && height >= 0.0f)
    {
        vector3d height_vector = pill_matrix->up;
        fast_normalize3d(&height_vector);
        scale_vector3d(&height_vector, height, &height_vector);

        real_point3d base;
        base.x = 0.0f;
        base.y = 0.0f;
        base.z = -0.5f * height;
        matrix4x3_transform_point(pill_matrix, &base, &base);

        collision = fast_vector_intersects_sphere(&base, &height_vector, point, pill_radius);
    }

    return collision;
};

bool collision_point_in_box(real_point3d const * point, real_matrix4x3 const * box_matrix, real width, real length, real height)
{
    mangled_ppc("?collision_point_in_box@@YA_NPBTreal_point3d@@PBUreal_matrix4x3@@MMM@Z");

    bool collision = false;
    assert_tag_debug_untracked_jul_11_2011(122, point!=NULL);
    assert_tag_debug_untracked_jul_11_2011(123, box_matrix!=NULL);

    if (width > k_real_epsilon && length > k_real_epsilon && height > k_real_epsilon)
    {
        vector3d normal = box_matrix->forward;
        plane3d yz_plane;
        plane3d_from_point_and_normal(&yz_plane, &box_matrix->position, fast_normalize3d(&normal));
        real forward_distance = fabs(plane3d_distance_to_point(&yz_plane, point));
        if (forward_distance <= width * 0.5f)
        {
            normal = box_matrix->left;
            plane3d xz_plane;
            plane3d_from_point_and_normal(&xz_plane, &box_matrix->position, fast_normalize3d(&normal));
            real sideways_distance = fabs(plane3d_distance_to_point(&xz_plane, point));
            if (sideways_distance <= length * 0.5f)
            {
                normal = box_matrix->up;
                plane3d xy_plane;
                plane3d_from_point_and_normal(&xy_plane, &box_matrix->position, fast_normalize3d(&normal));
                real vertical_distance = fabs(plane3d_distance_to_point(&xy_plane, point));
                if (vertical_distance <= height * 0.5f)
                {
                    collision = true;
                }
            }
        }
    }

    return collision;
};

bool collision_point_in_cone(real_point3d const * point, real_matrix4x3 const * cone_matrix, vector3d const * cone_axis, real cone_length, real base_radius, real * out_axial_distance_from_endpoint, real * out_radial_distance_from_cone_axis)
{
    mangled_ppc("?collision_point_in_cone@@YA_NPBTreal_point3d@@PBUreal_matrix4x3@@PBTvector3d@@MMPAM3@Z");

    bool collision;
    assert_tag_debug_untracked_jul_11_2011(173, point!=NULL);
    assert_tag_debug_untracked_jul_11_2011(174, cone_matrix!=NULL);
    assert_tag_debug_untracked_jul_11_2011(175, cone_axis!=NULL);

    if ((fabs(cone_axis->i) > k_real_epsilon || fabs(cone_axis->j) > k_real_epsilon || fabs(cone_axis->k) > k_real_epsilon) &&
        cone_length > k_real_epsilon && base_radius > k_real_epsilon)
    {
        real cone_angle = 2.0f * arctangent(base_radius, cone_length);
        real cosine_angle = cosine(cone_angle);
        collision = point_in_cone3d(point, &cone_matrix->position, cone_axis, cone_length, cosine_angle);
        if (collision && (out_axial_distance_from_endpoint || out_radial_distance_from_cone_axis))
        {
            vector3d cone_end_to_point;
            vector_from_points3d(&cone_matrix->position, point, &cone_end_to_point);
            if (out_axial_distance_from_endpoint)
            {
                *out_axial_distance_from_endpoint = dot_product3d(&cone_end_to_point, cone_axis);
            }
            if (out_radial_distance_from_cone_axis)
            {
                *out_radial_distance_from_cone_axis = point_to_line_distance3d(point, &cone_matrix->position, cone_axis);
            }
        }
    }
    else
    {
        collision = false;
    }

    return collision;
};
