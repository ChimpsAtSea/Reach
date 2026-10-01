#pragma once
#ifndef __LOCATION_NAME_DEFINITIONS_H__
#define __LOCATION_NAME_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    LOCATION_NAME_GLOBALS_TAG = 'locs',
};

/* ---------- definitions */

struct s_location_name_tag_definition
{
    long name; // 0x0
};
static_assert(sizeof(s_location_name_tag_definition) == 0x4, "s_location_name_tag_definition");

struct s_location_name_globals_tag_definition
{
    s_tag_block location_names; // 0x0
    s_tag_reference location_name_string_list; // 0xC
};
static_assert(sizeof(s_location_name_globals_tag_definition) == 0x1C, "s_location_name_globals_tag_definition");

/* ---------- prototypes */

long location_names_get_name_count(void);
long location_names_get_name(long location_name_index);
s_location_name_globals_tag_definition const * try_and_get_location_name_globals(void);
long location_names_get_name_index_from_string_id(long name);

/* ---------- globals */

/* ---------- public code */

#endif // __LOCATION_NAME_DEFINITIONS_H__

