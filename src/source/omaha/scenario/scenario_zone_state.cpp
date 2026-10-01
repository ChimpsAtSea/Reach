#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_zone_state.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_zone_state.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool scenario_zone_states_any_active_changes(struct s_scenario_zone_state const *, struct s_scenario_zone_state const *);
// bool scenario_zone_states_any_pending_changes(struct s_scenario_zone_state const *, struct s_scenario_zone_state const *);

bool scenario_zone_states_any_active_changes(s_scenario_zone_state const * lhs, s_scenario_zone_state const * rhs)
{
    mangled_ppc("?scenario_zone_states_any_active_changes@@YA_NPBUs_scenario_zone_state@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(13, lhs);
    assert_tag_debug_untracked_jul_11_2011(14, rhs);

    return lhs->using_designer_zones != rhs->using_designer_zones
        || lhs->active_bsp_mask != rhs->active_bsp_mask
        || lhs->touched_bsp_mask != rhs->touched_bsp_mask
        || lhs->active_designer_zone_mask != rhs->active_designer_zone_mask
        || lhs->active_cinematic_zone_mask != rhs->active_cinematic_zone_mask;
};

bool scenario_zone_states_any_pending_changes(s_scenario_zone_state const * lhs, s_scenario_zone_state const * rhs)
{
    mangled_ppc("?scenario_zone_states_any_pending_changes@@YA_NPBUs_scenario_zone_state@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(29, lhs);
    assert_tag_debug_untracked_jul_11_2011(30, rhs);

    return lhs->using_designer_zones != rhs->using_designer_zones
        || lhs->pending_bsp_zone_mask != rhs->pending_bsp_zone_mask
        || lhs->pending_designer_zone_mask != rhs->pending_designer_zone_mask
        || lhs->pending_cinematic_zone_mask != rhs->pending_cinematic_zone_mask;
};

