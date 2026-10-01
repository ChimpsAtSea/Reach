#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\editor_director.cpp"
/* ---------- headers */

#include <math.h>

#include "omaha\camera\editor_director.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "omaha\camera\camera_globals.h"
#include "omaha\camera\flying_camera.h"
#include "omaha\camera\observer.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\player_mapping.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static long const g_speed_multiples[5] = { 1, 5, 20, 40, 100 };
static real_point3d desired_camera_position;
static euler_angles2d desired_camera_orientation;
static long speed_multiplier_index;
static float speed_scale = 1.0f;
static bool use_desired_position = false;
static char const * editor_director_scripted_mode_strings[2] = { "exiting", "entering" };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_editor_director::c_editor_director(void);
// public: virtual enum e_director_mode c_editor_director::get_type(void) const;
// public: virtual bool c_editor_director::should_draw_hud_normal(void) const;
// public: virtual bool c_editor_director::should_draw_hud_saved_film(void) const;
// public: c_editor_director::c_editor_director(enum e_output_user_index);
// public: virtual void c_editor_director::update(float);
// public: virtual void c_editor_director::handle_deleted_object(long);
// public: void c_editor_director::get_focus(union real_point3d *, union euler_angles2d *);
// public: void c_editor_director::move_to_point(union real_point3d const *);
// public: void c_editor_director::set_position(union real_point3d const *, union euler_angles2d const *);
// public: void c_editor_director::set_position_and_roll(union real_point3d const *, union euler_angles3d const *);
// public: void c_editor_director::set_focus(union real_point3d const *, union euler_angles2d const *);
// public: void c_editor_director::bump_speed(void);
// public: static float c_editor_director::get_speed(void);
// public: bool c_editor_director::use_roll(bool);
// public: void c_editor_director::set_unit_focus(long);
// public: long c_editor_director::get_unit_focus(void) const;
// public: void c_editor_director::set_scripted(bool);
// public: bool c_editor_director::get_scripted(void) const;
// bool editor_director_valid(void);
// class c_editor_director * get_editor_director(void);
// void editor_director_set_position(union real_point3d const *, union euler_angles2d const *);
// void editor_director_save_position(void);

c_editor_director::c_editor_director() :
    c_director()
{
    mangled_ppc("??0c_editor_director@@QAA@XZ");
};

// get_type, should_draw_hud_normal and should_draw_hud_saved_film are inline in editor_director.h

c_editor_director::c_editor_director(e_output_user_index output_user_index) :
    c_director(output_user_index)
{
    mangled_ppc("??0c_editor_director@@QAA@W4e_output_user_index@@@Z");

    set_camera_mode(_camera_mode_flying, 0.0f);
    c_flying_camera * camera = static_cast<c_flying_camera *>(get_camera());
    vector3d forward = *global_forward3d;
    if (get_output_user_index() == player_mapping_first_active_output_user() && use_desired_position)
    {
        vector3d_from_euler_angles2d(&forward, &desired_camera_orientation);
        camera->set_position(&desired_camera_position);
        use_desired_position = false;
    }
    else if (global_scenario_get()->player_starting_locations.count != 0 && global_scenario_get()->player_starting_locations.address != NULL)
    {
        scenario_player_starting_location * starting_location = static_cast<scenario_player_starting_location *>(tag_block_get_element_with_size(&global_scenario_get()->player_starting_locations, 0, sizeof(scenario_player_starting_location)));
        vector3d_from_angle(&forward, starting_location->facing);
        camera->set_position(&starting_location->position);
    }
    camera->set_forward(&forward);
    camera->set_lock_in_xy_plane(true);
    camera->set_collision(false);
    m_unit_focus = NONE;
    m_is_scripted = false;
    m_use_roll = false;
};

void c_editor_director::update(float dt)
{
    mangled_ppc("?update@c_editor_director@@UAAXM@Z");

    c_director::update(dt);
};

void c_editor_director::handle_deleted_object(long object_index)
{
    mangled_ppc("?handle_deleted_object@c_editor_director@@UAAXJ@Z");

    c_director::handle_deleted_object(object_index);
    if (m_unit_focus == object_index)
    {
        m_unit_focus = NONE;
    }
};

void c_editor_director::get_focus(real_point3d * position, euler_angles2d * angles)
{
    mangled_ppc("?get_focus@c_editor_director@@QAAXPATreal_point3d@@PATeuler_angles2d@@@Z");

    if (position)
    {
        *position = get_last_observer_command()->focus_position;
    }
    if (angles)
    {
        euler_angles2d_from_vector3d(angles, &get_last_observer_command()->forward);
    }
};

void c_editor_director::move_to_point(real_point3d const * position)
{
    mangled_ppc("?move_to_point@c_editor_director@@QAAXPBTreal_point3d@@@Z");

    real_point3d point;
    point_from_line3d(position, &get_last_observer_command()->forward, -2.5f, &point);
    get_camera()->set_position(&point);
};

void c_editor_director::set_position(real_point3d const * position, euler_angles2d const * angles)
{
    mangled_ppc("?set_position@c_editor_director@@QAAXPBTreal_point3d@@PBTeuler_angles2d@@@Z");

    vector3d forward;
    vector3d_from_euler_angles2d(&forward, angles);
    get_camera()->set_position(position);
    get_camera()->set_forward(&forward);
};

