#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\player_commendations.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\player_commendations.h"
#include "blamlib\player_rewards.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\game_results.h"
#include "omaha\game\player_mapping.h"
#include "omaha\game\player_rewards\internal\player_reward_persistence.h"
#include "omaha\game\player_rewards\player_commendation_definitions.h"
#include "omaha\game\player_rewards\player_cookies.h"
#include "omaha\input\controllers.h"
#include "omaha\interface\chud\chud_messaging.h"
#include "omaha\networking\online\online_achievements.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool g_allow_offline_commendations = false;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_allow_offline_commendations; // "?g_allow_offline_commendations@@3_NA"

// bool player_rewards_commendation_progress_increment_for_controller(enum e_controller_index, long);
// bool player_rewards_commendation_progress_increment_local(enum e_controller_index, long);
// enum e_commendation_progression_level & operator++(enum e_commendation_progression_level &);
// enum e_commendation_progression_level commendation_get_cookie_reward_cap_level(struct s_commendation_globals_definition const *, struct s_commendation_definition const *);
// bool player_rewards_commendation_progress_increment_for_player(long, long);
// long player_rewards_commendation_get_progress(enum e_controller_index, long);
// long player_rewards_commendation_get_next_level_goal(enum e_controller_index, long);
// unsigned char player_rewards_commendation_calculate_percent_completed(enum e_controller_index);
// void player_rewards_commendation_progress_increment_hs(enum e_controller_index, long);
// bool player_rewards_commendation_set_progress_for_controller_hs(enum e_controller_index, long, long);
// public: enum e_commendation_progression_level c_enum_no_init<enum e_commendation_progression_level, char, -1, 7, struct s_default_enum_string_resolver>::operator enum e_commendation_progression_level(void) const;
// bool operator!=<enum e_commendation_progression_level>(enum e_commendation_progression_level const &, enum e_none_sentinel const &);
// bool operator==<enum e_commendation_progression_level>(enum e_commendation_progression_level const &, enum e_none_sentinel const &);

bool player_rewards_commendation_progress_increment_for_controller(e_controller_index controller_index, long commendation_name)
{
    mangled_ppc("?player_rewards_commendation_progress_increment_for_controller@@YA_NW4e_controller_index@@J@Z");

    bool success = false;
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        long commendation_absolute_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, commendation_name);
        if (commendation_absolute_index != NONE)
        {
            success = player_rewards_commendation_progress_increment_local(controller_index, commendation_absolute_index);
        }
        else
        {
            event_wrapped(_event_error, "player_rewards:commendations: failed to resolve commendation id %d to a valid commendation index.", commendation_name);
        }
    }

    return success;
};

bool player_rewards_commendation_progress_increment_local(e_controller_index controller_index, long commendation_absolute_index)
{
    mangled_ppc("?player_rewards_commendation_progress_increment_local@@YA_NW4e_controller_index@@J@Z");

    bool result = false;
    if (!player_rewards_reward_state_is_online(controller_index) && !g_allow_offline_commendations)
    {
        event_wrapped(_event_warning, "player_rewards:commendations: commendation_progress_increment_local tried to grant a commendation (index %d) to an offline rewards controller.  This will be denied by the LSP, so we're not going to increment it locally.", commendation_absolute_index);
    }
    else
    {
        long old_progress = reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index);
        result = reward_persistence_commendation_increment(controller_index, commendation_absolute_index);
        if (result)
        {
            s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
            if (commendation_globals)
            {
                e_commendation_progression_level new_commendation_progression_level;
                s_commendation_definition const * commendation = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, commendation_absolute_index, sizeof(s_commendation_definition)));
                if (commendation_definition_get_progress_level(commendation, reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index)) >= commendation_get_cookie_reward_cap_level(commendation_globals, commendation))
                {
                    player_rewards_add_cookies_to_controller(controller_index, commendation->post_cap_reward_value, static_cast<e_cookie_award_client_authoritative_type>(0));
                }
                else
                {
                    player_rewards_add_cookies_to_controller(controller_index, commendation->reward_value, static_cast<e_cookie_award_client_authoritative_type>(0));
                }

                long new_progress = reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index);
                e_commendation_progression_level old_commendation_progression_level = commendation_definition_get_progress_level(commendation, old_progress);
                new_commendation_progression_level = commendation_definition_get_progress_level(commendation, new_progress);
                assert_tag_debug_untracked_jul_11_2011(126, old_commendation_progression_level<=new_commendation_progression_level);

                for (e_commendation_progression_level level = static_cast<e_commendation_progression_level>(old_commendation_progression_level + 1); level <= new_commendation_progression_level; ++level)
                {
                    player_rewards_add_cookies_to_controller(controller_index, commendation->level_reward_value[level], static_cast<e_cookie_award_client_authoritative_type>(0));
                    chud_messaging_post_commendation_callout(player_mapping_get_player_by_input_controller(controller_index), commendation->name, commendation_globals->callout_display_time, level);
                }

                if (new_commendation_progression_level >= _commendation_progression_level_silver)
                {
                    controller_grant_achievement(controller_index, static_cast<e_achievement>(38));
                }

                assert_tag_debug_untracked_jul_11_2011(150, new_commendation_progression_level==commendation_definition_get_progress_level(commendation, reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index)));
            }

            game_results_local_commendation_increment(controller_index, commendation_absolute_index);
        }
    }

    return result;
};

