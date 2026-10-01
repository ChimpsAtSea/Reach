#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_file_layout_persist.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_file_layout_persist.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_file_interface.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool tag_file_read_into_block(struct s_tag_persist_parameters const *, class c_tag_file_read_interface *, bool, struct s_tag_block *);
// public: c_tag_group_files_persist_context::c_tag_group_files_persist_context(class c_persist_stream *, struct s_tag_persist_parameters const *, bool);
// public: virtual class c_persist_stream * c_tag_group_files_persist_context::get_root_data_stream(void);
// public: virtual class c_tag_field_editor_manager * c_tag_group_files_persist_context::get_editor_manager(void);
// public: virtual class c_tag_allocator * c_tag_group_files_persist_context::get_allocator(void);
// public: virtual class c_allocation_interface * c_tag_group_files_persist_context::get_scratch_allocator(void);
// public: virtual class c_tag_resource_persist_reader * c_tag_group_files_persist_context::get_resource_reader(void);
// public: virtual class c_tag_resource_persist_writer * c_tag_group_files_persist_context::get_resource_writer(void);
// public: virtual enum e_runtime_platform_type c_tag_group_files_persist_context::get_runtime_platform(void);
// public: virtual bool c_tag_group_files_persist_context::editing(void);
// public: virtual bool c_tag_group_files_persist_context::for_checkpoint(void);
// bool tag_load_new(struct s_tag_persist_parameters *, class c_tag_file_read_backend *, bool, enum e_tag_file_open_result *, bool *, unsigned long *, struct s_tag_group const *, char const *, struct s_tag_block *, class c_tag_alternate_stream_consumer *);
// bool tag_load_new_from_backend(struct s_tag_read_parameters *, class c_tag_file_read_backend *, class c_tag_file_resource_backend *, bool, enum e_tag_file_open_result *, bool *, unsigned long *, struct s_tag_group const *, char const *, struct s_tag_block *, class c_tag_alternate_stream_consumer *);
// bool tag_save_new(struct s_tag_persist_parameters *, class c_tag_file_create_backend *, struct s_tag_group const *, char const *, bool, struct s_tag_block *, unsigned long *, class c_tag_alternate_stream_iterator *);
// bool tag_file_write_from_block(class c_persist_stream *, struct s_tag_persist_parameters *, struct s_tag_block *);

bool tag_file_read_into_block(s_tag_persist_parameters const * persist_parameters, c_tag_file_read_interface * read_interface, bool editing, s_tag_block * out_block)
{
    mangled_ppc("?tag_file_read_into_block@@YA_NPBUs_tag_persist_parameters@@PAVc_tag_file_read_interface@@_NPAUs_tag_block@@@Z");

    bool success = false;
    if (read_interface)
    {
        c_tag_group_fixupper * fixupper = read_interface->get_group_fixupper();
        if (fixupper)
        {
            s_tag_block source_block;
            tag_block_initialize(&source_block, fixupper->get_source_block_definition());

            c_persist_stream * root_data_stream = read_interface->get_root_data_stream();
            if (root_data_stream)
            {
                c_tag_group_files_persist_context context(root_data_stream, persist_parameters, editing);
                success = tag_block_load_from_context(&source_block, &context);
                if (!success)
                {
                    event_wrapped(_event_warning, "failed to load tag from context");
                }
            }
            else
            {
                event_wrapped(_event_warning, "failed to get data stream '%s' from tag file", fixupper->get_destination_block_definition()->get_block_name());
            }

            if (success)
            {
                tag_block_initialize(out_block, fixupper->get_destination_block_definition());

                s_tag_fixup_context fixup_context;
                fixup_context.allocator = persist_parameters->allocator;
                fixup_context.resource_reader = persist_parameters->resource_reader;
                fixup_context.byte_swap = root_data_stream->needs_byteswapping();
                success = fixupper->fixup_tag(&source_block, out_block, &fixup_context);
                if (!success)
                {
                    event_wrapped(_event_warning, "failed to fixup tag stream '%s'", fixupper->get_destination_block_definition()->get_block_name());
                }
            }
        }

        read_interface->signal_complete();
    }

    return success;
};

c_tag_group_files_persist_context::c_tag_group_files_persist_context(c_persist_stream * root_data_stream, s_tag_persist_parameters const * persist_parameters, bool editing) :
    c_tag_persist_context(),
    m_root_data_stream(root_data_stream),
    m_persist_parameters(persist_parameters),
    m_editing(editing),
    m_for_checkpoint(false)
{
    mangled_ppc("??0c_tag_group_files_persist_context@@QAA@PAVc_persist_stream@@PBUs_tag_persist_parameters@@_N@Z");
};

