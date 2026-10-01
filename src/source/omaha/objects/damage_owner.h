#pragma once
#ifndef __DAMAGE_OWNER_H__
#define __DAMAGE_OWNER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_damage_owner
{
    // inline in the target (f i, simulation_game_bipeds.obj): constructs the c_game_team at 0x8; body not reversed yet
    s_damage_owner(void);

    long damage_owner_player_index; // 0x0
    long damage_owner_object_index; // 0x4
    unsigned char damage_owner_team[4]; // 0x8 $TODO c_game_team
};
static_assert(sizeof(s_damage_owner) == 0xC, "s_damage_owner");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DAMAGE_OWNER_H__

