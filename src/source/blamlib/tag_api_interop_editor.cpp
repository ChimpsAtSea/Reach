/* ---------- headers */

#include "blamlib\tag_api_interop_editor.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_api_interop.h"
#include "omaha\toolbox\chunk_persist_streams.h"

/* ---------- constants */

enum
{
    k_tag_interop_chunk_tag = 'ti][',
    k_tag_interop_data_chunk_tag = 'tid@',
    k_tag_interop_null_chunk_tag = 'ti00',
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_interop_editor g_tag_interop_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_tag_interop_editor g_tag_interop_editor; // "?g_tag_interop_editor@@3Vc_tag_interop_editor@@A"

// public: virtual bool c_tag_interop_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_interop_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_interop_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_interop_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);
// class c_tag_field_editor * get_default_tag_interop_editor(void);
// public: c_tag_interop_editor::c_tag_interop_editor(void);
// public: c_tag_field_editor::c_tag_field_editor(void);

bool c_tag_interop_editor::write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_interop_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool result = false;
    {
        c_scoped_variable_chunk interop_chunk(chunk_writer);
        if (interop_chunk.create_chunk())
        {
            s_tag_interop * interop = static_cast<s_tag_interop *>(field_data);
            c_persist_stream * interop_stream = interop_chunk.get_chunk_stream();
            c_tag_field_editor_manager * manager = context->get_editor_manager();
            s_tag_struct_definition const * struct_definition = manager->get_struct_from_interop_definition(interop->definition);
            c_tag_field_editor * struct_editor = manager->tag_struct_editor_get(struct_definition);
            c_persist_chunk_writer interop_chunk_writer(interop_stream);
            if (tag_interop_descriptor_exists(interop))
            {
                void * interop_data = tag_interop_descriptor_get_with_definition(interop, struct_definition);
                {
                    c_scoped_variable_chunk data_chunk(&interop_chunk_writer);
                    if (data_chunk.create_chunk())
                    {
                        c_persist_stream * data_stream = data_chunk.get_chunk_stream();
                        if (data_stream->write_bs(interop_data, struct_definition->get_struct_size(), 1, struct_definition->get_byte_swap_definition()))
                        {
                            result = data_chunk.commit_chunk(k_tag_interop_data_chunk_tag, 0);
                        }
                    }
                }

                if (result)
                {
                    result = struct_editor->write(interop_data, interop_data, struct_definition, &interop_chunk_writer, context);
                }
            }
            else
            {
                c_persist_stream * null_stream = interop_chunk_writer.add_chunk(k_tag_interop_null_chunk_tag, 0, 0);
                interop_chunk_writer.close_chunk(null_stream);
                result = true;
            }

            if (result)
            {
                result = interop_chunk.commit_chunk(k_tag_interop_chunk_tag, 0);
            }
            else
            {
                event_wrapped(_event_warning, "tags:write: failed to write out interop on save");
            }
        }
    }

    return result;
};

bool c_tag_interop_editor::create(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_interop_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_interop * interop = static_cast<s_tag_interop *>(field_data);
    s_tag_interop_definition const * interop_definition = static_cast<s_tag_interop_definition const *>(field_definition);
    tag_interop_initialize(interop, interop_definition);

    return true;
};

void c_tag_interop_editor::dispose(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_interop_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_interop * interop = static_cast<s_tag_interop *>(field_data);
    tag_interop_destroy(interop);
};

// $TODO nonmatching
bool c_tag_interop_editor::read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_interop_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    bool result = false;
    if (chunk_header->tag == k_tag_interop_chunk_tag && chunk_header->version == 0)
    {
        s_tag_interop * interop = static_cast<s_tag_interop *>(field_data);
        c_tag_field_editor_manager * manager = context->get_editor_manager();
        c_tag_allocator * allocator = context->get_allocator();
        s_tag_struct_definition const * interop_struct_definition = manager->get_struct_from_interop_definition(interop->definition);
        c_tag_field_editor * struct_editor = manager->tag_struct_editor_get(interop_struct_definition);
        c_persist_chunk_iterator iterator(context->get_root_data_stream(), chunk_stream);
        if (iterator.next())
        {
            if (iterator.get_chunk_header()->tag == k_tag_interop_data_chunk_tag)
            {
                void * interop_data = allocator->allocate(interop_struct_definition->get_struct_size(), interop_struct_definition->get_alignment_bits(), interop->definition->get_interop_name(), 0);
                c_persist_stream * data_stream = iterator.acquire_chunk_stream();
                result = data_stream->read_bs(interop_data, interop_struct_definition->get_struct_size(), 1, interop_struct_definition->get_byte_swap_definition());
                iterator.release_chunk_stream();
                if (struct_editor->create(interop_data, interop_struct_definition, context) && iterator.next())
                {
                    result = struct_editor->read(interop_data, interop_struct_definition, interop_data, interop_struct_definition, iterator.get_chunk_header(), iterator.acquire_chunk_stream(), context);
                    iterator.release_chunk_stream();
                }

                if (result)
                {
                    interop->descriptor = interop_data;
                }
                else
                {
                    allocator->deallocate(interop_data, interop_struct_definition->get_alignment_bits(), 0);
                }
            }
            else if (iterator.get_chunk_header()->tag == k_tag_interop_null_chunk_tag)
            {
                result = true;
            }
        }
    }

    return result;
};

c_tag_field_editor * get_default_tag_interop_editor(void)
{
    mangled_ppc("?get_default_tag_interop_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_interop_editor;
};



