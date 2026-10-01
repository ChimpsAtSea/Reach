#pragma once
#ifndef __CACHE_FILES_WINDOWS_H__
#define __CACHE_FILES_WINDOWS_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\scenario\scenario.h"

/* ---------- constants */

enum e_cache_file_shared_file_type
{
    _shared_file_mainmenu = 0,
    _shared_file_multiplayer,
    _shared_file_campaign,

    k_number_of_shared_file_types
};

/* ---------- definitions */

/* ---------- prototypes */

bool cache_file_map_should_open_directly(char const * map_name);
long cache_file_round_up_read_size(long size);
c_static_string<256> cache_file_get_canonical_path(char const * scenario_path);
long cache_file_get_maximum_size(e_scenario_type scenario_type);
long cache_file_get_absolute_maximum_size(void);
unsigned long cache_files_get_estimated_dvd_speed(void);
char const * cache_file_shared_get_file_name(e_cache_file_shared_file_type shared_file_type);
c_static_string<256> cache_file_shared_get_file_path(e_cache_file_shared_file_type shared_file_type);

/* ---------- globals */

extern bool g_log_precache_progress;
extern char const * const k_primary_cache_drive_path;
extern char const * const k_secondary_cache_drive_path;
extern char const * k_shared_file_type_names[k_number_of_shared_file_types];
extern bool display_precache_progress;

/* ---------- public code */

#endif // __CACHE_FILES_WINDOWS_H__

