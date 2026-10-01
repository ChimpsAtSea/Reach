#pragma once
#ifndef __DAMAGE_REPORTING_H__
#define __DAMAGE_REPORTING_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_damage_reporting_info
{
    // inline in the target (f i, simulation_game_action.obj): constructs the c_enum<e_damage_reporting_modifier, unsigned char, 0, 6> at 0x1; body not reversed yet
    s_damage_reporting_info(void);

    unsigned char type; // 0x0
    unsigned char modifier; // 0x1 $TODO c_enum<e_damage_reporting_modifier, unsigned char, 0, 6>
};
static_assert(sizeof(s_damage_reporting_info) == 0x2, "s_damage_reporting_info");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DAMAGE_REPORTING_H__

