#pragma once
#ifndef __TAG_COPY_PASTE_H__
#define __TAG_COPY_PASTE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_runtime_platform_type;

class c_allocation_interface;
class c_persist_stream;
class c_tag_allocator;
class c_tag_field_editor_manager;
class c_tag_resource_persist_reader;
class c_tag_resource_persist_writer;

// vtable order from ??_7c_tag_group_files_persist_context@@6B@
class c_tag_persist_context
{
public:
    virtual c_persist_stream * get_root_data_stream(void) = 0;
    virtual c_tag_field_editor_manager * get_editor_manager(void) = 0;
    virtual c_tag_allocator * get_allocator(void) = 0;
    virtual c_allocation_interface * get_scratch_allocator(void) = 0;
    virtual c_tag_resource_persist_reader * get_resource_reader(void) = 0;
    virtual c_tag_resource_persist_writer * get_resource_writer(void) = 0;
    virtual e_runtime_platform_type get_runtime_platform(void) = 0;
    virtual bool editing(void) = 0;
    virtual bool for_checkpoint(void) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_COPY_PASTE_H__

