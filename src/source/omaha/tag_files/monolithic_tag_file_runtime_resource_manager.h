#pragma once
#ifndef __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__
#define __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__

/* ---------- headers */

#include "foundation\baselib\memory\allocation_interface.h"
#include "omaha\tag_files\tag_resource_runtime.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_allocator;

class c_tag_allocator_wrapper_to_allocation_base :
    public c_allocation_interface
{
public:
    c_tag_allocator_wrapper_to_allocation_base(void);

    void set_allocator(c_tag_allocator * allocator);

    virtual void * allocate(unsigned int, char const *, long, char const *, char const *, char const *);
    virtual void deallocate(void *, char const *, long);

private:
    c_tag_allocator * m_actual_allocator;
};

class c_monolithic_tag_file_single_zone_set_resource_set :
    public c_tag_resource_runtime_active_set
{
public:
    void initialize(c_tag_resource_runtime_listener * listener);

    virtual bool any_resources_active(void) const;
    virtual bool is_resource_required(long, long) const;
    virtual bool is_resource_deferred(long, long) const;

private:
    c_tag_resource_runtime_listener * __unknown4;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__

