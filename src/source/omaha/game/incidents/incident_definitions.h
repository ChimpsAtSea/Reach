#pragma once
#ifndef __INCIDENT_DEFINITIONS_H__
#define __INCIDENT_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\game_mode_definitions.h"

/* ---------- constants */

// incident_definition_flags
enum e_incident_definition_flag
{
    _incident_definition_never_network_bit = 0,
    _incident_definition_always_network_to_everyone_bit,
    _incident_definition_use_long_delay_bit,
    _incident_definition_force_game_engine_event_display_in_campaign_bit,

    k_incident_definition_flag_count
};

// suppressed_incident_flags
enum e_suppressed_incident_flags
{
    _suppressed_incident_cause_player_game_engine_event_bit = 0,
    _suppressed_incident_effect_player_game_engine_event_bit,
    _suppressed_incident_cause_team_game_engine_event_bit,
    _suppressed_incident_effect_team_game_engine_event_bit,
    _suppressed_incident_medal_display_bit,
    _suppressed_incident_medal_stats_bit,

    k_suppressed_incident_flags_count
};

/* ---------- definitions */

// incident_definition_block
struct s_incident_definition
{
    long name; // 0x0 string_id
    c_flags<e_incident_definition_flag, unsigned char, k_incident_definition_flag_count> flags; // 0x4
    unsigned char pad5[0x3]; // 0x5
    s_game_mode_flags disallowed_game_modes; // 0x8
    s_tag_block suppressed_incidents; // 0xC
    s_tag_block specialized_incidents; // 0x18
    s_tag_block accumulator_incidents; // 0x24
    s_tag_block response; // 0x30 s_game_incident_response
};
static_assert(sizeof(s_incident_definition) == 0x3C, "s_incident_definition");

// incident_global_properties_definition_block ('igpd')
struct s_incident_global_properties_definition
{
    float campaign_multikill_time; // 0x0
    float survival_multikill_time; // 0x4
    float multiplayer_multikill_time; // 0x8
    float low_health_threshold; // 0xC
    float shield_recharge_threshold; // 0x10
    float lifesaver_damage_threshold; // 0x14
    float avenger_dead_time; // 0x18
    s_tag_reference cookie_globals; // 0x1C
    s_tag_reference commendation_globals; // 0x2C
    short maximum_heat; // 0x3C
    char pad0[0x2]; // 0x3E
    float full_heat_decay_time; // 0x40
    float full_heat_stun_time; // 0x44
    float betrayal_heat_stun_time; // 0x48
    s_tag_block incident_definitions; // 0x4C
    s_tag_block default_incident_definition; // 0x58
};
static_assert(sizeof(s_incident_global_properties_definition) == 0x64, "s_incident_global_properties_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __INCIDENT_DEFINITIONS_H__

