#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\animation_debug_director.cpp"
/* ---------- headers */

#include "blamlib\animation_debug_director.h"
#include "omaha\camera\orbiting_camera.h"
#include "omaha\game\player_mapping.h"
#include "omaha\input\input_abstraction.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

long const k_animation_director_camera_mode_count = 2;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

float g_animation_debug_initial_camera_distance = 4.0f;
e_camera_mode animation_director_camera_modes[k_animation_director_camera_mode_count] = { _camera_mode_orbiting, _camera_mode_static };
float g_animation_debug_initial_target_vertical_offset;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float g_animation_debug_initial_camera_distance; // "?g_animation_debug_initial_camera_distance@@3MA"
// enum e_camera_mode *animation_director_camera_modes; // "?animation_director_camera_modes@@3PAW4e_camera_mode@@A"
// float g_animation_debug_initial_target_vertical_offset; // "?g_animation_debug_initial_target_vertical_offset@@3MA"

// public: c_animation_debug_director::c_animation_debug_director(void);
// public: virtual enum e_director_mode c_animation_debug_director::get_type(void) const;
// public: c_animation_debug_director::c_animation_debug_director(enum e_output_user_index);
// private: void c_animation_debug_director::initialize(void);
// public: virtual void c_animation_debug_director::update(float);
// public: void c_orbiting_camera::get_orientation(union euler_angles2d *);
// public: virtual bool c_animation_debug_director::should_draw_hud_normal(void) const;
// public: virtual bool c_animation_debug_director::should_draw_hud_saved_film(void) const;
// public: virtual bool c_animation_debug_director::inhibits_facing(void) const;
// public: virtual bool c_animation_debug_director::inhibits_input(void) const;

c_animation_debug_director::c_animation_debug_director() :
    c_director()
{
    mangled_ppc("??0c_animation_debug_director@@QAA@XZ");

    initialize();
};

e_director_mode c_animation_debug_director::get_type() const
{
    mangled_ppc("?get_type@c_animation_debug_director@@UBA?AW4e_director_mode@@XZ");

    return _director_mode_animation_debug;
};

c_animation_debug_director::c_animation_debug_director(e_output_user_index output_user_index) :
    c_director(output_user_index)
{
    mangled_ppc("??0c_animation_debug_director@@QAA@W4e_output_user_index@@@Z");

    initialize();
};

void c_animation_debug_director::initialize()
{
    mangled_ppc("?initialize@c_animation_debug_director@@AAAXXZ");

    m_camera_control_enabled = true;
    m_camera_mode_index = 0;
    set_camera_mode(animation_director_camera_modes[m_camera_mode_index], 0.5f);
    m_vertical_offset = 0.0f;

    c_camera * camera;
    if (get_camera_as(_camera_mode_orbiting, &camera))
    {
        static_cast<c_orbiting_camera *>(camera)->set_distance(g_animation_debug_initial_camera_distance);
        static_cast<c_orbiting_camera *>(camera)->set_vertical_offset(g_animation_debug_initial_target_vertical_offset);
    }
    m_vertical_offset = g_animation_debug_initial_target_vertical_offset;
};

void c_animation_debug_director::update(float dt)
{
    mangled_ppc("?update@c_animation_debug_director@@UAAXM@Z");

    e_output_user_index output_user_index = get_output_user_index();
    long unit_index = player_mapping_get_unit_by_output_user(output_user_index);
    c_camera * orbiting_camera = NULL;

    if (get_camera()->get_target() != unit_index)
    {
        euler_angles2d orientation = *global_zero_angles2d;

        orbiting_camera = NULL;
        if (get_camera_as(_camera_mode_orbiting, &orbiting_camera))
        {
            static_cast<c_orbiting_camera *>(orbiting_camera)->get_orientation(&orientation);
        }

        get_camera()->set_target(unit_index);
        get_camera()->set_next_move_instantly();

        orbiting_camera = NULL;
        if (get_camera_as(_camera_mode_orbiting, &orbiting_camera))
        {
            static_cast<c_orbiting_camera *>(orbiting_camera)->set_orientation(&orientation);
        }
    }

    e_controller_index controller_index = get_controller_index();
    if (controller_index != k_no_controller && !camera_input_inhibited(controller_index))
    {
        s_game_input_state * input_state;
        input_abstraction_get_input_state(controller_index, &input_state);

        c_abstract_button * dpad_up = &input_state->abstract_gamepad_buttons[2];
        c_abstract_button * dpad_down = &input_state->abstract_gamepad_buttons[3];
        c_abstract_button * dpad_left = &input_state->abstract_gamepad_buttons[4];
        c_abstract_button * dpad_right = &input_state->abstract_gamepad_buttons[5];
        c_abstract_button * back_button = &input_state->abstract_gamepad_buttons[12];

        if (dpad_up->down_frames() || dpad_down->down_frames())
        {
            m_vertical_offset += dpad_down->down_frames() ? -0.01f : 0.01f;
        }

        if (dpad_left->down_frames() || dpad_right->down_frames())
        {
            m_horizontal_offset += dpad_left->down_frames() ? -0.01f : 0.01f;
        }

        if (get_camera()->get_type() == _camera_mode_orbiting && input_state->abstract_gamepad_buttons[9].down_frames() == 1)
        {
            input_state->abstract_gamepad_buttons[9].latch();
            m_camera_control_enabled = !m_camera_control_enabled;
        }

        if (get_camera()->get_type() == _camera_mode_static)
        {
            m_camera_control_enabled = false;
        }

        if (back_button->down_frames())
        {
            back_button->latch();
            m_camera_mode_index = (m_camera_mode_index + 1) % k_animation_director_camera_mode_count;
            if (animation_director_camera_modes[m_camera_mode_index] == _camera_mode_orbiting)
            {
                m_camera_control_enabled = true;
            }
        }
    }

    set_camera_mode(animation_director_camera_modes[m_camera_mode_index], 0.5f);

    orbiting_camera = NULL;
    if (get_camera_as(_camera_mode_orbiting, &orbiting_camera))
    {
        static_cast<c_orbiting_camera *>(orbiting_camera)->set_vertical_offset(m_vertical_offset);
        static_cast<c_orbiting_camera *>(orbiting_camera)->set_horizontal_offset(m_horizontal_offset);
        orbiting_camera->enable_movement(m_camera_control_enabled);
        orbiting_camera->enable_orientation(m_camera_control_enabled);
    }
    else
    {
        get_camera()->set_target(unit_index);
    }

    c_director::update(dt);
};

void c_orbiting_camera::get_orientation(euler_angles2d * orientation)
{
    mangled_ppc("?get_orientation@c_orbiting_camera@@QAAXPATeuler_angles2d@@@Z");

    *orientation = m_orientation;
};

bool c_animation_debug_director::should_draw_hud_normal() const
{
    mangled_ppc("?should_draw_hud_normal@c_animation_debug_director@@UBA_NXZ");

    return false;
};

bool c_animation_debug_director::should_draw_hud_saved_film() const
{
    mangled_ppc("?should_draw_hud_saved_film@c_animation_debug_director@@UBA_NXZ");

    return false;
};

bool c_animation_debug_director::inhibits_facing() const
{
    mangled_ppc("?inhibits_facing@c_animation_debug_director@@UBA_NXZ");

    return m_camera_control_enabled;
};

bool c_animation_debug_director::inhibits_input() const
{
    mangled_ppc("?inhibits_input@c_animation_debug_director@@UBA_NXZ");

    return m_camera_control_enabled;
};

