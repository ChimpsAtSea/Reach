#pragma once
#ifndef __PLAYER_COOKIE_DEFINITIONS_H__
#define __PLAYER_COOKIE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    COOKIE_GLOBALS_DEFINITION_TAG = 'cook',
};

/* ---------- definitions */

// cookie_award_definition_block
struct s_cookie_award_definition
{
    long name; // 0x0 string_id
    char type; // 0x4
    char pad0[0x1]; // 0x5
    short cookie_amount; // 0x6
};
static_assert(sizeof(s_cookie_award_definition) == 0x8, "s_cookie_award_definition");

// cookie_globals_definition_block ('cook')
struct s_cookie_globals_definition
{
    s_tag_block cookie_awards; // 0x0 s_cookie_award_definition
};
static_assert(sizeof(s_cookie_globals_definition) == 0xC, "s_cookie_globals_definition");

/* ---------- prototypes */

long cookie_globals_get_cookie_award_definition_index_by_name(s_cookie_globals_definition const * cookie_globals, long name);
s_cookie_award_definition const * cookie_globals_get_cookie_award_definition_by_name(s_cookie_globals_definition const * cookie_globals, long name);
s_cookie_globals_definition const * cookie_globals_try_and_get();

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_COOKIE_DEFINITIONS_H__

