#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_file_interface.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_file_interface.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"
#include "omaha\toolbox\chunk_persist_streams.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool tag_block_load_from_context(struct s_tag_block *, class c_tag_persist_context *);
// bool tag_block_save_into_context(struct s_tag_block *, class c_tag_persist_context *);

bool tag_block_load_from_context(s_tag_block * block, c_tag_persist_context * context)
{
    mangled_ppc("?tag_block_load_from_context@@YA_NPAUs_tag_block@@PAVc_tag_persist_context@@@Z");

    assert_tag_debug_untracked_jul_11_2011(20, block);

    bool success = false;
    c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
    c_tag_field_editor * block_editor = editor_manager->tag_field_editor_get(static_cast<e_tag_field>(0x28) /* _field_block */, block->definition);
    c_persist_chunk_iterator iterator(context->get_root_data_stream());

    if (iterator.next())
    {
        s_persist_chunk_header const * chunk_header = iterator.get_chunk_header();
        c_persist_stream * chunk_stream = iterator.acquire_chunk_stream();
        success = block_editor->read(NULL, NULL, block, block->definition, chunk_header, chunk_stream, context);
        iterator.release_chunk_stream();
    }

    return success;
};

bool tag_block_save_into_context(s_tag_block * block, c_tag_persist_context * context)
{
    mangled_ppc("?tag_block_save_into_context@@YA_NPAUs_tag_block@@PAVc_tag_persist_context@@@Z");

    assert_tag_debug_untracked_jul_11_2011(44, block);

    bool success = false;
    c_persist_chunk_writer chunk_writer(context->get_root_data_stream());
    c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
    c_tag_field_editor * block_editor = editor_manager->tag_field_editor_get(static_cast<e_tag_field>(0x28) /* _field_block */, block->definition);
    success = block_editor->write(NULL, block, block->definition, &chunk_writer, context);

    return success;
};

