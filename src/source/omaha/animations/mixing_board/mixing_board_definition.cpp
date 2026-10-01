#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\mixing_board\\mixing_board_definition.cpp"
/* ---------- headers */

#include "omaha\animations\mixing_board\mixing_board_definition.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

long g_mixing_board_component_sizes[k_total_mixing_board_component_types] = { 12, 88, 36, 64, 104, 108 };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long *g_mixing_board_component_sizes; // "?g_mixing_board_component_sizes@@3PAJA"
// class c_mixing_board_definition *g_mixing_board_definition_list; // "?g_mixing_board_definition_list@@3PAVc_mixing_board_definition@@A"

// class c_mixing_board_definition const * get_mixing_board_definition(long);
// public: long c_mixing_board_definition::get_component_offset(long, long) const;
// public: c_mixing_board_component_data::c_mixing_board_component_data(long, long);

c_mixing_board_definition const * get_mixing_board_definition(long index)
{
    mangled_ppc("?get_mixing_board_definition@@YAPBVc_mixing_board_definition@@J@Z");

    c_mixing_board_definition const * definition = NULL;
    if (VALID_INDEX(index, k_total_mixing_board_definitions))
    {
        definition = &g_mixing_board_definition_list[index];
    }

    return definition;
};

long c_mixing_board_definition::get_component_offset(long component_type, long component_index) const
{
    mangled_ppc("?get_component_offset@c_mixing_board_definition@@QBAJJJ@Z");

    assert_tag_debug_untracked_jul_11_2011(141, component_type>=k_mixing_board_first_component_type && component_type<=k_mixing_board_last_component_type);
    assert_tag_debug_untracked_jul_11_2011(142, validate_component_index(component_type, component_index));

    long offset = get_component_type_offset(component_type);
    offset += g_mixing_board_component_sizes[component_type] * component_index;
    assert_tag_debug_untracked_jul_11_2011(145, offset>=0);
    assert_tag_debug_untracked_jul_11_2011(146, offset+g_mixing_board_component_sizes[component_type] <= get_total_size());

    return offset;
};

c_mixing_board_component_data::c_mixing_board_component_data(long _offset, long _count) :
    offset(_offset),
    count(_count)
{
    mangled_ppc("??0c_mixing_board_component_data@@QAA@JJ@Z");

    assert_decomp(count>=0 && count<k_maximum_components_per_type, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\mixing_board\\mixing_board_definition.h", 61);
};

