#pragma once
#ifndef __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__
#define __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "omaha\tag_files\tag_resource_runtime.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_allocator;

// vtable ??_7c_tag_allocator_wrapper_to_allocation_base@@6B@: allocate, deallocate
class c_tag_allocator_wrapper_to_allocation_base :
    public c_allocation_interface
{
public:
    c_tag_allocator_wrapper_to_allocation_base(void);

    void set_allocator(c_tag_allocator * allocator);

    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);

private:
    c_tag_allocator * m_actual_allocator; // 0x4
};
static_assert(sizeof(c_tag_allocator_wrapper_to_allocation_base) == 0x8, "c_tag_allocator_wrapper_to_allocation_base");

// forwards the active set queries to the listener's active set
class c_monolithic_tag_file_single_zone_set_resource_set :
    public c_tag_resource_runtime_active_set
{
public:
    void initialize(c_tag_resource_runtime_listener * listener);

    virtual bool any_resources_active(void) const;
    virtual bool is_resource_required(long owner_index, long resource_index) const;
    virtual bool is_resource_deferred(long owner_index, long resource_index) const;

private:
    c_tag_resource_runtime_listener * m_listener; // 0x4
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MONOLITHIC_TAG_FILE_RUNTIME_RESOURCE_MANAGER_H__
