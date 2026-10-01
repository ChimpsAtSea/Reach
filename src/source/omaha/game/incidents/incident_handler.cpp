#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\incidents\\incident_handler.cpp"
/* ---------- headers */

#include "omaha\game\incidents\incident_handler.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\campaign_metagame.h"
#include "omaha\game\challenges\challenges.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine_events.h"
#include "omaha\game\game_heat.h"
#include "omaha\game\game_mode_definitions.h"
#include "omaha\game\game_results.h"
#include "omaha\game\incidents\incident.h"
#include "omaha\game\incidents\incident_definitions.h"
#include "omaha\game\incidents\incident_response_definition.h"
#include "omaha\game\player_mapping.h"
#include "omaha\game\player_rewards\player_achievements.h"
#include "omaha\game\player_rewards\player_avatar_awards.h"
#include "omaha\game\player_rewards\player_commendations.h"
#include "omaha\game\player_rewards\player_medals.h"
#include "omaha\game\players.h"
#include "omaha\hs\hs_runtime.h"
#include "omaha\hs\hs_scenario_definitions.h"
#include "omaha\input\controllers.h"
#include "omaha\interface\chud\chud_messaging.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool handle_incident_would_produce_response(long, long);
// void incident_award_heat(long, long);
// void incident_increment_commendation(long, long);
// void incident_grant_achievement(long, long);
// void incident_grant_avatar_award(long, long);
// void incident_display_medal(long, long);
// void incident_record_medal_statistic(long, long);
// void incident_award_daily_challenge(long, long);
// void incident_run_hs_script(long);
// void handle_incident(long, class c_flags<enum e_suppressed_incident_flags, unsigned char, 6, struct s_default_enum_string_resolver> const &, struct s_incident_metadata const &);
// public: bool c_flags_no_init<enum e_suppressed_incident_flags, unsigned char, 6, struct s_default_enum_string_resolver>::test(enum e_suppressed_incident_flags) const;
// public: static bool c_flags_no_init<enum e_suppressed_incident_flags, unsigned char, 6, struct s_default_enum_string_resolver>::valid_bit(enum e_suppressed_incident_flags);
// private: static unsigned char c_flags_no_init<enum e_suppressed_incident_flags, unsigned char, 6, struct s_default_enum_string_resolver>::flag_size_type(enum e_suppressed_incident_flags);

bool handle_incident_would_produce_response(long incident_name, long player_index)
{
    mangled_ppc("?handle_incident_would_produce_response@@YA_NJJ@Z");

    bool result = false;
    s_incident_definition const * incident = incident_globals_find_incident_by_name(incident_name);
    if (incident)
    {
        for (long response_index = 0; response_index < incident->response.count; response_index++)
        {
            s_game_incident_response const * incident_response = static_cast<s_game_incident_response const *>(tag_block_get_element_with_size(&incident->response, response_index, sizeof(s_game_incident_response)));
            assert_tag_debug_untracked_jul_11_2011(57, incident_response);

            if (test_allowed_game_mode_flags(incident_response->allowed_game_modes))
            {
                result = true;
                break;
            }
        }
    }

    return result;
};

void incident_award_heat(long player_index, long heat)
{
    mangled_ppc("?incident_award_heat@@YAXJJ@Z");

    if (player_index != NONE)
    {
        player_award_heat(player_index, heat);
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_award_heat received a player_index of NONE.");
    }
};

void incident_increment_commendation(long player_index, long commendation_name)
{
    mangled_ppc("?incident_increment_commendation@@YAXJJ@Z");

    if (player_index != NONE)
    {
        player_rewards_commendation_progress_increment_for_player(player_index, commendation_name);
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_increment_commendation received a player_index of NONE.");
    }
};

void incident_grant_achievement(long player_index, long achievement_name)
{
    mangled_ppc("?incident_grant_achievement@@YAXJJ@Z");

    if (player_index != NONE)
    {
        player_grant_achievement_by_name(player_index, achievement_name);
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_grant_achievement received a player_index of NONE.");
    }
};

void incident_grant_avatar_award(long player_index, long avatar_award_name)
{
    mangled_ppc("?incident_grant_avatar_award@@YAXJJ@Z");

    if (player_index != NONE)
    {
        player_avatar_awards_grant_by_name(player_index, avatar_award_name);
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_grant_avatar_award received a player_index of NONE.");
    }
};

void incident_display_medal(long player_index, long medal_name)
{
    mangled_ppc("?incident_display_medal@@YAXJJ@Z");

    if (player_index != NONE)
    {
        if (!game_is_campaign() || campaign_metagame_enabled())
        {
            chud_messaging_post_medal(player_index, medal_name);
        }
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_award_medal received a player_index of NONE.");
    }
};

void incident_record_medal_statistic(long player_index, long medal_name)
{
    mangled_ppc("?incident_record_medal_statistic@@YAXJJ@Z");

    if (player_index != NONE)
    {
        if (!game_is_campaign() || campaign_metagame_enabled())
        {
            long medal_index = game_medal_definition_find(medal_name);
            if (medal_index != NONE)
            {
                game_results_medal_increment(player_index, medal_index, 1);
            }
        }
    }
    else
    {
        event_wrapped(_event_warning, "player_rewards:incident:incident_award_medal received a player_index of NONE.");
    }
};

