/* ---------- headers */

#include "blamlib\tag_resource_editor.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_resource_runtime.h"
#include "omaha\toolbox\chunk_persist_streams.h"

/* ---------- constants */

enum
{
    k_tag_resource_null_chunk_tag = 'tg\0c',
    k_tag_resource_exploded_chunk_tag = 'tgrc',
    k_tag_resource_xsynced_chunk_tag = 'tgxc',
    k_tag_resource_data_chunk_tag = 'tgdt',
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_resource_editor g_tag_resource_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_tag_resource_editor g_tag_resource_editor; // "?g_tag_resource_editor@@3Vc_tag_resource_editor@@A"

// public: virtual bool c_tag_resource_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_resource_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_resource_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_resource_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);
// private: bool c_tag_resource_editor::read_xsynced_chunk(struct s_tag_resource *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_resource_persist_reader *);
// private: bool c_tag_resource_editor::write_xsynced_chunk(class c_allocation_interface *, struct s_tag_resource const *, class c_persist_chunk_writer *, class c_tag_resource_persist_writer *);
// private: bool c_tag_resource_editor::read_exploded_chunk(struct s_tag_resource *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *, class c_tag_resource_persist_reader *);
// private: bool c_tag_resource_editor::write_exploded_chunk(struct s_tag_resource const *, class c_persist_chunk_writer *, class c_tag_persist_context *, class c_tag_resource_persist_writer *);
// private: bool c_tag_resource_editor::read_null_chunk(struct s_tag_resource *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_resource_persist_reader *);
// private: bool c_tag_resource_editor::write_null_chunk(struct s_tag_resource const *, class c_persist_chunk_writer *);
// class c_tag_field_editor * get_default_tag_resource_editor(void);
// public: c_tag_resource_editor::c_tag_resource_editor(void);

bool c_tag_resource_editor::write(void * struct_data, void * field_data, void const * field_definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_resource_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool success = true;
    c_tag_resource_persist_writer * resource_writer = context->get_resource_writer();
    if (resource_writer)
    {
        s_tag_resource const * resource = static_cast<s_tag_resource const *>(field_data);
        if (resource_writer->resource_is_cached_for_xsync(resource))
        {
            write_xsynced_chunk(context->get_scratch_allocator(), resource, chunk_writer, resource_writer);
        }
        else if (resource_writer->resource_available(resource))
        {
            write_exploded_chunk(resource, chunk_writer, context, resource_writer);
        }
        else
        {
            write_null_chunk(resource, chunk_writer);
        }
    }
    else
    {
        event_wrapped(_event_warning, "this tag runtime does not support saving tag resources");
        success = false;
    }

    return success;
};

bool c_tag_resource_editor::create(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_resource_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_resource * resource = static_cast<s_tag_resource *>(field_data);
    s_tag_resource_definition const * resource_definition = static_cast<s_tag_resource_definition const *>(field_definition);
    tag_resource_initialize(resource, resource_definition);

    return true;
};

void c_tag_resource_editor::dispose(void * field_data, void const * field_definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_resource_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    c_tag_resource_persist_reader * resource_reader = context->get_resource_reader();
    if (resource_reader)
    {
        s_tag_resource * resource = static_cast<s_tag_resource *>(field_data);
        resource_reader->free_resource(resource);
    }
};

bool c_tag_resource_editor::read(void * struct_data, s_tag_struct_definition const * struct_definition, void * field_data, void const * field_definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_resource_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    bool result = false;
    c_tag_resource_persist_reader * resource_reader = context->get_resource_reader();
    if (resource_reader)
    {
        s_tag_resource * resource = static_cast<s_tag_resource *>(field_data);
        switch (chunk_header->tag)
        {
        case k_tag_resource_exploded_chunk_tag:
            result = read_exploded_chunk(resource, chunk_header, chunk_stream, context, resource_reader);
            break;
        case k_tag_resource_xsynced_chunk_tag:
            result = read_xsynced_chunk(resource, chunk_header, chunk_stream, resource_reader);
            break;
        case k_tag_resource_null_chunk_tag:
            result = read_null_chunk(resource, chunk_header, chunk_stream, resource_reader);
            break;
        default:
            s_static_string<5> tag_string;
            event_wrapped(_event_warning, "cannot read tag resource, invalid chunk tag ('%s')", tag_string.from_tag(chunk_header->tag));
            break;
        }
    }
    else
    {
        event_wrapped(_event_warning, "this tag runtime does not support loading tag resources");
    }

    return result;
};

bool c_tag_resource_editor::read_xsynced_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_resource_persist_reader * resource_reader)
{
    mangled_ppc("?read_xsynced_chunk@c_tag_resource_editor@@AAA_NPAUs_tag_resource@@PBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_resource_persist_reader@@@Z");

    bool result = false;
    if (chunk_header->tag == k_tag_resource_xsynced_chunk_tag && resource_reader)
    {
        result = resource_reader->restore_xsync_state_and_register(chunk_header->version, resource, chunk_stream);
        if (!result)
        {
            resource_reader->free_resource(resource);
        }
    }

    return result;
};

