#pragma once
#ifndef __TAG_GROUPS_H__
#define __TAG_GROUPS_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\data_array.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_instance_datum;
struct s_tag_block_definition;
struct s_tag_data_definition;
struct s_tag_resource;

// $TODO layout: only the leading fields are reversed (from ?shader_group@@3Us_tag_group@@A data); sizeof unknown
struct s_tag_group
{
    char const * name; // 0x0
    unsigned long flags; // 0x4
    unsigned long group_tag; // 0x8
    unsigned long parent_group_tag; // 0xC
    short version; // 0x10
    s_tag_block_definition * block_definition; // 0x14
};

class c_allocation_interface;
class c_persist_stream;
class c_tag_allocator;
struct s_tag_struct_definition;
template<typename t_type> class c_basic_buffer;

// vtable order from ??_7c_tag_resource_persist_manager_simple@@6Bc_tag_resource_persist_writer@@@
class c_tag_resource_persist_writer
{
public:
    virtual bool resource_is_cached_for_xsync(s_tag_resource const * resource) = 0;
    virtual unsigned long get_xsync_state_version(void) = 0;
    virtual bool save_xsync_state(c_allocation_interface * allocator, s_tag_resource const * resource, c_persist_stream * persist_stream) = 0;
    virtual bool resource_available(s_tag_resource const * resource) = 0;
    virtual void * get_resource_data(s_tag_resource const * resource) = 0;
};
static_assert(sizeof(c_tag_resource_persist_writer) == 0x4, "c_tag_resource_persist_writer");

// vtable order from ??_7c_tag_resource_persist_manager_simple@@6Bc_tag_resource_persist_reader@@@
class c_tag_resource_persist_reader
{
public:
    virtual bool restore_xsync_state_and_register(unsigned long xsync_state_version, s_tag_resource * resource, c_persist_stream * persist_stream) = 0;
    virtual bool resource_available(s_tag_resource const * resource) = 0;
    virtual void * get_mutable_resource_data(s_tag_resource const * resource) = 0;
    virtual bool allocate_resource(s_tag_resource * resource) = 0;
    virtual void free_resource(s_tag_resource * resource) = 0;
    virtual bool matches_tag_allocator(c_tag_allocator * allocator) = 0;
};
static_assert(sizeof(c_tag_resource_persist_reader) == 0x4, "c_tag_resource_persist_reader");

struct s_tag_persistent_identifier
{
    unsigned long data[4]; // 0x0
};
static_assert(sizeof(s_tag_persistent_identifier) == 0x10, "s_tag_persistent_identifier");

struct s_tag_resource_definition;

// vtable from ??_7c_tag_resource_definition_dictionary@@6B@ (0x8214756C, 1 slot); slot name from c_default_tag_resource_definition_dictionary
class c_tag_resource_definition_dictionary
{
public:
    virtual s_tag_resource_definition const * lookup_resource_definition(s_tag_persistent_identifier const & persistent_identifier) = 0;
};
static_assert(sizeof(c_tag_resource_definition_dictionary) == 0x4, "c_tag_resource_definition_dictionary");

class c_tag_index
{
public:
    // inline in the target (f i, projectiles.obj): empty body
    c_tag_index(void);

    operator long(void) const
    {
        mangled_ppc("??Bc_tag_index@@QBAJXZ");

        return m_index;
    };

    long m_index; // 0x0
};
static_assert(sizeof(c_tag_index) == 0x4, "c_tag_index");

struct s_tag_block
{
    long count; // 0x0
    void * address; // 0x4
    s_tag_block_definition const * definition; // 0x8
};
static_assert(sizeof(s_tag_block) == 0xC, "s_tag_block");

struct s_tag_data
{
    long size; // 0x0
    unsigned long internal_flags; // 0x4
    unsigned long file_offset; // 0x8
    void * address; // 0xC
    s_tag_data_definition const * definition; // 0x10
};
static_assert(sizeof(s_tag_data) == 0x14, "s_tag_data");

struct s_tag_reference
{
    unsigned long group_tag; // 0x0
    char const * name; // 0x4
    long name_length; // 0x8
    long index; // 0xC
};
static_assert(sizeof(s_tag_reference) == 0x10, "s_tag_reference");

