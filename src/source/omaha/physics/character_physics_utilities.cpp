#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\character_physics_utilities.cpp"
/* ---------- headers */

#include "omaha\physics\character_physics_utilities.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\physics\character_physics_definitions.h"
#include "omaha\units\units.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_half_circle = k_pi;
static real k_quarter_circle = k_half_pi;

static float const k_flying_stationary_velocity = 0.5f;
static float k_flying_stationary_angular_velocity = k_degrees_to_radians * 2.0f;
static float const k_flying_stationary_throttle = 0.01f;
static float const k_flying_turning_bank_requirement = 0.3f;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool character_physics_flying_update_turning(union vector3d const *, union vector3d const *, union vector3d const *, union vector3d const *, struct s_character_physics_flying_definition const *, float, union vector3d const *, union vector3d const *, float, float *, union vector3d *, union vector3d *, union vector3d *);
// bool character_physics_flying_update_turning(long, struct s_character_physics_flying_definition const *, float, union vector3d const *, union vector3d const *, float, float *);

// $TODO nonmatching: the inline fabs ternary loads its true arm after the fsel selector (99.57%)
bool character_physics_flying_update_turning(vector3d const * forward, vector3d const * up, vector3d const * translational_velocity, vector3d const * angular_velocity, s_character_physics_flying_definition const * flying, float dt, vector3d const * desired_facing_vector, vector3d const * throttle, float turning_threshold, float * bank, vector3d * out_forward, vector3d * out_up, vector3d * out_angular_velocity)
{
    mangled_ppc("?character_physics_flying_update_turning@@YA_NPBTvector3d@@000PBUs_character_physics_flying_definition@@M00MPAMPAT1@33@Z");

    bool ignore_turning = false;
    *bank = 0.0f;
    *out_forward = *forward;
    *out_up = *up;
    *out_angular_velocity = *angular_velocity;

    assert_valid_real_vector3d_axes2(45, forward, up);
    assert_tag_debug_untracked_jul_11_2011(46, dt>0.0f);

    if (magnitude_squared3d(translational_velocity) < k_flying_stationary_velocity * k_flying_stationary_velocity
        && magnitude_squared3d(angular_velocity) < k_flying_stationary_angular_velocity * k_flying_stationary_angular_velocity
        && magnitude_squared3d(throttle) < k_flying_stationary_throttle * k_flying_stationary_throttle)
    {
        ignore_turning = dot_product3d(desired_facing_vector, forward) > turning_threshold;
    }

    vector3d final_facing_vector;
    if (ignore_turning)
    {
        final_facing_vector = *forward;
    }
    else
    {
        float pitch = flying->flying_pitch_amount * throttle->k;

        final_facing_vector = *desired_facing_vector;
        if (pitch != 0.0f)
        {
            final_facing_vector.k = final_facing_vector.k + pitch;
            if (normalize3d(&final_facing_vector) == 0.0f)
            {
                final_facing_vector = *desired_facing_vector;
            }
        }
    }

    real_rectangle2d facing_bounds;
    {
        float right_turn_amount;
        {
            vector3d right_vector;

            cross_product3d(forward, up, &right_vector);
            right_turn_amount = dot_product3d(&right_vector, desired_facing_vector) / k_flying_turning_bank_requirement;
        }

        float desired_bank = -throttle->j + throttle->i * right_turn_amount;
        desired_bank = (desired_bank > 1.5f ? 1.5f : desired_bank) * flying->flying_bank_amount;

        float apply_amount;
        if (desired_bank * *bank <= 0.0f)
        {
            apply_amount = 1.0f;
        }
        else
        {
            if (((desired_bank >= 0) ? (desired_bank) : -(desired_bank)) > k_valid_real_epsilon)
            {
                apply_amount = 1.0f - (*bank / desired_bank > 1.0f ? 1.0f : *bank / desired_bank);
            }
            else
            {
                apply_amount = 0.0f;
            }
        }

        float bank_interp_time = apply_amount * flying->flying_bank_apply_time + (1.0f - apply_amount) * flying->flying_bank_decay_time;
        if (bank_interp_time > dt)
        {
            *bank = *bank + (desired_bank - *bank) * dt / bank_interp_time;
        }
        else
        {
            *bank = desired_bank;
        }
    }

    facing_bounds.x0 = -k_half_circle;
    facing_bounds.x1 = k_half_circle;
    facing_bounds.y0 = -k_quarter_circle;
    facing_bounds.y1 = k_quarter_circle;

    if (flying->flying_angular_acceleration == 0.0f)
    {
        *out_forward = final_facing_vector;
    }
    else
    {
        unit_euler_aiming_update(
            NULL,
            0.0f,
            out_forward,
            &final_facing_vector,
            dt,
            out_angular_velocity,
            &facing_bounds,
            flying->flying_angular_velocity,
            flying->flying_angular_acceleration,
            NULL);
    }

    {
        float up_forward_dot = dot_product3d(out_forward, out_up);
        if (!realcmp(up_forward_dot, 0.0f))
        {
            vector3d component;

            scale_vector3d(out_forward, up_forward_dot, &component);
            subtract_vectors3d(out_up, &component, out_up);
            normalize3d(out_up);
        }
    }

    assert_valid_real_vector3d_axes2(159, out_forward, out_up);

    return true;
};

bool character_physics_flying_update_turning(long object_index, s_character_physics_flying_definition const * flying, float dt, vector3d const * desired_facing_vector, vector3d const * throttle, float turning_threshold, float * bank)
{
    mangled_ppc("?character_physics_flying_update_turning@@YA_NJPBUs_character_physics_flying_definition@@MPBTvector3d@@1MPAM@Z");

    object_datum * object = static_cast<object_datum *>(object_get_and_verify_type(object_index, NONE));
    bool success = false;
    vector3d new_forward;
    vector3d new_up;
    vector3d new_angular_velocity;

    success = character_physics_flying_update_turning(&object->object.forward, &object->object.up, &object->object.translational_velocity, &object->object.angular_velocity, flying, dt, desired_facing_vector, throttle, turning_threshold, bank, &new_forward, &new_up, &new_angular_velocity);
    if (success)
    {
        object->object.forward = new_forward;
        object->object.up = new_up;
        object->object.angular_velocity = new_angular_velocity;
        assert_valid_real_vector3d_axes2(198, &object->object.forward, &object->object.up);
    }

    return success;
};

