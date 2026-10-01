#pragma once
#ifndef __OPTIONAL_CACHE_CONSTANTS_H__
#define __OPTIONAL_CACHE_CONSTANTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

enum e_optional_cache_user
{
    _optional_cache_user_cache_file_copying = 0,
    _optional_cache_user_bink,
    _optional_cache_user_screenshots,
    _optional_cache_user_game_state_saving,
    _optional_cache_user_game_state_loading,
    _optional_cache_user_game_state_compressor,

    k_number_of_optional_cache_users
};

enum e_optional_cache_user_priority
{
    _optional_cache_user_can_fail = 0,
    _optional_cache_user_cant_fail_nonblocking,
    _optional_cache_user_cant_fail_blocking,

    k_number_of_optional_cache_user_priorities
};

enum e_map_memory_configuration;

/* ---------- definitions */

struct s_optional_cache_user_memory_configuration
{
    e_optional_cache_user_priority maximum_priority;
    unsigned long maximum_size;
};
static_assert(sizeof(s_optional_cache_user_memory_configuration) == 0x8, "s_optional_cache_user_memory_configuration");

struct s_optional_cache_priority_sizes
{
    unsigned long minimum_no_fail_size;
    unsigned long desired_no_fail_size;
    unsigned long minimum_can_fail_size;
    unsigned long desired_can_fail_size;
};
static_assert(sizeof(s_optional_cache_priority_sizes) == 0x10, "s_optional_cache_priority_sizes");

// vtable owned by game_state.obj (implicit inline constructor)
class c_optional_cache_user_callback
{
public:
    virtual char const * get_name(void) = 0;
    virtual void get_memory_configuration(e_map_memory_configuration map_configuration, s_optional_cache_user_memory_configuration * memory_configuration) = 0;
    virtual void idle(void const * pointer)
    {
        mangled_ppc("?idle@c_optional_cache_user_callback@@UAAXPBX@Z");
    };
    virtual void terminate(void const * pointer) = 0;
};
static_assert(sizeof(c_optional_cache_user_callback) == 0x4, "c_optional_cache_user_callback");

// vtable owned by cache_file_tag_resource_runtime.obj (implicit inline constructor)
class c_optional_cache_backend
{
public:
    virtual void initialize(e_map_memory_configuration map_configuration, s_static_array<s_optional_cache_user_memory_configuration, k_number_of_optional_cache_users> const * memory_configurations) = 0;
    virtual void dispose(void) = 0;
    virtual void * try_to_allocate(e_optional_cache_user user, e_optional_cache_user_priority priority, char const * file, long line, long size, c_optional_cache_user_callback * callback) = 0;
    virtual void deallocate(e_optional_cache_user user, char const * file, long line, void * pointer) = 0;
};
static_assert(sizeof(c_optional_cache_backend) == 0x4, "c_optional_cache_backend");

/* ---------- prototypes */

void optional_cache_calculate_priority_sizes(s_static_array<s_optional_cache_user_memory_configuration, k_number_of_optional_cache_users> const * memory_configurations, s_optional_cache_priority_sizes * out_priority_sizes);

/* ---------- globals */

/* ---------- public code */

#endif // __OPTIONAL_CACHE_CONSTANTS_H__

