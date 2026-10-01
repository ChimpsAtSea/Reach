#pragma once
#ifndef __GAME_OPTIONS_H__
#define __GAME_OPTIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\campaign_metagame.h"
#include "omaha\game\game.h"
#include "omaha\game\game_variant.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout only partially reversed; size per game_options_new's memset (0x1E598),
// defaults per game_options_new, remaining offsets per game_options_get_launch_settings
struct s_game_options
{
    e_game_mode game_mode; // 0x0
    unsigned char unknown4[0xC]; // 0x4
    unsigned __int64 game_instance; // 0x10 name unverified (copied into s_content_item_metadata by content_item_metadata_set_from_game_options)
    unsigned char unknown18[0x10]; // 0x18
    c_game_variant game_variant; // 0x28
    long campaign_id; // 0xF82C NONE by default $TODO e_campaign_id
    long map_id; // 0xF830 NONE by default $TODO e_map_id
    char scenario_path[260]; // 0xF834
    char initial_script_name[128]; // 0xF938 name unverified (copied from the launch settings)
    unsigned char unknownF9B8[0x8]; // 0xF9B8
    bool record_saved_film; // 0xF9C0
    unsigned char unknownF9C1[0xB]; // 0xF9C1
    long unknownF9CC; // 0xF9CC 1 by default
    short campaign_insertion_point; // 0xF9D0
    unsigned char unknownF9D2[0x2]; // 0xF9D2
    e_campaign_metagame_scoring campaign_metagame_scoring; // 0xF9D4
    unsigned char unknownF9D8[0x4]; // 0xF9D8
    c_flags_no_init<e_game_skulls, unsigned long, k_game_skull_count> skulls; // 0xF9DC
    unsigned char unknownF9E0[0x70]; // 0xF9E0
    bool unknownFA50; // 0xFA50 selects the theater gui game mode in content_item_metadata_set_from_game_options
    unsigned char unknownFA51[0x5]; // 0xFA51
    short unknownFA56; // 0xFA56 copied into s_content_item_metadata 0x290 when unknownFA50 is set
    unsigned char unknownFA58[0xEB40]; // 0xFA58
};
static_assert(sizeof(s_game_options) == 0x1E598, "s_game_options");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_OPTIONS_H__
