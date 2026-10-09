#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_streams.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_streams.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_tag_block * tag_try_and_get_alternate_stream_block(long tag_index, unsigned long stream_tag);
extern void * tag_block_get_element(s_tag_block const * block, long element_index);
extern bool tag_block_resize(s_tag_block * block, long element_count);
extern void tag_block_delete_all_elements(s_tag_block * block);

/* ---------- globals */

/* ---------- public code */

void * tag_get_alternate_stream(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_get_alternate_stream@@YAPAXJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(20, stream_block);

    void * stream = tag_block_get_element(stream_block, 0);
    return stream;
};

void * tag_try_and_get_alternate_stream(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_try_and_get_alternate_stream@@YAPAXJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);

    void * stream = stream_block ? tag_block_get_element(stream_block, 0) : NULL;
    return stream;
};

bool tag_alternate_stream_exists(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_alternate_stream_exists@@YA_NJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);

    return stream_block && stream_block->count > 0;
};

bool tag_alternate_stream_create(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_alternate_stream_create@@YA_NJK@Z");

    bool result = false;
    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(54, stream_block);

    if (stream_block->count == 0)
    {
        result = tag_block_resize(stream_block, 1);
    }
    else
    {
        result = true;
    }

    return result;
};

void tag_alternate_stream_destroy(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_alternate_stream_destroy@@YAXJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(73, stream_block);

    tag_block_delete_all_elements(stream_block);
};

bool tag_alternate_stream_reset(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_alternate_stream_reset@@YA_NJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(85, stream_block);

    tag_block_delete_all_elements(stream_block);
    bool success = tag_block_resize(stream_block, 1);

    return success;
};

void * tag_try_and_get_or_create_alternate_stream(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_try_and_get_or_create_alternate_stream@@YAPAXJK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(99, stream_block);

    void * stream = NULL;
    if (tag_block_resize(stream_block, 1))
    {
        stream = tag_block_get_element(stream_block, 0);
    }

    return stream;
};

s_tag_block * tag_get_alternate_stream_root_block(long tag_index, unsigned long stream_tag)
{
    mangled_ppc("?tag_get_alternate_stream_root_block@@YAPAUs_tag_block@@JK@Z");

    s_tag_block * stream_block = tag_try_and_get_alternate_stream_block(tag_index, stream_tag);
    assert_tag_debug_untracked_jul_11_2011(116, stream_block);

    return stream_block;
};

/* ---------- private code */

/* ---------- reverse engineering */
