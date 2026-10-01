#pragma once
#ifndef __TAG_STRUCT_EDITOR_H__
#define __TAG_STRUCT_EDITOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_struct_editor : public c_tag_field_editor
{
public:
    c_tag_struct_editor();

    virtual bool write(void * data, void * runtime_data, void const * definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context);
    virtual bool create(void * data, void const * definition, c_tag_persist_context * context);
    virtual void dispose(void * data, void const * definition, c_tag_persist_context * context);
    virtual bool read(void * data, s_tag_struct_definition const * struct_definition, void * runtime_data, void const * definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context);

private:
    static void initialize_tag_field_scan_state(tag_field_scan_state * scan_state, void * data, s_tag_struct_definition const * struct_definition, c_tag_field_editor_manager * editor_manager);
};
static_assert(sizeof(c_tag_struct_editor) == 0x4, "c_tag_struct_editor");

/* ---------- prototypes */

c_tag_field_editor * get_default_tag_struct_editor();

/* ---------- globals */

extern c_tag_struct_editor g_tag_struct_editor;

/* ---------- public code */

#endif // __TAG_STRUCT_EDITOR_H__

