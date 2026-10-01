#pragma once
#ifndef __SPRING_ACCELERATION_DEFINITIONS_H__
#define __SPRING_ACCELERATION_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\function_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SPRING_ACCELERATION_TAG = 'sadt',
};

/* ---------- definitions */

struct s_spring_linear_acceleration_block
{
    real acceleration_range; // 0x0
    real inverse_acceleration_range; // 0x4
    real world_acceleration_scale; // 0x8
    s_scalar_function_named_struct spring_damping; // 0xC
    real velocity_domain; // 0x20
    s_scalar_function_named_struct spring_acceleration; // 0x24
};
static_assert(sizeof(s_spring_linear_acceleration_block) == 0x38, "s_spring_linear_acceleration_block");

struct s_spring_acceleration_struct_definition
{
    s_tag_block linear_accelerations; // 0x0
    short axis_linear_acceleration_indices[3]; // 0xC
    unsigned char pad[2]; // 0x12
};
static_assert(sizeof(s_spring_acceleration_struct_definition) == 0x14, "s_spring_acceleration_struct_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SPRING_ACCELERATION_DEFINITIONS_H__

