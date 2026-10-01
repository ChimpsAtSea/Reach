#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_portals.cpp"
/* ---------- headers */

#include "omaha\game\game_portals.h"
#include "omaha\cseries\cseries.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\structures\structure_bsp_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_portal_reference game_get_machine_door_portal_reference(long, long, long);
// long game_get_machine_door_portal_references_count(long, long);
// struct s_portal_reference game_get_occluding_portal_reference(long, long, long);
// long game_get_occluding_portal_references_count(long, long);
// void game_clear_machine_door_portal_indices_count(long);
// bool game_add_machine_door_portal_index(long, long, long, unsigned short *);
// void game_clear_occluding_portal_indices(long, long);
// bool game_add_occluding_portal_index(long, long, long);

s_portal_reference game_get_machine_door_portal_reference(long zone_set_index, long structure_bsp_index, long machine_door_portal_index)
{
    mangled_ppc("?game_get_machine_door_portal_reference@@YA?AUs_portal_reference@@JJJ@Z");

    s_portal_reference portal_reference;
    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));
    portal_reference_set(&portal_reference, structure_bsp_index, *static_cast<short *>(tag_block_get_element_with_size(&portal_device_mapping->game_portal_to_portal_map, machine_door_portal_index, sizeof(short))));

    return portal_reference;
};

long game_get_machine_door_portal_references_count(long zone_set_index, long structure_bsp_index)
{
    mangled_ppc("?game_get_machine_door_portal_references_count@@YAJJJ@Z");

    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));

    return portal_device_mapping->game_portal_to_portal_map.count;
};

s_portal_reference game_get_occluding_portal_reference(long zone_set_index, long structure_bsp_index, long occluding_portal_index)
{
    mangled_ppc("?game_get_occluding_portal_reference@@YA?AUs_portal_reference@@JJJ@Z");

    s_portal_reference portal_reference;
    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));
    portal_reference_set(&portal_reference, structure_bsp_index, *static_cast<short *>(tag_block_get_element_with_size(&portal_device_mapping->occluding_portal_to_portal_map, occluding_portal_index, sizeof(short))));

    return portal_reference;
};

long game_get_occluding_portal_references_count(long zone_set_index, long structure_bsp_index)
{
    mangled_ppc("?game_get_occluding_portal_references_count@@YAJJJ@Z");

    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));

    return portal_device_mapping->occluding_portal_to_portal_map.count;
};

void game_clear_machine_door_portal_indices_count(long zone_set_index)
{
    mangled_ppc("?game_clear_machine_door_portal_indices_count@@YAXJ@Z");

    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    tag_block_delete_all_elements(&zone_set_pvs->portal_device_mapping);
    tag_block_resize(&zone_set_pvs->portal_device_mapping, global_scenario_get()->structure_bsps.count);
};

bool game_add_machine_door_portal_index(long zone_set_index, long structure_bsp_index, long portal_index, unsigned short * out_game_portal_index)
{
    mangled_ppc("?game_add_machine_door_portal_index@@YA_NJJJPAG@Z");

    bool success = false;
    structure_bsp const * structure = global_structure_bsp_get(structure_bsp_index);
    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));

    assert_tag_debug_untracked_jul_11_2011(96, VALID_INDEX(portal_index, structure->cluster_portals.count));
    assert_tag_debug_untracked_jul_11_2011(97, out_game_portal_index);

    long game_portal_index = tag_block_add_element(&portal_device_mapping->game_portal_to_portal_map);
    if (game_portal_index != NONE)
    {
        *out_game_portal_index = static_cast<unsigned short>(game_portal_index);
        *static_cast<short *>(tag_block_get_element_with_size(&portal_device_mapping->game_portal_to_portal_map, game_portal_index, sizeof(short))) = static_cast<short>(portal_index);
        success = true;
    }
    else
    {
        event_wrapped(_event_warning, "machine doors referenced too many portals: %d", 128);
    }

    return success;
};

void game_clear_occluding_portal_indices(long zone_set_index, long structure_bsp_index)
{
    mangled_ppc("?game_clear_occluding_portal_indices@@YAXJJ@Z");

    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));
    tag_block_delete_all_elements(&portal_device_mapping->occluding_portal_to_portal_map);
};

bool game_add_occluding_portal_index(long zone_set_index, long structure_bsp_index, long portal_index)
{
    mangled_ppc("?game_add_occluding_portal_index@@YA_NJJJ@Z");

    bool success = false;
    s_scenario_zone_set * zone_set = static_cast<s_scenario_zone_set *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)));
    s_scenario_zone_set_pvs * zone_set_pvs = static_cast<s_scenario_zone_set_pvs *>(tag_block_get_element_with_size(&global_scenario_get()->zone_set_pvs, zone_set->pvs_index, sizeof(s_scenario_zone_set_pvs)));
    s_structure_portal_device_mapping * portal_device_mapping = static_cast<s_structure_portal_device_mapping *>(tag_block_get_element_with_size(&zone_set_pvs->portal_device_mapping, structure_bsp_index, sizeof(s_structure_portal_device_mapping)));
    structure_bsp const * structure = global_structure_bsp_get(structure_bsp_index);

    assert_tag_debug_untracked_jul_11_2011(136, VALID_INDEX(portal_index, structure->cluster_portals.count));

    long occluding_portal_index = tag_block_add_element(&portal_device_mapping->occluding_portal_to_portal_map);
    if (occluding_portal_index != NONE)
    {
        *static_cast<short *>(tag_block_get_element_with_size(&portal_device_mapping->occluding_portal_to_portal_map, occluding_portal_index, sizeof(short))) = static_cast<short>(portal_index);
        success = true;
    }
    else
    {
        event_wrapped(_event_warning, "we are generating too many occluding portals: %d", 128);
    }

    return success;
};

