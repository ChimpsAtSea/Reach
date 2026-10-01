#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\variant_definitions.cpp"
/* ---------- headers */

#include "omaha\game\variant_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_variant.h"
#include "omaha\memory\bitstream.h"
#include "omaha\saved_games\content\content_item_metadata.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\scenario\scenario_map_variant.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition variant_globals_block; // "?variant_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group variant_globals_group; // "?variant_globals_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_variant_globals_vtable; // "?legacy_variant_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_variant_globals_stream_definition; // "?legacy_variant_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_variant_globals_xsync_declaration; // "?legacy_variant_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_variant_globals_vtable_shim; // "?legacy_variant_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: bool s_single_variant_definition::get_metadata(class c_content_item_metadata *) const;
// struct s_variant_globals_definition const * variant_globals_try_and_get(void);
// bool variant_definition_decode_map_variant(struct s_single_variant_definition const *, class c_map_variant *);
// bool variant_definition_decode_custom_game_variant(struct s_single_variant_definition const *, class c_game_variant *);

bool s_single_variant_definition::get_metadata(c_content_item_metadata * out_metadata) const
{
    mangled_ppc("?get_metadata@s_single_variant_definition@@QBA_NPAVc_content_item_metadata@@@Z");

    bool success = false;
    c_bitstream bitstream(static_cast<unsigned char *>(metadata.address), metadata.size);
    assert_tag_debug_untracked_jul_11_2011(78, out_metadata);

    bitstream.begin_reading();
    content_item_metadata_decode(&bitstream, out_metadata);
    bitstream.finish_reading();
    assert_tag_debug_untracked_jul_11_2011(84, !bitstream.error_occurred());

    success = content_item_metadata_valid(out_metadata);

    return success;
};

s_variant_globals_definition const * variant_globals_try_and_get(void)
{
    mangled_ppc("?variant_globals_try_and_get@@YAPBUs_variant_globals_definition@@XZ");

    s_variant_globals_definition const * variant_globals = NULL;
    scenario * scenario = global_scenario_try_and_get();
    if (scenario != NULL)
    {
        variant_globals = scenario->variant_globals.index != NONE ? static_cast<s_variant_globals_definition const *>(tag_get(VARIANT_GLOBALS_TAG, scenario->variant_globals.index)) : NULL;
    }

    return variant_globals;
};

bool variant_definition_decode_map_variant(s_single_variant_definition const * map_variant_definition, c_map_variant * out_map_variant)
{
    mangled_ppc("?variant_definition_decode_map_variant@@YA_NPBUs_single_variant_definition@@PAVc_map_variant@@@Z");

    assert_tag_debug_untracked_jul_11_2011(109, map_variant_definition);
    assert_tag_debug_untracked_jul_11_2011(110, out_map_variant);

    c_bitstream bitstream(static_cast<unsigned char *>(tag_data_get_pointer(&map_variant_definition->full_data, 0, 0)), map_variant_definition->full_data.size);
    bitstream.begin_reading();
    out_map_variant->decode(&bitstream);
    bitstream.finish_reading();

    return !bitstream.error_occurred();
};

bool variant_definition_decode_custom_game_variant(s_single_variant_definition const * game_variant_definition, c_game_variant * out_game_variant)
{
    mangled_ppc("?variant_definition_decode_custom_game_variant@@YA_NPBUs_single_variant_definition@@PAVc_game_variant@@@Z");

    assert_tag_debug_untracked_jul_11_2011(127, game_variant_definition);
    assert_tag_debug_untracked_jul_11_2011(128, out_game_variant);

    c_bitstream bitstream(static_cast<unsigned char *>(tag_data_get_pointer(&game_variant_definition->full_data, 0, 0)), game_variant_definition->full_data.size);
    out_game_variant->set_game_engine_index(_game_engine_type_megalo);
    c_game_engine_custom_variant * custom_variant = out_game_variant->get_custom_variant_writeable();
    custom_variant->initialize();
    bitstream.begin_reading();
    custom_variant->decode(&bitstream);
    bitstream.finish_reading();
    custom_variant->validate();

    return !bitstream.error_occurred();
};
