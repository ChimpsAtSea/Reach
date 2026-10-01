#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\dead_camera.cpp"
/* ---------- headers */

#include "omaha\camera\dead_camera.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\camera\camera_globals.h"
#include "omaha\camera\observer.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\player_mapping.h"
#include "omaha\game\players.h"
#include "omaha\math\random_math.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\units\bipeds.h"
#include "omaha\units\units.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_full_circle = k_2pi;
static real k_quarter_circle = k_half_pi;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_dead_camera::c_dead_camera(void);
// public: virtual enum e_camera_mode c_dead_camera::get_type(void) const;
// public: virtual enum e_director_perspective c_dead_camera::get_perspective(void) const;
// public: c_dead_camera::c_dead_camera(enum e_output_user_index);
// public: virtual void c_dead_camera::set_target(long);
// public: virtual void c_dead_camera::update(enum e_output_user_index, float, struct s_observer_command *);
// public: virtual void c_dead_camera::handle_deleted_player(long);
// public: virtual void c_dead_camera::handle_deleted_object(long);
// private: long c_dead_camera::get_target_unit_index(void);
// private: long c_dead_camera::get_target_player_index(void);
// private: bool c_dead_camera::get_killer_position(union real_point3d *);

c_dead_camera::c_dead_camera()
{
    mangled_ppc("??0c_dead_camera@@QAA@XZ");
};

// get_type and get_perspective are inline in dead_camera.h

c_dead_camera::c_dead_camera(e_output_user_index output_user_index)
{
    mangled_ppc("??0c_dead_camera@@QAA@W4e_output_user_index@@@Z");

    m_output_user_index = output_user_index;
    m_player_index = player_mapping_get_player_by_output_user(output_user_index);
    if (m_player_index != NONE)
    {
        long unit_index = player_get_unit_index_even_if_dead(m_player_index);
        if (unit_index != NONE)
        {
            set_target(unit_index);
        }
    }
};

// $TODO nonmatching: only the TLS slot offset of player_data differs (target li 0x204 is the linked .tls offset; ours is the unlinked 0)
void c_dead_camera::set_target(long object_index)
{
    mangled_ppc("?set_target@c_dead_camera@@UAAXJ@Z");

    c_camera::set_target(object_index);
    m_field_of_view = observer_suggested_field_of_view();
    m_distance = g_camera_globals.dead_camera_final_distance;
    m_timer = 0.0f;
    m_unit_fell_to_death = false;
    if (m_target_object_index != NONE)
    {
        object_datum * target_object = static_cast<object_datum *>(object_get(m_target_object_index));
        euler_angles2d_from_vector3d(&m_orientation, &target_object->object.forward);
        m_orientation.pitch = -0.4 * k_quarter_circle;
    }
    else
    {
        m_orientation.yaw = _real_random_range(get_local_random_seed_address(), NULL, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 67, 0.0f, k_full_circle);
        m_orientation.pitch = -_real_random_range(get_local_random_seed_address(), NULL, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 68, 0.3f * k_quarter_circle, 0.7f * k_quarter_circle);
    }

    m_killer_object_index = NONE;
    if (m_target_object_index != NONE && game_is_multiplayer() && TEST_BIT(_object_mask_unit, object_get_type(m_target_object_index)))
    {
        unit_datum * unit = static_cast<unit_datum *>(object_get_and_verify_type(m_target_object_index, _object_mask_unit));
        long killer_player_index = NONE;
        if (unit->last_player_index != NONE)
        {
            player_datum * player = static_cast<player_datum *>(datum_try_and_get(player_data, unit->last_player_index));
            if (player && player->__unknown490 != NONE)
            {
                killer_player_index = player->__unknown490;
            }
        }

        long best_attacker_index = 0;
        for (long attacker_index = 1; attacker_index < static_cast<long>(NUMBEROF(unit->attackers)); attacker_index++)
        {
            if (unit->attackers[attacker_index].damage_inflicted > unit->attackers[best_attacker_index].damage_inflicted)
            {
                best_attacker_index = attacker_index;
            }
        }

        if (killer_player_index == NONE)
        {
            killer_player_index = unit->attackers[best_attacker_index].damage_owner_player_index;
        }

        player_datum * killer_player = static_cast<player_datum *>(datum_try_and_get(player_data, killer_player_index));
        if (killer_player)
        {
            m_killer_object_index = killer_player->unit_index;
        }
        else
        {
            long damage_owner_object_index = unit->attackers[best_attacker_index].damage_owner_object_index;
            if (object_try_and_get_and_verify_type(damage_owner_object_index, NONE))
            {
                m_killer_object_index = damage_owner_object_index;
            }
        }
    }
};

