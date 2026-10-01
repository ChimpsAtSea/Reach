/* ---------- headers */

#include "blamlib\tracked_target_camera.h"
#include "omaha\camera\following_camera.h"
#include "omaha\camera\observer.h"
#include "omaha\game\aim_target.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\target_tracking.h"
#include "omaha\units\units.h"

/* ---------- constants */

static real const k_tracked_target_camera_height_scale = 1.0f; // $TODO name unknown
static real const k_tracked_target_camera_distance_scale = 3.0f; // $TODO name unknown

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_tracked_target_camera::c_tracked_target_camera(void);
// public: virtual enum e_camera_mode c_tracked_target_camera::get_type(void) const;
// public: virtual enum e_director_perspective c_tracked_target_camera::get_perspective(void) const;
// public: virtual bool c_tracked_target_camera::should_draw_reticule(void) const;
// public: c_tracked_target_camera::c_tracked_target_camera(long);
// public: virtual void c_tracked_target_camera::update(enum e_output_user_index, float, struct s_observer_command *);

c_tracked_target_camera::c_tracked_target_camera()
{
    mangled_ppc("??0c_tracked_target_camera@@QAA@XZ");
};

// get_type, get_perspective and should_draw_reticule are inline in tracked_target_camera.h

c_tracked_target_camera::c_tracked_target_camera(long target_object_index)
{
    mangled_ppc("??0c_tracked_target_camera@@QAA@J@Z");

    c_camera::set_target(target_object_index);
};

void c_tracked_target_camera::update(e_output_user_index output_user_index, float dt, s_observer_command * result)
{
    mangled_ppc("?update@c_tracked_target_camera@@UAAXW4e_output_user_index@@MPAUs_observer_command@@@Z");

    s_unit_camera_info camera_info;
    unit_get_camera_info(m_target_object_index, &camera_info);
    unit_datum * unit = static_cast<unit_datum *>(object_get_and_verify_type(camera_info.unit_index, _object_mask_unit));
    if (unit->target_tracking.get_const()->is_locked())
    {
        real_point3d unit_center;
        vector3d unit_to_target;
        vector3d camera_forward;
        real radius;
        real_point3d bounding_sphere_center;
        vector3d cross;
        vector3d up_vector;
        real_point3d target_position;

        object_get_center_of_mass_interpolated(camera_info.unit_index, &unit_center);
        object_get_center_of_mass_interpolated(unit->target_tracking.get_const()->get_target()->get_object_index(), &target_position);
        vector_from_points3d(&unit_center, &target_position, &unit_to_target);
        up_vector = *global_up3d;
        cross_product3d(&up_vector, &unit_to_target, &cross);
        cross_product3d(&unit_to_target, &cross, &up_vector);
        camera_forward = unit_to_target;
        normalize3d_with_default(&camera_forward, &unit->desired_aiming_vector);
        normalize3d_with_default(&up_vector, &unit->object.up);
        object_get_bounding_sphere(camera_info.unit_index, &bounding_sphere_center, &radius);
        point_from_line3d(&unit_center, &camera_forward, -radius * k_tracked_target_camera_distance_scale, &unit_center);
        point_from_line3d(&unit_center, &up_vector, radius * k_tracked_target_camera_height_scale, &unit_center);
        following_camera_at_point(camera_info.unit_index, &unit_center, &camera_forward, &up_vector, result);
        object_get_velocities(camera_info.unit_index, &result->focus_velocity, NULL);
        result->horizontal_field_of_view = observer_suggested_field_of_view();
        result->timer = 0.5f;
        SET_BIT(result->flags, _observer_command_valid_bit, true);
        SET_BIT(result->flags, _observer_command_variable_up_bit, true);
    }
    else
    {
        following_camera_deterministic(m_target_object_index, &result->focus_position, &result->forward, _following_camera_deterministic_blending_enabled);
    }
};

