#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\multiplayer_definitions.cpp"
/* ---------- headers */

#include "omaha\game\multiplayer_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_globals.h"
#include "omaha\items\equipment_definitions.h"
#include "omaha\items\projectile_definitions.h"
#include "omaha\items\weapon_definitions.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\text\text_group.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\vehicle_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition spawn_influence_weight_falloff_function_block; // "?spawn_influence_weight_falloff_function_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition spawn_influence_weight_falloff_function_block_struct_definition; // "?spawn_influence_weight_falloff_function_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition multiplayer_color_block_struct_definition; // "?multiplayer_color_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition multiplayer_color_block; // "?multiplayer_color_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition weapon_spawn_influence_block_struct_definition; // "?weapon_spawn_influence_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition weapon_spawn_influence_block; // "?weapon_spawn_influence_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition vehicle_spawn_influence_block; // "?vehicle_spawn_influence_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition vehicle_spawn_influence_block_struct_definition; // "?vehicle_spawn_influence_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition projectile_spawn_influence_block_struct_definition; // "?projectile_spawn_influence_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition projectile_spawn_influence_block; // "?projectile_spawn_influence_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition equipment_spawn_influence_block; // "?equipment_spawn_influence_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition equipment_spawn_influence_block_struct_definition; // "?equipment_spawn_influence_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition game_engine_status_response_block; // "?game_engine_status_response_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition game_engine_status_response_block_struct_definition; // "?game_engine_status_response_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition multiplayer_globals_block; // "?multiplayer_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group multiplayer_globals_group; // "?multiplayer_globals_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_multiplayer_globals_vtable; // "?legacy_multiplayer_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_multiplayer_globals_stream_definition; // "?legacy_multiplayer_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_multiplayer_globals_xsync_declaration; // "?legacy_multiplayer_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_multiplayer_globals_vtable_shim; // "?legacy_multiplayer_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long create_fakey_tag(unsigned long, char const *);
// void multiplayer_globals_clean_for_mainmenu(struct s_multiplayer_globals_definition *);
// void multiplayer_globals_fix_dependent_references(long, bool);
// void multiplayer_scenario_globals_fix_dependent_references(long, long);
// struct s_multiplayer_universal_globals_definition * scenario_multiplayer_globals_try_and_get_universal_data(void);
// struct s_multiplayer_universal_globals_definition * multiplayer_globals_try_and_get_universal_data(struct s_multiplayer_globals_definition const *);
// struct s_multiplayer_runtime_globals_definition * scenario_multiplayer_globals_try_and_get_runtime_data(void);
// bool multiplayer_runtime_data_get_respawn_string(enum e_player_respawn_status_string, class c_static_wchar_string<256> *);

long create_fakey_tag(unsigned long group_tag, char const * name)
{
    mangled_ppc("?create_fakey_tag@@YAJKPBD@Z");

    long tag_index = tag_loaded(group_tag, name);
    if (tag_index == NONE)
    {
        tag_index = tag_new(group_tag, name);
    }

    return tag_index;
};

