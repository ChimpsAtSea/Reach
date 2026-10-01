/* ---------- headers */

#include "blamlib\tag_string_id_editor.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\chunk_persist_streams.h"

#include <string.h>

/* ---------- constants */

unsigned long const k_tag_string_id_chunk_tag = 'tgsi';

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_string_id_editor g_tag_string_id_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long volatile `public: virtual bool __cdecl c_tag_string_id_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *)'::`19'::x_event_category_index; // "?x_event_category_index@?BD@??read@c_tag_string_id_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z@4JC"
// class c_tag_string_id_editor g_tag_string_id_editor; // "?g_tag_string_id_editor@@3Vc_tag_string_id_editor@@A"

// class c_tag_field_editor * get_default_tag_string_id_editor(void);
// public: c_tag_string_id_editor::c_tag_string_id_editor(void);
// public: virtual bool c_tag_string_id_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_string_id_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_string_id_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_string_id_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);

c_tag_field_editor * get_default_tag_string_id_editor()
{
    mangled_ppc("?get_default_tag_string_id_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_string_id_editor;
};

c_tag_string_id_editor::c_tag_string_id_editor()
{
    mangled_ppc("??0c_tag_string_id_editor@@QAA@XZ");
};

bool c_tag_string_id_editor::write(void * data, void * runtime_data, void const * definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_string_id_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool result = false;
    long * string_id = static_cast<long *>(runtime_data);
    c_tag_allocator * tag_allocator = context->get_allocator();
    char const * string_value = tag_allocator->string_id_get_string_const(*string_id);
    if (*string_id != 0 && string_value)
    {
        long size = strlen(string_value);
        c_persist_stream * stream = chunk_writer->add_chunk(k_tag_string_id_chunk_tag, 0, size);
        if (stream)
        {
            result = stream->write(string_value, size);
            if (result)
            {
                chunk_writer->close_chunk(stream);
            }
            else
            {
                chunk_writer->abort_chunk(stream);
            }
        }
    }
    else
    {
        c_persist_stream * stream = chunk_writer->add_chunk(k_tag_string_id_chunk_tag, 0, 0);
        if (stream)
        {
            result = true;
            chunk_writer->close_chunk(stream);
        }
    }

    return result;
};

bool c_tag_string_id_editor::create(void * data, void const * definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_string_id_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    bool success = true;
    long * string_id = static_cast<long *>(data);
    *string_id = 0;

    return success;
};

void c_tag_string_id_editor::dispose(void * data, void const * definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_string_id_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    long * string_id = static_cast<long *>(data);
    c_tag_allocator * allocator = context->get_allocator();
    allocator->string_id_release(*string_id);
};

bool c_tag_string_id_editor::read(void * data, s_tag_struct_definition const * struct_definition, void * runtime_data, void const * definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_string_id_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    bool success = false;
    if (chunk_header->tag == k_tag_string_id_chunk_tag)
    {
        if (chunk_header->size > 0)
        {
            long * string_id = static_cast<long *>(runtime_data);
            char string[128];
            if (chunk_stream->read(string, MIN(chunk_header->size, 128)))
            {
                string[MIN(chunk_header->size, 127)] = 0;
                c_tag_allocator * tag_allocator = context->get_allocator();
                long string_id_value = tag_allocator->string_id_new(string);
                if (string_id_value != -1)
                {
                    *string_id = string_id_value;
                    success = true;
                }
            }
        }
        else
        {
            success = true;
        }
    }
    else
    {
        s_static_string<5> expected_tag_string;
        s_static_string<5> chunk_tag_string;
        event_wrapped(_event_warning, "cannot read tag string_id, invalid chunk tag ('%s' should be '%s')", chunk_tag_string.from_tag(chunk_header->tag), expected_tag_string.from_tag(k_tag_string_id_chunk_tag));
    }

    return success;
};

