#pragma once
#ifndef __COLLISION_CONSTANTS_H__
#define __COLLISION_CONSTANTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO both members are c_flags_no_init<e_collision_test_flag, unsigned long, 22> / c_flags_no_init<e_collision_test_objects_flag, unsigned long, 15>
struct s_collision_test_flags
{
    unsigned long collision_flags; // 0x0
    unsigned long object_flags; // 0x4
};
static_assert(sizeof(s_collision_test_flags) == 0x8, "s_collision_test_flags");

/* ---------- prototypes */

/* ---------- globals */

extern s_collision_test_flags _collision_test_for_line_of_sight_obstruction_flags;
extern s_collision_test_flags _collision_test_for_objects_structure_ignore_invisible_flags;

/* ---------- public code */

#endif // __COLLISION_CONSTANTS_H__

