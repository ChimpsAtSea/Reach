#ifndef __CONTENT_ITEM_METADATA_H__
#define __CONTENT_ITEM_METADATA_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\campaign_metagame.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_globals.h"
#include "omaha\interface\user_interface_networking.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// range per c_enum_no_init<e_content_item_type, char, -1, 8>; 6 = game variant (per game_engine_variant_initialize_built_in_metadata)
enum e_content_item_type
{
    _content_item_type_none = -1,

    k_content_item_type_count = 8
};

// range per c_flags_no_init<e_content_item_author_flag, unsigned char, 1>
enum e_content_item_author_flag
{
    _content_item_author_signed_in_to_live_bit = 0, // name unverified (set from c_controller_interface::is_signed_in_to_live)

    k_content_item_author_flag_count
};

/* ---------- definitions */

// 4-byte packed like s_content_item_metadata (embedded at 0x38 and 0x5C)
#pragma pack(push, 4)
struct s_content_item_history
{
    unsigned __int64 timestamp; // 0x0
    unsigned __int64 author_id; // 0x8
    char author_name[16]; // 0x10
    c_flags_no_init<e_content_item_author_flag, unsigned char, k_content_item_author_flag_count> author_flags; // 0x20
    unsigned char pad21[0x3]; // 0x21
};
#pragma pack(pop)
static_assert(sizeof(s_content_item_history) == 0x24, "s_content_item_history");

// campaign / survival settings at s_content_item_metadata 0x2A0 (names unverified)
struct s_content_item_campaign_metadata
{
    char campaign_id; // 0x0
    c_enum_no_init<e_campaign_difficulty_level, char, _campaign_difficulty_level_easy, k_campaign_difficulty_levels_count> difficulty; // 0x1
    c_enum_no_init<e_campaign_metagame_scoring, char, _metagame_off, k_metagame_scoring_count> metagame_scoring; // 0x2
    char insertion_point; // 0x3
    unsigned long skulls; // 0x4
};
static_assert(sizeof(s_content_item_campaign_metadata) == 0x8, "s_content_item_campaign_metadata");

struct s_content_item_survival_metadata
{
    c_enum_no_init<e_campaign_difficulty_level, char, _campaign_difficulty_level_easy, k_campaign_difficulty_levels_count> difficulty; // 0x0
    unsigned char pad1[0x3]; // 0x1
    unsigned long skulls; // 0x4
};
static_assert(sizeof(s_content_item_survival_metadata) == 0x8, "s_content_item_survival_metadata");

// $TODO: layout only partially reversed (content_item_metadata_set_defaults memsets 0x2B0)
// 4-byte packed: c_game_engine_base_variant holds it at offset 0x4 while it contains 64-bit ids
#pragma pack(push, 4)
struct s_content_item_metadata
{
    c_enum_no_init<e_content_item_type, char, -1, k_content_item_type_count> content_type; // 0x0
    unsigned char pad1[0x7]; // 0x1
    unsigned __int64 unique_id; // 0x8 $TODO names of the three ids unverified (all set by update_built_in_metadata)
    unsigned __int64 parent_unique_id; // 0x10
    unsigned __int64 root_unique_id; // 0x18
    unsigned __int64 game_instance; // 0x20 name unverified (from s_game_options 0x10)
    c_enum_no_init<e_gui_game_mode, char, _gui_game_mode_none, k_gui_game_mode_count> gui_game_mode; // 0x28
    c_enum_no_init<e_game_mode, char, _game_mode_none, k_game_mode_count> game_mode; // 0x29
    c_enum_no_init<e_game_engine_type, char, _game_engine_type_none, k_game_engine_type_count> game_engine_type; // 0x2A
    unsigned char pad2B[0x1]; // 0x2B
    long unknown2C; // 0x2C set to -1 by set_defaults; map id per content_item_metadata_set_from_game_options
    char unknown30; // 0x30 set to -1 by set_defaults; custom variant category index per content_item_metadata_set_from_game_options
    unsigned char unknown31[0x7]; // 0x31
    s_content_item_history creation_history; // 0x38 name unverified (initialized by content_item_metadata_create)
    s_content_item_history modification_history; // 0x5C (initialized by content_item_metadata_modify)
    wchar_t name[128]; // 0x80
    unsigned char unknown180[0x100]; // 0x180
    char unknown280; // 0x280
    unsigned char unknown281[0xF]; // 0x281
    short unknown290; // 0x290 from s_game_options 0xFA56
    unsigned char unknown292[0xE]; // 0x292
    union
    {
        s_content_item_campaign_metadata campaign; // 0x2A0
        s_content_item_survival_metadata survival; // 0x2A0
    };
    unsigned char unknown2A8[0x8]; // 0x2A8
};
#pragma pack(pop)
static_assert(sizeof(s_content_item_metadata) == 0x2B0, "s_content_item_metadata");

// passed to s_content_item_metadata * parameters without adjustment (variant_definitions.obj)
class c_content_item_metadata :
    public s_content_item_metadata
{
};

class c_bitstream;

/* ---------- prototypes */

extern void content_item_metadata_initialize(s_content_item_metadata * metadata, e_content_item_type content_type, unsigned long size_in_bytes, wchar_t const * name, wchar_t const * description);
extern void content_item_metadata_initialize_built_in_history(s_content_item_metadata * metadata, unsigned __int64 timestamp);
extern void content_item_metadata_decode(c_bitstream * packet, s_content_item_metadata * metadata);
extern bool content_item_metadata_valid(s_content_item_metadata const * metadata);

/* ---------- globals */

/* ---------- public code */

#endif // __CONTENT_ITEM_METADATA_H__