bool c_tag_resource_editor::write_xsynced_chunk(c_allocation_interface * allocator, s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer, c_tag_resource_persist_writer * resource_writer)
{
    mangled_ppc("?write_xsynced_chunk@c_tag_resource_editor@@AAA_NPAVc_allocation_interface@@PBUs_tag_resource@@PAVc_persist_chunk_writer@@PAVc_tag_resource_persist_writer@@@Z");

    bool result = false;
    if (resource_writer)
    {
        c_scoped_variable_chunk resource_chunk(chunk_writer);
        if (resource_chunk.create_chunk())
        {
            c_persist_stream * chunk_stream = resource_chunk.get_chunk_stream();
            if (resource_writer->save_xsync_state(allocator, resource, chunk_stream))
            {
                long xsync_state_version = resource_writer->get_xsync_state_version();
                result = resource_chunk.commit_chunk(k_tag_resource_xsynced_chunk_tag, xsync_state_version);
            }
        }
    }

    return result;
};

bool c_tag_resource_editor::read_exploded_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context, c_tag_resource_persist_reader * resource_reader)
{
    mangled_ppc("?read_exploded_chunk@c_tag_resource_editor@@AAA_NPAUs_tag_resource@@PBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@PAVc_tag_resource_persist_reader@@@Z");

    bool result = false;
    if (chunk_header->tag == k_tag_resource_exploded_chunk_tag && chunk_header->version == 0 && resource_reader->allocate_resource(resource))
    {
        c_tag_field_editor_manager * manager = context->get_editor_manager();
        s_tag_struct_definition const * struct_definition = manager->get_struct_from_resource_definition(resource->definition);
        c_tag_field_editor * struct_editor = manager->tag_struct_editor_get(struct_definition);
        void * resource_data = resource_reader->get_mutable_resource_data(resource);
        if (resource_data)
        {
            c_persist_chunk_iterator iterator(context->get_root_data_stream(), chunk_stream);
            if (iterator.next() && iterator.get_chunk_header()->tag == k_tag_resource_data_chunk_tag)
            {
                c_persist_stream * data_stream = iterator.acquire_chunk_stream();
                result = data_stream->read_bs(resource_data, struct_definition->get_struct_size(), 1, struct_definition->get_byte_swap_definition());
                iterator.release_chunk_stream();
            }

            if (result)
            {
                result = false;
                if (struct_editor->create(resource_data, struct_definition, context) && iterator.next())
                {
                    result = struct_editor->read(resource_data, struct_definition, resource_data, struct_definition, iterator.get_chunk_header(), iterator.acquire_chunk_stream(), context);
                    iterator.release_chunk_stream();
                }
            }
        }

        if (!result)
        {
            resource_reader->free_resource(resource);
        }
    }

    return result;
};

bool c_tag_resource_editor::write_exploded_chunk(s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context, c_tag_resource_persist_writer * resource_writer)
{
    mangled_ppc("?write_exploded_chunk@c_tag_resource_editor@@AAA_NPBUs_tag_resource@@PAVc_persist_chunk_writer@@PAVc_tag_persist_context@@PAVc_tag_resource_persist_writer@@@Z");

    bool result = false;
    {
        c_scoped_variable_chunk resource_chunk(chunk_writer);
        if (resource_chunk.create_chunk())
        {
            c_persist_stream * chunk_stream = resource_chunk.get_chunk_stream();
            if (resource_writer->resource_available(resource))
            {
                c_tag_field_editor_manager * manager = context->get_editor_manager();
                s_tag_struct_definition const * struct_definition = manager->get_struct_from_resource_definition(resource->definition);
                c_tag_field_editor * struct_editor = manager->tag_struct_editor_get(struct_definition);
                c_persist_chunk_writer resource_chunk_writer(chunk_stream);
                void * resource_data = resource_writer->get_resource_data(resource);
                if (resource_data)
                {
                    {
                        c_scoped_variable_chunk data_chunk(&resource_chunk_writer);
                        if (data_chunk.create_chunk())
                        {
                            c_persist_stream * data_stream = data_chunk.get_chunk_stream();
                            if (data_stream->write_bs(resource_data, struct_definition->get_struct_size(), 1, struct_definition->get_byte_swap_definition()))
                            {
                                result = data_chunk.commit_chunk(k_tag_resource_data_chunk_tag, 0);
                            }
                        }
                    }

                    if (result)
                    {
                        result = struct_editor->write(resource_data, resource_data, struct_definition, &resource_chunk_writer, context);
                    }
                }
            }

            if (result)
            {
                result = resource_chunk.commit_chunk(k_tag_resource_exploded_chunk_tag, 0);
            }
        }
    }

    return result;
};

bool c_tag_resource_editor::read_null_chunk(s_tag_resource * resource, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_resource_persist_reader * resource_reader)
{
    mangled_ppc("?read_null_chunk@c_tag_resource_editor@@AAA_NPAUs_tag_resource@@PBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_resource_persist_reader@@@Z");

    bool result = false;
    if (chunk_header->tag == k_tag_resource_null_chunk_tag)
    {
        result = true;
    }

    return result;
};

bool c_tag_resource_editor::write_null_chunk(s_tag_resource const * resource, c_persist_chunk_writer * chunk_writer)
{
    mangled_ppc("?write_null_chunk@c_tag_resource_editor@@AAA_NPBUs_tag_resource@@PAVc_persist_chunk_writer@@@Z");

    bool result = false;
    {
        c_scoped_variable_chunk resource_chunk(chunk_writer);
        if (resource_chunk.create_chunk())
        {
            result = resource_chunk.commit_chunk(k_tag_resource_null_chunk_tag, 0);
        }
    }

    return result;
};

c_tag_field_editor * get_default_tag_resource_editor(void)
{
    mangled_ppc("?get_default_tag_resource_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_resource_editor;
};

