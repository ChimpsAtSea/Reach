#pragma once
#ifndef __GAME_DAMAGE_GLOBALS_H__
#define __GAME_DAMAGE_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

// Reach layout from armor_modifier_block (tag json), size 0x8
struct s_armor_modifier_definition
{
    long name; // 0x0
    float damage_multiplier; // 0x4
};
static_assert(sizeof(s_armor_modifier_definition) == 0x8, "s_armor_modifier_definition");

// Reach layout from damage_group_block (tag json), size 0x10
struct s_damage_group_definition
{
    long name; // 0x0
    s_tag_block armor_modifiers; // 0x4
};
static_assert(sizeof(s_damage_group_definition) == 0x10, "s_damage_group_definition");

// Reach layout from game_globals_damage_block (tag json), size 0xC
struct s_damage_globals_definition
{
    s_tag_block damage_groups; // 0x0
};
static_assert(sizeof(s_damage_globals_definition) == 0xC, "s_damage_globals_definition");

/* ---------- prototypes */

extern bool game_globals_damage_group_postprocess(long element_index, void * element, bool for_editor);
extern bool damage_armor_modifier_compare_proc(void const * element_a, void const * element_b, void const * context);
extern bool game_globals_damage_globals_postprocess(long element_index, void * element, bool for_editor);
extern bool damage_group_compare_proc(void const * element_a, void const * element_b, void const * context);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_DAMAGE_GLOBALS_H__

