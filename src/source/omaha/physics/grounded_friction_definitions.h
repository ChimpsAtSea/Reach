#pragma once
#ifndef __GROUNDED_FRICTION_DEFINITIONS_H__
#define __GROUNDED_FRICTION_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\math\function_definitions.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    GROUNDED_FRICTION_GROUP_TAG = 'grfr',
};

/* ---------- definitions */

struct s_grounded_friction_definition
{
    c_function_definition friction_over_time; // 0x0 (scalar_function_named_struct)
    real friction_over_time_domain_min; // 0x14 seconds
    real friction_over_time_domain_max; // 0x18 seconds
    real maximum_slope_for_friction; // 0x1C degrees
    real minimum_asymmetry_ratio_for_axis_lock; // 0x20
};
static_assert(sizeof(s_grounded_friction_definition) == 0x24, "s_grounded_friction_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GROUNDED_FRICTION_DEFINITIONS_H__

