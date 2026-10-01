#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\character_physics_mode_flying.cpp"
/* ---------- headers */

#include "omaha\physics\character_physics_mode_flying.h"
#include "omaha\game\game_time.h"
#include "omaha\physics\character_physics.h"
#include "omaha\physics\character_physics_definitions.h"
#include "omaha\units\units.h"
#include "foundation\baselib\datatypes\static_string.h"
#include <math.h>
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

static real k_half_circle = k_pi;
static float const k_turning_disabled_duration = 1.5f;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_character_physics_mode_flying_datum::initialize(void);
// public: void c_character_physics_mode_flying_datum::dispose(void);
// public: void c_character_physics_mode_flying_datum::update(struct s_character_physics_update_output_datum *, struct s_character_physics_update_input_datum const *);
// public: void c_character_physics_mode_flying_datum::snap_facing(union vector3d *, union vector3d *, struct s_character_physics_update_input_datum const *);
// public: static void c_character_physics_mode_flying_datum::update_animation(struct s_character_physics_update_output_datum *, struct s_character_physics_update_input_datum const *);
// public: static void c_character_physics_mode_flying_datum::move(struct s_character_physics_move_output_datum *, struct s_character_physics_move_input_datum const *);
// public: void c_character_physics_mode_flying_datum::disable_turning(void);
// public: bool c_character_physics_mode_flying_datum::is_turning_disabled(void) const;

void c_character_physics_mode_flying_datum::initialize()
{
    mangled_ppc("?initialize@c_character_physics_mode_flying_datum@@QAAXXZ");

    m_turning_disabled_counter = 0;
    m_uprighting_angular_velocity = *global_zero_vector3d;
};

void c_character_physics_mode_flying_datum::dispose()
{
    mangled_ppc("?dispose@c_character_physics_mode_flying_datum@@QAAXXZ");
};

void c_character_physics_mode_flying_datum::update(s_character_physics_update_output_datum * physics_output, s_character_physics_update_input_datum const * physics_input)
{
    mangled_ppc("?update@c_character_physics_mode_flying_datum@@QAAXPAUs_character_physics_update_output_datum@@PBUs_character_physics_update_input_datum@@@Z");

    vector3d desired_velocity;
    vector3d desired_velocity_delta;
    vector3d delta_velocity;

    {
        vector3d up_vector;
        vector3d movement_speed;
        vector3d left_vector;

        real_vector3d_build_axes_from_forward(&physics_input->forward, &left_vector, &up_vector);
        scale_vector3d(&physics_input->desired_movement_speed, physics_input->movement_scale, &movement_speed);
        if (TEST_BIT(physics_input->character_physics_definition->flying.flying_flags, 0))
        {
            up_vector = *global_up3d;
        }
        scale_vector3d(&physics_input->forward, movement_speed.i, &desired_velocity);
        point_from_line3d(reinterpret_cast<real_point3d *>(&desired_velocity), &left_vector, movement_speed.j, reinterpret_cast<real_point3d *>(&desired_velocity));
        point_from_line3d(reinterpret_cast<real_point3d *>(&desired_velocity), &up_vector, movement_speed.k, reinterpret_cast<real_point3d *>(&desired_velocity));
    }

    subtract_vectors3d(&desired_velocity, &physics_input->velocity, &delta_velocity);

    {
        vector3d acceleration_direction = delta_velocity;
        real velocity_delta_magnitude = normalize3d(&acceleration_direction);
        real velocity_delta_maximum = game_tick_length() * physics_input->acceleration_maximum;

        if (velocity_delta_magnitude > velocity_delta_maximum)
        {
            scale_vector3d(&acceleration_direction, velocity_delta_maximum, &desired_velocity_delta);
        }
        else
        {
            desired_velocity_delta = delta_velocity;
        }
    }

    add_vectors3d(&physics_input->velocity, &desired_velocity_delta, &physics_output->new_velocity);

    m_turning_disabled_counter = MAX(m_turning_disabled_counter - 1, 0);
};

