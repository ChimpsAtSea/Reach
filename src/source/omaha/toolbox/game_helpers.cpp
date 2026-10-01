#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\game_helpers.cpp"
/* ---------- headers */

#include "omaha\toolbox\game_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\camera\director.h"
#include "omaha\camera\observer.h"
#include "omaha\game\player_control.h"
#include "omaha\game\player_mapping.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\physics\collision_constants.h"
#include "omaha\physics\collisions.h"
#include "omaha\units\units.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool user_get_look_at_point(enum e_output_user_index, union real_point3d *);

bool user_get_look_at_point(e_output_user_index output_user_index, real_point3d * result_point)
{
    mangled_ppc("?user_get_look_at_point@@YA_NW4e_output_user_index@@PATreal_point3d@@@Z");

    assert_tag_debug_untracked_jul_11_2011(19, result_point);

    bool hit = false;
    if (output_user_index != k_output_user_none)
    {
        real_point3d origin;
        long unit_index;
        vector3d ray;
        if (director_get_perspective(output_user_index) == _director_perspective_first_person && (unit_index = player_mapping_get_unit_by_output_user(output_user_index)) != NONE)
        {
            unit_get_camera_position(unit_index, &origin);
            player_control_get_aiming_vector(output_user_index, &ray);
        }
        else
        {
            s_observer_result const * camera = observer_get_camera(output_user_index);
            origin = camera->position;
            ray = camera->forward;
        }

        scale_vector3d(&ray, 1000.0f, &ray);

        {
            s_collision_test_flags collision_flags = _collision_test_for_objects_structure_ignore_invisible_flags;
            collision_result result;
            long ignore_object_index = NONE;
            long times = 0;
            {
                real_point3d position = origin;
                vector3d vector = ray;
                do
                {
                    hit = collision_test_vector(collision_flags, &position, &vector, ignore_object_index, NONE, &result);

                    {
                        vector3d temp;
                        vector_from_points3d(&result.point, &position, &temp);
                        point_from_line3d(reinterpret_cast<real_point3d const *>(&vector), &temp, 1.0f, reinterpret_cast<real_point3d *>(&vector));
                    }
                    position = result.point;

                    if (result.type == _collision_result_object)
                    {
                        if (result.object_index != ignore_object_index)
                        {
                            object_datum * object = static_cast<object_datum *>(object_get_and_verify_type(result.object_index, NONE));
                            if (object->object.flags.test(_object_static_pathfinding_bit) || object_get_root_source(result.object_index) == _object_source_structure_object)
                            {
                                break;
                            }
                        }
                        ignore_object_index = result.object_index;
                    }
                }
                while (result.type == _collision_result_object && times++ < 200);
            }

            if (hit)
            {
                *result_point = result.point;
            }
        }
    }

    return hit;
};

