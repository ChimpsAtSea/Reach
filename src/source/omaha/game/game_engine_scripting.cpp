#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_scripting.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_scripting.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\game_allegiance.h"
#include "omaha\game\game_constants.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\players.h"
#include "omaha\hs\object_lists.h"
#include "omaha\simulation\simulation_queue_global_events.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void game_engine_scripting_initialize(void);
// void game_engine_scripting_dispose(void);
// void game_engine_scripting_initialize_for_new_map(void);
// void game_engine_scripting_dispose_from_old_map(void);
// long game_engine_player_count_by_team(enum e_multiplayer_team);
// long game_engine_players_by_team(enum e_multiplayer_team);
// long game_engine_active_player_count_by_team(enum e_multiplayer_team);
// void game_engine_finish_game(void);
// void game_engine_game_won(enum e_multiplayer_team);
// void game_engine_respawn_override_timers(enum e_multiplayer_team);
// void game_engine_form_team_allegiance(enum e_campaign_team, enum e_multiplayer_team);
// void game_engine_ai_scripting_allegiance(enum e_campaign_team, enum e_multiplayer_team);
// void game_engine_mp_team_allegiance(enum e_multiplayer_team, enum e_multiplayer_team);

void game_engine_scripting_initialize(void)
{
    mangled_ppc("?game_engine_scripting_initialize@@YAXXZ");
};

void game_engine_scripting_dispose(void)
{
    mangled_ppc("?game_engine_scripting_dispose@@YAXXZ");
};

void game_engine_scripting_initialize_for_new_map(void)
{
    mangled_ppc("?game_engine_scripting_initialize_for_new_map@@YAXXZ");
};

void game_engine_scripting_dispose_from_old_map(void)
{
    mangled_ppc("?game_engine_scripting_dispose_from_old_map@@YAXXZ");
};

long game_engine_player_count_by_team(e_multiplayer_team team_index)
{
    mangled_ppc("?game_engine_player_count_by_team@@YAJW4e_multiplayer_team@@@Z");

    long count = 0;
    if (VALID_INDEX(team_index, k_multiplayer_team_count))
    {
        c_player_in_game_iterator player_iterator;
        player_iterator.begin();
        while (player_iterator.next())
        {
            if (game_get_player_team(player_iterator.get_index()).get_multiplayer_team() == team_index)
            {
                count++;
            }
        }
    }
    else
    {
        event_wrapped(_event_warning, "invalid team index #%ld", team_index);
    }

    return count;
};

// $TODO nonmatching: only the TLS offset of player_data (target li 0x204 is link-resolved, ours is the unlinked 0)
long game_engine_players_by_team(e_multiplayer_team team_index)
{
    mangled_ppc("?game_engine_players_by_team@@YAJW4e_multiplayer_team@@@Z");

    long player_list_index = NONE;
    if (VALID_INDEX(team_index, k_multiplayer_team_count))
    {
        player_list_index = object_list_new();
        if (player_list_index != NONE)
        {
            for (long player_index = data_next_index(player_data, NONE);
                player_index != NONE;
                player_index = data_next_index(player_data, player_index))
            {
                player_datum * player = static_cast<player_datum *>(datum_get(player_data, player_index));
                if (player->unit_index != NONE && player->team.get_multiplayer_team() == team_index)
                {
                    object_list_add(player_list_index, player->unit_index);
                }
            }
        }
    }
    else
    {
        event_wrapped(_event_warning, "invalid team index #%ld passed to game_engine_players_by_team", team_index);
    }

    return player_list_index;
};

// $TODO nonmatching: only the TLS offset of player_data (target li 0x204 is link-resolved, ours is the unlinked 0)
long game_engine_active_player_count_by_team(e_multiplayer_team team_index)
{
    mangled_ppc("?game_engine_active_player_count_by_team@@YAJW4e_multiplayer_team@@@Z");

    long count = 0;
    if (VALID_INDEX(team_index, k_multiplayer_team_count))
    {
        for (long player_index = data_next_index(player_data, NONE);
            player_index != NONE;
            player_index = data_next_index(player_data, player_index))
        {
            player_datum * player = static_cast<player_datum *>(datum_get(player_data, player_index));
            if (player->team.get_multiplayer_team() == team_index && (player->unit_index != NONE || player->remaining_lives > 0))
            {
                count++;
            }
        }
    }
    else
    {
        event_wrapped(_event_warning, "invalid team index #%ld passed to game_engine_active_player_count_by_team", team_index);
    }

    return count;
};

