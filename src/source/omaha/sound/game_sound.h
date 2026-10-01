#pragma once
#ifndef __GAME_SOUND_H__
#define __GAME_SOUND_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// layout per IDA (0x10), offsets 0x8/0xE/0xF confirmed by determinism_debug_consumer_sound.obj
struct s_game_sound_impulse_datum
{
    long sound_definition_index; // 0x0
    long start_time; // 0x4
    union
    {
        long sound_impulse_index; // 0x8
        long attached_to_object_index; // 0x8
    };
    unsigned char deterministic_permutation[2]; // 0xC $TODO s_game_sound_deterministic_permutation
    bool fake_cinematic_lipsync; // 0xE
    unsigned char pad; // 0xF
};
static_assert(sizeof(s_game_sound_impulse_datum) == 0x10, "s_game_sound_impulse_datum");

/* ---------- prototypes */

void game_sound_cleanup(long game_state_proc_flags);
void game_sound_clear(long game_state_proc_flags);
void game_sound_restore(long game_state_proc_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_SOUND_H__