void multiplayer_globals_clean_for_mainmenu(s_multiplayer_globals_definition * multiplayer_globals)
{
    mangled_ppc("?multiplayer_globals_clean_for_mainmenu@@YAXPAUs_multiplayer_globals_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(479, multiplayer_globals);
};

void multiplayer_globals_fix_dependent_references(long multiplayer_globals_index, bool load_missing_tags)
{
    mangled_ppc("?multiplayer_globals_fix_dependent_references@@YAXJ_N@Z");

    if (multiplayer_globals_index != NONE)
    {
        s_multiplayer_runtime_globals_definition * runtime_data;
        s_multiplayer_globals_definition * multiplayer_globals = static_cast<s_multiplayer_globals_definition *>(tag_get(k_multiplayer_globals_definition_tag, multiplayer_globals_index));
        runtime_data = multiplayer_globals_try_and_get_runtime_data(multiplayer_globals);
        if (runtime_data && runtime_data->multiplayer_constants.count > 0)
        {
            s_multiplayer_constants * multiplayer_constants = static_cast<s_multiplayer_constants *>(tag_block_get_element_with_size(&runtime_data->multiplayer_constants, 0, sizeof(s_multiplayer_constants)));

            for (long weapon_index = 0; weapon_index < multiplayer_constants->weapon_influencers.count; weapon_index++)
            {
                s_weapon_spawn_influence * weapon_influence = &static_cast<s_weapon_spawn_influence *>(multiplayer_constants->weapon_influencers.address)[weapon_index];
                weapon_influence->weapon.index = tag_loaded(WEAPON_DEFINITION_TAG, weapon_influence->weapon.name);
                if (weapon_influence->weapon.index == NONE)
                {
                    if (load_missing_tags)
                    {
                        weapon_influence->weapon.index = tag_load(WEAPON_DEFINITION_TAG, weapon_influence->weapon.name, 0);
                    }

                    if (weapon_influence->weapon.index == NONE)
                    {
                        event_wrapped(_event_warning, "### weapon spawn influencer '%s' not available in mp runtime globals constants for this scenario", weapon_influence->weapon.name);
                    }
                }
            }

            for (long vehicle_index = 0; vehicle_index < multiplayer_constants->vehicle_influencers.count; vehicle_index++)
            {
                s_vehicle_spawn_influence * vehicle_influence = &static_cast<s_vehicle_spawn_influence *>(multiplayer_constants->vehicle_influencers.address)[vehicle_index];
                vehicle_influence->vehicle.index = tag_loaded(VEHICLE_DEFINITION_TAG, vehicle_influence->vehicle.name);
                if (vehicle_influence->vehicle.index == NONE)
                {
                    if (load_missing_tags)
                    {
                        vehicle_influence->vehicle.index = tag_load(VEHICLE_DEFINITION_TAG, vehicle_influence->vehicle.name, 0);
                    }

                    if (vehicle_influence->vehicle.index == NONE)
                    {
                        event_wrapped(_event_warning, "### vehicle spawn influencer '%s' not available in mp runtime globals constants for this scenario", vehicle_influence->vehicle.name);
                    }
                }
            }

            for (long projectile_index = 0; projectile_index < multiplayer_constants->projectile_influencers.count; projectile_index++)
            {
                s_projectile_spawn_influence * projectile_influence = &static_cast<s_projectile_spawn_influence *>(multiplayer_constants->projectile_influencers.address)[projectile_index];
                projectile_influence->projectile.index = tag_loaded(PROJECTILE_DEFINITION_TAG, projectile_influence->projectile.name);
                if (projectile_influence->projectile.index == NONE)
                {
                    if (load_missing_tags)
                    {
                        projectile_influence->projectile.index = tag_load(PROJECTILE_DEFINITION_TAG, projectile_influence->projectile.name, 0);
                    }

                    if (projectile_influence->projectile.index == NONE)
                    {
                        event_wrapped(_event_warning, "### projectile spawn influencer '%s' not available in mp runtime globals constants for this scenario", projectile_influence->projectile.name);
                    }
                }
            }

            for (long equipment_index = 0; equipment_index < multiplayer_constants->equipment_influencers.count; equipment_index++)
            {
                s_equipment_spawn_influence * equipment_influence = &static_cast<s_equipment_spawn_influence *>(multiplayer_constants->equipment_influencers.address)[equipment_index];
                equipment_influence->equipment.index = tag_loaded(EQUIPMENT_DEFINITION_TAG, equipment_influence->equipment.name);
                if (equipment_influence->equipment.index == NONE)
                {
                    if (load_missing_tags)
                    {
                        equipment_influence->equipment.index = tag_load(EQUIPMENT_DEFINITION_TAG, equipment_influence->equipment.name, 0);
                    }

                    if (equipment_influence->equipment.index == NONE)
                    {
                        event_wrapped(_event_warning, "### equipment spawn influencer '%s' not available in mp runtime globals constants for this scenario", equipment_influence->equipment.name);
                    }
                }
            }
        }
    }
};

void multiplayer_scenario_globals_fix_dependent_references(long game_globals_index, long scenario_index)
{
    mangled_ppc("?multiplayer_scenario_globals_fix_dependent_references@@YAXJJ@Z");

    scenario * scenario = static_cast<::scenario *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
    if (scenario->type == _scenario_type_multiplayer)
    {
        long globals_index = game_globals_index;
        if (globals_index != NONE)
        {
            s_game_globals * game_globals = static_cast<s_game_globals *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, globals_index));
            long multiplayer_globals_index = game_globals->multiplayer_globals.index;
            if (multiplayer_globals_index != NONE)
            {
                multiplayer_globals_fix_dependent_references(multiplayer_globals_index, false);
            }
        }
    }
};

