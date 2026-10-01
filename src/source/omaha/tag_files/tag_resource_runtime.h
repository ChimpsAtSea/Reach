#ifndef __TAG_RESOURCE_RUNTIME_H__
#define __TAG_RESOURCE_RUNTIME_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource_definition;
struct s_tag_group;

template<typename t_type> class c_wrapped_array;

// vtable order from ??_7c_cache_file_tag_resource_runtime_manager@@6Bc_tag_resource_runtime_active_set@@@
class c_tag_resource_runtime_active_set
{
public:
    virtual bool any_resources_active(void) const = 0;
    virtual bool is_resource_required(long owner_index, long resource_index) const = 0;
    virtual bool is_resource_deferred(long owner_index, long resource_index) const = 0;
    virtual bool is_resource_pending(long owner_index, long resource_index) const = 0;
    virtual bool describe_active_set(c_wrapped_array<char> description) const = 0;
};
static_assert(sizeof(c_tag_resource_runtime_active_set) == 0x4, "c_tag_resource_runtime_active_set");

// vtable order from ??_7c_tag_resource_runtime_listener_simple@@6B@
class c_tag_resource_runtime_listener
{
public:
    virtual long lookup_resource_owner(s_tag_group const * group, char const * name) = 0;
    virtual bool resource_owner_is_reloading(long owner_index) = 0;
    virtual bool describe_resource_owner(long owner_index, s_tag_group const ** out_group, c_wrapped_array<char> out_name) = 0;
    virtual c_tag_resource_runtime_active_set * get_resource_active_set_dont_cache(void) = 0;
    virtual bool register_resource(long owner_index, long resource_index, s_tag_resource_definition const * definition, void * data) = 0;
    virtual void unregister_resource(long owner_index, long resource_index, s_tag_resource_definition const * definition, void * data) = 0;
};
static_assert(sizeof(c_tag_resource_runtime_listener) == 0x4, "c_tag_resource_runtime_listener");

struct s_tag_resource
{
    long resource_handle; // 0x0
    s_tag_resource_definition const * definition; // 0x4
};
static_assert(sizeof(s_tag_resource) == 0x8, "s_tag_resource");

class c_tag_resource_prediction_filter
{
public:
    c_tag_resource_prediction_filter()
    {
        mangled_ppc("??0c_tag_resource_prediction_filter@@QAA@XZ");
    };

    virtual bool should_predict_through_tag(long tag_index) = 0;
};

/* ---------- prototypes */

long tag_resources_lock_game(void);
void tag_resources_unlock_game(long & lock_key);
void tag_resource_initialize(s_tag_resource * resource, s_tag_resource_definition const * definition);

void tag_resources_set_prediction_filter(c_tag_resource_prediction_filter * filter);

template<typename t_type> class c_basic_buffer;
c_basic_buffer<void> tag_resources_try_to_steal_memory(unsigned long size);
void tag_resources_return_memory(c_basic_buffer<void> buffer);

/* ---------- globals */

/* ---------- public code */

// f i (scenario.obj)
class c_tag_resources_game_lock
{
public:
    c_tag_resources_game_lock(void)
    {
        mangled_ppc("??0c_tag_resources_game_lock@@QAA@XZ");

        m_resource_key = tag_resources_lock_game();
    };

    ~c_tag_resources_game_lock(void)
    {
        mangled_ppc("??1c_tag_resources_game_lock@@QAA@XZ");

        tag_resources_unlock_game(m_resource_key);
    };

private:
    long m_resource_key; // 0x0
};
static_assert(sizeof(c_tag_resources_game_lock) == 0x4, "c_tag_resources_game_lock");

#endif // __TAG_RESOURCE_RUNTIME_H__

