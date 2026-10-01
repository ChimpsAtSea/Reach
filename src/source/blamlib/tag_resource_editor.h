#pragma once
#ifndef __TAG_RESOURCE_EDITOR_H__
#define __TAG_RESOURCE_EDITOR_H__

/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource;

class c_allocation_interface;
class c_tag_resource_persist_reader;
class c_tag_resource_persist_writer;

class c_tag_resource_editor :
    public c_tag_field_editor
{
public:
    // ??0c_tag_resource_editor@@QAA@XZ
    c_tag_resource_editor()
    {
    };

    virtual bool write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context);
    virtual bool create(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual void dispose(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual bool read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context);

private:
    bool read_xsynced_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_resource_persist_reader * resource_reader);
    bool write_xsynced_chunk(c_allocation_interface * allocator, s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer, c_tag_resource_persist_writer * resource_writer);
    bool read_exploded_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context, c_tag_resource_persist_reader * resource_reader);
    bool write_exploded_chunk(s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context, c_tag_resource_persist_writer * resource_writer);
    bool read_null_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_resource_persist_reader * resource_reader);
    bool write_null_chunk(s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer);
};
static_assert(sizeof(c_tag_resource_editor) == 0x4, "c_tag_resource_editor");

/* ---------- prototypes */

c_tag_field_editor * get_default_tag_resource_editor(void);

/* ---------- globals */

extern c_tag_resource_editor g_tag_resource_editor;

/* ---------- public code */

#endif // __TAG_RESOURCE_EDITOR_H__

