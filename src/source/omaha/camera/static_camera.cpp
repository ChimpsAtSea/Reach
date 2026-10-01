#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\static_camera.cpp"
/* ---------- headers */

#include "omaha\camera\static_camera.h"
#include "omaha\camera\observer.h"
#include "omaha\objects\objects.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_static_camera::c_static_camera(void);
// public: virtual enum e_camera_mode c_static_camera::get_type(void) const;
// public: virtual enum e_director_perspective c_static_camera::get_perspective(void) const;
// public: virtual bool c_static_camera::should_apply_player_effects(void) const;
// public: virtual void c_static_camera::set_position(union real_point3d const *);
// public: virtual void c_static_camera::set_forward(union vector3d const *);
// public: c_static_camera::c_static_camera(enum e_output_user_index);
// public: virtual void c_static_camera::update(enum e_output_user_index, float, struct s_observer_command *);
// public: virtual void c_static_camera::set_target(long);

c_static_camera::c_static_camera()
{
    mangled_ppc("??0c_static_camera@@QAA@XZ");
};

// get_type, get_perspective, should_apply_player_effects, set_position and set_forward are inline in static_camera.h

c_static_camera::c_static_camera(e_output_user_index output_user_index)
{
    mangled_ppc("??0c_static_camera@@QAA@W4e_output_user_index@@@Z");

    s_observer_result const * camera = observer_get_camera(output_user_index);
    m_position = camera->position;
    m_forward = camera->forward;
    m_field_of_view = camera->horizontal_field_of_view;
};

void c_static_camera::update(e_output_user_index output_user_index, float dt, s_observer_command * result)
{
    mangled_ppc("?update@c_static_camera@@UAAXW4e_output_user_index@@MPAUs_observer_command@@@Z");

    s_observer_result const * camera;

    assert_tag_debug_untracked_jul_11_2011(38, result);

    result->focus_position = m_position;
    result->focus_distance = 0.0f;

    if (m_target_object_index != NONE)
    {
        real_point3d target_position;
        vector3d forward;

        camera = observer_get_camera(output_user_index);
        object_get_center_of_mass(m_target_object_index, &target_position);
        vector_from_points3d(&camera->position, &target_position, &forward);
        if (normalize3d(&forward) != 0.0f)
        {
            m_forward = forward;
        }
    }

    result->forward = m_forward;
    generate_up_vector3d(&m_forward, &result->up);
    result->horizontal_field_of_view = m_field_of_view;
    result->flags = FLAG(_observer_command_valid_bit);
};

void c_static_camera::set_target(long object_index)
{
    mangled_ppc("?set_target@c_static_camera@@UAAXJ@Z");

    c_camera::set_target(object_index);
};