c_persist_stream * c_tag_group_files_persist_context::get_root_data_stream(void)
{
    mangled_ppc("?get_root_data_stream@c_tag_group_files_persist_context@@UAAPAVc_persist_stream@@XZ");

    return m_root_data_stream;
};

c_tag_field_editor_manager * c_tag_group_files_persist_context::get_editor_manager(void)
{
    mangled_ppc("?get_editor_manager@c_tag_group_files_persist_context@@UAAPAVc_tag_field_editor_manager@@XZ");

    return m_persist_parameters->editor_manager;
};

c_tag_allocator * c_tag_group_files_persist_context::get_allocator(void)
{
    mangled_ppc("?get_allocator@c_tag_group_files_persist_context@@UAAPAVc_tag_allocator@@XZ");

    return m_persist_parameters->allocator;
};

c_allocation_interface * c_tag_group_files_persist_context::get_scratch_allocator(void)
{
    mangled_ppc("?get_scratch_allocator@c_tag_group_files_persist_context@@UAAPAVc_allocation_interface@@XZ");

    return m_persist_parameters->scratch_allocator;
};

c_tag_resource_persist_reader * c_tag_group_files_persist_context::get_resource_reader(void)
{
    mangled_ppc("?get_resource_reader@c_tag_group_files_persist_context@@UAAPAVc_tag_resource_persist_reader@@XZ");

    return m_persist_parameters->resource_reader;
};

c_tag_resource_persist_writer * c_tag_group_files_persist_context::get_resource_writer(void)
{
    mangled_ppc("?get_resource_writer@c_tag_group_files_persist_context@@UAAPAVc_tag_resource_persist_writer@@XZ");

    return m_persist_parameters->resource_writer;
};

e_runtime_platform_type c_tag_group_files_persist_context::get_runtime_platform(void)
{
    mangled_ppc("?get_runtime_platform@c_tag_group_files_persist_context@@UAA?AW4e_runtime_platform_type@@XZ");

    return m_persist_parameters->runtime_platform;
};

bool c_tag_group_files_persist_context::editing(void)
{
    mangled_ppc("?editing@c_tag_group_files_persist_context@@UAA_NXZ");

    return m_editing;
};

bool c_tag_group_files_persist_context::for_checkpoint(void)
{
    mangled_ppc("?for_checkpoint@c_tag_group_files_persist_context@@UAA_NXZ");

    return m_for_checkpoint;
};

bool tag_load_new(s_tag_persist_parameters * persist_parameters, c_tag_file_read_backend * read_backend, bool editing, e_tag_file_open_result * out_open_result, bool * out_unknown, unsigned long * out_checksum, s_tag_group const * group, char const * name, s_tag_block * out_block, c_tag_alternate_stream_consumer * stream_consumer)
{
    mangled_ppc("?tag_load_new@@YA_NPAUs_tag_persist_parameters@@PAVc_tag_file_read_backend@@_NPAW4e_tag_file_open_result@@PA_NPAKPBUs_tag_group@@PBDPAUs_tag_block@@PAVc_tag_alternate_stream_consumer@@@Z");

    assert_tag_debug_untracked_jul_11_2011(178, read_backend);
    assert_tag_debug_untracked_jul_11_2011(179, persist_parameters);

    bool success = out_block == NULL;
    c_tag_file_alternate_stream_read_iterator * alternate_stream_iterator = NULL;

    if (strcmp(name, "objects\\weapons\\pistol\\magnum\\magnum") == 0 && group->group_tag == TAG('c', 'o', 'l', 'l'))
    {
        long breakpoint = 0;
        breakpoint = breakpoint;
    }

    c_tag_file_read_interface * tag_file = read_backend->load_tag_file(persist_parameters->scratch_allocator, group, name, out_unknown, out_checksum, out_open_result, &alternate_stream_iterator);

    if (strcmp(name, "objects\\weapons\\pistol\\magnum\\magnum") == 0 && group->group_tag == TAG('c', 'o', 'l', 'l'))
    {
        c_tag_group_fixupper * fixupper = tag_file->get_group_fixupper();
        fixupper = fixupper;
    }

    if (tag_file && out_block)
    {
        success = tag_file_read_into_block(persist_parameters, tag_file, editing, out_block);
    }

    if (stream_consumer && alternate_stream_iterator)
    {
        while (stream_consumer->can_keep_consuming_streams() && alternate_stream_iterator->next())
        {
            unsigned long stream_tag = alternate_stream_iterator->get_alternate_stream_tag();
            s_tag_block_definition const * definition;
            s_tag_block * stream_block = stream_consumer->get_stream_block_destination(stream_tag, &definition);
            if (stream_block)
            {
                c_tag_file_read_interface * read_interface = alternate_stream_iterator->get_alternate_stream(definition);
                bool stream_success = tag_file_read_into_block(persist_parameters, read_interface, true, stream_block);
                if (!stream_success)
                {
                    event_wrapped(_event_warning, "failed to read stream '%s'", definition->get_block_name());
                }
            }
        }
    }

    if (tag_file)
    {
        read_backend->release_tag_file(group, name, tag_file);
    }

    return success;
};

