#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\tag_helpers.cpp"
/* ---------- headers */

#include "omaha\toolbox\tag_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries_strings.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\tag_files\tag_group_editing.h"
#include "omaha\tag_files\tag_group_series.h"

#include <iterator>
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_tag_block_from_struct::c_tag_block_from_struct(void const *, struct s_tag_struct_definition const *);
// __int64 tag_block_get_max_element_size(struct s_tag_block_definition const *);
// __int64 tag_struct_get_max_size(struct s_tag_struct_definition const *);
// public: c_auto_tag_reference::c_auto_tag_reference(void);
// public: c_auto_tag_reference::~c_auto_tag_reference(void);
// bool path_to_tag_name_and_group(char const *, unsigned long *, class c_wrapped_array<char>);
// int std::distance<char const *>(char const *, char const *);
// void std::_Distance2<char const *, int>(char const *, char const *, int &, struct std::random_access_iterator_tag);

c_tag_block_from_struct::c_tag_block_from_struct(void const * struct_data, s_tag_struct_definition const * struct_definition)
{
    mangled_ppc("??0c_tag_block_from_struct@@QAA@PBXPBUs_tag_struct_definition@@@Z");

    s_tag_block_definition block_definition = { "fake_block_init", "fake_block_init", 1, "1", struct_definition };
    m_block_definition = block_definition;
    count = 1;
    address = const_cast<void *>(struct_data);
    definition = &m_block_definition;
};

__int64 tag_block_get_max_element_size(s_tag_block_definition const * block_definition)
{
    mangled_ppc("?tag_block_get_max_element_size@@YA_JPBUs_tag_block_definition@@@Z");

    return tag_struct_get_max_size(block_definition->struct_definition);
};

// $TODO nonmatching (stack slot order: target has scanner@0x50, max_size@0x120, aggregate_definition@0x128)
__int64 tag_struct_get_max_size(s_tag_struct_definition const * struct_definition)
{
    mangled_ppc("?tag_struct_get_max_size@@YA_JPBUs_tag_struct_definition@@@Z");

    __int64 max_size = struct_definition->get_struct_size();
    {
        c_tag_field_scanner scanner(struct_definition, NULL);
        scanner.add_all_external_aggregate_types();
        while (scanner.next())
        {
            s_tag_struct_definition const * aggregate_definition = tag_field_get_aggregate_definition(scanner.field());
            long external_maximum_element_count = tag_field_get_external_maximum_element_count(scanner.field());
            max_size += tag_struct_get_max_size(aggregate_definition) * external_maximum_element_count;
        }
    }
    return max_size;
};

c_auto_tag_reference::c_auto_tag_reference(void)
{
    mangled_ppc("??0c_auto_tag_reference@@QAA@XZ");

    tag_reference_initialize(this);
};

c_auto_tag_reference::~c_auto_tag_reference(void)
{
    mangled_ppc("??1c_auto_tag_reference@@QAA@XZ");

    destroy_tag_reference(this);
};

// $TODO nonmatching (target copies out_tag_name via the template ctor ??$?0D@?$c_wrapped_array@D@@QAA@AAV0@@Z; outer local slots swapped)
bool path_to_tag_name_and_group(char const * tag_path_plus_extension, unsigned long * out_group_tag, c_wrapped_array<char> out_tag_name)
{
    mangled_ppc("?path_to_tag_name_and_group@@YA_NPBDPAKV?$c_wrapped_array@D@@@Z");

    assert_tag_debug_untracked_jul_11_2011(338, tag_path_plus_extension);
    assert_tag_debug_untracked_jul_11_2011(339, out_group_tag);

    bool success = false;
    char const * extension = strchr(tag_path_plus_extension, '.');
    if (extension)
    {
        extension++;
    }

    if (string_is_not_empty(extension))
    {
        unsigned long group_tag = group_name_to_group_tag(extension);
        s_tag_group const * group = tag_group_get(group_tag);
        long tag_name_length = std::distance(tag_path_plus_extension, extension - 1);
        if (group && tag_name_length < out_tag_name.count())
        {
            string_copy_bounded(c_wrapped_array<char>(out_tag_name), make_wrapped_array(tag_path_plus_extension, tag_name_length));
            *out_group_tag = group->group_tag;
            success = true;
        }
    }

    return success;
};

// std::distance<char const *> and std::_Distance2<char const *, int> are instantiated from <iterator> by path_to_tag_name_and_group