void incident_award_daily_challenge(long player_index, long challenge_name)
{
    mangled_ppc("?incident_award_daily_challenge@@YAXJJ@Z");

    if (player_index != NONE)
    {
        e_controller_index controller_index = player_mapping_get_input_controller(player_index);
        if (VALID_INDEX(controller_index, k_number_of_controllers))
        {
            challenge_progress(controller_index, challenge_name);
        }
        else
        {
            event_wrapped(_event_verbose, "player_rewards:incident:incident_award_daily_challenge received a player_index who doesn't have a controller - normal in a multibox game, can't award challenges to remote players.");
        }
    }
    else
    {
        event_wrapped(_event_verbose, "player_rewards:incident:incident_award_daily_challenge received a player_index of NONE, granting to all controllers.");

        c_player_in_game_iterator player_iterator;
        player_iterator.begin();
        while (player_iterator.next())
        {
            e_controller_index controller_index = player_mapping_get_input_controller(player_iterator.get_index());
            if (VALID_INDEX(controller_index, k_number_of_controllers))
            {
                challenge_progress(controller_index, challenge_name);
            }
        }
    }
};

void incident_run_hs_script(long script_index)
{
    mangled_ppc("?incident_run_hs_script@@YAXJ@Z");

    if (script_index != NONE)
    {
        hs_script const * script = static_cast<hs_script const *>(tag_block_get_element_with_size(&global_scenario_get()->scripts, script_index, sizeof(hs_script)));
        if (script)
        {
            long result;
            hs_runtime_evaluate(script->root_expression_index, &result, true);
        }
    }
};

void handle_incident(long incident_name, c_flags<e_suppressed_incident_flags, unsigned char, k_suppressed_incident_flags_count> const & suppressed_flags, s_incident_metadata const & incident)
{
    mangled_ppc("?handle_incident@@YAXJABV?$c_flags@W4e_suppressed_incident_flags@@E$05Us_default_enum_string_resolver@@@@ABUs_incident_metadata@@@Z");

    s_incident_definition const * incident_definition = incident_globals_find_incident_by_name(incident_name);
    if (incident_definition)
    {
        for (long response_index = 0; response_index < incident_definition->response.count; response_index++)
        {
            s_game_incident_response const * incident_response = static_cast<s_game_incident_response const *>(tag_block_get_element_with_size(&incident_definition->response, response_index, sizeof(s_game_incident_response)));
            assert_tag_debug_untracked_jul_11_2011(255, incident_response);

            if (test_allowed_game_mode_flags(incident_response->allowed_game_modes))
            {
                if (incident_response->heat_award != 0)
                {
                    incident_award_heat(incident.cause_player_index, incident_response->heat_award);
                }

                if (incident_response->game_engine_event != _string_id_invalid && incident_response->game_engine_event != _string_id_empty_string)
                {
                    if (!game_is_campaign() || incident_definition->flags.test(_incident_definition_force_game_engine_event_display_in_campaign_bit))
                    {
                        game_engine_event_play(incident_response->game_engine_event, suppressed_flags, incident);
                    }
                }

                if (incident_response->medal != _string_id_invalid && incident_response->medal != _string_id_empty_string)
                {
                    if (!suppressed_flags.test(_suppressed_incident_medal_display_bit))
                    {
                        incident_display_medal(incident.cause_player_index, incident_response->medal);
                    }
                    else
                    {
                        incident_event_with_information(_event_message, "suppressing medal display", incident_name, incident);
                    }

                    if (!suppressed_flags.test(_suppressed_incident_medal_stats_bit))
                    {
                        incident_record_medal_statistic(incident.cause_player_index, incident_response->medal);
                    }
                    else
                    {
                        incident_event_with_information(_event_message, "suppressing medal statistic", incident_name, incident);
                    }
                }

                if (incident_response->commendation != _string_id_invalid && incident_response->commendation != _string_id_empty_string)
                {
                    incident_increment_commendation(incident.cause_player_index, incident_response->commendation);
                }

                if (incident_response->achievement != _string_id_invalid && incident_response->achievement != _string_id_empty_string)
                {
                    incident_grant_achievement(incident.cause_player_index, incident_response->achievement);
                }

                if (incident_response->avatar_award != _string_id_invalid && incident_response->avatar_award != _string_id_empty_string)
                {
                    incident_grant_avatar_award(incident.cause_player_index, incident_response->avatar_award);
                }

                for (long challenge_index = 0; challenge_index < incident_response->challenges.count; challenge_index++)
                {
                    s_daily_challenge_to_increment const * challenge = static_cast<s_daily_challenge_to_increment const *>(tag_block_get_element_with_size(&incident_response->challenges, challenge_index, sizeof(s_daily_challenge_to_increment)));
                    if (challenge->daily_challenge != _string_id_invalid && challenge->daily_challenge != _string_id_empty_string)
                    {
                        incident_award_daily_challenge(incident.cause_player_index, challenge->daily_challenge);
                    }
                }

                if (incident_response->internal_hs_script_index != NONE)
                {
                    incident_run_hs_script(incident_response->internal_hs_script_index);
                }
            }
        }
    }
    else
    {
        event_wrapped(_event_error, "player_rewards:incident:incident_handler: unable to locate incident by string id %i", incident_name);
    }
};

