#pragma once
#ifndef __TAG_REFERENCE_EDITOR_H__
#define __TAG_REFERENCE_EDITOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_reference;

class c_tag_reference_editor :
    public c_tag_field_editor
{
public:
    c_tag_reference_editor(void);

    virtual bool write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context);
    virtual bool create(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual void dispose(void * field_data, void const * field_definition, c_tag_persist_context * context);
    virtual bool read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context);

private:
    static bool write_to_stream(c_persist_stream * stream, s_tag_reference * reference);
};
static_assert(sizeof(c_tag_reference_editor) == 0x4, "c_tag_reference_editor");

/* ---------- prototypes */

c_tag_field_editor * get_default_tag_reference_editor(void);

/* ---------- globals */

extern c_tag_reference_editor g_tag_reference_editor;

/* ---------- public code */

#endif // __TAG_REFERENCE_EDITOR_H__

