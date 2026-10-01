/* ---------- headers */

#include "omaha\game\player_rewards\player_cookie_definitions.h"
#include "omaha\game\incidents\incident_definitions.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition cookie_globals_definition_block; // "?cookie_globals_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group cookie_globals_definition_group; // "?cookie_globals_definition_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_cookie_globals_definition_vtable; // "?legacy_cookie_globals_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_cookie_globals_definition_stream_definition; // "?legacy_cookie_globals_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_cookie_globals_definition_xsync_declaration; // "?legacy_cookie_globals_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_cookie_globals_definition_vtable_shim; // "?legacy_cookie_globals_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long cookie_globals_get_cookie_award_definition_index_by_name(struct s_cookie_globals_definition const *, long);
// struct s_cookie_award_definition const * cookie_globals_get_cookie_award_definition_by_name(struct s_cookie_globals_definition const *, long);
// struct s_cookie_globals_definition const * cookie_globals_try_and_get(void);

long cookie_globals_get_cookie_award_definition_index_by_name(s_cookie_globals_definition const * cookie_globals, long name)
{
    mangled_ppc("?cookie_globals_get_cookie_award_definition_index_by_name@@YAJPBUs_cookie_globals_definition@@J@Z");

    long cookie_award_index = NONE;
    s_cookie_globals_definition const * globals = cookie_globals_try_and_get();
    if (globals)
    {
        for (long award_index = 0; award_index < globals->cookie_awards.count; award_index++)
        {
            s_cookie_award_definition const * cookie_award = static_cast<s_cookie_award_definition const *>(tag_block_get_element_with_size(&globals->cookie_awards, award_index, sizeof(s_cookie_award_definition)));
            if (cookie_award->name == name)
            {
                cookie_award_index = award_index;
            }
        }
    }

    return cookie_award_index;
};

s_cookie_award_definition const * cookie_globals_get_cookie_award_definition_by_name(s_cookie_globals_definition const * cookie_globals, long name)
{
    mangled_ppc("?cookie_globals_get_cookie_award_definition_by_name@@YAPBUs_cookie_award_definition@@PBUs_cookie_globals_definition@@J@Z");

    return static_cast<s_cookie_award_definition const *>(tag_block_get_element_with_size(&cookie_globals->cookie_awards, cookie_globals_get_cookie_award_definition_index_by_name(cookie_globals, name), sizeof(s_cookie_award_definition)));
};

s_cookie_globals_definition const * cookie_globals_try_and_get()
{
    mangled_ppc("?cookie_globals_try_and_get@@YAPBUs_cookie_globals_definition@@XZ");

    s_cookie_globals_definition const * cookie_globals = NULL;
    if (global_scenario_game_globals_index_get() != NONE)
    {
        s_game_globals const * game_globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()));
        if (game_globals && game_globals->incident_global_properties.index != NONE)
        {
            s_incident_global_properties_definition const * incident_globals = static_cast<s_incident_global_properties_definition const *>(tag_get(game_globals->incident_global_properties.group_tag, game_globals->incident_global_properties.index));
            if (incident_globals && incident_globals->cookie_globals.index != NONE)
            {
                cookie_globals = static_cast<s_cookie_globals_definition const *>(tag_get(COOKIE_GLOBALS_DEFINITION_TAG, incident_globals->cookie_globals.index));
            }
        }
    }

    return cookie_globals;
};

