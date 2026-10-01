#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_field_editors\\tag_data_editor.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_data_editor.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\chunk_persist_streams.h"

/* ---------- constants */

unsigned long const k_tag_data_chunk_tag = 'tgda';

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_data_editor g_tag_data_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long volatile `public: virtual bool __cdecl c_tag_data_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *)'::`71'::x_event_category_index; // "?x_event_category_index@?EH@??read@c_tag_data_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z@4JC"
// long volatile `public: virtual bool __cdecl c_tag_data_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *)'::`55'::x_event_category_index; // "?x_event_category_index@?DH@??read@c_tag_data_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z@4JC"
// class c_tag_data_editor g_tag_data_editor; // "?g_tag_data_editor@@3Vc_tag_data_editor@@A"

// class c_tag_field_editor * get_default_tag_data_editor(void);
// public: c_tag_data_editor::c_tag_data_editor(void);
// public: virtual bool c_tag_data_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_data_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_data_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_data_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);

c_tag_field_editor * get_default_tag_data_editor(void)
{
    mangled_ppc("?get_default_tag_data_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_data_editor;
};

c_tag_data_editor::c_tag_data_editor(void)
{
    mangled_ppc("??0c_tag_data_editor@@QAA@XZ");
};

bool c_tag_data_editor::write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_data_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool success = false;
    s_tag_data * data = static_cast<s_tag_data *>(field_data);
    if (data->address != NULL || data->size == 0)
    {
        c_persist_stream * stream = chunk_writer->add_chunk(k_tag_data_chunk_tag, 0, data->size);
        if (stream)
        {
            s_tag_data_definition const * data_definition = data->definition;
            bool byte_swap = data_definition->byte_swap_proc && stream->needs_byteswapping();
            if (byte_swap)
            {
                data_definition->byte_swap_proc(struct_data, data->address, data->size, false);
            }
            success = stream->write(data->address, data->size);
            chunk_writer->close_chunk(stream);
            if (byte_swap)
            {
                data_definition->byte_swap_proc(struct_data, data->address, data->size, true);
            }
        }
    }

    return success;
};

bool c_tag_data_editor::create(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_data_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    bool success = true;
    s_tag_data * data = static_cast<s_tag_data *>(field_data);
    data->definition = static_cast<s_tag_data_definition const *>(field_definition);
    data->address = NULL;
    data->file_offset = NONE;
    data->internal_flags = 0;
    data->size = 0;

    return success;
};

void c_tag_data_editor::dispose(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_data_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_data * data = static_cast<s_tag_data *>(field_data);
    if (data->address != NULL)
    {
        s_tag_data_definition const * data_definition = static_cast<s_tag_data_definition const *>(field_definition);
        c_tag_allocator * allocator = context->get_allocator();
        allocator->deallocate(data->address, data_definition->alignment_bits, data_definition->get_allocation_flags());
        data->address = NULL;
    }
};

// $TODO nonmatching: target SET_BIT on internal_flags spills the new value to a temp and uses it as the ternary result (ours rereads the field)
bool c_tag_data_editor::read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_data_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    bool success = false;
    if (chunk_header->tag == k_tag_data_chunk_tag)
    {
        s_tag_data * data = static_cast<s_tag_data *>(field_data);
        s_tag_data_definition const * data_definition = static_cast<s_tag_data_definition const *>(field_definition);
        data->size = chunk_header->size;
        success = chunk_stream->get_position_relative_to_stream(context->get_root_data_stream(), &data->file_offset);
        assert_tag_debug_untracked_jul_11_2011(115, success);
        if (success)
        {
            bool read_data = data->size > 0 && (!TEST_BIT(data_definition->flags, 0) || context->editing());
            if (!context->editing() && TEST_BIT(data_definition->flags, 4) && context->get_runtime_platform() == 1)
            {
                read_data = false;
            }
            if (!context->editing() && TEST_BIT(data_definition->flags, 5) && context->get_runtime_platform() == 0)
            {
                read_data = false;
            }
            if (read_data)
            {
                c_tag_allocator * allocator = context->get_allocator();
                void * address = allocator->allocate(data->size, data_definition->alignment_bits, data_definition->name, data_definition->get_allocation_flags());
                success = chunk_stream->read(address, data->size);
                if (success)
                {
                    data->address = address;
                    if (data_definition->byte_swap_proc && chunk_stream->needs_byteswapping())
                    {
                        if (!TEST_BIT(struct_definition->get_runtime_flags(), 6))
                        {
                            assert_tag_debug_untracked_jul_11_2011(153, !TEST_BIT(data_definition->flags, _tag_data_definition_is_temporary_bit));
                            data_definition->byte_swap_proc(struct_data, data->address, data->size, true);
                        }
                        else
                        {
                            SET_BIT(data->internal_flags, 3, true);
                        }
                    }
                }
                else
                {
                    allocator->deallocate(address, data_definition->alignment_bits, data_definition->get_allocation_flags());
                    event_wrapped(_event_error, "tags:data_editor:read: failed to read data '%s'", data_definition->name);
                }
            }
            else
            {
                data->size = 0;
            }
            if (TEST_BIT(data_definition->flags, _tag_data_definition_is_temporary_bit))
            {
                SET_BIT(data->internal_flags, 0, true);
            }
        }
    }
    else
    {
        s_static_string<5> chunk_tag_string;
        s_static_string<5> expected_tag_string;
        event_wrapped(_event_warning, "cannot read tag data, invalid chunk tag ('%s' should be '%s')", chunk_tag_string.from_tag(chunk_header->tag), expected_tag_string.from_tag(k_tag_data_chunk_tag));
    }

    return success;
};

