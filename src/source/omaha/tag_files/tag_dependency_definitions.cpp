#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_dependency_definitions.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_dependency_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_streams.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_stream_definition tag_dependency_list_stream_definition; // "?tag_dependency_list_stream_definition@@3Us_tag_stream_definition@@A"

// bool build_tag_dependency_list_from_tag(struct s_tag_block const *, struct s_tag_block *);
// bool add_tag_dependencies_from_block(struct s_tag_block const *, struct s_tag_dependency_list_definition *);
// bool add_single_tag_dependency(struct s_tag_reference const *, struct s_tag_reference_definition const *, struct s_tag_dependency_list_definition *);
// struct s_tag_block * tag_try_and_get_tag_dependency_list(long);
// struct s_tag_block * tag_get_or_create_tag_dependency_list(long);

bool build_tag_dependency_list_from_tag(s_tag_block const * block, s_tag_block * out_dependency_list_block)
{
    mangled_ppc("?build_tag_dependency_list_from_tag@@YA_NPBUs_tag_block@@PAU1@@Z");

    assert_tag_debug_untracked_jul_11_2011(76, out_dependency_list_block);
    assert_tag_debug_untracked_jul_11_2011(77, out_dependency_list_block->definition);

    tag_block_resize(out_dependency_list_block, 1);
    s_tag_dependency_list_definition * dependency_list = static_cast<s_tag_dependency_list_definition *>(tag_block_get_element_with_size(out_dependency_list_block, 0, sizeof(s_tag_dependency_list_definition)));
    tag_block_delete_all_elements(&dependency_list->dependencies);
    bool success = add_tag_dependencies_from_block(block, dependency_list);

    return success;
};

bool add_tag_dependencies_from_block(s_tag_block const * block, s_tag_dependency_list_definition * out_dependency_list)
{
    mangled_ppc("?add_tag_dependencies_from_block@@YA_NPBUs_tag_block@@PAUs_tag_dependency_list_definition@@@Z");

    bool success = true;

    for (long element_index = 0, element_count = block->count; element_index < element_count; element_index++)
    {
        c_tag_field_scanner scanner(block->definition, tag_block_get_element(block, element_index));
        scanner.add_scan_type(static_cast<e_tag_field>(0x27) /* _field_tag_reference */);
        scanner.add_scan_type(static_cast<e_tag_field>(0x28) /* _field_block */);

        while (scanner.next())
        {
            switch (scanner.type())
            {
            case 0x28: // _field_block
                add_tag_dependencies_from_block(static_cast<s_tag_block const *>(scanner.address()), out_dependency_list);
                break;
            case 0x27: // _field_tag_reference
                add_single_tag_dependency(static_cast<s_tag_reference const *>(scanner.address()), static_cast<s_tag_reference_definition const *>(scanner.definition()), out_dependency_list);
                break;
            }
        }
    }

    return success;
};

bool add_single_tag_dependency(s_tag_reference const * reference, s_tag_reference_definition const * reference_definition, s_tag_dependency_list_definition * out_dependency_list)
{
    mangled_ppc("?add_single_tag_dependency@@YA_NPBUs_tag_reference@@PBUs_tag_reference_definition@@PAUs_tag_dependency_list_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(20, reference);
    assert_tag_debug_untracked_jul_11_2011(21, reference_definition);
    assert_tag_debug_untracked_jul_11_2011(22, out_dependency_list);

    bool success = false;

    if (reference_points_somewhere(reference))
    {
        long dependency_index = tag_block_add_element(&out_dependency_list->dependencies);
        if (dependency_index != NONE)
        {
            s_tag_dependency_definition * dependency = static_cast<s_tag_dependency_definition *>(tag_block_get_element_with_size(&out_dependency_list->dependencies, dependency_index, sizeof(s_tag_dependency_definition)));
            tag_reference_copy(reference, &dependency->dependency);
            dependency->flags = reference_definition->flags;
        }
    }

    return success;
};

s_tag_block * tag_try_and_get_tag_dependency_list(long tag_index)
{
    mangled_ppc("?tag_try_and_get_tag_dependency_list@@YAPAUs_tag_block@@J@Z");

    s_tag_block * dependency_list_block = tag_try_and_get_alternate_stream_block(tag_index, 'want');
    return dependency_list_block;
};

s_tag_block * tag_get_or_create_tag_dependency_list(long tag_index)
{
    mangled_ppc("?tag_get_or_create_tag_dependency_list@@YAPAUs_tag_block@@J@Z");

    s_tag_block * dependency_list_block = tag_get_alternate_stream_root_block(tag_index, 'want');
    return dependency_list_block;
};

