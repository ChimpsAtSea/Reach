#pragma once
#ifndef __VARIANT_DEFINITIONS_H__
#define __VARIANT_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    VARIANT_GLOBALS_TAG = 'vtgl'
};

/* ---------- definitions */

class c_content_item_metadata;
class c_game_variant;
class c_map_variant;

struct s_single_variant_definition
{
    bool get_metadata(c_content_item_metadata * out_metadata) const;

    s_tag_data metadata; // 0x0
    s_tag_data full_data; // 0x14
    char filename[256]; // 0x28
};
static_assert(sizeof(s_single_variant_definition) == 0x128, "s_single_variant_definition");

struct s_variant_globals_definition
{
    enum
    {
        k_variant_globals_per_block_count_maximum = 1024
    };

    s_tag_block map_variants; // 0x0
    s_tag_block game_variants; // 0xC
};
static_assert(sizeof(s_variant_globals_definition) == 0x18, "s_variant_globals_definition");

/* ---------- prototypes */

s_variant_globals_definition const * variant_globals_try_and_get(void);
bool variant_definition_decode_map_variant(s_single_variant_definition const * map_variant_definition, c_map_variant * out_map_variant);
bool variant_definition_decode_custom_game_variant(s_single_variant_definition const * game_variant_definition, c_game_variant * out_game_variant);

/* ---------- globals */

/* ---------- public code */

#endif // __VARIANT_DEFINITIONS_H__