void c_dead_camera::update(e_output_user_index output_user_index, float dt, s_observer_command * result)
{
    mangled_ppc("?update@c_dead_camera@@UAAXW4e_output_user_index@@MPAUs_observer_command@@@Z");

    if (m_target_object_index != NONE)
    {
        if (object_get_type(m_target_object_index) == _object_type_biped)
        {
            real sphere_radius;
            real_point3d sphere_center;

            if (!m_unit_fell_to_death && static_cast<biped_datum *>(object_get_and_verify_type(m_target_object_index, _object_mask_biped))->flags.test(_biped_falling_to_his_death_bit))
            {
                m_unit_fell_to_death = true;
                m_falling_camera_position = observer_get_camera(m_output_user_index)->position;
            }

            object_get_bounding_sphere(m_target_object_index, &sphere_center, &sphere_radius);
            object_get_interpolated_version_of_world_space_position(m_target_object_index, &sphere_center, &result->focus_position);
            if (m_unit_fell_to_death)
            {
                result->focus_position = m_falling_camera_position;
                vector_from_points3d(&m_falling_camera_position, &sphere_center, &result->forward);
                normalize3d_with_default(&result->forward, global_down3d);
                generate_up_vector3d(&result->forward, &result->up);
                result->horizontal_field_of_view = m_field_of_view;
                object_get_velocities(m_target_object_index, &result->focus_velocity, NULL);
                result->flags = FLAG(_observer_command_valid_bit);
                result->timer = FLOOR(g_camera_globals.dead_camera_transition_time - m_timer, 0.0f);
            }
            else
            {
                real_point3d killer_position;

                result->focus_distance = m_distance;
                result->focus_position.z += g_camera_globals.dead_camera_z_offset;
                if (get_killer_position(&killer_position))
                {
                    vector_from_points3d(&result->focus_position, &killer_position, &result->forward);
                    euler_angles2d_from_vector3d(&m_orientation, &result->forward);
                    m_orientation.pitch = MAX(-g_camera_globals.dead_camera_maximum_elevation, m_orientation.pitch);
                }
                vector3d_from_euler_angles2d(&result->forward, &m_orientation);
                generate_up_vector3d(&result->forward, &result->up);
                result->focus_distance = m_distance;
                if (game_is_lost())
                {
                    float const k_dead_cam_drift_per_second_start = 0.9f;
                    float const k_dead_cam_drift_per_second_end = 0.25f;
                    float const k_dead_cam_drift_time = 6.0f;
                    float const k_dead_cam_drift_max_distance = g_camera_globals.dead_camera_final_distance * 5.0f;
                    float dead_cam_drift_t = MIN(m_timer / k_dead_cam_drift_time, 1.0f);

                    dead_cam_drift_t = pow(dead_cam_drift_t, 0.5f);
                    m_distance += (dead_cam_drift_t * k_dead_cam_drift_per_second_end + (1.0f - dead_cam_drift_t) * k_dead_cam_drift_per_second_start) * dt;
                    m_distance = m_distance > k_dead_cam_drift_max_distance ? k_dead_cam_drift_max_distance : m_distance;
                }
                result->horizontal_field_of_view = m_field_of_view;
                result->focus_offset = *global_zero_vector3d;
                result->focus_velocity = *global_zero_vector3d;
                result->flags = FLAG(_observer_command_valid_bit);
                result->timer = MAX(g_camera_globals.dead_camera_movement_delay, g_camera_globals.dead_camera_transition_time - m_timer);
                result->parameter_timers[_observer_focus_position] = 0.0f;
                result->parameter_flags[_observer_focus_position] = FLAG(_observer_time_valid_bit) | FLAG(_observer_time_force_bit);
                if (m_timer == 0.0f)
                {
                    result->focus_distance = g_camera_globals.dead_camera_initial_distance;
                    result->parameter_timers[_observer_focus_distance] = 0.0f;
                    result->parameter_flags[_observer_focus_distance] = FLAG(_observer_time_valid_bit) | FLAG(_observer_time_force_bit);
                }
            }
        }

        object_get_center_of_mass(object_get_ultimate_parent(m_target_object_index), &result->safe_position);
        SET_BIT(result->flags, _observer_command_has_safe_position_bit, true);
    }

    m_timer += dt;
    observer_validate_camera_command(result);
};

void c_dead_camera::handle_deleted_player(long player_index)
{
    mangled_ppc("?handle_deleted_player@c_dead_camera@@UAAXJ@Z");

    c_camera::handle_deleted_player(player_index);
    if (m_player_index == player_index)
    {
        m_player_index = NONE;
    }
};

void c_dead_camera::handle_deleted_object(long object_index)
{
    mangled_ppc("?handle_deleted_object@c_dead_camera@@UAAXJ@Z");

    c_camera::handle_deleted_object(object_index);
    if (m_killer_object_index == object_index)
    {
        m_killer_object_index = NONE;
    }
};

long c_dead_camera::get_target_unit_index()
{
    mangled_ppc("?get_target_unit_index@c_dead_camera@@AAAJXZ");

    long target_unit_index = NONE;
    if (m_target_object_index != NONE && object_get_type(m_target_object_index) == _object_type_biped)
    {
        target_unit_index = m_target_object_index;
    }

    return target_unit_index;
};

long c_dead_camera::get_target_player_index()
{
    mangled_ppc("?get_target_player_index@c_dead_camera@@AAAJXZ");

    long unit_index = get_target_unit_index();

    return unit_index != NONE ? player_index_from_unit_index(unit_index) : NONE;
};

bool c_dead_camera::get_killer_position(real_point3d * position)
{
    mangled_ppc("?get_killer_position@c_dead_camera@@AAA_NPATreal_point3d@@@Z");

    bool got_position = false;
    if (m_killer_object_index != NONE)
    {
        if (position)
        {
            object_get_origin_interpolated(m_killer_object_index, position);
        }
        got_position = true;
    }

    return got_position;
};

