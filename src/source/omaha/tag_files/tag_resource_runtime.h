#ifndef __TAG_RESOURCE_RUNTIME_H__
#define __TAG_RESOURCE_RUNTIME_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_group;
struct s_tag_resource_definition;

template<typename t_type> class c_wrapped_array;

class c_tag_resource_runtime_active_set
{
public:
    virtual bool any_resources_active(void) const = 0;
    virtual bool is_resource_required(long, long) const = 0;
    virtual bool is_resource_deferred(long, long) const = 0;
    virtual bool is_resource_pending(long, long) const = 0;
    virtual bool describe_active_set(c_wrapped_array<char>) const = 0;
};

class c_tag_resource_runtime_listener
{
public:
    virtual long lookup_resource_owner(s_tag_group const *, char const *) = 0;
    virtual bool resource_owner_is_reloading(long) = 0;
    virtual bool describe_resource_owner(long, s_tag_group const * *, c_wrapped_array<char>) = 0;
    virtual c_tag_resource_runtime_active_set * get_resource_active_set_dont_cache(void) = 0;
    virtual bool register_resource(long, long, s_tag_resource_definition const *, void *) = 0;
    virtual void unregister_resource(long, long, s_tag_resource_definition const *, void *) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_RESOURCE_RUNTIME_H__

