#pragma once
#ifndef __SCENARIO_MUNGE_H__
#define __SCENARIO_MUNGE_H__

/* ---------- headers */

#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// $TODO: bit names unknown; usage in scenario_prune: 0 deletes scenario resources, 1-6 prune the scenario
// (2 keeps scenery/decals/crates/creatures, 3 keeps cinematics/subtitles, 5 keeps pathfinding, 6 keeps scripts), 7 builds per-bsp zone sets
enum e_scenario_prune_flags
{
    _scenario_prune_bit0 = 0,
    _scenario_prune_bit1,
    _scenario_prune_bit2,
    _scenario_prune_bit3,
    _scenario_prune_bit4,
    _scenario_prune_bit5,
    _scenario_prune_bit6,
    _scenario_prune_bit7,

    k_scenario_prune_flags_count
};

/* ---------- definitions */

/* ---------- prototypes */

bool scenario_prune(long scenario_index, c_flags<e_scenario_prune_flags, unsigned long, k_scenario_prune_flags_count> prune_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_MUNGE_H__

