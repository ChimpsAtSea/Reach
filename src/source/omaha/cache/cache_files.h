#pragma once
#ifndef __CACHE_FILES_H__
#define __CACHE_FILES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

struct s_cache_file_loaded_tags_header;

struct s_cache_file_tag_instance_bounds
{
    long first_tag_instance_index; // 0x0
    long tag_instance_count; // 0x4
};
static_assert(sizeof(s_cache_file_tag_instance_bounds) == 0x8, "s_cache_file_tag_instance_bounds");

/* ---------- prototypes */

void cache_file_get_instance_bounds_from_header(s_cache_file_loaded_tags_header const * tags_header, s_cache_file_tag_instance_bounds * instance_bounds);
c_static_string<256> cache_file_get_path(char const * scenario_name);

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILES_H__

