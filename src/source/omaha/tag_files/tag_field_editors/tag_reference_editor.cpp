#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_field_editors\\tag_reference_editor.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_reference_editor.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\chunk_persist_streams.h"
#include "omaha\toolbox\simple_persist_streams.h"

#include <string.h>

/* ---------- constants */

unsigned long const k_tag_reference_chunk_tag = 'tgrf';

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_reference_editor g_tag_reference_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_tag_reference_editor g_tag_reference_editor; // "?g_tag_reference_editor@@3Vc_tag_reference_editor@@A"

// public: virtual bool c_tag_reference_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_reference_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_reference_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_reference_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);
// private: static bool c_tag_reference_editor::write_to_stream(class c_persist_stream *, struct s_tag_reference *);
// class c_tag_field_editor * get_default_tag_reference_editor(void);
// public: c_tag_reference_editor::c_tag_reference_editor(void);

bool c_tag_reference_editor::write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_reference_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool success = false;
    s_tag_reference * reference = static_cast<s_tag_reference *>(field_data);
    if (reference_points_somewhere(reference))
    {
        c_used_size_only_stream used_size_stream;
        if (write_to_stream(&used_size_stream, reference))
        {
            unsigned long used_reference_size;
            if (used_size_stream.get_total_size(&used_reference_size))
            {
                {
                    unsigned long position;
                    if (used_size_stream.get_absolute_position(&position))
                    {
                        assert_tag_debug_untracked_jul_11_2011(70, position==used_reference_size);
                    }
                    else
                    {
                        dassert_tag_debug_untracked_jul_11_2011(74, false, "unreachable");
                    }
                }
                c_persist_stream * stream = chunk_writer->add_chunk(k_tag_reference_chunk_tag, 0, used_reference_size);
                if (stream)
                {
                    success = write_to_stream(stream, reference);
                    chunk_writer->close_chunk(stream);
                }
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(89, false, "unreachable");
            }
        }
    }
    else
    {
        c_persist_stream * stream = chunk_writer->add_chunk(k_tag_reference_chunk_tag, 0, 0);
        if (stream)
        {
            success = true;
            chunk_writer->close_chunk(stream);
        }
    }

    return success;
};

bool c_tag_reference_editor::create(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_reference_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    bool success = true;
    c_tag_allocator * allocator = context->get_allocator();
    s_tag_reference * reference = static_cast<s_tag_reference *>(field_data);
    reference->group_tag = NONE;
    reference->name = allocator->add_tracked_string("");
    reference->index = NONE;
    reference->name_length = 0;

    return success;
};

void c_tag_reference_editor::dispose(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_reference_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_reference * reference = static_cast<s_tag_reference *>(field_data);
    c_tag_allocator * allocator = context->get_allocator();
    allocator->remove_tracked_string(reference->name);
    reference->name = NULL;
};

bool c_tag_reference_editor::read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_reference_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    bool success = false;
    if (chunk_header->tag == k_tag_reference_chunk_tag)
    {
        success = create(field_data, field_definition, context);
        if (success)
        {
            c_tag_allocator * allocator = context->get_allocator();
            s_tag_reference * reference = static_cast<s_tag_reference *>(field_data);
            if (chunk_header->size > 0)
            {
                unsigned long group_tag;
                success = chunk_stream->read_typed(&group_tag, 1);
                if (success)
                {
                    char name[256];
                    long name_size = chunk_header->size - sizeof(group_tag);
                    if (chunk_stream->read(name, MIN(name_size, sizeof(name))))
                    {
                        name[MIN(name_size, 255)] = 0;
                        reference->group_tag = group_tag;
                        reference->name = allocator->add_tracked_string(name);
                        reference->name_length = strlen(reference->name);
                    }
                }
            }
            else
            {
                reference->name = allocator->add_tracked_string("");
                reference->name_length = 0;
            }
        }
    }
    else
    {
        s_static_string<5> chunk_tag_string;
        s_static_string<5> expected_tag_string;
        event_wrapped(_event_warning, "cannot read tag reference, invalid chunk tag ('%s' should be '%s')", chunk_tag_string.from_tag(chunk_header->tag), expected_tag_string.from_tag(k_tag_reference_chunk_tag));
    }

    return success;
};

bool c_tag_reference_editor::write_to_stream(c_persist_stream * persist_stream, s_tag_reference * reference)
{
    mangled_ppc("?write_to_stream@c_tag_reference_editor@@CA_NPAVc_persist_stream@@PAUs_tag_reference@@@Z");

    assert_tag_debug_untracked_jul_11_2011(200, persist_stream);
    assert_tag_debug_untracked_jul_11_2011(201, reference);

    bool success = false;
    success = persist_stream->write_typed(&reference->group_tag, 1);
    success = success && persist_stream->write(reference->name, strlen(reference->name));

    return success;
};

c_tag_field_editor * get_default_tag_reference_editor(void)
{
    mangled_ppc("?get_default_tag_reference_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_reference_editor;
};

c_tag_reference_editor::c_tag_reference_editor(void)
{
    mangled_ppc("??0c_tag_reference_editor@@QAA@XZ");
};

