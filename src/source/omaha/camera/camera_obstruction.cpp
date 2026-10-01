#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\camera_obstruction.cpp"
/* ---------- headers */

#include "omaha\camera\camera_obstruction.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\color_math.h"
#include "omaha\math\real_math.h"
#include "omaha\physics\collisions.h"
#include "omaha\render\render_debug.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void camera_obstruction_update_internal(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float * out_t, float * out_safe_t);
bool obstruction_test_with_t(s_collision_test_flags const * flags, real_point3d const * point0, real_point3d const * point1, long first_ignore_object_index, long second_ignore_object_index, float * t, real_point3d * point);
bool observer_collision_test_differential(s_collision_test_flags const * flags, real_point3d const * point0, real_point3d const * point1, vector3d const * offset, float scale, float fraction, long first_ignore_object_index, long second_ignore_object_index, float * t, real_point3d * point);
void camera_obstruction_update_position_linear_acceleration(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, float desired_t);
void camera_obstruction_update_position_linear_spring(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, float desired_t, float inward_spring_constant, float outward_spring_constant);
void camera_obstruction_update_postprocess(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float safe_t);

/* ---------- globals */

float observer_collision_speed_scale = 1.0f;
bool observer_collision_debug = false;

static real k_cosine60 = k_sine30;
static real k_sine60 = k_cosine30;
static c_static_string<256> observer_debug_string;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float observer_collision_speed_scale; // "?observer_collision_speed_scale@@3MA"
// struct s_tag_struct_definition camera_obstruction_struct; // "?camera_obstruction_struct@@3Us_tag_struct_definition@@A"
// bool observer_collision_debug; // "?observer_collision_debug@@3_NA"

// void camera_obstruction_update(float, struct s_collision_test_flags const *, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, union real_point3d const *, union real_point3d const *);
// void camera_obstruction_update_spring(float, struct s_collision_test_flags const *, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, union real_point3d const *, union real_point3d const *, float, float);
// public: void s_camera_obstruction_state::initialize(void);
// void camera_obstruction_update_internal(float, struct s_collision_test_flags const *, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, union real_point3d const *, union real_point3d const *, float *, float *);
// bool obstruction_test_with_t(struct s_collision_test_flags const *, union real_point3d const *, union real_point3d const *, long, long, float *, union real_point3d *);
// bool observer_collision_test_differential(struct s_collision_test_flags const *, union real_point3d const *, union real_point3d const *, union vector3d const *, float, float, long, long, float *, union real_point3d *);
// void camera_obstruction_update_position_linear_acceleration(float, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, float);
// void camera_obstruction_update_position_linear_spring(float, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, float, float, float);
// void camera_obstruction_update_postprocess(float, struct s_camera_obstruction_parameters const *, struct s_camera_obstruction_state *, union real_point3d const *, union real_point3d const *, float);

void camera_obstruction_update(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point)
{
    mangled_ppc("?camera_obstruction_update@@YAXMPBUs_collision_test_flags@@PBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@PBTreal_point3d@@3@Z");

    float t = 1.0f;
    float safe_t = 1.0f;

    observer_debug_string.clear();
    camera_obstruction_update_internal(dt, flags, parameters, state, focus_point, camera_point, &t, &safe_t);
    camera_obstruction_update_position_linear_acceleration(dt, parameters, state, t);
    camera_obstruction_update_postprocess(dt, parameters, state, focus_point, camera_point, safe_t);
};

void camera_obstruction_update_spring(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float inward_spring_constant, float outward_spring_constant)
{
    mangled_ppc("?camera_obstruction_update_spring@@YAXMPBUs_collision_test_flags@@PBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@PBTreal_point3d@@3MM@Z");

    float t = 0.0f;
    float safe_t = 0.0f;

    observer_debug_string.clear();
    camera_obstruction_update_internal(dt, flags, parameters, state, focus_point, camera_point, &t, &safe_t);
    camera_obstruction_update_position_linear_spring(dt, parameters, state, t, inward_spring_constant, outward_spring_constant);
    camera_obstruction_update_postprocess(dt, parameters, state, focus_point, camera_point, safe_t);
};

void s_camera_obstruction_state::initialize()
{
    mangled_ppc("?initialize@s_camera_obstruction_state@@QAAXXZ");

    t = 1.0f;
    velocity = 0.0f;
    first_ignore_object_index = NONE;
    second_ignore_object_index = NONE;
};