void c_character_physics_mode_flying_datum::snap_facing(vector3d * forward, vector3d * up, s_character_physics_update_input_datum const * physics_input)
{
    mangled_ppc("?snap_facing@c_character_physics_mode_flying_datum@@QAAXPATvector3d@@0PBUs_character_physics_update_input_datum@@@Z");

    if (is_turning_disabled())
    {
        *up = physics_input->up;
        *forward = physics_input->forward;

        real_rectangle2d facing_bounds = { -k_half_circle, k_half_circle, -k_half_circle, k_half_circle };
        static real k_facing_bound = k_pi;

        unit_euler_aiming_update(
            NULL,
            0.0f,
            up,
            global_up3d,
            game_tick_length(),
            &m_uprighting_angular_velocity,
            &facing_bounds,
            physics_input->character_physics_definition->flying.flying_angular_velocity,
            physics_input->character_physics_definition->flying.flying_angular_acceleration,
            NULL);

        {
            vector3d axis = m_uprighting_angular_velocity;
            real angle = normalize3d(&axis) * game_tick_length();
            real cosine_angle = cosine(angle);
            real sine_angle = sine(angle);
            vector3d forward_up_component;

            rotate_vector_about_axis(up, &axis, sine_angle, cosine_angle);

            scale_vector3d(up, dot_product3d(up, forward), &forward_up_component);
            subtract_vectors3d(forward, &forward_up_component, forward);

            if (normalize3d(forward) == 0.0f)
            {
                *up = *global_up3d;
                *forward = *global_forward3d;
            }

            if (angle == 0.0f)
            {
                m_turning_disabled_counter = 0;
            }
        }
    }
    else
    {
        assert_valid_real_normal3d(136, forward);

        vector3d new_right;
        vector3d new_up;

        cross_product3d(forward, global_up3d, &new_right);
        cross_product3d(&new_right, forward, &new_up);

        if (normalize3d(&new_up) == 0.0f)
        {
            new_up = *global_forward3d;
            new_right = *global_left3d;
        }

        {
            real bank_cosine = cosine(physics_input->flying.bank);
            real bank_sine = sine(physics_input->flying.bank);

            scale_vector3d(&new_up, bank_cosine, &new_up);
            normalize3d(&new_right);
            point_from_line3d(reinterpret_cast<real_point3d const *>(&new_up), &new_right, bank_sine, reinterpret_cast<real_point3d *>(up));
        }

        normalize3d(forward);

        {
            vector3d up_forward_component;

            scale_vector3d(forward, dot_product3d(forward, up), &up_forward_component);
            subtract_vectors3d(up, &up_forward_component, up);
        }

        normalize3d(up);
    }

    assert_valid_real_vector3d_axes2(170, forward, up);
};

void c_character_physics_mode_flying_datum::update_animation(s_character_physics_update_output_datum * character_physics_update_output_datum, s_character_physics_update_input_datum const * character_physics_update_input_datum)
{
    mangled_ppc("?update_animation@c_character_physics_mode_flying_datum@@SAXPAUs_character_physics_update_output_datum@@PBUs_character_physics_update_input_datum@@@Z");

    character_physics_update_output_datum->animation_state = s_character_physics_update_output_datum::_state_idle;
    if (fabs(character_physics_update_input_datum->throttle.i) < fabs(character_physics_update_input_datum->throttle.j))
    {
        if (character_physics_update_input_datum->throttle.j < -k_real_epsilon)
        {
            character_physics_update_output_datum->animation_state = s_character_physics_update_output_datum::_state_move_right;
        }
        else if (character_physics_update_input_datum->throttle.j > k_real_epsilon)
        {
            character_physics_update_output_datum->animation_state = s_character_physics_update_output_datum::_state_move_left;
        }
    }
    else
    {
        if (character_physics_update_input_datum->throttle.i < -k_real_epsilon)
        {
            character_physics_update_output_datum->animation_state = s_character_physics_update_output_datum::_state_move_back;
        }
        else if (character_physics_update_input_datum->throttle.i > k_real_epsilon)
        {
            character_physics_update_output_datum->animation_state = s_character_physics_update_output_datum::_state_move_front;
        }
    }
};

void c_character_physics_mode_flying_datum::move(s_character_physics_move_output_datum * character_physics_move_output_datum, s_character_physics_move_input_datum const * character_physics_move_input_datum)
{
    mangled_ppc("?move@c_character_physics_mode_flying_datum@@SAXPAUs_character_physics_move_output_datum@@PBUs_character_physics_move_input_datum@@@Z");
};

void c_character_physics_mode_flying_datum::disable_turning()
{
    mangled_ppc("?disable_turning@c_character_physics_mode_flying_datum@@QAAXXZ");

    m_turning_disabled_counter = game_seconds_to_ticks_round(k_turning_disabled_duration);
    m_uprighting_angular_velocity = *global_zero_vector3d;
    assert_tag_debug_untracked_jul_11_2011(220, m_turning_disabled_counter>=1);
};

bool c_character_physics_mode_flying_datum::is_turning_disabled() const
{
    mangled_ppc("?is_turning_disabled@c_character_physics_mode_flying_datum@@QBA_NXZ");

    return m_turning_disabled_counter > 0;
};

