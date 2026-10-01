#pragma once
#ifndef __GAME_DIFFICULTY_GLOBALS_H__
#define __GAME_DIFFICULTY_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

enum
{
    k_coop_difficulty_scale_count = 11,
    k_coop_difficulty_player_count_type_count = 3 // two, four, six players
};

/* ---------- definitions */

// scale groups: shield recharge delay, shield recharge timer, grenade dive chance, armor lock chance, evasion danger threshold,
// evasion delay timer, evasion chance, burst duration, burst separation, damage modifier, projectile speed
struct s_game_globals_coop_difficulty_information
{
    real scales[k_coop_difficulty_scale_count][k_coop_difficulty_player_count_type_count]; // 0x0
};
static_assert(sizeof(s_game_globals_coop_difficulty_information) == 0x84, "s_game_globals_coop_difficulty_information");

class c_game_globals_coop_difficulty_information_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static bool on_new_proc(void * data)
    {
        mangled_ppc("?on_new_proc@c_game_globals_coop_difficulty_information_vtable@@SA_NPAX@Z");

        s_game_globals_coop_difficulty_information * coop_difficulty = static_cast<s_game_globals_coop_difficulty_information *>(data);
        for (long scale_index = 0; scale_index < k_coop_difficulty_scale_count; scale_index++)
        {
            for (long player_count_index = 0; player_count_index < k_coop_difficulty_player_count_type_count; player_count_index++)
            {
                coop_difficulty->scales[scale_index][player_count_index] = 1.0f;
            }
        }
        return true;
    }
};

/* ---------- prototypes */

/* ---------- globals */

extern c_tag_struct_vtable<c_game_globals_coop_difficulty_information_vtable> coop_difficulty_block_struct_struct_vtable;

/* ---------- public code */

#endif // __GAME_DIFFICULTY_GLOBALS_H__
