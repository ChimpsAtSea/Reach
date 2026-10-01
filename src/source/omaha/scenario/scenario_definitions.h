#pragma once
#ifndef __SCENARIO_DEFINITIONS_H__
#define __SCENARIO_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\scenario\scenario.h"

/* ---------- constants */

enum
{
    SCENARIO_GROUP_TAG = 'scnr',
};

/* ---------- definitions */

struct s_scenario_zone_debugger_block_definition_struct
{
    unsigned long active_designer_zones; // 0x0
};
static_assert(sizeof(s_scenario_zone_debugger_block_definition_struct) == 0x4, "s_scenario_zone_debugger_block_definition_struct");

struct scenario_object_name
{
    long name; // 0x0
    short object_type; // 0x4
    short scenario_datum_index; // 0x6
};
static_assert(sizeof(scenario_object_name) == 0x8, "scenario_object_name");

struct s_scenario_zone_set
{
    long name; // 0x0
    char name_string[256]; // 0x4
    long pvs_index; // 0x104
    unsigned long flags; // 0x108
    unsigned long bsp_zone_flags; // 0x10C
    unsigned long structure_design_zone_flags; // 0x110
    unsigned long runtime_bsp_zone_flags; // 0x114
    unsigned long runtime_structure_design_zone_flags; // 0x118
    unsigned long required_designer_zones; // 0x11C
    unsigned long forbidden_designer_zones; // 0x120
    unsigned long cinematic_zones; // 0x124
    long hint_previous_zone_set; // 0x128
    long audibility_index; // 0x12C
    s_tag_block planar_fog_visibility; // 0x130
};
static_assert(sizeof(s_scenario_zone_set) == 0x13C, "s_scenario_zone_set");

// structure_portal_device_mapping_block (Reach tag layout)
struct s_structure_portal_device_mapping
{
    s_tag_block device_portal_associations; // 0x0
    s_tag_block game_portal_to_portal_map; // 0xC short
    s_tag_block occluding_portal_to_portal_map; // 0x18 short
};
static_assert(sizeof(s_structure_portal_device_mapping) == 0x24, "s_structure_portal_device_mapping");

// scenario_zone_set_pvs_block (Reach tag layout)
struct s_scenario_zone_set_pvs
{
    long structure_bsp_mask; // 0x0
    short version; // 0x4
    unsigned short flags; // 0x6
    s_tag_block bsp_checksums; // 0x8
    s_tag_block structure_bsp_pvs; // 0x14
    s_tag_block portal_device_mapping; // 0x20 s_structure_portal_device_mapping (one per structure bsp)
};
static_assert(sizeof(s_scenario_zone_set_pvs) == 0x2C, "s_scenario_zone_set_pvs");

// layout from scenario_lightmap_setting_struct (Reach tag definitions)
struct scenario_lightmap_setting
{
    static long const k_number_of_lightmap_resolution_buckets = 7;

    real lightmap_resolution_scales[k_number_of_lightmap_resolution_buckets]; // 0x0
    unsigned char lightmap_flags; // 0x1C
    unsigned char pad[3]; // 0x1D
    real analytical_light_bounce_modifier; // 0x20
    real non_analytical_light_bounce_modifier; // 0x24
    unsigned long extra_lighting_bsp_flags; // 0x28
};
static_assert(sizeof(scenario_lightmap_setting) == 0x2C, "scenario_lightmap_setting");

// scenario_structure_bsp_reference_block (Reach tag layout)
struct scenario_structure_bsp_reference
{
    s_tag_reference structure_bsp; // 0x0
    s_tag_reference local_structure_bsp; // 0x10
    s_tag_reference structure_lighting_info; // 0x20
    s_tag_reference local_structure_lighting_info; // 0x30
    long size_classification; // 0x40
    real hacky_ambient_minimum_luminance; // 0x44
    real hacky_ambient_minimum_luminance_direct; // 0x48
    real maximum_structure_vertex_sink; // 0x4C
    unsigned short flags; // 0x50
    short default_sky_reference_index; // 0x52
    short default_instance_fade_start_pixels; // 0x54
    short default_instance_fade_end_pixels; // 0x56
    s_tag_reference cubemap_bitmap_group_reference; // 0x58
    s_tag_reference wind_reference; // 0x68
    unsigned long cloned_bsp_flags; // 0x78
    scenario_lightmap_setting lightmap_setting; // 0x7C
    real custom_gravity_scale; // 0xA8
};
static_assert(sizeof(scenario_structure_bsp_reference) == 0xAC, "scenario_structure_bsp_reference");

struct s_scenario_sky_reference
{
    s_tag_reference sky; // 0x0
    real cloud_scale; // 0x10
    real cloud_speed; // 0x14
    real cloud_direction; // 0x18
    s_tag_reference cloud_texture; // 0x1C
    short name; // 0x2C
    unsigned short active_on_bsps; // 0x2E
};
static_assert(sizeof(s_scenario_sky_reference) == 0x30, "s_scenario_sky_reference");

