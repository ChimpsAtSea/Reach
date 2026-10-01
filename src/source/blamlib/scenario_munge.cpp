/* ---------- headers */

#include "blamlib\scenario_munge.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\hs\hs_scenario_definitions.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\scenario\scenario_resource_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool scenario_prune(long, class c_flags<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>);
// public: void c_flags_no_init<enum e_scenario_split_resource_bit, unsigned long, 1, struct s_default_enum_string_resolver>::set(enum e_scenario_split_resource_bit, bool);
// public: bool c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::test(enum e_scenario_prune_flags) const;
// public: static bool c_flags_no_init<enum e_scenario_split_resource_bit, unsigned long, 1, struct s_default_enum_string_resolver>::valid_bit(enum e_scenario_split_resource_bit);
// private: static unsigned long c_flags_no_init<enum e_scenario_split_resource_bit, unsigned long, 1, struct s_default_enum_string_resolver>::flag_size_type(enum e_scenario_split_resource_bit);

bool scenario_prune(long scenario_index, c_flags<e_scenario_prune_flags, unsigned long, k_scenario_prune_flags_count> prune_flags)
{
    mangled_ppc("?scenario_prune@@YA_NJV?$c_flags@W4e_scenario_prune_flags@@K$07Us_default_enum_string_resolver@@@@@Z");

    scenario * scenario_definition = static_cast<scenario *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));

    if (prune_flags.test(_scenario_prune_bit0))
    {
        tag_block_delete_all_elements(&scenario_definition->scenario_resources);
    }

    if (prune_flags.test(_scenario_prune_bit1) ||
        prune_flags.test(_scenario_prune_bit3) ||
        prune_flags.test(_scenario_prune_bit4) ||
        prune_flags.test(_scenario_prune_bit2) ||
        prune_flags.test(_scenario_prune_bit5) ||
        prune_flags.test(_scenario_prune_bit6))
    {
        tag_block_delete_all_elements(&scenario_definition->predicted_resources);
        tag_data_resize(&scenario_definition->editor_scenario_data, 0);
        tag_block_delete_all_elements(&scenario_definition->unused_scenario_environment_objects);
        tag_block_delete_all_elements(&scenario_definition->bipeds);
        tag_block_delete_all_elements(&scenario_definition->biped_palette);
        tag_block_delete_all_elements(&scenario_definition->vehicles);
        tag_block_delete_all_elements(&scenario_definition->vehicle_palette);
        tag_block_delete_all_elements(&scenario_definition->equipment);
        tag_block_delete_all_elements(&scenario_definition->equipment_palette);
        tag_block_delete_all_elements(&scenario_definition->weapons);
        tag_block_delete_all_elements(&scenario_definition->weapon_palette);
        tag_block_delete_all_elements(&scenario_definition->terminals);
        tag_block_delete_all_elements(&scenario_definition->terminal_palette);
        tag_block_delete_all_elements(&scenario_definition->giants);
        tag_block_delete_all_elements(&scenario_definition->giant_palette);
        tag_block_delete_all_elements(&scenario_definition->map_variant_palettes);
        tag_block_delete_all_elements(&scenario_definition->soft_ceilings);
        tag_block_delete_all_elements(&scenario_definition->recorded_animations);
        tag_block_delete_all_elements(&scenario_definition->zone_set_switch_trigger_volumes);
        tag_block_delete_all_elements(&scenario_definition->enemy_forbid_influence);
        tag_block_delete_all_elements(&scenario_definition->enemy_bias_influence);
        tag_block_delete_all_elements(&scenario_definition->ally_bias_influence);
        tag_block_delete_all_elements(&scenario_definition->selected_ally_bias_influence);
        tag_block_delete_all_elements(&scenario_definition->dead_teammate_influence);
        tag_block_delete_all_elements(&scenario_definition->weapon_spawn_influencers);
        tag_block_delete_all_elements(&scenario_definition->vehicle_spawn_influencers);
        tag_block_delete_all_elements(&scenario_definition->projectile_spawn_influencers);
        tag_block_delete_all_elements(&scenario_definition->style_pallette);
        tag_block_delete_all_elements(&scenario_definition->squad_groups);
        tag_block_delete_all_elements(&scenario_definition->squads);
        tag_block_delete_all_elements(&scenario_definition->zones);
        tag_block_delete_all_elements(&scenario_definition->squad_patrols);
        tag_block_delete_all_elements(&scenario_definition->mission_scenes);
        tag_block_delete_all_elements(&scenario_definition->character_palette);

        if (!prune_flags.test(_scenario_prune_bit5))
        {
            tag_block_delete_all_elements(&scenario_definition->ai_pathfinding_data);
        }

        tag_block_delete_all_elements(&scenario_definition->ai_user_hint_data);
        tag_block_delete_all_elements(&scenario_definition->ai_recording_references);

        if (!prune_flags.test(_scenario_prune_bit6))
        {
            tag_data_resize(&scenario_definition->script_string_data, 0);
            tag_block_delete_all_elements(&scenario_definition->scripts);
            tag_block_delete_all_elements(&scenario_definition->globals);
            tag_block_delete_all_elements(&scenario_definition->references);
            tag_block_delete_all_elements(&scenario_definition->source_files);
            tag_block_delete_all_elements(&scenario_definition->scripting_data);
            tag_block_delete_all_elements(&scenario_definition->hs_syntax_datums);
            tag_block_delete_all_elements(&scenario_definition->hs_unit_seats);
            tag_block_delete_all_elements(&scenario_definition->editor_folders);
        }

        if (!prune_flags.test(_scenario_prune_bit2) && !prune_flags.test(_scenario_prune_bit4))
        {
            tag_block_delete_all_elements(&scenario_definition->scenery);
            tag_block_delete_all_elements(&scenario_definition->scenery_palette);
        }

        if (!prune_flags.test(_scenario_prune_bit2))
        {
            tag_block_delete_all_elements(&scenario_definition->decals);
            tag_block_delete_all_elements(&scenario_definition->decal_palette);
            tag_block_delete_all_elements(&scenario_definition->crates);
            tag_block_delete_all_elements(&scenario_definition->crate_palette);
            tag_block_delete_all_elements(&scenario_definition->decorators);
            tag_block_delete_all_elements(&scenario_definition->creatures);
            tag_block_delete_all_elements(&scenario_definition->creature_palette);
        }

        if (!prune_flags.test(_scenario_prune_bit3))
        {
            tag_block_delete_all_elements(&scenario_definition->cutscene_flags);
            tag_block_delete_all_elements(&scenario_definition->cutscene_camera_points);
            tag_block_delete_all_elements(&scenario_definition->cutscene_titles);
            tag_reference_clear(&scenario_definition->custom_object_names);
            tag_reference_clear(&scenario_definition->chapter_title_text);
        }

        if (scenario_definition->scenario_resources.count > 0)
        {
            s_scenario_resources_block * resources = static_cast<s_scenario_resources_block *>(tag_block_get_element_with_size(&scenario_definition->scenario_resources, 0, sizeof(s_scenario_resources_block)));
            resources->flags.set(_scenario_split_resource_dont_reset_split_resource_paths_bit, true);

            if (!prune_flags.test(_scenario_prune_bit6))
            {
                tag_block_delete_all_elements(&resources->script_source);
                tag_block_delete_all_elements(&resources->ai_resources);

                if (prune_flags.test(_scenario_prune_bit3))
                {
                    long global_scripts_index = tag_block_add_element(&resources->script_source);
                    if (global_scripts_index != NONE)
                    {
                        s_tag_reference * global_scripts = static_cast<s_tag_reference *>(tag_block_get_element_with_size(&resources->script_source, global_scripts_index, sizeof(s_scenario_hs_source_reference_block)));
                        tag_reference_set(global_scripts, HS_SOURCE_FILE_TAG, "globals\\global_scripts");
                    }
                    else
                    {
                        event_wrapped(_event_warning, "couldn't add global_scripts.scenario_hs_source_file, boo-urns!");
                    }

                    if (scenario_definition->type == _scenario_type_solo)
                    {
                        long global_extras_index = tag_block_add_element(&resources->script_source);
                        if (global_extras_index != NONE)
                        {
                            s_tag_reference * global_extras = static_cast<s_tag_reference *>(tag_block_get_element_with_size(&resources->script_source, global_extras_index, sizeof(s_scenario_hs_source_reference_block)));
                            tag_reference_set(global_extras, HS_SOURCE_FILE_TAG, "globals\\global_extras");
                        }
                        else
                        {
                            event_wrapped(_event_warning, "couldn't add global_scripts.scenario_hs_source_file, boo-urns!");
                        }
                    }
                }
            }

            if (resources->new_split_resources.count > 0)
            {
                s_scenario_split_resources_block * split_resources = static_cast<s_scenario_split_resources_block *>(tag_block_get_element_with_size(&resources->new_split_resources, 0, sizeof(s_scenario_split_resources_block)));

                if (!prune_flags.test(_scenario_prune_bit2))
                {
                    tag_reference_clear(&split_resources->scenery_resource);
                    tag_reference_clear(&split_resources->decorator_resource);
                    tag_reference_clear(&split_resources->decal_resource);
                }

                tag_reference_clear(&split_resources->biped_resource);
                tag_reference_clear(&split_resources->vehicle_resource);
                tag_reference_clear(&split_resources->equipment_resource);
                tag_reference_clear(&split_resources->weapon_resource);

                if (!prune_flags.test(_scenario_prune_bit3))
                {
                    tag_reference_clear(&split_resources->cutscene_data_resource);
                }

                tag_reference_clear(&split_resources->creature_resource);
            }
        }

        tag_block_delete_all_elements(&scenario_definition->scenario_kill_triggers);
        tag_block_delete_all_elements(&scenario_definition->orders);
        tag_block_delete_all_elements(&scenario_definition->triggers);
        tag_block_delete_all_elements(&scenario_definition->spawn_data);
        tag_reference_clear(&scenario_definition->game_engine_strings);
        tag_block_delete_all_elements(&scenario_definition->mission_dialogue);
        tag_reference_clear(&scenario_definition->objectives);
        tag_block_delete_all_elements(&scenario_definition->shared_references);
        tag_block_delete_all_elements(&scenario_definition->reference_frames);
        tag_block_delete_all_elements(&scenario_definition->ai_objectives);
        tag_block_delete_all_elements(&scenario_definition->designer_zones);

        if (!prune_flags.test(_scenario_prune_bit3))
        {
            tag_reference_clear(&scenario_definition->subtitles);
            tag_block_delete_all_elements(&scenario_definition->cinematics);
        }

        tag_block_delete_all_elements(&scenario_definition->override_player_representations);
    }

    if (prune_flags.test(_scenario_prune_bit7))
    {
        unsigned long single_bsp_zone_flags = 0;
        for (long zone_set_index = 0; zone_set_index < scenario_definition->zone_sets.count; zone_set_index++)
        {
            s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&scenario_definition->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
            if (count_bits(zone_set->runtime_bsp_zone_flags) == 1)
            {
                single_bsp_zone_flags |= zone_set->runtime_bsp_zone_flags;
            }
        }

        if (count_bits(single_bsp_zone_flags) < scenario_definition->structure_bsps.count / 2)
        {
            for (long structure_bsp_index = 0; structure_bsp_index < scenario_definition->structure_bsps.count; structure_bsp_index++)
            {
                long zone_set_index = tag_block_add_element(&scenario_definition->zone_sets);
                if (zone_set_index != NONE)
                {
                    s_tag_reference const * structure_bsp_reference = global_structure_bsp_tag_reference_get(scenario_definition, structure_bsp_index);
                    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&scenario_definition->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
                    zone_set->name = string_id_new(tag_name_strip_path(structure_bsp_reference->name));
                    zone_set->pvs_index = NONE;
                    zone_set->runtime_bsp_zone_flags = FLAG(structure_bsp_index);
                    zone_set->required_designer_zones = 0;
                    zone_set->forbidden_designer_zones = 0;
                }
                else
                {
                    event_wrapped(_event_warning, "couldn't add zone sets for bsp #%d and above -- the scenario has too many zone sets", structure_bsp_index);
                    break;
                }
            }
        }
    }

    return true;
};





