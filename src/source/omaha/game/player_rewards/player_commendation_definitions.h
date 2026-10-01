#pragma once
#ifndef __PLAYER_COMMENDATION_DEFINITIONS_H__
#define __PLAYER_COMMENDATION_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\color_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    COMMENDATION_GLOBALS_DEFINITION_TAG = 'comg',
};

// commendation_progression_level_enum
enum e_commendation_progression_level
{
    _commendation_progression_level_clear = 0,
    _commendation_progression_level_steel,
    _commendation_progression_level_bronze,
    _commendation_progression_level_silver,
    _commendation_progression_level_gold,
    _commendation_progression_level_onyx,
    _commendation_progression_level_max,

    k_commendation_progression_level_count,
    k_commendation_progression_level_none = -1,
};

// ??E@YAAAW4e_commendation_progression_level@@AAW40@@Z (f i)
inline e_commendation_progression_level & operator++(e_commendation_progression_level & level)
{
    mangled_ppc("??E@YAAAW4e_commendation_progression_level@@AAW40@@Z");

    level = static_cast<e_commendation_progression_level>(level + 1);

    return level;
};

/* ---------- definitions */

template<long k_maximum_count>
class c_static_wchar_string;

// commendation_block (tag json)
struct s_commendation_definition
{
    enum
    {
        k_maximum_commendation_definitions = 500,
    };

    long name; // 0x0 string_id
    long description_text; // 0x4 string_id
    long reward_value; // 0x8
    long post_cap_reward_value; // 0xC
    short progression_display_interval; // 0x10
    char sequence_index; // 0x12
    char override_reward_level_cap; // 0x13 e_commendation_progression_level + 1 (0 = default)
    short level_minimum[k_commendation_progression_level_count - 1]; // 0x14 steel .. max
    char pad0[0x2]; // 0x20
    short level_reward_value[k_commendation_progression_level_count]; // 0x22 clear .. max
    short medal_sprite_index; // 0x30
    short game_type_sprite_index; // 0x32
};
static_assert(sizeof(s_commendation_definition) == 0x34, "s_commendation_definition");

// commendation_globals_definition_struct_definition (tag json)
struct s_commendation_globals_definition
{
    s_tag_reference commendation_text; // 0x0
    c_enum_no_init<e_commendation_progression_level, char, k_commendation_progression_level_none, k_commendation_progression_level_count> reward_level_cap; // 0x10
    char pad0[0x3]; // 0x11
    short callout_display_time; // 0x14
    short progression_display_time; // 0x16
    argb_color campaign_color; // 0x18
    argb_color firefight_color; // 0x28
    argb_color multiplayer_color; // 0x38
    argb_color level_color[k_commendation_progression_level_count]; // 0x48
    s_tag_block commendations; // 0xB8
};
static_assert(sizeof(s_commendation_globals_definition) == 0xC4, "s_commendation_globals_definition");

/* ---------- prototypes */

long commendation_globals_get_commendation_definition_index_by_name(s_commendation_globals_definition const * commendation_globals, long name);
s_commendation_definition const * commendation_globals_get_commendation_definition_by_name(s_commendation_globals_definition const * commendation_globals, long name);
s_commendation_definition const * commendation_globals_try_and_get_commendation_definition_by_name(s_commendation_globals_definition const * commendation_globals, long name);
e_commendation_progression_level commendation_definition_get_progress_level(s_commendation_definition const * commendation_definition, long value);
e_commendation_progression_level commendation_definition_get_next_progress_level(s_commendation_definition const * commendation_definition, long value);
long commendation_definition_get_progress_level_minimum(s_commendation_definition const * commendation_definition, e_commendation_progression_level level);
unsigned long commendation_globals_generate_checksum();
s_commendation_globals_definition const * commendation_globals_try_and_get();
bool commendation_globals_get_game_type_color(argb_color * out_color);
argb_color const * commendation_globals_get_game_type_color_reference();
bool commendation_globals_get_level_color(e_commendation_progression_level level, argb_color * out_color);
argb_color const * commendation_globals_get_level_color_reference(e_commendation_progression_level level);
bool commendation_globals_get_commendation_text(s_commendation_globals_definition const * commendation_globals, long name, c_static_wchar_string<256> * out_string);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_COMMENDATION_DEFINITIONS_H__

