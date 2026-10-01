#pragma once
#ifndef __SCENARIO_ZONE_STATE_H__
#define __SCENARIO_ZONE_STATE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_scenario_zone_state
{
    bool using_designer_zones; // 0x0
    unsigned long active_bsp_mask; // 0x4
    unsigned long touched_bsp_mask; // 0x8
    unsigned long active_designer_zone_mask; // 0xC
    unsigned long active_cinematic_zone_mask; // 0x10
    unsigned long pending_bsp_zone_mask; // 0x14
    unsigned long pending_designer_zone_mask; // 0x18
    unsigned long pending_cinematic_zone_mask; // 0x1C
};
static_assert(sizeof(s_scenario_zone_state) == 0x20, "s_scenario_zone_state");

/* ---------- prototypes */

bool scenario_zone_states_any_active_changes(s_scenario_zone_state const * lhs, s_scenario_zone_state const * rhs);
bool scenario_zone_states_any_pending_changes(s_scenario_zone_state const * lhs, s_scenario_zone_state const * rhs);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_ZONE_STATE_H__

