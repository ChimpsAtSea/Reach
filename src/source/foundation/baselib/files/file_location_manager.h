#pragma once
#ifndef __FILE_LOCATION_MANAGER_H__
#define __FILE_LOCATION_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

enum e_file_location
{
    k_file_location_invalid = -1,

    _file_location_development_relative = 0,

    // $TODO: names of locations 1-4 unknown (1-2: working directory on devkit else media read-only, 3-4: utility drives 0-1)
    _file_location_1,
    _file_location_2,
    _file_location_3,
    _file_location_4,

    k_file_location_count,
};

enum e_file_location_usage_mode
{
    _file_location_read = 0,
    _file_location_write,

    k_file_location_usage_mode_count,
};

enum e_file_location_device
{
    // $TODO: enumerator names unknown
};

/* ---------- definitions */

struct s_file_available_location
{
    e_file_location_device device; // 0x0
    s_static_string<256> path; // 0x4
};
static_assert(sizeof(s_file_available_location) == 0x104, "s_file_available_location");

struct s_file_location
{
    s_flags<e_file_location_usage_mode, unsigned long, k_file_location_usage_mode_count> usage_flags; // 0x0
    e_file_location_device device; // 0x4
    s_static_string<256> root_path; // 0x8
};
static_assert(sizeof(s_file_location) == 0x108, "s_file_location");

struct s_file_location_globals
{
    s_static_array<s_file_location, k_file_location_count> locations; // 0x0
};
static_assert(sizeof(s_file_location_globals) == 0x528, "s_file_location_globals");

/* ---------- prototypes */

extern void file_locations_initialize(void);
extern s_file_location_globals const * file_location_globals_get(void);
extern bool file_location_available(e_file_location location, e_file_location_usage_mode usage_mode);
extern e_file_location_device file_location_get_device_type(e_file_location location);
extern char const * file_location_get_root_absolute_path(e_file_location location);
extern void file_locations_configure(s_file_location_globals * globals);
extern void file_location_set_read_only(s_file_location * file_location, s_file_available_location const * available_location);
extern void file_location_set_read_write(s_file_location * file_location, s_file_available_location const * available_location);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_LOCATION_MANAGER_H__

