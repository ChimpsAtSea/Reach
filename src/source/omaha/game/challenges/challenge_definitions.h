#pragma once
#ifndef __CHALLENGE_DEFINITIONS_H__
#define __CHALLENGE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_maximum_challenge_categories = 10,
    k_maximum_challenges_per_category = 200,
};

/* ---------- definitions */

// field names from the challenge_block tag definition
struct s_challenge_definition
{
    long challenge_name; // 0x0
    long display_string; // 0x4
    long display_name; // 0x8
    long display_description; // 0xC
    long completion_toast_string; // 0x10
    long required_progress_count; // 0x14
    long cookie_reward; // 0x18
    long progress_tracking_interval; // 0x1C
    long chud_progress_string; // 0x20
    long chud_progress_bitmap_sequence_index; // 0x24
    unsigned char flags; // 0x28
    unsigned char pad[3]; // 0x29
    unsigned long auto_progress_on; // 0x2C
    unsigned char unknown30[0x50 - 0x30]; // 0x30 permitted game types, level_name, map_id, skulls, ...
};
static_assert(sizeof(s_challenge_definition) == 0x50, "s_challenge_definition");

struct s_challenge_category_definition
{
    long category_name; // 0x0
    char challenge_category; // 0x4
    unsigned char pad[3]; // 0x5
    s_tag_block challenges; // 0x8
};
static_assert(sizeof(s_challenge_category_definition) == 0x14, "s_challenge_category_definition");

struct s_challenge_globals_definition
{
    s_tag_block challenge_categories; // 0x0
};
static_assert(sizeof(s_challenge_globals_definition) == 0xC, "s_challenge_globals_definition");

class c_challenge_definition_iterator
{
public:
    c_challenge_definition_iterator(s_challenge_globals_definition const * globals);
    bool next(void);
    s_challenge_definition const * get(void);
    s_challenge_category_definition const * get_category(void);

protected:
    short m_category_index; // 0x0
    short m_challenge_index; // 0x2
    s_challenge_globals_definition const * m_globals; // 0x4
};
static_assert(sizeof(c_challenge_definition_iterator) == 0x8, "c_challenge_definition_iterator");

/* ---------- prototypes */

s_challenge_definition const * challenge_definition_find(long challenge_name);
s_challenge_globals_definition const * challenge_globals_definition_try_and_get(void);
s_challenge_category_definition const * challenge_category_definition_try_and_get(long category_index);
s_challenge_definition const * challenge_definition_try_and_get(long category_index, long challenge_index);
bool challenge_globals_postprocess(long tag_index, bool for_editor);

/* ---------- globals */

/* ---------- public code */

#endif // __CHALLENGE_DEFINITIONS_H__

