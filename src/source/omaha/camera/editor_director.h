#pragma once
#ifndef __EDITOR_DIRECTOR_H__
#define __EDITOR_DIRECTOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\camera\director.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

class c_editor_director : public c_director
{
public:
    c_editor_director();
    c_editor_director(e_output_user_index output_user_index);

    virtual e_director_mode get_type() const
    {
        mangled_ppc("?get_type@c_editor_director@@UBA?AW4e_director_mode@@XZ");

        return _director_mode_editor;
    };

    virtual void update(float dt);

    virtual bool should_draw_hud_normal() const
    {
        mangled_ppc("?should_draw_hud_normal@c_editor_director@@UBA_NXZ");

        return false;
    };

    virtual bool should_draw_hud_saved_film() const
    {
        mangled_ppc("?should_draw_hud_saved_film@c_editor_director@@UBA_NXZ");

        return false;
    };

    virtual void handle_deleted_object(long object_index);

    void get_focus(real_point3d * position, euler_angles2d * angles);
    void move_to_point(real_point3d const * position);
    void set_position(real_point3d const * position, euler_angles2d const * angles);
    void set_position_and_roll(real_point3d const * position, euler_angles3d const * angles);
    void set_focus(real_point3d const * position, euler_angles2d const * angles);
    void bump_speed();
    static float get_speed();
    bool use_roll(bool enable);
    void set_unit_focus(long unit_index);
    long get_unit_focus() const;
    void set_scripted(bool scripted);
    bool get_scripted() const;

private:
    long m_unit_focus; // 0x184
    bool m_is_scripted; // 0x188
    bool m_use_roll; // 0x189
};
static_assert(sizeof(c_editor_director) == 0x18C, "c_editor_director");

/* ---------- prototypes */

bool editor_director_valid();
c_editor_director * get_editor_director();
void editor_director_set_position(real_point3d const * position, euler_angles2d const * orientation);
void editor_director_save_position();

/* ---------- globals */

/* ---------- public code */

#endif // __EDITOR_DIRECTOR_H__