void c_editor_director::set_position_and_roll(real_point3d const * position, euler_angles3d const * angles)
{
    mangled_ppc("?set_position_and_roll@c_editor_director@@QAAXPBTreal_point3d@@PBTeuler_angles3d@@@Z");

    real_matrix4x3 matrix;
    matrix4x3_rotation_from_angles(&matrix, angles->yaw, angles->pitch, angles->roll);

    real roll;
    if (fabs(fabs(matrix.forward.k) - 1.0f) >= k_real_epsilon)
    {
        roll = arctangent(matrix.left.k, matrix.up.k);
    }
    else
    {
        roll = 0.0f;
    }

    get_camera()->set_position(position);
    get_camera()->set_forward(&matrix.forward);
    get_camera()->set_roll(roll);
};

void c_editor_director::set_focus(real_point3d const * position, euler_angles2d const * angles)
{
    mangled_ppc("?set_focus@c_editor_director@@QAAXPBTreal_point3d@@PBTeuler_angles2d@@@Z");

    set_position(position, angles);
};

void c_editor_director::bump_speed()
{
    mangled_ppc("?bump_speed@c_editor_director@@QAAXXZ");

    speed_multiplier_index = (speed_multiplier_index + 1) % NUMBEROF(g_speed_multiples);
    float speed = get_speed();
    if (speed > 10.0f)
    {
        output_message("speed is now %dx", static_cast<long>(speed));
    }
    else
    {
        output_message("speed is now %.1fx", speed);
    }
};

// $TODO nonmatching: the only difference is `subi r7, r8, 0x54e8` (target, address already resolved) vs `addi r7, r8, g_speed_multiples@l` (relocation), which the source cannot control
float c_editor_director::get_speed()
{
    mangled_ppc("?get_speed@c_editor_director@@SAMXZ");

    return g_director_camera_speed_scale * g_speed_multiples[speed_multiplier_index] * speed_scale;
};

bool c_editor_director::use_roll(bool enable)
{
    mangled_ppc("?use_roll@c_editor_director@@QAA_N_N@Z");

    bool old_use_roll = m_use_roll;
    m_use_roll = enable;
    get_camera()->enable_roll(enable);
    if (!m_use_roll)
    {
        get_camera()->set_roll(0.0f);
    }
    return old_use_roll;
};

void c_editor_director::set_unit_focus(long unit_index)
{
    mangled_ppc("?set_unit_focus@c_editor_director@@QAAXJ@Z");

    m_unit_focus = unit_index;
};

long c_editor_director::get_unit_focus() const
{
    mangled_ppc("?get_unit_focus@c_editor_director@@QBAJXZ");

    return m_unit_focus;
};

void c_editor_director::set_scripted(bool scripted)
{
    mangled_ppc("?set_scripted@c_editor_director@@QAAX_N@Z");

    if (scripted)
    {
        set_camera_mode(_camera_mode_scripted, 0.0f);
    }
    else
    {
        set_camera_mode(_camera_mode_flying, 0.0f);
        c_flying_camera * camera = static_cast<c_flying_camera *>(get_camera());
        camera->set_position(&get_last_observer_command()->focus_position);
        camera->set_forward(&get_last_observer_command()->forward);
        camera->set_lock_in_xy_plane(true);
    }
    m_is_scripted = scripted;
    output_message("%s scripted camera mode", editor_director_scripted_mode_strings[scripted]);
};

bool c_editor_director::get_scripted() const
{
    mangled_ppc("?get_scripted@c_editor_director@@QBA_NXZ");

    return m_is_scripted;
};

bool editor_director_valid()
{
    mangled_ppc("?editor_director_valid@@YA_NXZ");

    e_output_user_index output_user_index = player_mapping_first_active_output_user();
    bool valid = false;
    if (VALID_INDEX(output_user_index, k_number_of_users))
    {
        c_director * director = director_get(output_user_index);
        valid = director->get_type() == _director_mode_editor;
    }
    return valid;
};

c_editor_director * get_editor_director()
{
    mangled_ppc("?get_editor_director@@YAPAVc_editor_director@@XZ");

    c_editor_director * director = static_cast<c_editor_director *>(director_get(player_mapping_first_active_output_user()));
    assert_tag_debug_untracked_jul_11_2011(326, director->get_type()==_director_mode_editor);

    return director;
};

void editor_director_set_position(real_point3d const * position, euler_angles2d const * orientation)
{
    mangled_ppc("?editor_director_set_position@@YAXPBTreal_point3d@@PBTeuler_angles2d@@@Z");

    if (!editor_director_valid())
    {
        desired_camera_position = *position;
        desired_camera_orientation = *orientation;
        use_desired_position = true;
    }
    else
    {
        get_editor_director()->set_position(position, orientation);
        use_desired_position = false;
    }
};

void editor_director_save_position()
{
    mangled_ppc("?editor_director_save_position@@YAXXZ");

    e_output_user_index output_user_index = player_mapping_first_active_output_user();
    if (VALID_INDEX(output_user_index, k_number_of_users) && global_structure_bsp_active_mask_get() != 0)
    {
        euler_angles2d_from_vector3d(&desired_camera_orientation, &observer_get_camera(output_user_index)->forward);
        desired_camera_position = observer_get_camera(output_user_index)->position;
        use_desired_position = true;
    }
};
