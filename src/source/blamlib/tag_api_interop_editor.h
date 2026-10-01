#pragma once
#ifndef __TAG_API_INTEROP_EDITOR_H__
#define __TAG_API_INTEROP_EDITOR_H__

/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_interop_editor :
    public c_tag_field_editor
{
public:
    // ??0c_tag_interop_editor@@QAA@XZ
    c_tag_interop_editor()
    {
    };

    virtual bool write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context);
    virtual bool create(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual void dispose(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual bool read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context);
};
static_assert(sizeof(c_tag_interop_editor) == 0x4, "c_tag_interop_editor");

/* ---------- prototypes */

c_tag_field_editor * get_default_tag_interop_editor(void);

/* ---------- globals */

extern c_tag_interop_editor g_tag_interop_editor;

/* ---------- public code */

#endif // __TAG_API_INTEROP_EDITOR_H__

