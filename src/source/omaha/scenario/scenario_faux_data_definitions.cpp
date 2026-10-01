#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_faux_data_definitions.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_faux_data_definitions.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition scenario_faux_data_block; // "?scenario_faux_data_block@@3Us_tag_block_definition@@A"
// struct s_tag_group scenario_faux_data_group; // "?scenario_faux_data_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_scenario_faux_data_vtable; // "?legacy_scenario_faux_data_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_scenario_faux_data_stream_definition; // "?legacy_scenario_faux_data_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_scenario_faux_data_xsync_declaration; // "?legacy_scenario_faux_data_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_scenario_faux_data_vtable_shim; // "?legacy_scenario_faux_data_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// struct s_faux_data_lightmap_group_data * faux_data_find_lightgroup_for_bsp(long, long);

s_faux_data_lightmap_group_data * faux_data_find_lightgroup_for_bsp(long faux_data_index, long bsp_index)
{
    mangled_ppc("?faux_data_find_lightgroup_for_bsp@@YAPAUs_faux_data_lightmap_group_data@@JJ@Z");

    s_faux_data_lightmap_group_data * result = NULL;
    if (faux_data_index != NONE)
    {
        s_scenario_faux_data * faux_data = static_cast<s_scenario_faux_data *>(tag_get(SCENARIO_FAUX_DATA_TAG, faux_data_index));
        for (long lightmap_group_index = 0; result == NULL && lightmap_group_index < faux_data->lightmap_groups.count; lightmap_group_index++)
        {
            s_faux_data_lightmap_group_data * lightmap_group = static_cast<s_faux_data_lightmap_group_data *>(tag_block_get_element_with_size(&faux_data->lightmap_groups, lightmap_group_index, sizeof(s_faux_data_lightmap_group_data)));
            if (lightmap_group->bsp_reference_index == bsp_index)
            {
                result = lightmap_group;
            }
        }
    }

    return result;
};

