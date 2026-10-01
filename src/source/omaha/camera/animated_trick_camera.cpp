#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\animated_trick_camera.cpp"
/* ---------- headers */

#include "omaha\camera\animated_trick_camera.h"
#include "omaha\camera\observer.h"
#include "omaha\camera\following_camera.h"
#include "omaha\game\game_time.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\units\vehicles.h"
#include "omaha\units\vehicle_type_component.h"
#include "omaha\units\units.h"
#include "omaha\units\unit_definitions.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_types.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

long debug_vehicle_animated_trick_camera_name;
long debug_vehicle_animated_trick_animation_name;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long debug_vehicle_animated_trick_camera_name; // "?debug_vehicle_animated_trick_camera_name@@3JA"
// long debug_vehicle_animated_trick_animation_name; // "?debug_vehicle_animated_trick_animation_name@@3JA"

// public: c_animated_trick_camera::c_animated_trick_camera(void);
// public: virtual enum e_camera_mode c_animated_trick_camera::get_type(void) const;
// public: virtual enum e_director_perspective c_animated_trick_camera::get_perspective(void) const;
// public: virtual bool c_animated_trick_camera::should_draw_reticule(void) const;
// public: c_animated_trick_camera::c_animated_trick_camera(long);
// public: virtual void c_animated_trick_camera::update(enum e_output_user_index, float, struct s_observer_command *);
// bool animated_trick_camera_setup_target(long, struct s_unit_camera_info const *, struct s_observer_command *);
// void animated_trick_camera_setup_fov(long, struct s_unit_camera_info const *, struct s_observer_command *);
// void animated_trick_camera_setup_collision(long, struct s_unit_camera_info const *, struct s_observer_command *);

c_animated_trick_camera::c_animated_trick_camera()
{
    mangled_ppc("??0c_animated_trick_camera@@QAA@XZ");
};

// get_type, get_perspective and should_draw_reticule are inline in animated_trick_camera.h

c_animated_trick_camera::c_animated_trick_camera(long unit_index)
{
    mangled_ppc("??0c_animated_trick_camera@@QAA@J@Z");

    c_camera::set_target(unit_index);
};

void c_animated_trick_camera::update(e_output_user_index output_user_index, float dt, s_observer_command * result)
{
    mangled_ppc("?update@c_animated_trick_camera@@UAAXW4e_output_user_index@@MPAUs_observer_command@@@Z");

    s_unit_camera_info camera_info;

    unit_get_camera_info(m_target_object_index, &camera_info);
    result->flags = 0;
    if (animated_trick_camera_setup_target(m_target_object_index, &camera_info, result))
    {
        SET_BIT(result->flags, _observer_command_valid_bit, true);
        animated_trick_camera_setup_fov(m_target_object_index, &camera_info, result);
        animated_trick_camera_setup_collision(m_target_object_index, &camera_info, result);
    }
    observer_validate_camera_command(result);
};

