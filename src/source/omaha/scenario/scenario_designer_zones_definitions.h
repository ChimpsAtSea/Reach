#pragma once
#ifndef __SCENARIO_DESIGNER_ZONES_DEFINITIONS_H__
#define __SCENARIO_DESIGNER_ZONES_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_scenario_designer_zone
{
    long name; // 0x0
    unsigned long flags; // 0x4
    s_tag_block biped_indices; // 0x8
    s_tag_block vehicle_indices; // 0x14
    s_tag_block weapon_indices; // 0x20
    s_tag_block equipment_indices; // 0x2C
    s_tag_block scenery_indices; // 0x38
    s_tag_block machine_indices; // 0x44
    s_tag_block terminal_indices; // 0x50
    s_tag_block control_indices; // 0x5C
    s_tag_block sound_scenery_indices; // 0x68
    s_tag_block crate_indices; // 0x74
    s_tag_block creature_indices; // 0x80
    s_tag_block giant_indices; // 0x8C
    s_tag_block effect_scenery_indices; // 0x98
    s_tag_block character_indices; // 0xA4
    s_tag_block budget_reference_indices; // 0xB0
};
static_assert(sizeof(s_scenario_designer_zone) == 0xBC, "s_scenario_designer_zone");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_DESIGNER_ZONES_DEFINITIONS_H__

