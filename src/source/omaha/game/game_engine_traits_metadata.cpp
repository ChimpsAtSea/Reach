#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_traits_metadata.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_traits_metadata.h"
#include "omaha\game\game_engine_traits.h"
#include "omaha\game\game_engine_traits_structures.h"
#include "omaha\saved_games\content\content_item_metadata.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void update_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void game_engine_variant_initialize_built_in_metadata(class c_game_engine_base_variant *, unsigned int, enum e_game_engine_type, unsigned __int64);
// void game_engine_variant_update_built_in_metadata(class c_game_engine_base_variant *, unsigned int);
// void update_built_in_metadata(class c_game_engine_base_variant *, unsigned int);

void game_engine_variant_initialize_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index, e_game_engine_type game_engine_index, unsigned __int64 timestamp)
{
    mangled_ppc("?game_engine_variant_initialize_built_in_metadata@@YAXPAVc_game_engine_base_variant@@IW4e_game_engine_type@@_K@Z");

    assert_tag_debug_untracked_jul_11_2011(24, variant);

    c_static_wchar_string<128> name;
    s_content_item_metadata * metadata = variant->get_metadata();
    name.set(variant->get_metadata()->name);
    content_item_metadata_initialize(metadata, static_cast<e_content_item_type>(6), 0x5329, name.get_string(), L"");

    {
        s_content_item_metadata * built_in_metadata = metadata;
        switch (game_engine_index)
        {
        case _game_engine_type_megalo:
            {
                built_in_metadata->gui_game_mode = static_cast<e_gui_game_mode>(3);
                built_in_metadata->game_mode = _game_mode_multiplayer;
                built_in_metadata->game_engine_type = _game_engine_type_megalo;
            }
            break;
        case _game_engine_type_sandbox:
            {
                built_in_metadata->gui_game_mode = static_cast<e_gui_game_mode>(4);
                built_in_metadata->game_mode = _game_mode_multiplayer;
                built_in_metadata->game_engine_type = _game_engine_type_sandbox;
            }
            break;
        case _game_engine_type_campaign:
            {
                built_in_metadata->gui_game_mode = static_cast<e_gui_game_mode>(1);
                built_in_metadata->game_mode = _game_mode_campaign;
                built_in_metadata->game_engine_type = _game_engine_type_campaign;
            }
            break;
        case _game_engine_type_survival:
            {
                built_in_metadata->gui_game_mode = static_cast<e_gui_game_mode>(6);
                built_in_metadata->game_mode = _game_mode_survival;
                built_in_metadata->game_engine_type = _game_engine_type_survival;
            }
            break;
        }
    }

    content_item_metadata_initialize_built_in_history(metadata, timestamp);
    metadata->unknown280 = -1;
    update_built_in_metadata(variant, variant_index);
};

void game_engine_variant_update_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index)
{
    mangled_ppc("?game_engine_variant_update_built_in_metadata@@YAXPAVc_game_engine_base_variant@@I@Z");

    assert_tag_debug_untracked_jul_11_2011(76, variant);

    update_built_in_metadata(variant, variant_index);
};

void update_built_in_metadata(c_game_engine_base_variant * variant, unsigned int variant_index)
{
    mangled_ppc("?update_built_in_metadata@@YAXPAVc_game_engine_base_variant@@I@Z");

    unsigned __int64 uid = game_engine_variant_get_uid(variant, variant_index);
    s_content_item_metadata * metadata = variant->get_metadata();
    metadata->unique_id = uid;
    metadata->parent_unique_id = uid;
    metadata->root_unique_id = uid;
};

