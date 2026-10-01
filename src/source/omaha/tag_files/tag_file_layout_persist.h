#pragma once
#ifndef __TAG_FILE_LAYOUT_PERSIST_H__
#define __TAG_FILE_LAYOUT_PERSIST_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_copy_paste.h"

/* ---------- constants */

/* ---------- definitions */

enum e_runtime_platform_type;
enum e_tag_file_open_result;

class c_allocation_interface;
class c_persist_stream;
class c_tag_allocator;
class c_tag_field_editor_manager;
class c_tag_resource_persist_reader;
class c_tag_resource_persist_writer;
class c_tag_resource_persist_manager;
class c_tag_resource_runtime_manager;
struct s_tag_block;
struct s_tag_block_definition;
struct s_tag_group;
template<typename t_type> class c_basic_buffer;

// layout from tag_load_new_from_backend (copies the 4 leading fields of s_tag_read_parameters) and c_tag_group_files_persist_context accessors
struct s_tag_persist_parameters
{
    c_allocation_interface * scratch_allocator; // 0x0
    c_tag_allocator * allocator; // 0x4
    c_tag_field_editor_manager * editor_manager; // 0x8
    e_runtime_platform_type runtime_platform; // 0xC
    c_tag_resource_persist_reader * resource_reader; // 0x10
    c_tag_resource_persist_writer * resource_writer; // 0x14
};
static_assert(sizeof(s_tag_persist_parameters) == 0x18, "s_tag_persist_parameters");

struct s_tag_read_parameters
{
    c_allocation_interface * scratch_allocator; // 0x0
    c_tag_allocator * allocator; // 0x4
    c_tag_field_editor_manager * editor_manager; // 0x8
    e_runtime_platform_type runtime_platform; // 0xC
};
static_assert(sizeof(s_tag_read_parameters) == 0x10, "s_tag_read_parameters");

// built in tag_file_read_into_block
struct s_tag_fixup_context
{
    c_tag_allocator * allocator; // 0x0
    c_tag_resource_persist_reader * resource_reader; // 0x4
    bool byte_swap; // 0x8
};
static_assert(sizeof(s_tag_fixup_context) == 0xC, "s_tag_fixup_context");

// vtable order from ??_7c_tag_group_fixupper_default@@6B@
class c_tag_group_fixupper
{
public:
    virtual bool fixup_tag(s_tag_block * source_block, s_tag_block * destination_block, s_tag_fixup_context const * fixup_context) = 0;
    virtual s_tag_block_definition const * get_source_block_definition(void) = 0;
    virtual s_tag_block_definition const * get_destination_block_definition(void) = 0;
    virtual bool xsynced_resources_still_valid(void) = 0;
};

// vtable order from c_single_tag_file_reader / c_single_tag_file_block_stream
class c_tag_file_read_interface
{
public:
    virtual c_tag_group_fixupper * get_group_fixupper(void) = 0;
    virtual c_persist_stream * get_root_data_stream(void) = 0;
    virtual void signal_complete(void) = 0;
};

// vtable order from c_single_tag_file_reader
class c_tag_file_alternate_stream_read_iterator
{
public:
    virtual bool next(void) = 0;
    virtual unsigned long get_alternate_stream_tag(void) = 0;
    virtual c_tag_file_read_interface * get_alternate_stream(s_tag_block_definition const * definition) = 0;
};

// vtable order from ??_7c_single_tag_file_read_backend@@6Bc_tag_file_read_backend@@@
class c_tag_file_read_backend
{
public:
    virtual ~c_tag_file_read_backend();
    virtual bool can_load_tags(void) = 0;
    virtual bool tag_file_exists(s_tag_group const * group, char const * name) = 0;
    virtual bool tag_file_get_checksum(s_tag_group const * group, char const * name, unsigned long * out_checksum) = 0;
    virtual c_tag_file_read_interface * load_tag_file(c_allocation_interface * allocator, s_tag_group const * group, char const * name, bool * out_unknown, unsigned long * out_checksum, e_tag_file_open_result * out_open_result, c_tag_file_alternate_stream_read_iterator ** out_alternate_stream_iterator) = 0;
    virtual void release_tag_file(s_tag_group const * group, char const * name, c_tag_file_read_interface * read_interface) = 0;
    virtual bool get_total_bytes_read(unsigned __int64 * out_total_bytes_read) = 0;
    virtual bool try_to_read_from_tag_file(s_tag_group const * group, char const * name, unsigned long offset, c_basic_buffer<void> buffer) = 0;
};

