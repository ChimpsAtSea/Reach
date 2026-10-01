#pragma once
#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\camera\camera.h"
#include "omaha\game\player_mapping.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

enum e_director_mode
{
    _director_mode_game = 0, // $unsure
    _director_mode_saved_film, // $unsure
    _director_mode_observer, // $unsure
    _director_mode_debug, // $unsure
    _director_mode_cable_cam, // $unsure
    _director_mode_editor, // $unsure
    _director_mode_animation_debug, // c_animation_debug_director::get_type
};

/* ---------- definitions */

// vtable order verified against ??_7c_director@@6B@ (11 slots, no virtual destructor)
// $TODO: only the members used so far are known; the rest of the layout is not yet reversed
class c_director
{
public:
    c_director();
    c_director(e_output_user_index output_user_index);

    virtual e_director_mode get_type() const = 0;
    virtual void update(float dt);
    virtual bool should_draw_hud_normal() const;
    virtual bool should_draw_hud_saved_film() const;
    virtual bool should_draw_reticule() const;
    virtual bool should_apply_player_effects() const;
    virtual bool inhibits_facing() const;
    virtual bool inhibits_input() const;
    virtual void handle_deleted_player(long player_index);
    virtual void handle_deleted_object(long object_index);
    virtual bool can_use_camera_mode(e_camera_mode camera_mode) const;

    e_output_user_index get_output_user_index() const;
    c_camera * get_camera();
    c_camera const * get_camera() const;
    bool get_camera_as(e_camera_mode camera_mode, c_camera ** out_camera);
    bool force_set_camera_mode(e_camera_mode camera_mode, float interpolation_time);
    bool set_camera_mode(e_camera_mode camera_mode, float interpolation_time);

protected:
    e_controller_index get_controller_index() const;
    s_observer_command const * get_last_observer_command() const; // $TODO inline in the target (f i, director.obj); body not reversed yet

private:
    unsigned char m_unknown4[0x170]; // 0x4 $TODO
    e_output_user_index m_output_user_index; // 0x174
    unsigned char m_unknown178[0xC]; // 0x178 $TODO
};
static_assert(sizeof(c_director) == 0x184, "c_director");

/* ---------- prototypes */

void director_fix_vtables_for_saved_game(long game_state_proc_flags);
c_director * director_get(e_output_user_index output_user_index);
e_director_perspective director_get_perspective(e_output_user_index output_user_index);
void director_initialize_for_saved_game(long game_state_proc_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __DIRECTOR_H__

