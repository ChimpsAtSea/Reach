/* ---------- headers */

#include "blamlib\boat_engine.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_time.h"
#include "omaha\math\color_math.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\physics\boat_engine_definitions.h"
#include "omaha\physics\water_physics.h"
#include "omaha\render\render_debug.h"
#include "omaha\render\render_objects_static_lighting.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\units.h"
#include "omaha\units\vehicle_definitions.h"
#include "omaha\units\vehicles.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_quarter_circle = k_half_pi;

// only referenced by boat_engine_update (.data, 1.0f); name unknown
static real g_boat_engine_steering_scale = 1.0f;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void boat_engine_update(long, float, float, float, struct matrix3x3const *, union real_point3d const *, struct real_matrix4x3const *, struct s_boat_engine_definition const *, float *);
// public: bool c_flags_no_init<enum s_boat_engine_definition::e_boat_flags, unsigned char, 1, struct s_default_enum_string_resolver>::test(enum s_boat_engine_definition::e_boat_flags) const;
// public: static bool c_flags_no_init<enum s_boat_engine_definition::e_boat_flags, unsigned char, 1, struct s_default_enum_string_resolver>::valid_bit(enum s_boat_engine_definition::e_boat_flags);
// private: static unsigned char c_flags_no_init<enum s_boat_engine_definition::e_boat_flags, unsigned char, 1, struct s_default_enum_string_resolver>::flag_size_type(enum s_boat_engine_definition::e_boat_flags);

