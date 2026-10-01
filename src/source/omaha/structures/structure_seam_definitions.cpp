/* ---------- headers */

#include "omaha\structures\structure_seam_definitions.h"
#include "omaha\physics\havok_mopp_code_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition structure_seam_mapping_block_struct_definition; // "?structure_seam_mapping_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition structure_seam_mapping_block; // "?structure_seam_mapping_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_structure_seams_vtable; // "?legacy_structure_seams_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_block_definition structure_seams_block; // "?structure_seams_block@@3Us_tag_block_definition@@A"
// struct s_tag_group structure_seams_group; // "?structure_seams_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_structure_seams_stream_definition; // "?legacy_structure_seams_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_structure_seams_xsync_declaration; // "?legacy_structure_seams_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_structure_seams_vtable_shim; // "?legacy_structure_seams_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool structure_seams_postprocess(long, bool);
// bool structure_seam_identifiers_are_equal(struct s_structure_seam_identifier const *, struct s_structure_seam_identifier const *);

bool structure_seams_postprocess(long structure_seams_index, bool for_editor)
{
    mangled_ppc("?structure_seams_postprocess@@YA_NJ_N@Z");

    havok_mopp_code_definitions_fixup(&static_cast<s_structure_seams *>(tag_get(STRUCTURE_SEAMS_TAG, structure_seams_index))->seam_triangle_mopp_codes);

    return true;
};

bool structure_seam_identifiers_are_equal(s_structure_seam_identifier const * structure_seam_identifier0, s_structure_seam_identifier const * structure_seam_identifier1)
{
    mangled_ppc("?structure_seam_identifiers_are_equal@@YA_NPBUs_structure_seam_identifier@@0@Z");

    return system_global_unique_identifiers_equal(&structure_seam_identifier0->identifier, &structure_seam_identifier1->identifier);
};

