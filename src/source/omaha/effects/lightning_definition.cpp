/* ---------- headers */

#include "omaha\effects\lightning_definition.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition lightning_system_block; // "?lightning_system_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_lightning_system_vtable; // "?legacy_lightning_system_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group lightning_system_group; // "?lightning_system_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_lightning_system_stream_definition; // "?legacy_lightning_system_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_lightning_system_xsync_declaration; // "?legacy_lightning_system_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_lightning_system_vtable_shim; // "?legacy_lightning_system_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_bolt_definition::new_block_proc(void *);
// public: static bool s_bolt_definition::postprocess_block_proc(long, void *, bool);
// public: static bool s_lightning_system_definition::postprocess_proc(class c_tag_index, bool);

bool s_bolt_definition::new_block_proc(void * element)
{
    mangled_ppc("?new_block_proc@s_bolt_definition@@SA_NPAX@Z");

    return true;
};

bool s_bolt_definition::postprocess_block_proc(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_block_proc@s_bolt_definition@@SA_NJPAX_N@Z");

    bool success = true;

    return success;
};

bool s_lightning_system_definition::postprocess_proc(c_tag_index tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_lightning_system_definition@@SA_NVc_tag_index@@_N@Z");

    return true;
};

