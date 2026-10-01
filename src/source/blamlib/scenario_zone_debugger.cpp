/* ---------- headers */

#include "blamlib\scenario_zone_debugger.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\main\main.h"
#include "omaha\objects\object_placement.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void scenario_zone_debugger_initialize(void);
// void scenario_zone_debugger_update(void);
// void scenario_zone_debugger_synchronize(void);

void scenario_zone_debugger_initialize()
{
    mangled_ppc("?scenario_zone_debugger_initialize@@YAXXZ");

    long scenario_index = global_scenario_index_get();
    if (scenario_index != NONE)
    {
        scenario * scenario_definition = static_cast<scenario *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
        if (scenario_definition->zone_debugger.count > 0)
        {
            s_scenario_zone_debugger_block_definition_struct * zone_debugger = static_cast<s_scenario_zone_debugger_block_definition_struct *>(tag_block_get_element_with_size(&scenario_definition->zone_debugger, 0, sizeof(s_scenario_zone_debugger_block_definition_struct)));
            zone_debugger->active_designer_zones = global_designer_zone_active_mask_get();
        }
    }
};

void scenario_zone_debugger_update()
{
    mangled_ppc("?scenario_zone_debugger_update@@YAXXZ");

    long scenario_index = global_scenario_index_get();
    if (scenario_index != NONE)
    {
        scenario * scenario_definition = static_cast<scenario *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
        if (scenario_definition->zone_debugger.count > 0)
        {
            s_scenario_zone_debugger_block_definition_struct * zone_debugger = static_cast<s_scenario_zone_debugger_block_definition_struct *>(tag_block_get_element_with_size(&scenario_definition->zone_debugger, 0, sizeof(s_scenario_zone_debugger_block_definition_struct)));
            main_set_active_designer_zone_mask(zone_debugger->active_designer_zones);
        }
    }
};

void scenario_zone_debugger_synchronize()
{
    mangled_ppc("?scenario_zone_debugger_synchronize@@YAXXZ");

    object_placement_synchronize_for_designer_zone_debugger(false);
};