void camera_obstruction_update_internal(float dt, s_collision_test_flags const * flags, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float * out_t, float * out_safe_t)
{
    mangled_ppc("?camera_obstruction_update_internal@@YAXMPBUs_collision_test_flags@@PBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@PBTreal_point3d@@3PAM4@Z");

    dt *= observer_collision_speed_scale;

    vector3d line_vector;
    vector_from_points3d(focus_point, camera_point, &line_vector);
    vector3d forward = line_vector;
    float length = normalize3d(&forward);
    if (length > k_real_epsilon)
    {
        float safe_t = 1.0f;
        real_point3d obstruction_point;
        obstruction_test_with_t(flags, focus_point, camera_point, state->first_ignore_object_index, state->second_ignore_object_index, &safe_t, &obstruction_point);
        float minimum_t = safe_t;
        float sine_angle = sine(parameters->obstruction_test_angle);
        float radius = sine_angle * length;
        vector3d up;
        generate_up_vector3d(&forward, &up);
        vector3d offsets[3];
        scale_vector3d(&up, radius, &offsets[0]);
        offsets[1] = offsets[0];
        offsets[2] = offsets[0];
        rotate_vector_about_axis(&offsets[1], &forward, k_sine60, k_cosine60);
        rotate_vector_about_axis(&offsets[2], &forward, k_sine60, -k_cosine60);
        for (short index = 0; index < 6; index++)
        {
            float direction = (index & 1) ? -1.0f : 1.0f;
            real_point3d point;
            float t;
            if (observer_collision_test_differential(flags, focus_point, camera_point, &offsets[index / 2], direction, parameters->cylinder_fraction, state->first_ignore_object_index, state->second_ignore_object_index, &t, &point) && t < minimum_t)
            {
                minimum_t = t;
                obstruction_point = point;
            }
        }

        if (observer_collision_debug)
        {
            observer_debug_string.append_print("safe t: %1.2f|nminimum_t: %1.2f|n", safe_t, minimum_t);
        }

        if (state->remembered_point_valid)
        {
            vector3d remembered_vector;
            vector_from_points3d(focus_point, &state->remembered_point, &remembered_vector);
            float remembered_t = realcmp(length, 0.0f) ? 0.0f : dot_product3d(&remembered_vector, &forward) / length;
            if (remembered_t < 0.0f || remembered_t > 1.0f)
            {
                state->remembered_point_valid = false;
            }
            else
            {
                float remembered_radius = interpolate_linear(parameters->cylinder_fraction * radius, radius, remembered_t);
                float distance_squared = point_to_line_distance_squared3d(&state->remembered_point, focus_point, &line_vector, NULL);
                if (distance_squared <= remembered_radius * remembered_radius + k_real_epsilon)
                {
                    if (magnitude_squared3d(&remembered_vector) <= distance_squared3d(focus_point, &obstruction_point) + k_real_epsilon)
                    {
                        minimum_t = remembered_t;
                        obstruction_point = state->remembered_point;
                    }
                    else
                    {
                        state->remembered_point_valid = false;
                    }
                }
                else
                {
                    state->remembered_point_valid = false;
                }

                if (observer_collision_debug)
                {
                    observer_debug_string.append_print("remembered t: %1.2f|n", remembered_t);
                }
            }
        }

        if (!state->remembered_point_valid && minimum_t < 1.0f)
        {
            state->remembered_point_valid = true;
            state->remembered_point = obstruction_point;
        }

        if (observer_collision_debug)
        {
            render_debug_point(false, &state->remembered_point, 0.25f, state->remembered_point_valid ? global_real_argb_red : global_real_argb_black);
        }

        *out_t = minimum_t;
        *out_safe_t = safe_t;
    }
};

bool obstruction_test_with_t(s_collision_test_flags const * flags, real_point3d const * point0, real_point3d const * point1, long first_ignore_object_index, long second_ignore_object_index, float * t, real_point3d * point)
{
    mangled_ppc("?obstruction_test_with_t@@YA_NPBUs_collision_test_flags@@PBTreal_point3d@@1JJPAMPAT2@@Z");

    collision_result collision;
    bool result = false;

    if (observer_collision_debug)
    {
        render_debug_line(false, point0, point1, global_real_argb_red);
    }

    *point = *point1;
    if (distance_squared3d(point0, point1) > k_valid_real_epsilon * k_valid_real_epsilon && collision_test_line(*flags, point0, point1, first_ignore_object_index, second_ignore_object_index, &collision))
    {
        *t = collision.t;
        *point = collision.point;
        result = true;
    }

    return result;
};