e_commendation_progression_level commendation_get_cookie_reward_cap_level(s_commendation_globals_definition const * commendation_globals, s_commendation_definition const * commendation)
{
    mangled_ppc("?commendation_get_cookie_reward_cap_level@@YA?AW4e_commendation_progression_level@@PBUs_commendation_globals_definition@@PBUs_commendation_definition@@@Z");

    e_commendation_progression_level reward_level_cap = commendation_globals->reward_level_cap;
    if (commendation->post_cap_reward_value != 0)
    {
        reward_level_cap = static_cast<e_commendation_progression_level>(commendation->override_reward_level_cap - 1);
    }

    return reward_level_cap;
};

bool player_rewards_commendation_progress_increment_for_player(long player_index, long commendation_name)
{
    mangled_ppc("?player_rewards_commendation_progress_increment_for_player@@YA_NJJ@Z");

    bool result = true;
    bool incremented = false;
    bool is_playback = game_is_playback();
    bool has_local_controller = true;
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        long commendation_absolute_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, commendation_name);
        if (commendation_absolute_index != NONE)
        {
            e_controller_index controller_index = player_mapping_get_input_controller(player_index);
            if (controller_index != k_no_controller)
            {
                result = player_rewards_commendation_progress_increment_local(controller_index, commendation_absolute_index);
                incremented = result;
                has_local_controller = true;
            }
            else
            {
                has_local_controller = false;
            }

            if (result && game_is_authoritative() && game_results_get_game_recording())
            {
                game_results_commendation_increment(DATUM_INDEX_TO_ABSOLUTE_INDEX(player_index), commendation_absolute_index);
                incremented = true;
            }
        }
        else
        {
            event_wrapped(_event_error, "player_rewards:commendations: failed to resolve commendation id %d to a valid commendation index.", commendation_name);
        }
    }

    if (!incremented)
    {
        if (!has_local_controller && is_playback)
        {
            // playback without a local controller is expected to have no effect
        }
        else
        {
            event_wrapped(_event_warning, "player_rewards:commendations: incrementing of commendation had no effect - didn't successfully grant to a local player or increment game results.");
        }
    }

    return result;
};

long player_rewards_commendation_get_progress(e_controller_index controller_index, long commendation_name)
{
    mangled_ppc("?player_rewards_commendation_get_progress@@YAJW4e_controller_index@@J@Z");

    long progress = 0;
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        long commendation_absolute_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, commendation_name);
        if (commendation_absolute_index != NONE)
        {
            progress = reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index);
        }
        else
        {
            event_wrapped(_event_error, "player_rewards:commendations: failed to resolve commendation id %d to a valid commendation index.", commendation_name);
        }
    }

    return progress;
};

long player_rewards_commendation_get_next_level_goal(e_controller_index controller_index, long commendation_name)
{
    mangled_ppc("?player_rewards_commendation_get_next_level_goal@@YAJW4e_controller_index@@J@Z");

    long next_level_goal = 0;
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        long commendation_absolute_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, commendation_name);
        s_commendation_definition const * commendation_definition = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, commendation_absolute_index, sizeof(s_commendation_definition)));
        assert_tag_debug_untracked_jul_11_2011(299, commendation_definition);

        e_commendation_progression_level next_level = commendation_definition_get_next_progress_level(commendation_definition, reward_persistence_commendation_get_progress(controller_index, commendation_absolute_index));
        if (next_level != k_commendation_progression_level_none)
        {
            next_level_goal = commendation_definition->level_minimum[next_level];
        }
    }

    return next_level_goal;
};

unsigned char player_rewards_commendation_calculate_percent_completed(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_commendation_calculate_percent_completed@@YAEW4e_controller_index@@@Z");

    c_game_tag_defense_push_scope tag_defense_scope(false);
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    long total_progress = 0;
    long maximum_progress = 0;
    if (commendation_globals)
    {
        for (long commendation_index = 0; commendation_index < commendation_globals->commendations.count; commendation_index++)
        {
            s_commendation_definition const * commendation = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, commendation_index, sizeof(s_commendation_definition)));
            long progress = reward_persistence_commendation_get_progress(controller_index, commendation_index);
            e_commendation_progression_level level = commendation_definition_get_progress_level(commendation, progress);
            if (level != NONE)
            {
                total_progress += PIN(level, 0, 5);
            }
            maximum_progress += 5;
        }
    }

    unsigned char percent_completed = 0;
    if (maximum_progress > 0)
    {
        percent_completed = static_cast<unsigned char>(PIN(total_progress * 100 / maximum_progress, 0, 100));
    }

    return percent_completed;
};

void player_rewards_commendation_progress_increment_hs(e_controller_index controller_index, long commendation_name)
{
    mangled_ppc("?player_rewards_commendation_progress_increment_hs@@YAXW4e_controller_index@@J@Z");

    player_rewards_commendation_progress_increment_for_controller(controller_index, commendation_name);
};

bool player_rewards_commendation_set_progress_for_controller_hs(e_controller_index controller_index, long commendation_name, long progress)
{
    mangled_ppc("?player_rewards_commendation_set_progress_for_controller_hs@@YA_NW4e_controller_index@@JJ@Z");

    bool result = false;
    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        long commendation_absolute_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, commendation_name);
        if (commendation_absolute_index != NONE)
        {
            reward_persistence_commendation_set_progress(controller_index, commendation_absolute_index, progress);
        }
        else
        {
            event_wrapped(_event_error, "player_rewards:commendations: failed to resolve commendation id %d to a valid commendation index.", commendation_name);
        }
    }

    return result;
};

