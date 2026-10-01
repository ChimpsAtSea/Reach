#pragma once
#ifndef __ANIMATION_DEBUG_DIRECTOR_H__
#define __ANIMATION_DEBUG_DIRECTOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\camera\director.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: size beyond 0x194 not verified
class c_animation_debug_director : public c_director
{
public:
    c_animation_debug_director();
    c_animation_debug_director(e_output_user_index output_user_index);

    virtual e_director_mode get_type() const;
    virtual void update(float dt);
    virtual bool should_draw_hud_normal() const;
    virtual bool should_draw_hud_saved_film() const;
    virtual bool inhibits_facing() const;
    virtual bool inhibits_input() const;

private:
    void initialize();

    long m_camera_mode_index; // 0x184
    bool m_camera_control_enabled; // 0x188
    float m_vertical_offset; // 0x18C
    float m_horizontal_offset; // 0x190
};

/* ---------- prototypes */

/* ---------- globals */

extern float g_animation_debug_initial_camera_distance;
extern e_camera_mode animation_director_camera_modes[];
extern float g_animation_debug_initial_target_vertical_offset;

/* ---------- public code */

#endif // __ANIMATION_DEBUG_DIRECTOR_H__

