#pragma once
#ifndef __PLAYER_GRADE_DEFINITIONS_H__
#define __PLAYER_GRADE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    PLAYER_GRADE_GLOBALS_DEFINITION_TAG = 'pggd',
};

enum e_player_grade
{
    _player_grade_first = 0,

    k_player_grade_count = 21
};

enum e_player_sub_grade
{
    _player_sub_grade_first = 0,

    k_player_sub_grade_count = 5
};

/* ---------- definitions */

// player_sub_grade_definition_block
struct s_player_sub_grade_definition
{
    long cookie_threshold; // 0x0
    long name; // 0x4 string_id
    short sprite_index; // 0x8
    char pad0[0x2]; // 0xA
};
static_assert(sizeof(s_player_sub_grade_definition) == 0xC, "s_player_sub_grade_definition");

// player_grade_definition_block
struct s_player_grade_definition
{
    s_tag_block sub_grades; // 0x0 s_player_sub_grade_definition
};
static_assert(sizeof(s_player_grade_definition) == 0xC, "s_player_grade_definition");

// player_grade_globals_definition_block ('pggd')
struct s_player_grade_globals_definition
{
    s_tag_block player_grades; // 0x0 s_player_grade_definition
};
static_assert(sizeof(s_player_grade_globals_definition) == 0xC, "s_player_grade_globals_definition");

/* ---------- prototypes */

s_player_grade_globals_definition const * player_grade_globals_try_and_get();
char * format_player_sub_grade_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
char * format_player_grade_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size);
bool pggd_postprocess(long element_index, s_player_grade_globals_definition * definition, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_GRADE_DEFINITIONS_H__

