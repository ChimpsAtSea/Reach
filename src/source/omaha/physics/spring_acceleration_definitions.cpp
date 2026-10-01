#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\spring_acceleration_definitions.cpp"
/* ---------- headers */

#include "omaha\physics\spring_acceleration_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern real fabs(real x);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition spring_acceleration_block; // "?spring_acceleration_block@@3Us_tag_block_definition@@A"
// struct s_tag_group spring_acceleration_group; // "?spring_acceleration_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_spring_acceleration_vtable; // "?legacy_spring_acceleration_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_spring_acceleration_stream_definition; // "?legacy_spring_acceleration_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_spring_acceleration_xsync_declaration; // "?legacy_spring_acceleration_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_spring_acceleration_vtable_shim; // "?legacy_spring_acceleration_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool spring_acceleration_linear_postprocess(long, void *, bool);

bool spring_acceleration_linear_postprocess(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?spring_acceleration_linear_postprocess@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_spring_linear_acceleration_block * linear_acceleration = static_cast<s_spring_linear_acceleration_block *>(element);
        if (linear_acceleration->world_acceleration_scale == 0.0f)
        {
            linear_acceleration->world_acceleration_scale = 1.0f;
        }

        if (!realcmp(linear_acceleration->acceleration_range, 0.0f))
        {
            linear_acceleration->inverse_acceleration_range = 1.0f / linear_acceleration->acceleration_range;
        }
        else
        {
            linear_acceleration->inverse_acceleration_range = 0.0f;
        }
    }

    return true;
};

