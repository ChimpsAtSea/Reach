#pragma once
#ifndef __EFFECTS_H__
#define __EFFECTS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\objects\damage_owner.h"
#include "omaha\objects\damage_reporting.h"

/* ---------- constants */

// iterate_next ranges in determinism_debug_consumer_effects.cpp
long const k_maximum_effects_per_map = 460;
long const k_maximum_events_per_map = 900;
long const k_maximum_effect_locations_per_map = 690;

/* ---------- definitions */

// only the count is verified (c_flags<e_effect_flags, unsigned long, 25>); bit names are H3's minus one unknown Reach addition
enum e_effect_flags
{
    k_effect_flags_count = 25
};

// $TODO partially reversed; layout from the Reach target (determinism_debug_consumer_effects.obj: sizeof 0xB0, ctor member offsets, deterministic resets)
// the IDA type is the H3 layout (0x9C) and is stale
struct effect_datum
{
    short identifier; // 0x0
    unsigned char pad2[2]; // 0x2
    c_flags<e_effect_flags, unsigned long, k_effect_flags_count> flags; // 0x4
    c_tag_index definition_index; // 0x8
    s_static_array<long, 4> looping_sound_indices; // 0xC
    unsigned char unknown1C[0x40 - 0x1C]; // 0x1C $TODO
    s_damage_owner damage_owner; // 0x40
    s_damage_reporting_info damage_reporting_info; // 0x4C
    char first_person_player_user_mask; // 0x4E
    char unknown4F; // 0x4F $TODO
    char first_person_weapon_user_index; // 0x50
    unsigned char unknown51[0x8C - 0x51]; // 0x51 $TODO
    long lightprobe_index; // 0x8C
    unsigned char unknown90[0x94 - 0x90]; // 0x90 $TODO
    unsigned long random_seed; // 0x94
    unsigned long unknown98; // 0x98 $TODO reset to 0 with random_seed
    unsigned char unknown9C[0xB0 - 0x9C]; // 0x9C $TODO
};
static_assert(sizeof(effect_datum) == 0xB0, "effect_datum");

/* ---------- prototypes */

void effects_handle_game_state_after_load(long game_state_proc_flags);

/* ---------- globals */

extern __declspec(thread) s_data_array * effect_data;

/* ---------- public code */

#endif // __EFFECTS_H__