struct scenario_detail_object_collection_palette_entry
{
    s_tag_reference reference; // 0x0
    long unused[8]; // 0x10
};
static_assert(sizeof(scenario_detail_object_collection_palette_entry) == 0x30, "scenario_detail_object_collection_palette_entry");

// layout from the scenario_players_block tag definition
struct scenario_player_starting_location
{
    real_point3d position; // 0x0
    real facing; // 0xC
    real pitch; // 0x10
    short insertion_point_index; // 0x14
    unsigned short flags; // 0x16
    short editor_folder; // 0x18
    unsigned char pad[2]; // 0x1A
};
static_assert(sizeof(scenario_player_starting_location) == 0x1C, "scenario_player_starting_location");

struct scenario
{
    c_enum_no_init<e_scenario_type, short, _scenario_type_solo, k_scenario_type_count> type; // 0x0 (scenario_prune calls its operator==)
    unsigned short flags; // 0x2
    unsigned long runtime_trigger_volume_flags; // 0x4
    long campaign_id; // 0x8
    long map_id; // 0xC
    long map_name; // 0x10
    short sound_permutation_mission_id; // 0x14
    unsigned char pad[2]; // 0x16
    long minimum_structure_bsp_importer_version; // 0x18
    real local_north; // 0x1C
    real local_sea_level; // 0x20
    real altitude_cap; // 0x24
    real_point3d sandbox_origin_point; // 0x28
    real sandbox_budget; // 0x34
    long default_vehicle_set; // 0x38
    s_tag_reference game_performance_throttles; // 0x3C
    s_tag_block structure_bsps; // 0x4C
    s_tag_block structure_designs; // 0x58
    s_tag_reference structure_seams; // 0x64
    s_tag_reference local_structure_seams; // 0x74
    s_tag_block skies; // 0x84
    s_tag_block zone_set_pvs; // 0x90
    s_tag_block zone_set_audibility; // 0x9C
    s_tag_block zone_sets; // 0xA8
    s_tag_block lighting_zone_sets; // 0xB4
    s_tag_block predicted_resources; // 0xC0
    s_tag_block functions; // 0xCC
    s_tag_data editor_scenario_data; // 0xD8
    s_tag_block comments; // 0xEC
    s_tag_block unused_scenario_environment_objects; // 0xF8
    s_tag_block object_names; // 0x104
    s_tag_block scenery; // 0x110
    s_tag_block scenery_palette; // 0x11C
    s_tag_block bipeds; // 0x128
    s_tag_block biped_palette; // 0x134
    s_tag_block vehicles; // 0x140
    s_tag_block vehicle_palette; // 0x14C
    s_tag_block equipment; // 0x158
    s_tag_block equipment_palette; // 0x164
    s_tag_block weapons; // 0x170
    s_tag_block weapon_palette; // 0x17C
    s_tag_block device_groups; // 0x188
    s_tag_block machines; // 0x194
    s_tag_block machine_palette; // 0x1A0
    s_tag_block terminals; // 0x1AC
    s_tag_block terminal_palette; // 0x1B8
    s_tag_block controls; // 0x1C4
    s_tag_block control_palette; // 0x1D0
    s_tag_block sound_scenery; // 0x1DC
    s_tag_block sound_scenery_palette; // 0x1E8
    s_tag_block giants; // 0x1F4
    s_tag_block giant_palette; // 0x200
    s_tag_block effect_scenery; // 0x20C
    s_tag_block effect_scenery_palette; // 0x218
    s_tag_block light_volumes; // 0x224
    s_tag_block light_volumes_palette; // 0x230
    s_tag_block map_variant_palettes; // 0x23C
    s_tag_reference multiplayer_object_types; // 0x248
    s_tag_block playtest_req_palette; // 0x258
    s_tag_block soft_ceilings; // 0x264
    s_tag_block player_starting_profile; // 0x270
    s_tag_block player_starting_locations; // 0x27C
    s_tag_block trigger_volumes; // 0x288
    s_tag_block acoustic_sectors; // 0x294
    s_tag_block acoustic_transitions; // 0x2A0
    s_tag_block atmosphere_dumplings; // 0x2AC
    s_tag_block weather_dumplings; // 0x2B8
    s_tag_block recorded_animations; // 0x2C4
    s_tag_block zone_set_switch_trigger_volumes; // 0x2D0
    s_tag_block named_location_volumes; // 0x2DC
    s_tag_reference air_strike; // 0x2E8
    s_tag_block enemy_forbid_influence; // 0x2F8
    s_tag_block enemy_bias_influence; // 0x304
    s_tag_block ally_bias_influence; // 0x310
    s_tag_block selected_ally_bias_influence; // 0x31C
    s_tag_block dead_teammate_influence; // 0x328
    s_tag_block weapon_spawn_influencers; // 0x334
    s_tag_block vehicle_spawn_influencers; // 0x340
    s_tag_block projectile_spawn_influencers; // 0x34C
    s_tag_block equipment_spawn_influencers; // 0x358
    s_tag_block fire_team_leader_bias_influence; // 0x364
    s_tag_block decals; // 0x370
    s_tag_block decal_palette; // 0x37C
    s_tag_block detail_object_collection_palette; // 0x388
    s_tag_block style_pallette; // 0x394
    s_tag_block squad_groups; // 0x3A0
    s_tag_block squads; // 0x3AC
    s_tag_block zones; // 0x3B8
    s_tag_block squad_patrols; // 0x3C4
    s_tag_block actual_cues; // 0x3D0
    s_tag_block full_cues; // 0x3DC
    s_tag_block quick_cues; // 0x3E8
    s_tag_block mission_scenes; // 0x3F4
    s_tag_block character_palette; // 0x400
    s_tag_block ai_pathfinding_data; // 0x40C
    s_tag_block ai_user_hint_data; // 0x418
    s_tag_block ai_recording_references; // 0x424
    s_tag_data script_string_data; // 0x430
    s_tag_block scripts; // 0x444
    s_tag_block globals; // 0x450
    s_tag_block references; // 0x45C
    s_tag_block source_files; // 0x468
    s_tag_block scripting_data; // 0x474
    s_tag_block cutscene_flags; // 0x480
    s_tag_block cutscene_camera_points; // 0x48C
    s_tag_block cutscene_titles; // 0x498
    s_tag_reference custom_object_names; // 0x4A4
    s_tag_reference chapter_title_text; // 0x4B4
    s_tag_block scenario_resources; // 0x4C4
    s_tag_block hs_unit_seats; // 0x4D0
    s_tag_block scenario_kill_triggers; // 0x4DC
    s_tag_block scenario_safe_zone_triggers; // 0x4E8
    s_tag_block scenario_trigger_volumes_mopp_code; // 0x4F4
    s_tag_block scenario_requisition_triggers; // 0x500
    s_tag_block scenario_location_name_triggers; // 0x50C
    s_tag_block hs_syntax_datums; // 0x518
    s_tag_block orders; // 0x524
    s_tag_block triggers; // 0x530
    s_tag_block acoustics_palette; // 0x53C
    s_tag_block atmosphere; // 0x548
    s_tag_block camera_fx_palette; // 0x554
    s_tag_block weather_palette; // 0x560
    s_tag_block scenario_cluster_data; // 0x56C
    long object_salts[32]; // 0x578
    s_tag_block spawn_data; // 0x5F8
    s_tag_reference sound_effect_collection; // 0x604
    s_tag_block crates; // 0x614
    s_tag_block crate_palette; // 0x620
    s_tag_block flock_palette; // 0x62C
    s_tag_block flocks; // 0x638
    s_tag_reference subtitles; // 0x644
    s_tag_block creatures; // 0x654
    s_tag_block creature_palette; // 0x660
    s_tag_block big_battle_creature_palette; // 0x66C
    s_tag_block editor_folders; // 0x678
    s_tag_reference game_engine_strings; // 0x684
    unsigned char pad_qvuc[8]; // 0x694
    s_tag_block mission_dialogue; // 0x69C
    s_tag_reference objectives; // 0x6A8
    s_tag_reference interpolators; // 0x6B8
    s_tag_block shared_references; // 0x6C8
    s_tag_reference camera_effects; // 0x6D4
    s_tag_reference global_screen_effect; // 0x6E4
    s_tag_reference global_ssao; // 0x6F4
    s_tag_reference old_atmosphere; // 0x704
    s_tag_reference atmosphere_globals; // 0x714
    s_tag_reference chocalate_mountain; // 0x724
    s_tag_reference new_lightmaps; // 0x734
    s_tag_reference performance_throttles; // 0x744
    s_tag_block reference_frames; // 0x754
    s_tag_block ai_objectives; // 0x760
    s_tag_block designer_zones; // 0x76C
    s_tag_block zone_debugger; // 0x778
    s_tag_block decorators; // 0x784
    s_tag_block neuticle_palette; // 0x790
    s_tag_block neuticles; // 0x79C
    s_tag_block cinematics; // 0x7A8
    s_tag_block cinematic_lighting_palette; // 0x7B4
    s_tag_block override_player_representations; // 0x7C0
    s_tag_block campaign_metagame; // 0x7CC
    s_tag_block soft_surfaces; // 0x7D8
    s_tag_block cubemaps; // 0x7E4
    s_tag_block airprobes; // 0x7F0
    s_tag_block budget_references; // 0x7FC
    s_tag_block model_references; // 0x808
    s_tag_block thespian; // 0x814
    s_tag_reference location_name_globals; // 0x820
    s_tag_block garbage_collection; // 0x830
    s_tag_reference chud_reference; // 0x83C
    s_tag_reference required_resources; // 0x84C
    s_tag_reference variant_globals; // 0x85C
};
static_assert(sizeof(scenario) == 0x86C, "scenario");

/* ---------- prototypes */

void scenario_definition_fixup(long scenario_index);
structure_bsp const * scenario_structure_bsp_get(scenario const * scenario, long structure_bsp_index);
long scenario_zone_set_structure_bsp_cluster_attached_sky_index_get(scenario const * scenario, long zone_set_index, long structure_bsp_index, long cluster_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_DEFINITIONS_H__

