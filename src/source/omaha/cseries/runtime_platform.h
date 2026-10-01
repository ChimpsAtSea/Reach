#pragma once
#ifndef __RUNTIME_PLATFORM_H__
#define __RUNTIME_PLATFORM_H__

/* ---------- headers */

/* ---------- constants */

enum e_runtime_platform_type
{
    _runtime_platform_xbox = 0,
    _runtime_platform_not_xbox,

    NUMBER_OF_RUNTIME_PLATFORMS,

    _runtime_platform_pc = _runtime_platform_not_xbox,
};

/* ---------- definitions */

/* ---------- prototypes */

e_runtime_platform_type get_runtime_platform_type(void);
e_runtime_platform_type set_runtime_platform_type(e_runtime_platform_type new_type);
bool runtime_platform_needs_byteswapping(void);
bool runtime_platform_needs_byteswapping(e_runtime_platform_type runtime_platform);
bool runtime_platform_building_for_cache_file(void);
void set_runtime_platform_building_for_cache_file(bool building);
bool runtime_platform_building_for_cache_file_cache(void);
void set_runtime_platform_building_for_cache_file_cache(bool building);
bool runtime_platform_building_cache_file_for_ship(void);
void set_runtime_platform_building_cache_file_for_ship(bool building);
bool runtime_platform_building_for_cache_file_language_specific_cache(void);
void set_runtime_platform_building_for_cache_file_language_specific_cache(bool building);
char const *describe_runtime_platform_type(e_runtime_platform_type runtime_platform);
bool runtime_platform_on_target_platform(void);

/* ---------- globals */

extern e_runtime_platform_type active_type;
extern bool g_building_cache_file;
extern bool g_building_cache_file_cache;
extern bool g_building_cache_file_for_ship;
extern bool g_building_cache_file_language_specific_cache;

/* ---------- public code */

#endif // __RUNTIME_PLATFORM_H__