// vtable order from ??_7c_single_tag_file_resource_and_cache_builder_backend@@6Bc_tag_file_resource_backend@@@
class c_tag_file_resource_backend
{
public:
    virtual ~c_tag_file_resource_backend();
    virtual c_tag_resource_runtime_manager * get_runtime_manager(void) = 0;
    virtual c_tag_resource_persist_writer * get_persist_writer(void) = 0;
    virtual c_tag_resource_persist_reader * get_persist_reader(s_tag_group const * group, char const * name) = 0;
    virtual void release_persist_reader(s_tag_group const * group, char const * name, c_tag_resource_persist_reader * reader) = 0;
};

// vtable order from ??_7c_tag_group_stream_consumer@@6B@
class c_tag_alternate_stream_consumer
{
public:
    virtual bool can_keep_consuming_streams(void) = 0;
    virtual s_tag_block * get_stream_block_destination(unsigned long stream_tag, s_tag_block_definition const ** out_definition) = 0;
};

// vtable order from c_single_tag_file_writer
class c_tag_file_write_interface
{
public:
    virtual c_persist_stream * create_root_stream(void) = 0;
    virtual c_persist_stream * create_alternate_data_stream(unsigned long stream_tag, s_tag_block_definition const * definition) = 0;
    virtual bool commit_stream(c_persist_stream * stream) = 0;
};

// vtable order from ??_7c_single_tag_file_create_backend@@6B@
class c_tag_file_create_backend
{
public:
    virtual ~c_tag_file_create_backend();
    virtual c_tag_file_write_interface * create_tag_file(s_tag_group const * group, bool unknown) = 0;
    virtual bool save_tag_file(c_tag_file_write_interface * write_interface, char const * name, unsigned long * out_checksum) = 0;
    virtual void cancel_save_tag_file(c_tag_file_write_interface * write_interface) = 0;
};

// vtable order from ??_7c_tag_group_stream_iterator@@6B@
class c_tag_alternate_stream_iterator
{
public:
    virtual bool next(void) = 0;
    virtual unsigned long get_stream_tag(void) = 0;
    virtual s_tag_block * get_stream_block(void) = 0;
};

// vtable order from ??_7c_tag_group_files_persist_context@@6B@
class c_tag_group_files_persist_context :
    public c_tag_persist_context
{
public:
    c_tag_group_files_persist_context(c_persist_stream * root_data_stream, s_tag_persist_parameters const * persist_parameters, bool editing);

    virtual c_persist_stream * get_root_data_stream(void);
    virtual c_tag_field_editor_manager * get_editor_manager(void);
    virtual c_tag_allocator * get_allocator(void);
    virtual c_allocation_interface * get_scratch_allocator(void);
    virtual c_tag_resource_persist_reader * get_resource_reader(void);
    virtual c_tag_resource_persist_writer * get_resource_writer(void);
    virtual e_runtime_platform_type get_runtime_platform(void);
    virtual bool editing(void);
    virtual bool for_checkpoint(void);

private:
    c_persist_stream * m_root_data_stream; // 0x4
    s_tag_persist_parameters const * m_persist_parameters; // 0x8
    bool m_editing; // 0xC
    bool m_for_checkpoint; // 0xD
};
static_assert(sizeof(c_tag_group_files_persist_context) == 0x10, "c_tag_group_files_persist_context");

/* ---------- prototypes */

bool tag_file_read_into_block(s_tag_persist_parameters const * persist_parameters, c_tag_file_read_interface * read_interface, bool editing, s_tag_block * out_block);
bool tag_load_new(s_tag_persist_parameters * persist_parameters, c_tag_file_read_backend * read_backend, bool editing, e_tag_file_open_result * out_open_result, bool * out_unknown, unsigned long * out_checksum, s_tag_group const * group, char const * name, s_tag_block * out_block, c_tag_alternate_stream_consumer * stream_consumer);
bool tag_load_new_from_backend(s_tag_read_parameters * read_parameters, c_tag_file_read_backend * read_backend, c_tag_file_resource_backend * resource_backend, bool editing, e_tag_file_open_result * out_open_result, bool * out_unknown, unsigned long * out_checksum, s_tag_group const * group, char const * name, s_tag_block * out_block, c_tag_alternate_stream_consumer * stream_consumer);
bool tag_save_new(s_tag_persist_parameters * persist_parameters, c_tag_file_create_backend * create_backend, s_tag_group const * group, char const * name, bool unknown, s_tag_block * block, unsigned long * out_new_checksum, c_tag_alternate_stream_iterator * stream_iterator);
bool tag_file_write_from_block(c_persist_stream * stream, s_tag_persist_parameters * persist_parameters, s_tag_block * block);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FILE_LAYOUT_PERSIST_H__
