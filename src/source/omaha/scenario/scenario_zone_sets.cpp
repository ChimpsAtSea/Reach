/* ---------- headers */

#include "omaha\scenario\scenario_zone_sets.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cutscene\cinematics_definitions.h"
#include "omaha\editor\editor_stubs.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\scenario\scenario_designer_zones_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

inline bool flags_are_subset_of(unsigned long subset_flags, unsigned long flags);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned long scenario_zone_set_bsp_active_mask_get(long);
// unsigned long scenario_zone_set_designer_zone_required_mask_get(long);
// unsigned long scenario_zone_set_designer_zone_forbidden_mask_get(long);
// unsigned long scenario_zone_set_cinematic_zone_required_mask_get(long);
// unsigned long scenario_zone_set_get_valid_designer_zones(long, unsigned long);
// unsigned long scenario_zone_set_compute_new_designer_zone_mask(unsigned long, unsigned long, unsigned long);
// bool scenario_zone_set_switch_loads_anything(struct s_scenario_game_state const *, long);
// bool flags_are_subset_of(unsigned long, unsigned long);
// long scenario_get_designer_zone_index_by_name(struct scenario const *, char const *);
// char const * scenario_get_designer_zone_name(struct scenario const *, long);
// char const * scenario_get_cinematic_zone_name(struct scenario const *, long);

unsigned long scenario_zone_set_bsp_active_mask_get(long zone_set_index)
{
    mangled_ppc("?scenario_zone_set_bsp_active_mask_get@@YAKJ@Z");

    return zone_set_index != NONE
        ? static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)))->runtime_bsp_zone_flags
        : 0;
};

unsigned long scenario_zone_set_designer_zone_required_mask_get(long zone_set_index)
{
    mangled_ppc("?scenario_zone_set_designer_zone_required_mask_get@@YAKJ@Z");

    return scenario_use_designer_zones()
        ? (zone_set_index != NONE
            ? static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)))->required_designer_zones
            : 0)
        : static_cast<unsigned long>((1i64 << global_scenario_get()->designer_zones.count) - 1);
};

unsigned long scenario_zone_set_designer_zone_forbidden_mask_get(long zone_set_index)
{
    mangled_ppc("?scenario_zone_set_designer_zone_forbidden_mask_get@@YAKJ@Z");

    return scenario_use_designer_zones()
        ? (zone_set_index != NONE
            ? static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)))->forbidden_designer_zones
            : 0)
        : 0;
};

unsigned long scenario_zone_set_cinematic_zone_required_mask_get(long zone_set_index)
{
    mangled_ppc("?scenario_zone_set_cinematic_zone_required_mask_get@@YAKJ@Z");

    return zone_set_index != NONE
        ? static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, zone_set_index, sizeof(s_scenario_zone_set)))->cinematic_zones
        : 0;
};

unsigned long scenario_zone_set_get_valid_designer_zones(long zone_set_index, unsigned long designer_zone_mask)
{
    mangled_ppc("?scenario_zone_set_get_valid_designer_zones@@YAKJK@Z");

    unsigned long allowed_designer_zone_flags = ~scenario_zone_set_designer_zone_forbidden_mask_get(zone_set_index);
    return allowed_designer_zone_flags & designer_zone_mask;
};

unsigned long scenario_zone_set_compute_new_designer_zone_mask(unsigned long current_designer_zone_mask, unsigned long required_designer_zone_mask, unsigned long forbidden_designer_zone_mask)
{
    mangled_ppc("?scenario_zone_set_compute_new_designer_zone_mask@@YAKKKK@Z");

    unsigned long new_designer_zone_mask = game_in_editor()
        ? static_cast<unsigned long>((1i64 << global_scenario_get()->designer_zones.count) - 1) & ~forbidden_designer_zone_mask
        : (current_designer_zone_mask | required_designer_zone_mask) & ~forbidden_designer_zone_mask;
    return new_designer_zone_mask;
};

bool scenario_zone_set_switch_loads_anything(s_scenario_game_state const * scenario_game_state, long pending_zone_set_index)
{
    mangled_ppc("?scenario_zone_set_switch_loads_anything@@YA_NPBUs_scenario_game_state@@J@Z");

    bool loading_anything = true;
    s_scenario_zone_set const * pending_zone_set = static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&global_scenario_get()->zone_sets, pending_zone_set_index, sizeof(s_scenario_zone_set)));
    if (scenario_game_state->zone_set_index == pending_zone_set_index)
    {
        loading_anything = false;
    }
    else if (flags_are_subset_of(pending_zone_set->runtime_bsp_zone_flags, scenario_game_state->active_bsp_mask)
        && flags_are_subset_of(scenario_zone_set_get_valid_designer_zones(pending_zone_set_index, scenario_game_state->designer_zone_mask), scenario_game_state->designer_zone_mask)
        && flags_are_subset_of(pending_zone_set->cinematic_zones, scenario_game_state->touched_cinematic_zone_mask))
    {
        loading_anything = false;
    }

    return loading_anything;
};

inline bool flags_are_subset_of(unsigned long subset_flags, unsigned long flags)
{
    mangled_ppc("?flags_are_subset_of@@YA_NKK@Z");

    return (subset_flags & flags) == subset_flags;
};

long scenario_get_designer_zone_index_by_name(scenario const * scenario, char const * designer_zone_name)
{
    mangled_ppc("?scenario_get_designer_zone_index_by_name@@YAJPBUscenario@@PBD@Z");

    long result_designer_zone_index = NONE;
    long designer_zone_id = string_id_retrieve(designer_zone_name);
    if (designer_zone_id != _string_id_invalid)
    {
        for (long designer_zone_index = 0; designer_zone_index < scenario->designer_zones.count; designer_zone_index++)
        {
            s_scenario_designer_zone const * designer_zone = static_cast<s_scenario_designer_zone const *>(tag_block_get_element_with_size(&scenario->designer_zones, designer_zone_index, sizeof(s_scenario_designer_zone)));
            if (designer_zone->name == designer_zone_id)
            {
                result_designer_zone_index = designer_zone_index;
                break;
            }
        }
    }

    return result_designer_zone_index;
};

char const * scenario_get_designer_zone_name(scenario const * scenario, long designer_zone_index)
{
    mangled_ppc("?scenario_get_designer_zone_name@@YAPBDPBUscenario@@J@Z");

    s_scenario_designer_zone const * designer_zone = static_cast<s_scenario_designer_zone const *>(tag_block_get_element_with_size(&scenario->designer_zones, designer_zone_index, sizeof(s_scenario_designer_zone)));
    return string_id_get_string_const(designer_zone->name);
};

char const * scenario_get_cinematic_zone_name(scenario const * scenario, long cinematic_zone_index)
{
    mangled_ppc("?scenario_get_cinematic_zone_name@@YAPBDPBUscenario@@J@Z");

    s_cinematic_reference const * cinematic_reference = static_cast<s_cinematic_reference const *>(tag_block_get_element_with_size(&scenario->cinematics, cinematic_zone_index, sizeof(s_cinematic_reference)));
    return cinematic_reference->name.index != NONE
        ? tag_name_strip_path(tag_get_name(cinematic_reference->name.index))
        : "";
};

