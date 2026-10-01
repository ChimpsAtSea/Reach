#pragma once
#ifndef __PLAYER_MEDALS_H__
#define __PLAYER_MEDALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

enum
{
    GAME_MEDAL_GLOBALS_TAG = 'gmeg',
};

/* ---------- definitions */

// game_medal_block
struct s_game_medal_definition
{
    enum
    {
        k_maximum_game_medal_definitions = 128
    };

    long name; // 0x0 string_id
    long description; // 0x4 string_id
    float horizontal_scale; // 0x8
    float vertical_scale; // 0xC
    char sequence_index; // 0x10
    char medal_class; // 0x11
    short rank; // 0x12
    long maximum_stat_count; // 0x14
};
static_assert(sizeof(s_game_medal_definition) == 0x18, "s_game_medal_definition");

// game_medal_globals_block ('gmeg')
struct s_game_medal_globals
{
    s_tag_block medals; // 0x0 s_game_medal_definition
};
static_assert(sizeof(s_game_medal_globals) == 0xC, "s_game_medal_globals");

class c_game_medal_block_struct_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static bool postprocess_proc(long tag_index, void * data, bool for_editor)
    {
        mangled_ppc("?postprocess_proc@c_game_medal_block_struct_vtable@@SA_NJPAX_N@Z");

        s_game_medal_definition * medal = static_cast<s_game_medal_definition *>(data);
        if (medal->horizontal_scale == 0.0f)
        {
            medal->horizontal_scale = 1.0f;
        }
        if (medal->vertical_scale == 0.0f)
        {
            medal->vertical_scale = 1.0f;
        }
        return true;
    }

    static bool on_new_proc(void * data)
    {
        mangled_ppc("?on_new_proc@c_game_medal_block_struct_vtable@@SA_NPAX@Z");

        s_game_medal_definition * medal = static_cast<s_game_medal_definition *>(data);
        medal->maximum_stat_count = 1023;
        return true;
    }
};

/* ---------- prototypes */

long game_medal_definition_get_count();
s_game_medal_definition const * game_medal_definition_get(long medal_index);
long game_medal_definition_find(long name);

/* ---------- globals */

extern c_tag_struct_vtable<c_game_medal_block_struct_vtable> game_medal_block_struct_struct_vtable;

/* ---------- public code */

#endif // __PLAYER_MEDALS_H__