s_multiplayer_universal_globals_definition * scenario_multiplayer_globals_try_and_get_universal_data(void)
{
    mangled_ppc("?scenario_multiplayer_globals_try_and_get_universal_data@@YAPAUs_multiplayer_universal_globals_definition@@XZ");

    s_multiplayer_universal_globals_definition * universal_data;
    s_game_globals * game_globals = scenario_try_and_get_game_globals();
    s_multiplayer_globals_definition const * multiplayer_globals = game_globals->multiplayer_globals.index != NONE ? static_cast<s_multiplayer_globals_definition const *>(tag_get(k_multiplayer_globals_definition_tag, game_globals->multiplayer_globals.index)) : NULL;
    universal_data = multiplayer_globals_try_and_get_universal_data(multiplayer_globals);

    return universal_data;
};

s_multiplayer_universal_globals_definition * multiplayer_globals_try_and_get_universal_data(s_multiplayer_globals_definition const * multiplayer_globals)
{
    mangled_ppc("?multiplayer_globals_try_and_get_universal_data@@YAPAUs_multiplayer_universal_globals_definition@@PBUs_multiplayer_globals_definition@@@Z");

    return multiplayer_globals && multiplayer_globals->universal.count > 0 ? static_cast<s_multiplayer_universal_globals_definition *>(tag_block_get_element_with_size(&multiplayer_globals->universal, 0, sizeof(s_multiplayer_universal_globals_definition))) : NULL;
};

s_multiplayer_runtime_globals_definition * scenario_multiplayer_globals_try_and_get_runtime_data(void)
{
    mangled_ppc("?scenario_multiplayer_globals_try_and_get_runtime_data@@YAPAUs_multiplayer_runtime_globals_definition@@XZ");

    s_game_globals * game_globals = scenario_try_and_get_game_globals();
    s_multiplayer_runtime_globals_definition * runtime_data;
    s_multiplayer_globals_definition const * multiplayer_globals = game_globals->multiplayer_globals.index != NONE ? static_cast<s_multiplayer_globals_definition const *>(tag_get(k_multiplayer_globals_definition_tag, game_globals->multiplayer_globals.index)) : NULL;
    runtime_data = multiplayer_globals_try_and_get_runtime_data(multiplayer_globals);

    return runtime_data;
};

bool multiplayer_runtime_data_get_respawn_string(e_player_respawn_status_string desired_string, c_static_wchar_string<256> * text_buffer)
{
    mangled_ppc("?multiplayer_runtime_data_get_respawn_string@@YA_NW4e_player_respawn_status_string@@PAV?$c_static_wchar_string@$0BAA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(636, VALID_INDEX(desired_string, k_number_of_respawn_status_strings));
    assert_tag_debug_untracked_jul_11_2011(637, text_buffer!=NULL);

    bool result = false;
    s_multiplayer_runtime_globals_definition * runtime_data = scenario_multiplayer_globals_try_and_get_runtime_data();
    if (runtime_data && runtime_data->in_game_text.index != NONE)
    {
        s_multiplayer_constants * multiplayer_constants = static_cast<s_multiplayer_constants *>(tag_block_get_element_with_size(&runtime_data->multiplayer_constants, 0, sizeof(s_multiplayer_constants)));
        long respawn_string = multiplayer_constants->respawn_strings[desired_string];
        if (respawn_string != -1 && respawn_string != 0)
        {
            string_list_get_normal_string(runtime_data->in_game_text.index, respawn_string, text_buffer, NULL);
            result = true;
        }
    }

    return result;
};

