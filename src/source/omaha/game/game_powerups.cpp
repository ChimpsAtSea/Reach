#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_powerups.cpp"
/* ---------- headers */

#include "omaha\game\game_powerups.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_internal.h"
#include "omaha\game\game_engine_player_traits_structures.h"
#include "omaha\game\game_engine_traits_structures.h"
#include "omaha\game\game_variant.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float game_get_powerup_duration_seconds(enum e_multiplayer_powerup_flavor);
// void game_get_powerup_traits(enum e_multiplayer_powerup_flavor, class c_player_traits *);

float game_get_powerup_duration_seconds(e_multiplayer_powerup_flavor powerup_flavor)
{
    mangled_ppc("?game_get_powerup_duration_seconds@@YAMW4e_multiplayer_powerup_flavor@@@Z");

    float duration = 0.0f;
    if (game_is_multiplayer() && game_engine_running())
    {
        c_game_variant const * variant = current_game_variant();
        c_game_engine_base_variant const * base_variant = variant->get_active_variant();
        switch (powerup_flavor)
        {
        case _powerup_flavor_red:
            {
                duration = static_cast<float>(base_variant->get_map_override_options()->get_red_powerup_duration_seconds());
            }
            break;
        case _powerup_flavor_blue:
            {
                duration = static_cast<float>(base_variant->get_map_override_options()->get_blue_powerup_duration_seconds());
            }
            break;
        case _powerup_flavor_yellow:
            {
                duration = static_cast<float>(base_variant->get_map_override_options()->get_yellow_powerup_duration_seconds());
            }
            break;
        }
    }

    return duration;
};

void game_get_powerup_traits(e_multiplayer_powerup_flavor powerup_flavor, c_player_traits * powerup_traits)
{
    mangled_ppc("?game_get_powerup_traits@@YAXW4e_multiplayer_powerup_flavor@@PAVc_player_traits@@@Z");

    assert_tag_debug_untracked_jul_11_2011(47, powerup_traits!=NULL);

    powerup_traits->clear();
    if (game_is_multiplayer() && game_engine_running())
    {
        c_game_variant const * variant = current_game_variant();
        c_game_engine_base_variant const * base_variant = variant->get_active_variant();
        bool const force = false;
        switch (powerup_flavor)
        {
        case _powerup_flavor_red:
            {
                powerup_traits->set(base_variant->get_map_override_options()->get_red_powerup_traits(), force);
            }
            break;
        case _powerup_flavor_blue:
            {
                powerup_traits->set(base_variant->get_map_override_options()->get_blue_powerup_traits(), force);
            }
            break;
        case _powerup_flavor_yellow:
            {
                powerup_traits->set(base_variant->get_map_override_options()->get_yellow_powerup_traits(), force);
            }
            break;
        }
    }
};