void game_engine_finish_game(void)
{
    mangled_ppc("?game_engine_finish_game@@YAXXZ");

    if (game_in_progress() && game_is_multiplayer() && game_is_authoritative())
    {
        simulation_queue_game_global_event_insert(_simulation_queue_game_global_event_type_game_finish);
    }
};

void game_engine_game_won(e_multiplayer_team team_index)
{
    mangled_ppc("?game_engine_game_won@@YAXW4e_multiplayer_team@@@Z");

    if (game_is_authoritative())
    {
        if (game_engine_has_teams())
        {
            if (VALID_INDEX(team_index, k_multiplayer_team_count))
            {
                bool end_game_instead_of_round = true;
                game_engine_end_round_with_winner(team_index, end_game_instead_of_round, _game_engine_game_end_scripting);
            }
            else
            {
                event_wrapped(_event_warning, "invalid team index #%ld passed to game_engine_game_won", team_index);
            }
        }
        else
        {
            event_wrapped(_event_warning, "game_engine_game_won: not a team game!");
        }
    }
};

// $TODO nonmatching: only the TLS offset of game_engine_globals (target li 0x214 is link-resolved, ours is the unlinked 0)
void game_engine_respawn_override_timers(e_multiplayer_team team_index)
{
    mangled_ppc("?game_engine_respawn_override_timers@@YAXW4e_multiplayer_team@@@Z");

    if (game_is_authoritative() && VALID_INDEX(team_index, k_multiplayer_team_count))
    {
        c_player_in_game_iterator player_iterator;
        player_iterator.begin();
        while (player_iterator.next())
        {
            player_datum * player = player_iterator.get_datum();
            if (player->team.get_multiplayer_team() == team_index && player->respawn_timer > 0)
            {
                long absolute_player_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(player_iterator.get_index());
                s_player_navpoint_data * player_navpoint_data = &game_engine_globals->player_navpoint_data[absolute_player_index];
                player->respawn_timer = 0;
                player_navpoint_data->last_living_location_valid = false;
            }
        }
    }
};

void game_engine_form_team_allegiance(e_campaign_team campaign_team, e_multiplayer_team multiplayer_team)
{
    mangled_ppc("?game_engine_form_team_allegiance@@YAXW4e_campaign_team@@W4e_multiplayer_team@@@Z");

    event_wrapped(_event_error, "networking: game engine attempting to set allegiances?");
};

void game_engine_ai_scripting_allegiance(e_campaign_team campaign_team, e_multiplayer_team multiplayer_team)
{
    mangled_ppc("?game_engine_ai_scripting_allegiance@@YAXW4e_campaign_team@@W4e_multiplayer_team@@@Z");

    if (VALID_INDEX(campaign_team, k_campaign_team_count))
    {
        if (VALID_INDEX(multiplayer_team, k_multiplayer_team_count))
        {
            if (game_is_authoritative())
            {
                game_engine_form_team_allegiance(campaign_team, multiplayer_team);
            }
        }
        else
        {
            event_wrapped(_event_warning, "mp_ai_allegiance: invalid multiplayer team #%d!", multiplayer_team);
        }
    }
    else
    {
        event_wrapped(_event_warning, "mp_ai_allegiance: invalid campaign team #%d!", campaign_team);
    }
};

void game_engine_mp_team_allegiance(e_multiplayer_team team1_index, e_multiplayer_team team2_index)
{
    mangled_ppc("?game_engine_mp_team_allegiance@@YAXW4e_multiplayer_team@@0@Z");

    if (VALID_INDEX(team1_index, k_multiplayer_team_count))
    {
        if (VALID_INDEX(team2_index, k_multiplayer_team_count))
        {
            if (game_is_authoritative())
            {
                event_wrapped(_event_error, "networking: game_engine_mp_team_allegiance attempting to set allegiances?");
            }
        }
        else
        {
            event_wrapped(_event_warning, "mp_allegiance: invalid multiplayer team #%d!", team2_index);
        }
    }
    else
    {
        event_wrapped(_event_warning, "mp_allegiance: invalid multiplayer team #%d!", team1_index);
    }
};