bool observer_collision_test_differential(s_collision_test_flags const * flags, real_point3d const * point0, real_point3d const * point1, vector3d const * offset, float scale, float fraction, long first_ignore_object_index, long second_ignore_object_index, float * t, real_point3d * point)
{
    mangled_ppc("?observer_collision_test_differential@@YA_NPBUs_collision_test_flags@@PBTreal_point3d@@1PBTvector3d@@MMJJPAMPAT2@@Z");

    real_point3d test_point0;
    real_point3d test_point1;

    point_from_line3d(point0, offset, scale * fraction, &test_point0);
    point_from_line3d(point1, offset, scale, &test_point1);

    return obstruction_test_with_t(flags, &test_point0, &test_point1, first_ignore_object_index, second_ignore_object_index, t, point);
};

void camera_obstruction_update_position_linear_acceleration(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, float desired_t)
{
    mangled_ppc("?camera_obstruction_update_position_linear_acceleration@@YAXMPBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@M@Z");

    if (dt == 0.0f)
    {
        state->t = desired_t;
    }
    else
    {
        float maximum_acceleration = real_max(parameters->obstruction_max_inward_acceleration, parameters->obstruction_max_outward_acceleration);
        float acceleration;
        if (state->t < desired_t)
        {
            if (state->velocity < 0.0f)
            {
                acceleration = maximum_acceleration;
            }
            else
            {
                acceleration = parameters->obstruction_max_outward_acceleration;
            }

            float minimum_delta = 0.05f;
            if (desired_t - state->t < minimum_delta)
            {
            }
            else if (state->return_delay_timer <= 0.0f)
            {
                state->return_delay_timer = 0.0f;
            }
            else
            {
                state->return_delay_timer -= dt;
                acceleration = 0.0f;
                state->velocity = 0.0f;
            }
        }
        else
        {
            if (state->velocity > 0.0f)
            {
                acceleration = maximum_acceleration;
            }
            else
            {
                acceleration = parameters->obstruction_max_inward_acceleration;
            }
            state->return_delay_timer = parameters->obstruction_return_delay;
        }

        if (observer_collision_debug)
        {
            observer_debug_string.append_print("velocity: %2.1f|naccel: %2.1f|n", state->velocity, acceleration);
        }

        accelerate_to_position(&state->t, &state->velocity, desired_t, dt, acceleration, parameters->obstruction_max_velocity, 0.0f, 1.0f, false);
    }
};

void camera_obstruction_update_position_linear_spring(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, float desired_t, float inward_spring_constant, float outward_spring_constant)
{
    mangled_ppc("?camera_obstruction_update_position_linear_spring@@YAXMPBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@MMM@Z");

    if (dt == 0.0f)
    {
        state->t = desired_t;
    }
    else
    {
        float spring_constant = inward_spring_constant;
        if (state->t < desired_t)
        {
            if (state->velocity < 0.0f)
            {
            }
            else
            {
                spring_constant = outward_spring_constant;
            }

            float minimum_delta = 0.05f;
            if (desired_t - state->t < minimum_delta)
            {
            }
            else if (state->return_delay_timer <= 0.0f)
            {
                state->return_delay_timer = 0.0f;
            }
            else
            {
                state->return_delay_timer -= dt;
                spring_constant = 0.0f;
                state->velocity = 0.0f;
            }
        }
        else
        {
            state->return_delay_timer = parameters->obstruction_return_delay;
        }

        float damping_constant = 2.0f * sqrtf(spring_constant);
        update_spring_system(&state->t, &state->velocity, desired_t, spring_constant, damping_constant, dt);
    }
};

void camera_obstruction_update_postprocess(float dt, s_camera_obstruction_parameters const * parameters, s_camera_obstruction_state * state, real_point3d const * focus_point, real_point3d const * camera_point, float safe_t)
{
    mangled_ppc("?camera_obstruction_update_postprocess@@YAXMPBUs_camera_obstruction_parameters@@PAUs_camera_obstruction_state@@PBTreal_point3d@@2M@Z");

    if (safe_t < state->t)
    {
        state->t = safe_t;
        state->return_delay_timer = parameters->obstruction_return_delay;
        state->velocity = 0.0f;
    }

    if (observer_collision_debug)
    {
        vector3d vector;
        real_point3d point;
        vector_from_points3d(focus_point, camera_point, &vector);
        point_from_line3d(focus_point, &vector, state->t, &point);
        render_debug_point(false, &point, 0.25f, global_real_argb_cyan);
    }

    if (observer_collision_debug)
    {
        observer_debug_string.append_print("result t: %1.2f|n", state->t);
    }

    if (observer_collision_debug)
    {
        render_debug_string_at_point(focus_point, observer_debug_string, global_real_argb_cyan);
    }
};
