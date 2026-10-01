#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_campaign.cpp"
/* ---------- headers */

#include <new>
#include "omaha\game\game_engine_campaign.h"
#include "blamlib\game_engine_campaign_traits.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\editor\editor_stubs.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_internal.h"
#include "omaha\game\game_variant.h"
#include "omaha\networking\network_game_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_campaign_engine internal_campaign_engine;
c_game_engine * campaign_engine = &internal_campaign_engine;
static c_game_engine_campaign_variant const * campaign_variant;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_game_engine *campaign_engine; // "?campaign_engine@@3PAVc_game_engine@@A"

// public: virtual bool c_campaign_engine::initialize_for_new_map(void) const;
// public: s_campaign_globals::s_campaign_globals(void);
// public: virtual void c_campaign_engine::dispose_from_old_map(void) const;
// public: virtual enum e_game_engine_type c_campaign_engine::get_type(void) const;
// public: virtual enum e_network_game_simulation_protocol c_campaign_engine::get_simulation_protocol(void) const;
// public: virtual bool c_campaign_engine::requires_valid_multiplayer_globals_in_scenario(void) const;
// public: virtual bool c_campaign_engine::desires_round_based_fading(void) const;
// public: virtual bool c_campaign_engine::competitive_game_in_progress(void) const;
// public: virtual bool c_campaign_engine::requires_scenario_object(long, enum e_object_type, long, struct s_scenario_object const *, struct s_scenario_multiplayer_object_properties const *) const;
// public: virtual bool c_campaign_engine::requires_unplaced_object(struct s_object_placement_data const *) const;
// public: virtual void c_campaign_engine::player_update(long) const;
// public: virtual bool c_campaign_engine::desires_garbage_collection(void) const;
// public: virtual bool c_campaign_engine::desires_influence_based_spawning(void) const;
// public: c_campaign_engine::c_campaign_engine(void);
// public: virtual bool c_campaign_engine::desires_teleporters(void) const;

// $TODO nonmatching: only the TLS offset of game_engine_globals differs (target li 0x214 is link-resolved, ours is the unlinked 0)
bool c_campaign_engine::initialize_for_new_map(void) const
{
    mangled_ppc("?initialize_for_new_map@c_campaign_engine@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(79, campaign_variant==NULL);
    dassert_tag_debug_untracked_jul_11_2011(84, current_game_variant()->get_active_variant()->can_be_cast_to(_game_engine_type_campaign, reinterpret_cast<void const **>(&campaign_variant)), "campaign game engine being initialized under non campaign game variant");

    new (game_engine_globals->multiplayer_globals_storage) s_campaign_globals;

    return true;
};

void c_campaign_engine::dispose_from_old_map(void) const
{
    mangled_ppc("?dispose_from_old_map@c_campaign_engine@@UBAXXZ");

    campaign_variant = NULL;
};

e_game_engine_type c_campaign_engine::get_type(void) const
{
    mangled_ppc("?get_type@c_campaign_engine@@UBA?AW4e_game_engine_type@@XZ");

    return _game_engine_type_campaign;
};

e_network_game_simulation_protocol c_campaign_engine::get_simulation_protocol(void) const
{
    mangled_ppc("?get_simulation_protocol@c_campaign_engine@@UBA?AW4e_network_game_simulation_protocol@@XZ");

    return _network_game_simulation_protocol_synchronous;
};

bool c_campaign_engine::requires_valid_multiplayer_globals_in_scenario(void) const
{
    mangled_ppc("?requires_valid_multiplayer_globals_in_scenario@c_campaign_engine@@UBA_NXZ");

    return false;
};

bool c_campaign_engine::desires_round_based_fading(void) const
{
    mangled_ppc("?desires_round_based_fading@c_campaign_engine@@UBA_NXZ");

    return false;
};

bool c_campaign_engine::competitive_game_in_progress(void) const
{
    mangled_ppc("?competitive_game_in_progress@c_campaign_engine@@UBA_NXZ");

    return false;
};

bool c_campaign_engine::requires_scenario_object(long scenario_datum_index, e_object_type object_type, long object_definition_index, s_scenario_object const * scenario_object, s_scenario_multiplayer_object_properties const * multiplayer_properties) const
{
    mangled_ppc("?requires_scenario_object@c_campaign_engine@@UBA_NJW4e_object_type@@JPBUs_scenario_object@@PBUs_scenario_multiplayer_object_properties@@@Z");

    bool result = c_game_engine::requires_scenario_object(scenario_datum_index, object_type, object_definition_index, scenario_object, multiplayer_properties);
    if (game_in_editor())
    {
        result = true;
    }

    return result;
};

bool c_campaign_engine::requires_unplaced_object(s_object_placement_data const * placement_data) const
{
    mangled_ppc("?requires_unplaced_object@c_campaign_engine@@UBA_NPBUs_object_placement_data@@@Z");

    return game_in_editor();
};

void c_campaign_engine::player_update(long player_index) const
{
    mangled_ppc("?player_update@c_campaign_engine@@UBAXJ@Z");

};

bool c_campaign_engine::desires_garbage_collection(void) const
{
    mangled_ppc("?desires_garbage_collection@c_campaign_engine@@UBA_NXZ");

    return false;
};

bool c_campaign_engine::desires_influence_based_spawning(void) const
{
    mangled_ppc("?desires_influence_based_spawning@c_campaign_engine@@UBA_NXZ");

    return false;
};

