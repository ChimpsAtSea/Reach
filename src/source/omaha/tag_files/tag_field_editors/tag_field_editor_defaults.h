#pragma once
#ifndef __TAG_FIELD_EDITOR_DEFAULTS_H__
#define __TAG_FIELD_EDITOR_DEFAULTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

enum e_tag_field;

struct s_tag_struct_definition;
struct s_tag_block_definition;
struct s_tag_resource_definition;
struct s_tag_interop_definition;
struct s_persist_chunk_header;
struct tag_field_scan_state;

class c_persist_stream;
class c_persist_chunk_writer;
class c_tag_persist_context;

// vtable ??_7c_tag_field_editor@@6B@ (tag_api_interop_editor.obj): 4 slots
class c_tag_field_editor
{
public:
    virtual bool write(void * data, void * runtime_data, void const * definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context) = 0;
    virtual bool create(void * data, void const * definition, c_tag_persist_context * context) = 0;
    virtual void dispose(void * data, void const * definition, c_tag_persist_context * context) = 0;
    virtual bool read(void * data, s_tag_struct_definition const * struct_definition, void * runtime_data, void const * definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context) = 0;
};
static_assert(sizeof(c_tag_field_editor) == 0x4, "c_tag_field_editor");

// vtable order from ??_7c_tag_field_editor_manager_default@@6B@
class c_tag_field_editor_manager
{
public:
    virtual c_tag_field_editor * tag_field_editor_get(e_tag_field field_type, void const * definition) = 0;
    virtual c_tag_field_editor * tag_struct_editor_get(s_tag_struct_definition const * struct_definition) = 0;
    virtual void set_tag_field_scanner_fields(tag_field_scan_state * scan_state) = 0;
    virtual s_tag_struct_definition const * get_struct_from_block_definition(s_tag_block_definition const * block_definition) = 0;
    virtual s_tag_struct_definition const * get_struct_from_resource_definition(s_tag_resource_definition const * resource_definition) = 0;
    virtual s_tag_struct_definition const * get_struct_from_interop_definition(s_tag_interop_definition const * interop_definition) = 0;
};
static_assert(sizeof(c_tag_field_editor_manager) == 0x4, "c_tag_field_editor_manager");

// ??0c_tag_field_editor_manager_default@@QAA@XZ is inline (tag_groups.obj)
class c_tag_field_editor_manager_default :
    public c_tag_field_editor_manager
{
public:
    virtual c_tag_field_editor * tag_field_editor_get(e_tag_field field_type, void const * definition);
    virtual c_tag_field_editor * tag_struct_editor_get(s_tag_struct_definition const * struct_definition);
    virtual void set_tag_field_scanner_fields(tag_field_scan_state * scan_state);
    virtual s_tag_struct_definition const * get_struct_from_block_definition(s_tag_block_definition const * block_definition);
    virtual s_tag_struct_definition const * get_struct_from_resource_definition(s_tag_resource_definition const * resource_definition);
    virtual s_tag_struct_definition const * get_struct_from_interop_definition(s_tag_interop_definition const * interop_definition);
};
static_assert(sizeof(c_tag_field_editor_manager_default) == 0x4, "c_tag_field_editor_manager_default");

/* ---------- prototypes */

c_tag_field_editor * get_default_tag_field_editor(e_tag_field field_type, void const * definition);
void initialize_tag_field_scanner_for_tag_field_editors(tag_field_scan_state * scan_state);
bool tag_field_has_storage_chunk(e_tag_field field_type);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FIELD_EDITOR_DEFAULTS_H__

