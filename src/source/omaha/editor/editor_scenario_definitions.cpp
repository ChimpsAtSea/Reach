#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\editor\\editor_scenario_definitions.cpp"
/* ---------- headers */

#include "omaha\editor\editor_scenario_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition g_scenario_editor_folder_block; // "?g_scenario_editor_folder_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition g_scenario_editor_folder_block_struct_definition; // "?g_scenario_editor_folder_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_field *folder_index_fields_v1; // "?folder_index_fields_v1@@3PAUs_tag_field@@A"
// struct s_tag_field *folder_index_fields_v2; // "?folder_index_fields_v2@@3PAUs_tag_field@@A"
// struct s_tag_struct_definition g_scenario_editor_folder_index_overlay_struct; // "?g_scenario_editor_folder_index_overlay_struct@@3Us_tag_struct_definition@@A"

// bool load_v1_editor_folder_index(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *);

bool load_v1_editor_folder_index(unsigned long version, s_tag_field const *old_fields, long old_count, long old_element_size, void *old_data, s_tag_field const *new_fields, long new_count, long new_element_size, void *new_data)
{
    mangled_ppc("?load_v1_editor_folder_index@@YA_NKPBUs_tag_field@@JJPAX0JJ1@Z");

    assert_tag_debug_untracked_jul_11_2011(42, version==0);
    assert_tag_debug_untracked_jul_11_2011(43, old_count==1);
    assert_tag_debug_untracked_jul_11_2011(44, new_count==1);
    assert_tag_debug_untracked_jul_11_2011(45, old_fields==folder_index_fields_v1);
    assert_tag_debug_untracked_jul_11_2011(46, new_fields==folder_index_fields_v2);
    assert_tag_debug_untracked_jul_11_2011(47, old_element_size==sizeof(short));
    assert_tag_debug_untracked_jul_11_2011(48, new_element_size==sizeof(short));
    assert_tag_debug_untracked_jul_11_2011(49, old_data);
    assert_tag_debug_untracked_jul_11_2011(50, new_data);

    *static_cast<short *>(new_data) = NONE;

    return true;
};

