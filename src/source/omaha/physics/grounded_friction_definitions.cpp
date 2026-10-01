/* ---------- headers */

#include "omaha\physics\grounded_friction_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_group_legacy_vtable legacy_grounded_friction_vtable; // "?legacy_grounded_friction_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_block_definition grounded_friction_block; // "?grounded_friction_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_grounded_friction_reference; // "?global_grounded_friction_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group grounded_friction_group; // "?grounded_friction_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_grounded_friction_stream_definition; // "?legacy_grounded_friction_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_grounded_friction_xsync_declaration; // "?legacy_grounded_friction_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_grounded_friction_vtable_shim; // "?legacy_grounded_friction_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool grounded_friction_postprocess(class c_tag_index, bool);

bool grounded_friction_postprocess(c_tag_index tag_index, bool for_editor)
{
    mangled_ppc("?grounded_friction_postprocess@@YA_NVc_tag_index@@_N@Z");

    s_grounded_friction_definition * definition = static_cast<s_grounded_friction_definition *>(tag_get(GROUNDED_FRICTION_GROUP_TAG, tag_index));
    if (realcmp(definition->minimum_asymmetry_ratio_for_axis_lock, 0.0f))
    {
        real default_minimum_asymmetry_ratio = 2.0f;
        definition->minimum_asymmetry_ratio_for_axis_lock = default_minimum_asymmetry_ratio;
    }

    return true;
};

