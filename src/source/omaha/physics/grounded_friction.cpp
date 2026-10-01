#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\grounded_friction.cpp"
/* ---------- headers */

#include "omaha\physics\grounded_friction.h"
#include "omaha\physics\grounded_friction_definitions.h"
#include "omaha\physics\havok.h"
#include "omaha\physics\havok_component.h"
#include "omaha\physics\havok_contact_points.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_early_movers.h"
#include "omaha\game\game_time.h"
#include "omaha\math\real_math.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\utility_math.inl"
#include "omaha\cseries\cseries.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<float, 3>::k_element_count; // "?k_element_count@?$s_static_array@M$02@@2JB"

// public: void c_grounded_friction_component::initialize(long);
// public: void c_grounded_friction_component::update(struct s_grounded_friction_update_input *);
// public: void c_grounded_friction_component::notify_of_acceleration(union vector3d const *, struct s_grounded_friction_definition *);
// private: bool c_grounded_friction_component::find_flattest_contact_surface(float *);
// public: static long s_static_array<float, 3>::get_count(void);
// public: float & s_static_array<float, 3>::operator[]<long>(long);
// void array_index_min_and_max<class s_static_array<float, 3> >(class s_static_array<float, 3> const &, long, long *, long *);
// public: static bool s_static_array<float, 3>::valid<long>(long);
// public: float const & s_static_array<float, 3>::operator[]<long>(long) const;

void c_grounded_friction_component::initialize(long object_index)
{
    mangled_ppc("?initialize@c_grounded_friction_component@@QAAXJ@Z");

    m_grounded_ticks = 0;
    m_object_index = object_index;
    assert_tag_debug_untracked_jul_11_2011(33, m_object_index!=NONE);
};

