#pragma once
#ifndef __CAMERA_SHAKE_DEFINITIONS_H__
#define __CAMERA_SHAKE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\math\function_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

// layouts from the camera_impulse_struct / camera_shake_struct / global_camera_impulse_block tag definitions
struct s_camera_impulse
{
    real impulse_duration; // 0x0
    c_function_definition mapping; // 0x4
    real rotation; // 0x18
    real pushback; // 0x1C
    real_bounds jitter; // 0x20
};
static_assert(sizeof(s_camera_impulse) == 0x28, "s_camera_impulse");

struct s_camera_shake
{
    real shake_duration; // 0x0
    c_function_definition mapping; // 0x4
    real random_translation; // 0x18
    real random_rotation; // 0x1C
    real wobble_function_period; // 0x20
    real wobble_weight; // 0x24
    short wobble_function; // 0x28
    char animated_shake_playback; // 0x2A
    char animated_shake_weight; // 0x2B
    s_tag_reference animation_graph; // 0x2C
    long animation_name; // 0x3C
};
static_assert(sizeof(s_camera_shake) == 0x40, "s_camera_shake");

struct s_camera_shake_definition
{
    s_camera_impulse camera_impulse; // 0x0
    s_camera_shake camera_shake; // 0x28
};
static_assert(sizeof(s_camera_shake_definition) == 0x68, "s_camera_shake_definition");

struct s_camera_impulse_globals
{
    c_function_definition mapping; // 0x0
};
static_assert(sizeof(s_camera_impulse_globals) == 0x14, "s_camera_impulse_globals");

class c_camera_shake_struct_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static bool postprocess_proc(long tag_index, void * data, bool for_editor);
};

/* ---------- prototypes */

extern bool camera_impulse_globals_on_new_proc(void * data);

/* ---------- globals */

extern c_tag_struct_vtable<c_camera_shake_struct_vtable> camera_shake_struct_struct_vtable;

/* ---------- public code */

#endif // __CAMERA_SHAKE_DEFINITIONS_H__
