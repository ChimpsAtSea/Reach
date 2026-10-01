#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_cache_file_definitions.cpp"
/* ---------- headers */

#include "omaha\sound\sound_cache_file_definitions.h"
#include "omaha\cache\cache_file_builder.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition sound_cache_file_gestalt_block; // "?sound_cache_file_gestalt_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition cache_file_sound_block; // "?cache_file_sound_block@@3Us_tag_block_definition@@A"
// struct s_tag_group sound_cache_file_gestalt_group; // "?sound_cache_file_gestalt_group@@3Us_tag_group@@A"
// struct s_tag_group cache_file_sound_group; // "?cache_file_sound_group@@3Us_tag_group@@A"
// bool g_allow_sound_cache_file_editing; // "?g_allow_sound_cache_file_editing@@3_NA"
// struct s_tag_group_legacy_vtable legacy_sound_cache_file_gestalt_vtable; // "?legacy_sound_cache_file_gestalt_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_sound_cache_file_gestalt_stream_definition; // "?legacy_sound_cache_file_gestalt_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_sound_cache_file_gestalt_xsync_declaration; // "?legacy_sound_cache_file_gestalt_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// struct s_tag_group_legacy_vtable legacy_cache_file_sound_vtable; // "?legacy_cache_file_sound_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_cache_file_sound_stream_definition; // "?legacy_cache_file_sound_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_cache_file_sound_xsync_declaration; // "?legacy_cache_file_sound_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_tag_struct_vtable<class c_null_tag_vtable> sound_gestalt_permutation_languages_block_struct_struct_vtable; // "?sound_gestalt_permutation_languages_block_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_null_tag_vtable@@@@A"
// class c_legacy_tag_group_vtable_shim legacy_sound_cache_file_gestalt_vtable_shim; // "?legacy_sound_cache_file_gestalt_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"
// class c_legacy_tag_group_vtable_shim legacy_cache_file_sound_vtable_shim; // "?legacy_cache_file_sound_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool build_cache_file_prepare_sound_gestalt(class c_cache_file_global_tag_registry *);

bool build_cache_file_prepare_sound_gestalt(c_cache_file_global_tag_registry * registry)
{
    mangled_ppc("?build_cache_file_prepare_sound_gestalt@@YA_NPAVc_cache_file_global_tag_registry@@@Z");

    bool success = false;
    long sound_gestalt_tag_index = registry->get_global_tag_index(SOUND_CACHE_FILE_GESTALT_TAG);
    if (sound_gestalt_tag_index != 0)
    {
        tag_rename(sound_gestalt_tag_index, "I've got a lovely bunch of coconuts");
        success = true;
    }

    return success;
};
