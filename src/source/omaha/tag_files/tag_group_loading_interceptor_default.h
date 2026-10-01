#pragma once
#ifndef __TAG_GROUP_LOADING_INTERCEPTOR_DEFAULT_H__
#define __TAG_GROUP_LOADING_INTERCEPTOR_DEFAULT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_files.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block;
struct s_tag_group;

class c_tag_alternate_stream_consumer;

// vtable ??_7c_tag_instance_loader@@6B@ (tag_groups.obj): 1 slot
class c_tag_instance_loader
{
public:
    virtual bool load_into_block(s_tag_block * block, s_tag_group const * group, char const * name, c_load_tag_flag flags, e_tag_file_open_result * open_result, bool * out_unknown, unsigned long * checksum, c_tag_alternate_stream_consumer * stream_consumer) = 0;
};
static_assert(sizeof(c_tag_instance_loader) == 0x4, "c_tag_instance_loader");

// vtable ??_7c_tag_file_backend_loader@@6B@ (tag_groups.obj)
class c_tag_file_backend_loader :
    public c_tag_instance_loader
{
public:
    virtual bool load_into_block(s_tag_block * block, s_tag_group const * group, char const * name, c_load_tag_flag flags, e_tag_file_open_result * open_result, bool * out_unknown, unsigned long * checksum, c_tag_alternate_stream_consumer * stream_consumer);
};
static_assert(sizeof(c_tag_file_backend_loader) == 0x4, "c_tag_file_backend_loader");

// vtable ??_7c_tag_instance_loader_redirector@@6B@ (tag_groups.obj): 4 slots
class c_tag_instance_loader_redirector
{
public:
    virtual c_tag_instance_loader * lookup_instance_loader(s_tag_group const * group, char const * name, c_load_tag_flag flags) = 0;
    virtual void reset_instance_loader(void) = 0;
    virtual char const * get_name(void) = 0;
    virtual void release_instance_loader(c_tag_instance_loader * instance_loader) = 0;
};
static_assert(sizeof(c_tag_instance_loader_redirector) == 0x4, "c_tag_instance_loader_redirector");

// vtable ??_7c_default_tag_instance_loader_redirector@@6B@ (tag_groups.obj)
class c_default_tag_instance_loader_redirector :
    public c_tag_instance_loader_redirector
{
public:
    virtual c_tag_instance_loader * lookup_instance_loader(s_tag_group const * group, char const * name, c_load_tag_flag flags);
    virtual void reset_instance_loader(void);
    virtual char const * get_name(void);
    virtual void release_instance_loader(c_tag_instance_loader * instance_loader);

protected:
    c_tag_file_backend_loader m_default_loader; // 0x4
};
static_assert(sizeof(c_default_tag_instance_loader_redirector) == 0x8, "c_default_tag_instance_loader_redirector");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUP_LOADING_INTERCEPTOR_DEFAULT_H__