void c_grounded_friction_component::update(s_grounded_friction_update_input * input)
{
    mangled_ppc("?update@c_grounded_friction_component@@QAAXPAUs_grounded_friction_update_input@@@Z");

    // local names are chosen for their /Od stack slot order
    object_datum * object = static_cast<object_datum *>(object_get_and_verify_type(m_object_index, NONE));
    if (input->definition)
    {
        bool on_flat = false;
        long ticks_since_havok_reset = game_time_get() - havok_last_state_reset_time_get();
        float slope;
        bool found_contact_surface = find_flattest_contact_surface(&slope);
        if (found_contact_surface && slope < input->definition->maximum_slope_for_friction * k_degrees_to_radians)
        {
            on_flat = true;
        }

        if (!on_flat)
        {
            if (ticks_since_havok_reset > 8)
            {
                m_grounded_ticks = 0;
            }
        }
        else if (m_grounded_ticks < UNSIGNED_SHORT_MAX)
        {
            m_grounded_ticks += 1;
        }

        if (m_grounded_ticks > game_seconds_to_ticks_round(input->definition->friction_over_time_domain_min))
        {
            float function_input = real_map_linear_intervals(
                input->definition->friction_over_time_domain_min,
                input->definition->friction_over_time_domain_max,
                0.0f,
                1.0f,
                game_ticks_to_seconds(static_cast<float>(m_grounded_ticks)));
            float friction = input->definition->friction_over_time.evaluate_scalar(function_input, 0.0f);
            if (!realcmp(friction, 0.0f))
            {
                vector3d translational_velocity;
                vector3d rotational_velocity;
                object_get_velocities(m_object_index, &translational_velocity, &rotational_velocity);

                vector3d mover_linear_velocity;
                vector3d early_mover_angular_velocity;
                bool has_early_mover_velocity = object_get_early_mover_local_space_velocity(m_object_index, &mover_linear_velocity, &early_mover_angular_velocity, true, false);
                if (has_early_mover_velocity)
                {
                    event_wrapped(_event_status, "item with local velocities");
                    subtract_vectors3d(&translational_velocity, &mover_linear_velocity, &translational_velocity);
                    subtract_vectors3d(&rotational_velocity, &early_mover_angular_velocity, &rotational_velocity);
                }

                vector3d result_linear_velocity;
                vector3d result_angular_velocity;
                scale_vector3d(&translational_velocity, 1.0f - friction, &result_linear_velocity);
                scale_vector3d(&rotational_velocity, 1.0f - friction, &result_angular_velocity);
                if (has_early_mover_velocity)
                {
                    add_vectors3d(&result_linear_velocity, &mover_linear_velocity, &result_linear_velocity);
                    add_vectors3d(&result_angular_velocity, &early_mover_angular_velocity, &result_angular_velocity);
                }

                if (object->object.havok_component_index != NONE)
                {
                    c_havok_component * havok_component = get_havok_component(object->object.havok_component_index);
                    long controlling_rigid_body_index = havok_component->get_object_postion_controlling_rigid_body_index();
                    if (controlling_rigid_body_index != NONE)
                    {
                        real_rectangle3d bounds;
                        if (havok_component->calculate_local_space_physics_bounding_box(controlling_rigid_body_index, &bounds))
                        {
                            s_static_array<float, 3> extents;
                            for (long axis = 0; axis <= 2; axis++)
                            {
                                extents[axis] = fabs(bounds.m[axis][1] - bounds.m[axis][0]);
                            }

                            long min_axis;
                            long max_axis;
                            array_index_min_and_max(extents, extents.get_count(), &min_axis, &max_axis);
                            if (extents[min_axis] > k_real_epsilon && extents[max_axis] / extents[min_axis] > input->definition->minimum_asymmetry_ratio_for_axis_lock)
                            {
                                real_matrix4x3 transform;
                                real_matrix4x3 inverse;
                                vector3d local_angular_velocity;
                                vector3d local_result_angular_velocity;
                                havok_component->get_rigid_body_transform(controlling_rigid_body_index, &transform);
                                matrix4x3_inverse(&transform, &inverse);
                                matrix4x3_transform_vector(&inverse, &rotational_velocity, &local_angular_velocity);
                                matrix4x3_transform_vector(&inverse, &result_angular_velocity, &local_result_angular_velocity);
                                for (long axis_index = 0; axis_index <= 2; axis_index++)
                                {
                                    if (axis_index != max_axis)
                                    {
                                        local_result_angular_velocity.n[axis_index] = local_angular_velocity.n[axis_index];
                                    }
                                }
                                matrix4x3_transform_vector(&transform, &local_result_angular_velocity, &result_angular_velocity);
                            }
                        }
                    }
                }

                if (ticks_since_havok_reset < 8)
                {
                    result_linear_velocity.k = translational_velocity.k;
                }
                object_set_velocities(m_object_index, &result_linear_velocity, &result_angular_velocity);
            }
        }
    }
};

void c_grounded_friction_component::notify_of_acceleration(vector3d const * acceleration, s_grounded_friction_definition * definition)
{
    mangled_ppc("?notify_of_acceleration@c_grounded_friction_component@@QAAXPBTvector3d@@PAUs_grounded_friction_definition@@@Z");

    if (definition && magnitude_squared3d(acceleration) > 0.040000003f)
    {
        m_grounded_ticks = 0;
    }
};

bool c_grounded_friction_component::find_flattest_contact_surface(float * slope)
{
    mangled_ppc("?find_flattest_contact_surface@c_grounded_friction_component@@AAA_NPAM@Z");

    float flattest_normal_k = k_real_min;
    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(204, slope);

    for (c_havok_contact_point_iterator iterator(m_object_index, false); iterator.valid(); iterator.next())
    {
        c_havok_contact_point * contact_point = iterator.get_contact_point();
        vector3d const * normal = contact_point->get_normal();
        if (normal->k > flattest_normal_k)
        {
            flattest_normal_k = normal->k;
            result = true;
        }
    }

    if (result)
    {
        *slope = arccosine(PIN(flattest_normal_k, 0.0f, 1.0f));
    }

    return result;
};
