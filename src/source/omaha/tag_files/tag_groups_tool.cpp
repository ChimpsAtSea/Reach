#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_groups_tool.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_groups_tool.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void tool_tag_block_resize_internal(struct s_tag_block *, long, char const *, char const *, long);
// long tool_tag_block_add_element_internal(struct s_tag_block *, char const *, long);
// void tool_duplicate_recursive_tag_block_elements_internal(struct s_tag_block const *, struct s_tag_block *, char const *, long);
// void tool_tag_data_resize_internal(struct s_tag_data *, unsigned long, char const *, char const *, long);

void tool_tag_block_resize_internal(s_tag_block * block, long element_count, char const * element_count_string, char const * file, long line)
{
    mangled_ppc("?tool_tag_block_resize_internal@@YAXPAUs_tag_block@@JPBD1J@Z");

    assert_tag_debug_untracked_jul_11_2011(31, block);
    assert_tag_debug_untracked_jul_11_2011(32, block->definition);
    assert_tag_debug_untracked_jul_11_2011(33, element_count >= 0);

    if (element_count > block->definition->maximum_element_count)
    {
        event_wrapped(_event_critical, "### FATAL ERROR tool overflowed %s (%s==%d > %s==%d at %s #%d)", block->definition->name, element_count_string, element_count, block->definition->maximum_element_count_string, block->definition->maximum_element_count, file, line);
        dassert_tag_debug_untracked_jul_11_2011(41, false, "halt()");
    }
    else if (tag_block_resize(block, element_count))
    {
    }
    else
    {
        event_wrapped(_event_critical, "### FATAL ERROR tool can't resize %s, out of memory? (%s==%d at %s #%d)", block->definition->name, element_count_string, element_count, file, line);
        dassert_tag_debug_untracked_jul_11_2011(52, false, "halt()");
    }
};

long tool_tag_block_add_element_internal(s_tag_block * block, char const * file, long line)
{
    mangled_ppc("?tool_tag_block_add_element_internal@@YAJPAUs_tag_block@@PBDJ@Z");

    long new_element_index = NONE;

    assert_tag_debug_untracked_jul_11_2011(66, block);
    assert_tag_debug_untracked_jul_11_2011(67, block->definition);

    if (block->count + 1 > block->definition->maximum_element_count)
    {
        event_wrapped(_event_critical, "### FATAL ERROR tool overflowed %s (%s==%d at %s #%d)", block->definition->name, block->definition->maximum_element_count_string, block->definition->maximum_element_count, file, line);
        dassert_tag_debug_untracked_jul_11_2011(74, false, "halt()");
    }
    else
    {
        new_element_index = tag_block_add_element(block);
        if (new_element_index == NONE)
        {
            event_wrapped(_event_critical, "### FATAL ERROR tool can't add element to %s, out of memory? (%s #%d)", block->definition->name, file, line);
            dassert_tag_debug_untracked_jul_11_2011(85, false, "halt()");
        }
    }

    assert_tag_debug_untracked_jul_11_2011(90, new_element_index != NONE);

    return new_element_index;
};

void tool_duplicate_recursive_tag_block_elements_internal(s_tag_block const * source_block, s_tag_block * destination_block, char const * file, long line)
{
    mangled_ppc("?tool_duplicate_recursive_tag_block_elements_internal@@YAXPBUs_tag_block@@PAU1@PBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(102, source_block);
    assert_tag_debug_untracked_jul_11_2011(103, destination_block);
    assert_tag_debug_untracked_jul_11_2011(104, source_block->definition);
    assert_tag_debug_untracked_jul_11_2011(105, source_block->definition == destination_block->definition);

    if (duplicate_recursive_tag_block_elements(source_block, destination_block))
    {
        return;
    }

    event_wrapped(_event_critical, "### FATAL ERROR tool can't duplicate %s, out of memory? (%s #%d)", source_block->definition->name, file, line);
    dassert_tag_debug_untracked_jul_11_2011(116, false, "halt()");
};

void tool_tag_data_resize_internal(s_tag_data * data, unsigned long size, char const * size_string, char const * file, long line)
{
    mangled_ppc("?tool_tag_data_resize_internal@@YAXPAUs_tag_data@@KPBD1J@Z");

    assert_tag_debug_untracked_jul_11_2011(129, data);
    assert_tag_debug_untracked_jul_11_2011(130, data->definition);
    assert_tag_debug_untracked_jul_11_2011(131, size >= 0);

    if (size > data->definition->maximum_size)
    {
        event_wrapped(_event_critical, "### FATAL ERROR tool overflowed %s (%s==%d > %s==%d at %s #%d)", data->definition->name, size_string, size, data->definition->maximum_size_string, data->definition->maximum_size, file, line);
        dassert_tag_debug_untracked_jul_11_2011(139, false, "halt()");
    }
    else if (tag_data_resize(data, size))
    {
    }
    else
    {
        event_wrapped(_event_critical, "### FATAL ERROR tool can't resize %s, out of memory? (%s==%d at %s #%d)", data->definition->name, size_string, size, file, line);
        dassert_tag_debug_untracked_jul_11_2011(150, false, "halt()");
    }
};

