#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_sky.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_sky.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\objects\object_placement.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\scenery_group.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\structures\structure_bsp_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void scenario_sky_objects_initialize(void);
// void scenario_sky_objects_dispose(void);
// void scenario_sky_objects_initialize_for_new_map(void);
// void scenario_sky_objects_dispose_from_old_map(void);
// public: static void c_scenerio_sky_objects_helper::create_sky_objects(struct scenario const *);
// public: static long c_scenerio_sky_objects_helper::create_sky_object(long);
// public: static struct s_game_cluster_bit_vectors const * c_scenerio_sky_objects_helper::calculate_sky_object_cluster_visibility(long, struct s_game_cluster_bit_vectors *);
// long scenario_cluster_get_attached_sky_reference_index(long, long, long);

void scenario_sky_objects_initialize(void)
{
    mangled_ppc("?scenario_sky_objects_initialize@@YAXXZ");
};

void scenario_sky_objects_dispose(void)
{
    mangled_ppc("?scenario_sky_objects_dispose@@YAXXZ");
};

void scenario_sky_objects_initialize_for_new_map(void)
{
    mangled_ppc("?scenario_sky_objects_initialize_for_new_map@@YAXXZ");
};

void scenario_sky_objects_dispose_from_old_map(void)
{
    mangled_ppc("?scenario_sky_objects_dispose_from_old_map@@YAXXZ");
};

void c_scenerio_sky_objects_helper::create_sky_objects(scenario const * scenario)
{
    mangled_ppc("?create_sky_objects@c_scenerio_sky_objects_helper@@SAXPBUscenario@@@Z");

    if (scenario)
    {
        for (long scenario_sky_index = 0; scenario_sky_index < scenario->skies.count; scenario_sky_index++)
        {
            create_sky_object(scenario_sky_index);
        }
    }
};

long c_scenerio_sky_objects_helper::create_sky_object(long scenario_sky_index)
{
    mangled_ppc("?create_sky_object@c_scenerio_sky_objects_helper@@SAJJ@Z");

    s_scenario_sky_reference const * sky_reference;
    long object_index = NONE;
    sky_reference = static_cast<s_scenario_sky_reference const *>(tag_block_get_element_with_size(&global_scenario_get()->skies, scenario_sky_index, sizeof(s_scenario_sky_reference)));
    if (sky_reference->sky.group_tag == SCENERY_DEFINITION_TAG)
    {
        long object_definition_index = sky_reference->sky.index;
        s_object_placement_data placement_data;
        object_placement_data_new(&placement_data, object_definition_index, NONE, NULL);
        placement_data.object_identifier.create_from_sky(_object_type_scenery, scenario_sky_index);
        if (placement_data.object_identifier.find_object_index() == NONE)
        {
            placement_data.flags.set(_object_placement_sky_visibility_bit, true);
            object_index = object_new(&placement_data);
            if (object_index != NONE)
            {
                if (sky_reference->name != NONE)
                {
                    object_set_object_index_for_name_index(sky_reference->name, object_index);
                    static_cast<object_datum *>(object_get_and_verify_type(object_index, NONE))->object.name_index = sky_reference->name;
                }
            }
            else
            {
                event_wrapped(_event_error, "### Sky object creation failed. sky index: '%d'", scenario_sky_index);
            }
        }
    }
    else
    {
        event_wrapped(_event_error, "### Sky objects need to be scenery objects. sky index: '%d'", scenario_sky_index);
    }

    return object_index;
};

// $TODO nonmatching: only the TLS offset of object_header_data differs (target li 0x7c is the linked .tls offset; ours is the unlinked 0)
s_game_cluster_bit_vectors const * c_scenerio_sky_objects_helper::calculate_sky_object_cluster_visibility(long object_index, s_game_cluster_bit_vectors * cluster_visibility)
{
    mangled_ppc("?calculate_sky_object_cluster_visibility@c_scenerio_sky_objects_helper@@SAPBUs_game_cluster_bit_vectors@@JPAU2@@Z");

    scenario const * scenario = global_scenario_get();
    object_header_datum const * object_header = static_cast<object_header_datum const *>(datum_get(object_header_data, object_index));
    object_datum const * object = object_header->datum;
    memset(cluster_visibility, 0, sizeof(s_game_cluster_bit_vectors));

    for (long structure_bsp_index = global_structure_bsp_first_active_index_get(); structure_bsp_index != NONE; structure_bsp_index = global_structure_bsp_next_active_index_get(structure_bsp_index))
    {
        structure_bsp const * structure_bsp = global_structure_bsp_get(structure_bsp_index);
        long scenario_sky_index = object->object.object_identifier.get_sky_identifier();
        assert_tag_debug_untracked_jul_11_2011(118, VALID_INDEX(scenario_sky_index, scenario->skies.count));

        for (long cluster_index = 0; cluster_index < structure_bsp->clusters.count; cluster_index++)
        {
            if (scenario_zone_set_structure_bsp_cluster_attached_sky_index_get(scenario, scenario_zone_set_index_get(), structure_bsp_index, cluster_index) == scenario_sky_index)
            {
                cluster_visibility->bit_vectors.element(structure_bsp_index).set(cluster_index, true);
            }
        }
    }

    return cluster_visibility;
};

long scenario_cluster_get_attached_sky_reference_index(long scenario_index, long structure_bsp_index, long cluster_index)
{
    mangled_ppc("?scenario_cluster_get_attached_sky_reference_index@@YAJJJJ@Z");

    scenario const * scenario = static_cast<struct scenario const *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
    scenario_structure_bsp_reference const * bsp_reference = static_cast<scenario_structure_bsp_reference const *>(tag_block_get_element_with_size(&scenario->structure_bsps, structure_bsp_index, sizeof(scenario_structure_bsp_reference)));
    structure_bsp const * structure_bsp = scenario_structure_bsp_get(scenario, structure_bsp_index);
    structure_cluster const * cluster = static_cast<structure_cluster const *>(tag_block_get_element_with_size(&structure_bsp->clusters, cluster_index, sizeof(structure_cluster)));
    long result = cluster->scenario_sky_index == NONE ? NONE : (VALID_INDEX(cluster->scenario_sky_index, scenario->skies.count) ? cluster->scenario_sky_index : bsp_reference->default_sky_reference_index);

    return result;
};

