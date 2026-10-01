#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_group.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_group.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\scenario\scenario.h"
#include "omaha\game\game_globals.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\string_ids.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char const * g_map_override_option_flags_strings[k_number_of_map_override_option_flags] =
{
    "grenades on map",
    "shortcuts on map",
    "equipment on map",
    "powerups on map",
    "turrets on map",
    "indestructible vehicles"
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **global_ai_trait_weapon_settings_strings; // "?global_ai_trait_weapon_settings_strings@@3PAPBDA"
// struct s_string_list_definition global_ai_trait_weapon_settings; // "?global_ai_trait_weapon_settings@@3Us_string_list_definition@@A"
// struct s_tag_struct_definition game_engine_ai_traits_list_block_struct_definition; // "?game_engine_ai_traits_list_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition game_engine_ai_traits_list_block; // "?game_engine_ai_traits_list_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition game_engine_settings_definition_block; // "?game_engine_settings_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group game_engine_settings_definition_group; // "?game_engine_settings_definition_group@@3Us_tag_group@@A"
// struct s_tag_block_definition game_engine_globals_block; // "?game_engine_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group game_engine_globals_group; // "?game_engine_globals_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_game_engine_settings_definition_vtable; // "?legacy_game_engine_settings_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_game_engine_settings_definition_stream_definition; // "?legacy_game_engine_settings_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_game_engine_settings_definition_xsync_declaration; // "?legacy_game_engine_settings_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// struct s_tag_group_legacy_vtable legacy_game_engine_globals_vtable; // "?legacy_game_engine_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_game_engine_globals_stream_definition; // "?legacy_game_engine_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_game_engine_globals_xsync_declaration; // "?legacy_game_engine_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_tag_struct_vtable<class c_null_tag_vtable> game_engine_ai_traits_struct_struct_vtable; // "?game_engine_ai_traits_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_null_tag_vtable@@@@A"
// class c_legacy_tag_group_vtable_shim legacy_game_engine_settings_definition_vtable_shim; // "?legacy_game_engine_settings_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"
// class c_legacy_tag_group_vtable_shim legacy_game_engine_globals_vtable_shim; // "?legacy_game_engine_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static void s_map_override_option_string_resolver::to_string(enum e_map_override_option_flags, class c_static_string<64> *);
// bool game_engine_team_options_new_block_proc(void *);
// struct s_game_engine_settings_definition const * game_engine_settings_try_and_get(void);
// struct s_game_engine_ai_traits const * game_engine_settings_ai_traits_get_by_name(long);
// struct s_game_engine_player_traits const * game_engine_settings_player_traits_get_by_name(long);
// struct s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(long);
// struct s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(long, struct s_tag_block const *, long);
// struct s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(char const *);
// struct s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(char const *, struct s_tag_block const *, long);
// struct s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(long);
// struct s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(char const *);
// struct s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(long);
// struct s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(char const *);
// public: struct s_game_engine_team_options_team_definition & s_static_array<struct s_game_engine_team_options_team_definition, 8>::operator[]<long>(long);
// public: static bool s_static_array<struct s_game_engine_team_options_team_definition, 8>::valid<long>(long);

void s_map_override_option_string_resolver::to_string(e_map_override_option_flags value, c_static_string<64> * string)
{
    mangled_ppc("?to_string@s_map_override_option_string_resolver@@SAXW4e_map_override_option_flags@@PAV?$c_static_string@$0EA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(34, VALID_INDEX(value, k_number_of_map_override_option_flags));
    string->set(g_map_override_option_flags_strings[value]);
};

bool game_engine_team_options_new_block_proc(void * element)
{
    mangled_ppc("?game_engine_team_options_new_block_proc@@YA_NPAX@Z");

    s_game_engine_team_options_definition * team_options = static_cast<s_game_engine_team_options_definition *>(element);
    for (long team_index = 0; team_index < NUMBEROF(team_options->teams.m_elements); team_index++)
    {
        team_options->teams[team_index].initial_team_designator = static_cast<e_multiplayer_team_designator>(team_index);
    }

    return true;
};

s_game_engine_settings_definition const * game_engine_settings_try_and_get(void)
{
    mangled_ppc("?game_engine_settings_try_and_get@@YAPBUs_game_engine_settings_definition@@XZ");

    s_game_engine_settings_definition const * game_engine_settings = NULL;
    s_game_globals * game_globals = scenario_try_and_get_game_globals();
    if (game_globals != NULL)
    {
        s_game_engine_globals_definition const * game_engine_globals = static_cast<s_game_engine_globals_definition const *>(game_globals->game_engine_globals.index != NONE ? tag_get(GAME_ENGINE_GLOBALS_GROUP_TAG, game_globals->game_engine_globals.index) : NULL);
        if (game_engine_globals != NULL)
        {
            long settings_tag_index = game_engine_globals->game_engine_settings.index;
            if (settings_tag_index != NONE)
            {
                game_engine_settings = static_cast<s_game_engine_settings_definition const *>(tag_get(GAME_ENGINE_SETTINGS_DEFINITION_GROUP_TAG, settings_tag_index));
            }
        }
    }

    return game_engine_settings;
};

s_game_engine_ai_traits const * game_engine_settings_ai_traits_get_by_name(long name)
{
    mangled_ppc("?game_engine_settings_ai_traits_get_by_name@@YAPBUs_game_engine_ai_traits@@J@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_ai_traits const * traits = NULL;
    if (game_engine_settings != NULL)
    {
        for (long traits_index = 0; traits_index < game_engine_settings->ai_traits.count; traits_index++)
        {
            s_game_engine_ai_traits_list_definition const * test_traits = static_cast<s_game_engine_ai_traits_list_definition const *>(tag_block_get_element_with_size(&game_engine_settings->ai_traits, traits_index, sizeof(s_game_engine_ai_traits_list_definition)));
            if (test_traits->name == name)
            {
                traits = &test_traits->ai_traits;
                break;
            }
        }
    }

    return traits;
};

s_game_engine_player_traits const * game_engine_settings_player_traits_get_by_name(long name)
{
    mangled_ppc("?game_engine_settings_player_traits_get_by_name@@YAPBUs_game_engine_player_traits@@J@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_player_traits const * traits = NULL;
    if (game_engine_settings != NULL)
    {
        for (long traits_index = 0; traits_index < game_engine_settings->player_traits.count; traits_index++)
        {
            s_game_engine_player_traits_list_definition const * test_traits = static_cast<s_game_engine_player_traits_list_definition const *>(tag_block_get_element_with_size(&game_engine_settings->player_traits, traits_index, sizeof(s_game_engine_player_traits_list_definition)));
            if (test_traits->name == name)
            {
                traits = &test_traits->player_traits;
                break;
            }
        }
    }

    return traits;
};

s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(long name)
{
    mangled_ppc("?game_engine_settings_sandbox_variant_definition_get_by_name@@YAPBUs_game_engine_sandbox_variant_definition@@J@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_sandbox_variant_definition const * variant_definition = NULL;
    if (name != _string_id_invalid && name != _string_id_empty_string && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_sandbox_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->sandbox_variants, sizeof(s_game_engine_sandbox_variant_definition)));
    }

    return variant_definition;
};

s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(long name, s_tag_block const * tag_block, long variant_size)
{
    mangled_ppc("?game_engine_settings_variant_definition_get_by_name@@YAPBUs_game_engine_base_variant_definition@@JPBUs_tag_block@@J@Z");

    s_game_engine_base_variant_definition const * variant_definition = NULL;
    assert_tag_debug_untracked_jul_11_2011(702, name);
    assert_tag_debug_untracked_jul_11_2011(703, tag_block);

    for (long variant_index = 0; variant_index < tag_block->count; variant_index++)
    {
        s_game_engine_base_variant_definition const * test_variant = static_cast<s_game_engine_base_variant_definition const *>(tag_block_get_element_with_size(tag_block, variant_index, variant_size));
        if (test_variant->name_string_id == name)
        {
            variant_definition = test_variant;
            break;
        }
    }

    return variant_definition;
};

s_game_engine_sandbox_variant_definition const * game_engine_settings_sandbox_variant_definition_get_by_name(char const * name)
{
    mangled_ppc("?game_engine_settings_sandbox_variant_definition_get_by_name@@YAPBUs_game_engine_sandbox_variant_definition@@PBD@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_sandbox_variant_definition const * variant_definition = NULL;
    if (name[0] != '\0' && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_sandbox_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->sandbox_variants, sizeof(s_game_engine_sandbox_variant_definition)));
    }

    return variant_definition;
};

s_game_engine_base_variant_definition const * game_engine_settings_variant_definition_get_by_name(char const * name, s_tag_block const * tag_block, long variant_size)
{
    mangled_ppc("?game_engine_settings_variant_definition_get_by_name@@YAPBUs_game_engine_base_variant_definition@@PBDPBUs_tag_block@@J@Z");

    s_game_engine_base_variant_definition const * variant_definition = NULL;
    assert_tag_debug_untracked_jul_11_2011(726, name);
    assert_tag_debug_untracked_jul_11_2011(727, tag_block);

    for (long variant_index = 0; variant_index < tag_block->count; variant_index++)
    {
        s_game_engine_base_variant_definition const * test_variant = static_cast<s_game_engine_base_variant_definition const *>(tag_block_get_element_with_size(tag_block, variant_index, variant_size));
        if (strcmp(string_id_get_string_const(test_variant->name_string_id), name) == 0)
        {
            variant_definition = test_variant;
            break;
        }
    }

    return variant_definition;
};

s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(long name)
{
    mangled_ppc("?game_engine_settings_survival_variant_definition_get_by_name@@YAPBUs_game_engine_survival_variant_definition@@J@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_survival_variant_definition const * variant_definition = NULL;
    if (name != _string_id_invalid && name != _string_id_empty_string && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_survival_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->survival_variants, sizeof(s_game_engine_survival_variant_definition)));
    }

    return variant_definition;
};

s_game_engine_survival_variant_definition const * game_engine_settings_survival_variant_definition_get_by_name(char const * name)
{
    mangled_ppc("?game_engine_settings_survival_variant_definition_get_by_name@@YAPBUs_game_engine_survival_variant_definition@@PBD@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_survival_variant_definition const * variant_definition = NULL;
    if (name[0] != '\0' && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_survival_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->survival_variants, sizeof(s_game_engine_survival_variant_definition)));
    }

    return variant_definition;
};

s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(long name)
{
    mangled_ppc("?game_engine_settings_campaign_variant_definition_get_by_name@@YAPBUs_game_engine_campaign_variant_definition@@J@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_campaign_variant_definition const * variant_definition = NULL;
    if (name != _string_id_invalid && name != _string_id_empty_string && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_campaign_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->campaign_variants, sizeof(s_game_engine_campaign_variant_definition)));
    }

    return variant_definition;
};

s_game_engine_campaign_variant_definition const * game_engine_settings_campaign_variant_definition_get_by_name(char const * name)
{
    mangled_ppc("?game_engine_settings_campaign_variant_definition_get_by_name@@YAPBUs_game_engine_campaign_variant_definition@@PBD@Z");

    s_game_engine_settings_definition const * game_engine_settings = game_engine_settings_try_and_get();
    s_game_engine_campaign_variant_definition const * variant_definition = NULL;
    if (name[0] != '\0' && game_engine_settings != NULL)
    {
        variant_definition = static_cast<s_game_engine_campaign_variant_definition const *>(game_engine_settings_variant_definition_get_by_name(name, &game_engine_settings->campaign_variants, sizeof(s_game_engine_campaign_variant_definition)));
    }

    return variant_definition;
};