void boat_engine_update(long vehicle_index, real steering, real mass, real throttle, matrix3x3 const * inertia_tensor, real_point3d const * center_of_mass, real_matrix4x3 const * matrix, s_boat_engine_definition const * definition, real * propeller_out_of_water_fraction)
{
    mangled_ppc("?boat_engine_update@@YAXJMMMPBUmatrix3x3@@PBTreal_point3d@@PBUreal_matrix4x3@@PBUs_boat_engine_definition@@PAM@Z");

    vehicle_datum * vehicle = static_cast<vehicle_datum *>(object_get_and_verify_type(vehicle_index, _object_mask_vehicle));
    vehicle_definition const * vehicle_tag = static_cast<vehicle_definition const *>(tag_get(VEHICLE_DEFINITION_TAG, vehicle->definition_index));
    real tick_length = game_tick_length();

    real boost_scale = 1.0f;
    *propeller_out_of_water_fraction = 1.0f;
    if (vehicle->flags.test(_vehicle_boosting_bit))
    {
        boost_scale = 1.0f + unit_compute_boost_fraction(vehicle_index) * (vehicle_tag->unit.boost.boost_peak_power - 1.0f);
    }

    object_marker propeller_marker;
    object_get_markers_by_string_id(vehicle_index, definition->propeller_marker_name, &propeller_marker, 1);

    steering = PIN(steering, -k_quarter_circle, k_quarter_circle);
    steering *= g_boat_engine_steering_scale;

    vector3d propeller_forward = propeller_marker.matrix.forward;
    real_point3d propeller_position = propeller_marker.matrix.position;
    rotate_vector_about_axis(&propeller_forward, &matrix->up, sine(-steering), cosine(-steering));
    normalize3d(&propeller_forward);
    negate_vector3d(&propeller_forward, &propeller_forward);

    real thrust_scale = boost_scale;
    if (boost_scale > 1.0f)
    {
        throttle = 1.0f;
    }

    s_water_physics_test_vector_result water_result;
    vector3d propeller_vector;
    scale_vector3d(&matrix->up, -definition->propeller_radius, &propeller_vector);
    if (water_physics_test_vector_solid(&propeller_marker.matrix.position, &propeller_vector, &water_result))
    {
        *propeller_out_of_water_fraction = water_result.t;
    }

    if (vehicle_tag->vehicle.havok_vehicle_physics.boat_physics.ground_vertical_extrusion > 0.0f)
    {
        vector3d down;
        scale_vector3d(&matrix->up, -1.0f, &down);

        real_point3d extrusion_point;
        point_from_line3d(&propeller_marker.matrix.position, &matrix->up, -0.5f * definition->propeller_radius, &extrusion_point);

        real depth;
        if (water_physics_test_extruded_water(vehicle_index, vehicle_tag->vehicle.havok_vehicle_physics.boat_physics.ground_vertical_extrusion, &extrusion_point, &down, 0.5f * definition->propeller_radius, &depth))
        {
            *propeller_out_of_water_fraction = CEILING(*propeller_out_of_water_fraction, 1.0f - depth);
        }
    }

    thrust_scale *= interpolate_linear(1.0f, definition->out_of_water_thrust_scale, *propeller_out_of_water_fraction);

    if (debug_objects && debug_objects_vehicle_physics)
    {
        real_point3d water_point;
        point_from_line3d(&propeller_marker.matrix.position, &propeller_vector, *propeller_out_of_water_fraction, &water_point);
        render_debug_vector(false, &propeller_marker.matrix.position, &propeller_vector, 1.0f, global_real_argb_cyan);
        render_debug_point(false, &water_point, 0.5f, *propeller_out_of_water_fraction == 1.0f ? global_real_argb_grey : global_real_argb_blue);
    }

    throttle *= thrust_scale;

    vector3d linear_velocity;
    vector3d angular_velocity;
    vector3d local_linear_velocity;
    vector3d local_angular_velocity;
    object_get_localized_velocities(vehicle_index, &linear_velocity, &angular_velocity, &local_linear_velocity, &local_angular_velocity);

    if (!definition->flags.test(s_boat_engine_definition::_boat_uses_fake_physics_bit))
    {
        vector3d force;
        scale_vector3d(&propeller_forward, definition->linear_acceleration * tick_length * throttle * mass, &force);
        propeller_forward.k = -fabs(propeller_forward.k);

        if (mass > k_real_epsilon)
        {
            real inverse_mass = 1.0f / mass;
            vector3d inverse_inertia;
            set_real_vector3d(&inverse_inertia, 1.0f / inertia_tensor->n[0][0], 1.0f / inertia_tensor->n[1][1], 1.0f / inertia_tensor->n[2][2]);
            point_from_line3d(reinterpret_cast<real_point3d *>(&linear_velocity), &force, inverse_mass, reinterpret_cast<real_point3d *>(&linear_velocity));

            vector3d lever_arm;
            vector_from_points3d(center_of_mass, &propeller_position, &lever_arm);

            vector3d torque;
            cross_product3d(&lever_arm, &force, &torque);

            vector3d local_torque;
            matrix4x3_inverse_transform_vector(matrix, &torque, &local_torque);
            multiply_vectors3d(&inverse_inertia, &local_torque, &local_torque);

            vector3d angular_acceleration;
            matrix4x3_transform_vector(matrix, &local_torque, &angular_acceleration);
            point_from_line3d(reinterpret_cast<real_point3d *>(&angular_velocity), &angular_acceleration, 1.0f, reinterpret_cast<real_point3d *>(&angular_velocity));
        }

        if (debug_objects && debug_objects_vehicle_physics)
        {
            render_debug_vector(false, &propeller_marker.matrix.position, &propeller_forward, -3.0f, global_real_argb_blue);
        }
    }
    else
    {
        real linear_acceleration = throttle >= 0.0f ? definition->linear_acceleration : definition->reverse_linear_acceleration;
        point_from_line3d(reinterpret_cast<real_point3d *>(&linear_velocity), &matrix->forward, throttle * linear_acceleration * tick_length, reinterpret_cast<real_point3d *>(&linear_velocity));

        real angular_acceleration = steering * definition->angular_acceleration * interpolate_linear(1.0f, definition->out_of_water_torque_scale, *propeller_out_of_water_fraction);
        point_from_line3d(reinterpret_cast<real_point3d *>(&angular_velocity), &matrix->up, throttle * angular_acceleration * tick_length, reinterpret_cast<real_point3d *>(&angular_velocity));
        point_from_line3d(reinterpret_cast<real_point3d *>(&angular_velocity), &matrix->left, (1.0f - *propeller_out_of_water_fraction) * -fabs(throttle) * linear_acceleration * tick_length * definition->propeller_torque_scale, reinterpret_cast<real_point3d *>(&angular_velocity));

        if (debug_objects && debug_objects_vehicle_physics)
        {
            render_debug_vector(false, &propeller_marker.matrix.position, &propeller_marker.matrix.forward, throttle * linear_acceleration * tick_length, global_real_argb_blue);
        }
    }

    if (definition->drag_input_range_velocity != 0.0f)
    {
        c_function_definition const * drag_function = boost_scale > 1.0f ? &definition->boost_drag : &definition->normal_drag;
        vector3d velocity_direction = linear_velocity;
        real speed = normalize3d(&velocity_direction);
        real drag_input = PIN(speed / definition->drag_input_range_velocity, 0.0f, 1.0f);
        if (speed != 0.0f)
        {
            real water_drag = drag_function->evaluate_scalar(drag_input, 0.0f);
            real air_drag = definition->air_drag.evaluate_scalar(drag_input, 0.0f);
            real drag = interpolate_linear(water_drag, air_drag, *propeller_out_of_water_fraction);
            drag *= tick_length;
            drag = MIN(drag, speed);

            if (debug_objects && debug_objects_vehicle_physics)
            {
                real_point3d drag_point = matrix->position;
                c_static_string<32> drag_string;
                drag_string.print("%2.1f", drag / speed * 100.0f);
                point_from_line3d(&drag_point, &velocity_direction, speed - drag, &drag_point);
                render_debug_vector(false, &matrix->position, &linear_velocity, 1.0f, global_real_argb_red);
                render_debug_point(false, &drag_point, 0.5f, global_real_argb_red);
                render_debug_string_at_point(&drag_point, drag_string.get_string(), global_real_argb_red);
            }

            point_from_line3d(reinterpret_cast<real_point3d *>(&linear_velocity), &velocity_direction, -drag, reinterpret_cast<real_point3d *>(&linear_velocity));
        }
    }

    if (*propeller_out_of_water_fraction > 0.5f && definition->stabilization_angular_acceleration > 0.0f)
    {
        vector3d up = matrix->up;
        vector3d desired_up = *global_up3d;
        vector3d pitch_axis = matrix->forward;
        pitch_axis.k = 0.0f;
        if (normalize3d(&pitch_axis) != 0.0f)
        {
            cross_product3d(&pitch_axis, global_up3d, &pitch_axis);
            rotate_vector_about_axis(&desired_up, &pitch_axis, sine(definition->stabilization_desired_inclination), cosine(definition->stabilization_desired_inclination));
            angular_accelerate_to_position(&up, &desired_up, game_tick_length(), &angular_velocity, 100.0f, *propeller_out_of_water_fraction * definition->stabilization_angular_acceleration, false);
        }
    }

    add_vectors3d(&linear_velocity, &local_linear_velocity, &linear_velocity);
    add_vectors3d(&angular_velocity, &local_angular_velocity, &angular_velocity);
    object_set_velocities(vehicle_index, &linear_velocity, &angular_velocity);
};
