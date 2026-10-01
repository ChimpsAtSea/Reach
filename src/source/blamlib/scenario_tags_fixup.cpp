/* ---------- headers */

#include "blamlib\scenario_tags_fixup.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\physics\physics_model_definitions.h"
#include "omaha\physics\havok_collision_filter_definitions.h"
#include "omaha\units\biped_definitions.h"
#include "omaha\objects\scenery_group.h"
#include "omaha\creatures\creature_definitions.h"
#include "omaha\units\vehicle_definitions.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\structures\structure_bsp_definitions.h"
#include "omaha\structures\structure_design_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void scenario_tags_fixup(void);
// void scenario_tags_teardown(void);
// void scenario_tags_actually_fixup(void);
// void scenario_tags_actually_teardown(void);
// void scenario_tag_single_fixup(long);
// void scenario_tag_single_teardown(long);

void scenario_tags_fixup()
{
    mangled_ppc("?scenario_tags_fixup@@YAXXZ");
};

void scenario_tags_teardown()
{
    mangled_ppc("?scenario_tags_teardown@@YAXXZ");
};

void scenario_tags_actually_fixup()
{
    mangled_ppc("?scenario_tags_actually_fixup@@YAXXZ");

    tag_iterator iterator;
    tag_iterator_new(&iterator, NONE);

    long tag_index;
    while ((tag_index = tag_iterator_next(&iterator)) != NONE)
    {
        scenario_tag_single_fixup(tag_index);
    }
};

void scenario_tags_actually_teardown()
{
    mangled_ppc("?scenario_tags_actually_teardown@@YAXXZ");

    tag_iterator iterator;
    tag_iterator_new(&iterator, NONE);

    long tag_index;
    while ((tag_index = tag_iterator_next(&iterator)) != NONE)
    {
        scenario_tag_single_teardown(tag_index);
    }
};

void scenario_tag_single_fixup(long tag_index)
{
    mangled_ppc("?scenario_tag_single_fixup@@YAXJ@Z");

    switch (tag_get_group_tag(tag_index))
    {
    case k_physics_model_definition_tag:
        physics_model_fixup(tag_index, false);
        break;
    case k_havok_collision_filter_definition_tag:
        havok_collision_filter_fixup(tag_index);
        break;
    case BIPED_DEFINITION_TAG:
        biped_definition_fixup(tag_index);
        break;
    case SCENERY_DEFINITION_TAG:
        scenery_definition_fixup(tag_index);
        break;
    case CREATURE_DEFINITION_TAG:
        creature_definition_fixup(tag_index);
        break;
    case VEHICLE_DEFINITION_TAG:
        vehicle_definition_fixup(tag_index);
        break;
    case SCENARIO_GROUP_TAG:
        scenario_definition_fixup(tag_index);
        break;
    case STRUCTURE_BSP_TAG:
        structure_bsp_fixup(tag_index);
        break;
    case k_structure_design_definition_tag:
        structure_design_fixup(tag_index);
        break;
    }
};

void scenario_tag_single_teardown(long tag_index)
{
    mangled_ppc("?scenario_tag_single_teardown@@YAXJ@Z");

    switch (tag_get_group_tag(tag_index))
    {
    case k_physics_model_definition_tag:
        physics_model_teardown(tag_index);
        break;
    case BIPED_DEFINITION_TAG:
        biped_definition_teardown(tag_index);
        break;
    case CREATURE_DEFINITION_TAG:
        creature_definition_teardown(tag_index);
        break;
    case VEHICLE_DEFINITION_TAG:
        vehicle_definition_teardown(tag_index);
        break;
    }
};