bool tag_load_new_from_backend(s_tag_read_parameters * read_parameters, c_tag_file_read_backend * read_backend, c_tag_file_resource_backend * resource_backend, bool editing, e_tag_file_open_result * out_open_result, bool * out_unknown, unsigned long * out_checksum, s_tag_group const * group, char const * name, s_tag_block * out_block, c_tag_alternate_stream_consumer * stream_consumer)
{
    mangled_ppc("?tag_load_new_from_backend@@YA_NPAUs_tag_read_parameters@@PAVc_tag_file_read_backend@@PAVc_tag_file_resource_backend@@_NPAW4e_tag_file_open_result@@PA_NPAKPBUs_tag_group@@PBDPAUs_tag_block@@PAVc_tag_alternate_stream_consumer@@@Z");

    c_tag_resource_persist_reader * persist_reader = resource_backend ? resource_backend->get_persist_reader(group, name) : NULL;
    s_tag_persist_parameters persist_parameters = { read_parameters->scratch_allocator, read_parameters->allocator, read_parameters->editor_manager, read_parameters->runtime_platform, persist_reader, NULL };
    bool success = tag_load_new(&persist_parameters, read_backend, editing, out_open_result, out_unknown, out_checksum, group, name, out_block, stream_consumer);

    if (resource_backend)
    {
        resource_backend->release_persist_reader(group, name, persist_reader);
    }

    return success;
};

bool tag_save_new(s_tag_persist_parameters * persist_parameters, c_tag_file_create_backend * create_backend, s_tag_group const * group, char const * name, bool unknown, s_tag_block * block, unsigned long * out_new_checksum, c_tag_alternate_stream_iterator * stream_iterator)
{
    mangled_ppc("?tag_save_new@@YA_NPAUs_tag_persist_parameters@@PAVc_tag_file_create_backend@@PBUs_tag_group@@PBD_NPAUs_tag_block@@PAKPAVc_tag_alternate_stream_iterator@@@Z");

    assert_tag_debug_untracked_jul_11_2011(320, persist_parameters);
    assert_tag_debug_untracked_jul_11_2011(322, create_backend);
    assert_tag_debug_untracked_jul_11_2011(323, out_new_checksum);

    bool success = false;
    c_tag_file_write_interface * writer = create_backend->create_tag_file(group, unknown);
    if (writer)
    {
        c_persist_stream * root_stream = writer->create_root_stream();
        if (root_stream)
        {
            success = tag_file_write_from_block(root_stream, persist_parameters, block);
            if (success)
            {
                success = writer->commit_stream(root_stream);
            }
        }

        if (stream_iterator)
        {
            while (success && stream_iterator->next())
            {
                unsigned long stream_tag = stream_iterator->get_stream_tag();
                s_tag_block * stream_block = stream_iterator->get_stream_block();
                if (stream_block)
                {
                    if (stream_block->count > 0)
                    {
                        c_persist_stream * stream = writer->create_alternate_data_stream(stream_tag, stream_block->definition);
                        if (stream)
                        {
                            success = tag_file_write_from_block(stream, persist_parameters, stream_block);
                            if (success)
                            {
                                success = writer->commit_stream(stream);
                            }
                        }
                    }
                }
                else
                {
                    success = false;
                }
            }
        }

        if (success)
        {
            success = create_backend->save_tag_file(writer, name, out_new_checksum);
        }
        else
        {
            create_backend->cancel_save_tag_file(writer);
        }
    }

    return success;
};

bool tag_file_write_from_block(c_persist_stream * stream, s_tag_persist_parameters * persist_parameters, s_tag_block * block)
{
    mangled_ppc("?tag_file_write_from_block@@YA_NPAVc_persist_stream@@PAUs_tag_persist_parameters@@PAUs_tag_block@@@Z");

    bool success = false;
    if (stream)
    {
        c_tag_group_files_persist_context context(stream, persist_parameters, false);
        success = tag_block_save_into_context(block, &context);
    }

    return success;
};