// layout from H3 (flags verified by add_single_tag_dependency)
struct s_tag_reference_definition
{
    unsigned long flags; // 0x0
    unsigned long group_tag; // 0x4
    unsigned long const * group_tags; // 0x8
};
static_assert(sizeof(s_tag_reference_definition) == 0xC, "s_tag_reference_definition");

struct s_tag_interop_definition;

struct s_tag_interop
{
    void * descriptor; // 0x0
    void * address; // 0x4
    s_tag_interop_definition const * definition; // 0x8
};
static_assert(sizeof(s_tag_interop) == 0xC, "s_tag_interop");

struct tag_iterator
{
    c_data_iterator<s_tag_instance_datum> iterator; // 0x0
    unsigned long key_group_tag; // 0x14
};
static_assert(sizeof(tag_iterator) == 0x18, "tag_iterator");

// vtable order from ??_7c_tag_allocator@@6B@ (0x82147DCC), names from c_default_tag_allocator
class c_tag_allocator
{
public:
    virtual long string_id_new(char const * string) = 0;
    virtual char const * string_id_get_string_const(long string_id) = 0;
    virtual void string_id_release(long string_id) = 0;
    virtual char const * add_tracked_string(char const * string) = 0;
    virtual void remove_tracked_string(char const * string) = 0;
    virtual void * allocate(long size, long alignment, char const * name, unsigned long flags) = 0;
    virtual void deallocate(void * address, long size, unsigned long flags) = 0;
    virtual void * allocate_temporary(long size, long alignment, char const * name) = 0;
    virtual void deallocate_temporary(void * address, long size) = 0;
};
static_assert(sizeof(c_tag_allocator) == 0x4, "c_tag_allocator");

/* ---------- prototypes */

long tag_load(unsigned long group_tag, char const * name, unsigned long flags);
void tag_unload(long tag_index);
void tag_reference_copy(s_tag_reference const * source, s_tag_reference * destination);
bool reference_points_somewhere(s_tag_reference const * reference);
unsigned long tag_get_group_tag(long tag_index);
s_tag_group const * tag_group_get(unsigned long group_tag);
void tag_iterator_new(tag_iterator * iterator, unsigned long group_tag);
long tag_iterator_next(tag_iterator * iterator);
char const * tag_name_strip_path(char const * name);
char const * tag_get_name_safe(long tag_index);
char const * tag_get_name(long tag_index);
char const * tag_group_get_name(unsigned long group_tag);
s_tag_block * tag_get_root_block(long tag_index);
void * tag_get(unsigned long group_tag, long tag_index);
void * tag_block_get_element_with_size(s_tag_block const * block, long element_index, long element_size);
void * tag_block_get_range_with_size(s_tag_block const * block, long first_element_index, long element_count, long element_size);
void * tag_block_get_element(s_tag_block const * block, long element_index);
s_tag_block * tag_try_and_get_alternate_stream_block(long tag_index, unsigned long stream_tag);
void * tag_data_get_pointer(s_tag_data const * data, long offset, long size);
long tag_block_add_element(s_tag_block * block);
long tag_block_insert_element(s_tag_block * block, long element_index);
bool tag_block_resize(s_tag_block * block, long element_count);
bool tag_data_resize(s_tag_data * data, long size);
void tag_reference_clear(s_tag_reference * reference);
void tag_reference_set(s_tag_reference * reference, unsigned long group_tag, char const * name);
void tag_block_delete_all_elements(s_tag_block * block);
void tag_reference_initialize(s_tag_reference * reference);
void tag_block_initialize(s_tag_block * block, s_tag_block_definition const * definition);
void destroy_tag_reference(s_tag_reference * reference);
unsigned long group_name_to_group_tag(char const * group_name);
long tag_loaded(unsigned long group_tag, char const * name);
bool tag_rename(long tag_index, char const * new_name);
long tag_new(unsigned long group_tag, char const * name);
void reassign_tag_block_and_memory(s_tag_block * destination, s_tag_block * source);
bool duplicate_recursive_tag_block_elements(s_tag_block const * source_block, s_tag_block * destination_block);
bool tag_struct_construct_in_place(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & struct_buffer, unsigned long flags);
void tag_struct_destroy_in_place(s_tag_struct_definition const * struct_definition, c_basic_buffer<void> & struct_buffer, unsigned long flags);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUPS_H__

