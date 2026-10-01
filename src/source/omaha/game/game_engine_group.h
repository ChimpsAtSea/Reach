#pragma once
#ifndef __GAME_ENGINE_GROUP_H__
#define __GAME_ENGINE_GROUP_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\game_constants.h"
#include "omaha\game\game_engine_traits_structures.h"
#include "omaha\game\game_engine_player_traits_definitions.h"
#include "blamlib\game_engine_campaign_traits.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    GAME_ENGINE_GLOBALS_GROUP_TAG = 'gegl',
    GAME_ENGINE_SETTINGS_DEFINITION_GROUP_TAG = 'wezr',
};

/* ---------- definitions */

// game_engine_globals_struct_definition (Reach tag layout)
struct s_game_engine_globals_definition
{
    s_tag_reference game_engine_settings; // 0x0
    s_tag_reference game_engine_text; // 0x10
    s_tag_block game_engine_event_response_list; // 0x20
};
static_assert(sizeof(s_game_engine_globals_definition) == 0x2C, "s_game_engine_globals_definition");

// game_engine_settings_definition_struct_definition (Reach tag layout)
struct s_game_engine_settings_definition
{
    long flags; // 0x0
    s_tag_block player_traits; // 0x4 s_game_engine_player_traits_list_definition
    s_tag_block ai_traits; // 0x10 s_game_engine_ai_traits_list_definition
    s_tag_block sandbox_variants; // 0x1C s_game_engine_sandbox_variant_definition
    s_tag_block survival_variants; // 0x28 s_game_engine_survival_variant_definition
    s_tag_block campaign_variants; // 0x34 s_game_engine_campaign_variant_definition
};
static_assert(sizeof(s_game_engine_settings_definition) == 0x40, "s_game_engine_settings_definition");

// game_engine_ai_traits_struct (Reach tag layout)
struct s_game_engine_ai_traits
{
    char vision_traits; // 0x0
    char sound_traits; // 0x1
    char luck_traits; // 0x2
    char weapon_traits; // 0x3
    char grenade_traits; // 0x4
    char drop_equipment_on_death; // 0x5
    char assassination_immunity; // 0x6
    char headshot_immunity; // 0x7
    char damage_resistance_percentage; // 0x8
    char damage_modifier_percentage; // 0x9
    char pad[2]; // 0xA
};
static_assert(sizeof(s_game_engine_ai_traits) == 0xC, "s_game_engine_ai_traits");

// game_engine_ai_traits_list_block (Reach tag layout)
struct s_game_engine_ai_traits_list_definition
{
    long name; // 0x0
    s_game_engine_ai_traits ai_traits; // 0x4
};
static_assert(sizeof(s_game_engine_ai_traits_list_definition) == 0x10, "s_game_engine_ai_traits_list_definition");

// game_engine_team_options_team_block (Reach tag layout)
struct s_game_engine_team_options_team_definition
{
    unsigned char flags; // 0x0
    c_enum<e_multiplayer_team_designator, char, _multiplayer_team_designator_none, k_multiplayer_team_designator_count, s_multiplayer_team_designator_string_resolver> initial_team_designator; // 0x1
    char model_override; // 0x2
    char number_of_fireteams; // 0x3
    long description; // 0x4
    unsigned long color_override; // 0x8
    unsigned long ui_text_tint_color_override; // 0xC
    unsigned long ui_bitmap_tint_color_override; // 0x10
};
static_assert(sizeof(s_game_engine_team_options_team_definition) == 0x14, "s_game_engine_team_options_team_definition");

// game_engine_team_options_block (Reach tag layout)
struct s_game_engine_team_options_definition
{
    char model_override_type; // 0x0
    char designator_switch_type; // 0x1
    char pad[2]; // 0x2
    s_static_array<s_game_engine_team_options_team_definition, 8> teams; // 0x4
};
static_assert(sizeof(s_game_engine_team_options_definition) == 0xA4, "s_game_engine_team_options_definition");

// game_engine_sandbox_variant_block (Reach tag layout)
struct s_game_engine_sandbox_variant_definition : s_game_engine_base_variant_definition
{
    long flags; // 0x50
    short edit_mode; // 0x54
    short respawn_time; // 0x56
    long all_players_traits; // 0x58
};
static_assert(sizeof(s_game_engine_sandbox_variant_definition) == 0x5C, "s_game_engine_sandbox_variant_definition");

// game_engine_survival_wave_properties_struct (Reach tag layout)
struct s_survival_wave_properties_definition
{
    unsigned char flags; // 0x0
    char wave_selection_type; // 0x1
    char pad[2]; // 0x2
    s_tag_block wave_squads; // 0x4
};
static_assert(sizeof(s_survival_wave_properties_definition) == 0x10, "s_survival_wave_properties_definition");

// game_engine_survival_bonus_wave_properties_struct (Reach tag layout)
struct s_survival_bonus_wave_properties_definition
{
    long skulls; // 0x0
    short duration; // 0x4
    char pad[2]; // 0x6
    s_survival_wave_properties_definition base_properties; // 0x8
};
static_assert(sizeof(s_survival_bonus_wave_properties_definition) == 0x18, "s_survival_bonus_wave_properties_definition");

// game_engine_survival_variant_block (Reach tag layout)
struct s_game_engine_survival_variant_definition : s_game_engine_base_variant_definition
{
    unsigned char flags; // 0x50
    char game_difficulty; // 0x51
    char pad[2]; // 0x52
    char set_count; // 0x54
    char bonus_lives_awarded; // 0x55
    short bonus_target; // 0x56
    short spartan_lives_on_elite_death; // 0x58
    short extra_life_score_target; // 0x5A
    short shared_team_life_count; // 0x5C
    short elite_life_count; // 0x5E
    short maximum_lives; // 0x60
    short generator_count; // 0x62
    long spartan_player_traits; // 0x64
    long elite_player_traits; // 0x68
    long ai_traits; // 0x6C
    s_tag_block elite_respawn_options; // 0x70
    s_tag_block set_properties; // 0x7C
    s_tag_block round_properties; // 0x88
    s_survival_bonus_wave_properties_definition bonus_round_properties; // 0x94
    s_tag_block custom_skulls; // 0xAC
};
static_assert(sizeof(s_game_engine_survival_variant_definition) == 0xB8, "s_game_engine_survival_variant_definition");

/* ---------- prototypes */

bool game_engine_team_options_new_block_proc(void * element);
s_game_engine_settings_definition const * game_engine_settings_try_and_get(void);
s_game_engine_ai_traits const * game_engine_settings_ai_traits_get_by_name(long name);
s_game_engine_player_traits const * game_engine_settings_player_traits_get_by_name(long name);
s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(long name);
s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(long name, s_tag_block const * tag_block, long variant_size);
s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(char const * name);
s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(char const * name, s_tag_block const * tag_block, long variant_size);
s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(long name);
s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(char const * name);
s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(long name);
s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(char const * name);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_GROUP_H__
