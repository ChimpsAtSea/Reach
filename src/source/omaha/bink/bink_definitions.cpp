#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\bink\\bink_definitions.cpp"
/* ---------- headers */

#include "omaha\bink\bink_definitions.h"
#include "omaha\memory\byte_swapping.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

long const bink_bs_codes[] = { _begin_bs_array, _1byte, _4byte, _end_bs_array };

static byte_swap_definition bink_bs_definition =
{
    "bink",
    4,
    bink_bs_codes,
    __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__,
    __LINE__,
    BYTE_SWAP_DEFINITION_SIGNATURE,
    false
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long const *const const bink_bs_codes; // "?bink_bs_codes@@3QBJB"
// struct s_tag_block_definition bink_block; // "?bink_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition bink_resource_struct; // "?bink_resource_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_resource_definition bink_resource; // "?bink_resource@@3Us_tag_resource_definition@@A"
// struct s_tag_group bink_group; // "?bink_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_bink_vtable; // "?legacy_bink_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_bink_stream_definition; // "?legacy_bink_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_bink_xsync_declaration; // "?legacy_bink_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_tag_struct_vtable<class c_null_tag_vtable> bink_resource_struct_vtable; // "?bink_resource_struct_vtable@@3V?$c_tag_struct_vtable@Vc_null_tag_vtable@@@@A"
// class c_tag_resource_vtable<class c_null_tag_vtable> bink_resource_resource_vtable; // "?bink_resource_resource_vtable@@3V?$c_tag_resource_vtable@Vc_null_tag_vtable@@@@A"
// class c_legacy_tag_group_vtable_shim legacy_bink_vtable_shim; // "?legacy_bink_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// void byte_swap_bink_resource_data(void *, void *, long, bool);

void byte_swap_bink_resource_data(void *resource, void *data, long data_size, bool unknown)
{
    mangled_ppc("?byte_swap_bink_resource_data@@YAXPAX0J_N@Z");

    if (!unknown && data_size > 0)
    {
        long data_count = (data_size - 1) / 4 + 1;
        byte_swap_data(&bink_bs_definition, data, data_count);
    }
};

