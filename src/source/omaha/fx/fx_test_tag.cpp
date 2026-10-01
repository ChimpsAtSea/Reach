/* ---------- headers */

#include "omaha\fx\fx_test_tag.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_group_legacy_vtable legacy_fx_test_vtable; // "?legacy_fx_test_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_block_definition fx_test_block; // "?fx_test_block@@3Us_tag_block_definition@@A"
// struct s_tag_group fx_test_group; // "?fx_test_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_fx_test_stream_definition; // "?legacy_fx_test_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_fx_test_xsync_declaration; // "?legacy_fx_test_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_fx_test_vtable_shim; // "?legacy_fx_test_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_fx_test::postprocess_proc(long, bool);

bool s_fx_test::postprocess_proc(long tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_fx_test@@SA_NJ_N@Z");

    return true;
};