bool animated_trick_camera_setup_target(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result)
{
    mangled_ppc("?animated_trick_camera_setup_target@@YA_NJPBUs_unit_camera_info@@PAUs_observer_command@@@Z");

    bool result = false;

    assert_tag_debug_untracked_jul_11_2011(84, unit_index!=NONE);
    assert_tag_debug_untracked_jul_11_2011(85, out_result);

    if (camera_info->unit_camera)
    {
        long camera_marker_name = camera_info->unit_camera->camera_marker_name;
        object_marker marker_data;

        if (camera_marker_name != 0 && camera_marker_name != -1 && object_get_markers_by_string_id(camera_info->unit_index, camera_marker_name, &marker_data, 1))
        {
            result = true;

            vehicle_datum * vehicle = static_cast<vehicle_datum *>(object_get_and_verify_type(camera_info->unit_index, _object_mask_vehicle));
            real_matrix4x3 inverse_matrix;
            real_matrix4x3 camera_matrix;
            real_matrix4x3 desired_transform;
            float blend;

            out_result->focus_position = marker_data.matrix.position;
            out_result->focus_distance = 0.0f;
            object_get_velocities(camera_info->unit_index, &out_result->focus_velocity, NULL);
            matrix4x3_inverse(object_get_node_matrix(camera_info->unit_index, 0), &inverse_matrix);
            matrix4x3_multiply(&inverse_matrix, &marker_data.matrix, &camera_matrix);
            vehicle->type_component.get_trick_desired_transform(camera_info->unit_index, &desired_transform);
            matrix4x3_multiply(&desired_transform, &camera_matrix, &camera_matrix);

            s_unit_trick_definition const * trick_definition = vehicle_get_current_trick_definition(camera_info->unit_index);
            long remaining_ticks = vehicle->type_component.get_trick_ticks_left(camera_info->unit_index);

            out_result->timer = trick_definition->camera_interpolation_time;
            if (remaining_ticks < game_seconds_to_ticks_round(trick_definition->trick_exit_time))
            {
                real_point3d position;
                vector3d forward;
                vector3d direction;

                following_camera_deterministic(unit_index, &position, &forward, _following_camera_deterministic_blending_enabled);
                vector_from_points3d(&marker_data.matrix.position, &position, &direction);
                point_from_line3d(&desired_transform.position, &direction, 1.0f, &position);
                out_result->timer = trick_definition->trick_exit_camera_interpolation_time_lower;

                blend = 1.0f - game_ticks_to_seconds(static_cast<float>(remaining_ticks)) / trick_definition->trick_exit_time;
                points_interpolate(&camera_matrix.position, &position, blend, &camera_matrix.position);
            }

            following_camera_at_point(camera_info->unit_index, &camera_matrix.position, &camera_matrix.forward, &camera_matrix.up, out_result);
        }
    }

    return result;
};

void animated_trick_camera_setup_fov(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result)
{
    mangled_ppc("?animated_trick_camera_setup_fov@@YAXJPBUs_unit_camera_info@@PAUs_observer_command@@@Z");

    assert_tag_debug_untracked_jul_11_2011(164, unit_index!=NONE);
    assert_tag_debug_untracked_jul_11_2011(165, camera_info);
    assert_tag_debug_untracked_jul_11_2011(166, out_result);

    SET_BIT(out_result->flags, _observer_command_can_modify_fov_bit, true);
    out_result->horizontal_field_of_view = observer_suggested_field_of_view();
    if (camera_info->unit_camera->override_field_of_view > 0.0f)
    {
        out_result->horizontal_field_of_view = camera_info->unit_camera->override_field_of_view;
    }
    else if (unit_index != camera_info->unit_index)
    {
        unit_definition const * unit_definition = static_cast<::unit_definition const *>(tag_get(UNIT_DEFINITION_TAG, static_cast<object_datum *>(object_get_and_verify_type(unit_index, _object_mask_unit))->definition_index));
        if (unit_definition->unit_camera.override_field_of_view > 0.0f)
        {
            out_result->horizontal_field_of_view = unit_definition->unit_camera.override_field_of_view;
        }
    }
};

void animated_trick_camera_setup_collision(long unit_index, s_unit_camera_info const * camera_info, s_observer_command * out_result)
{
    mangled_ppc("?animated_trick_camera_setup_collision@@YAXJPBUs_unit_camera_info@@PAUs_observer_command@@@Z");

    assert_tag_debug_untracked_jul_11_2011(196, unit_index!=NONE);
    assert_tag_debug_untracked_jul_11_2011(197, camera_info);
    assert_tag_debug_untracked_jul_11_2011(198, out_result);

    if (camera_info->seat_index != NONE)
    {
        out_result->collision_ignore_objects[0] = object_get_ultimate_parent(unit_index);
        out_result->collision_ignore_objects_count = 1;
        SET_BIT(out_result->flags, _observer_command_has_collision_ignore_objects_bit, true);
    }

    if (TEST_BIT(camera_info->unit_camera->flags, _unit_camera_only_collides_with_environment_bit))
    {
        SET_BIT(out_result->flags, _observer_command_only_collides_with_environment_bit, true);
    }
};

