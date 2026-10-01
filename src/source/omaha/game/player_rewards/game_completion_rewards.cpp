#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\game_completion_rewards.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\game_completion_rewards.h"
#include "omaha\game\player_rewards\game_completion_rewards_definitions.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\cseries\cseries.h"
#include "omaha\main\main_game.h"
#include "omaha\networking\network_configuration.h"
#include "omaha\simulation\simulation.h"
#include "blamlib\player_grades.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool game_completion_rewards_get_cookie_award(enum e_controller_index, struct s_game_completion_results const *, struct s_game_completion_overrides const *, struct s_game_completion_cookie_result *);
// struct s_game_completion_rewards_globals const * game_completion_rewards_globals_get(void);

bool game_completion_rewards_get_cookie_award(e_controller_index controller_index, s_game_completion_results const * results, s_game_completion_overrides const * overrides, s_game_completion_cookie_result * cookie_result_out)
{
    mangled_ppc("?game_completion_rewards_get_cookie_award@@YA_NW4e_controller_index@@PBUs_game_completion_results@@PBUs_game_completion_overrides@@PAUs_game_completion_cookie_result@@@Z");

    bool success = false;
    if (main_game_loaded_map())
    {
        c_game_tag_defense_push_scope game_tag_defense_scope(false);
        s_game_completion_rewards_globals const * globals = game_completion_rewards_globals_get();
        assert_tag_debug_untracked_jul_11_2011(36, VALID_INDEX(results->category, k_number_of_toplevel_categories));
        if (results->category == _game_completion_category_multiplayer)
        {
            assert_tag_debug_untracked_jul_11_2011(39, VALID_INDEX(results->multiplayer_mode, k_number_of_multiplayer_game_modes));
        }
        else
        {
            assert_tag_debug_untracked_jul_11_2011(43, VALID_INDEX(results->difficulty_level, k_campaign_difficulty_levels_count));
        }

        memset(cookie_result_out, 0, sizeof(s_game_completion_cookie_result));
        if (globals && globals->categories[results->category].count > 0)
        {
            s_game_completion_rewards_category const * category = static_cast<s_game_completion_rewards_category const *>(tag_block_get_element_with_size(&globals->categories[results->category], 0, sizeof(s_game_completion_rewards_category)));
            if (category->modes[results->subcategory].count > 0)
            {
                s_game_completion_rewards_definition const * rewards_definition = static_cast<s_game_completion_rewards_definition const *>(tag_block_get_element_with_size(&category->modes[results->subcategory], 0, sizeof(s_game_completion_rewards_definition)));
                float hopper_multiplier = rewards_definition->hopper_scaling_factor;
                float winner_scale = rewards_definition->winner_scaling_factor;
                float placed_scale = rewards_definition->performance_scaling_factor;
                if (overrides && overrides->enabled)
                {
                    hopper_multiplier *= overrides->earn_scale;
                    winner_scale *= overrides->win_scale;
                    placed_scale *= overrides->performance_scale;
                }

                float performance_multiplier = results->won ? winner_scale : (results->placed ? placed_scale : 1.0f);
                float total_minutes = static_cast<float>(MAX(0, results->length_seconds) / 60);
                float raw_cookies = 0.0f;
                if (rewards_definition->cpm_falloff_curve.count > 0)
                {
                    float prior_start_time = 0.0f;
                    float last_cookies_per_minute = static_cast<float>(rewards_definition->initial_cookies_per_minute);
                    bool still_counting = true;
                    for (long falloff_index = 0; still_counting && falloff_index < rewards_definition->cpm_falloff_curve.count; falloff_index++)
                    {
                        s_game_completion_rewards_falloff_point const * falloff_point = static_cast<s_game_completion_rewards_falloff_point const *>(tag_block_get_element_with_size(&rewards_definition->cpm_falloff_curve, falloff_index, sizeof(s_game_completion_rewards_falloff_point)));
                        if (total_minutes > static_cast<float>(falloff_point->start_time))
                        {
                            raw_cookies += last_cookies_per_minute * (static_cast<float>(falloff_point->start_time) - prior_start_time);
                            prior_start_time = static_cast<float>(falloff_point->start_time);
                            last_cookies_per_minute = static_cast<float>(falloff_point->cookies_per_minute);
                        }
                        else
                        {
                            raw_cookies += last_cookies_per_minute * (total_minutes - prior_start_time);
                            still_counting = false;
                        }
                    }
                }
                else
                {
                    raw_cookies = static_cast<float>(rewards_definition->initial_cookies_per_minute) * total_minutes;
                }

                float grade_modifier = 1.0f;
                if (player_rewards_grade_and_subgrade_available(controller_index))
                {
                    e_player_grade grade = player_rewards_get_controller_grade(controller_index);
                    e_player_sub_grade sub_grade = player_rewards_get_controller_sub_grade(controller_index);
                    if (get_network_configuration().cookie_multipliers.valid(grade) && get_network_configuration().cookie_multipliers[grade].valid(sub_grade))
                    {
                        grade_modifier = get_network_configuration().cookie_multipliers[grade][sub_grade];
                    }
                    else
                    {
                        event_wrapped(_event_error, "game:game_completion_rewards: Controller %d grade/subgrade %d/%d do not have a valid cookie multiplier in net config", controller_index, grade, sub_grade);
                    }
                }

                hopper_multiplier *= grade_modifier;
                float time_spent_cookie_value = raw_cookies * hopper_multiplier;
                long time_cookie_count = static_cast<long>(time_spent_cookie_value);
                float total_cookies_real = time_spent_cookie_value * performance_multiplier;
                long total_cookie_count = static_cast<long>(total_cookies_real);
                cookie_result_out->time_spent_cookies = time_cookie_count;
                cookie_result_out->time_spent_and_performance_cookies = total_cookie_count;
                assert_tag_debug_untracked_jul_11_2011(142, cookie_result_out->time_spent_cookies >= 0);
                assert_tag_debug_untracked_jul_11_2011(143, cookie_result_out->time_spent_and_performance_cookies >= 0);

                success = true;
            }
        }
    }

    return success;
};

s_game_completion_rewards_globals const * game_completion_rewards_globals_get()
{
    mangled_ppc("?game_completion_rewards_globals_get@@YAPBUs_game_completion_rewards_globals@@XZ");

    s_game_globals const * game_globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()));
    long game_completion_rewards_globals_index = game_globals->game_completion_rewards_globals.index;

    return game_completion_rewards_globals_index != NONE ? static_cast<s_game_completion_rewards_globals const *>(tag_get(GAME_COMPLETION_REWARDS_GLOBALS_TAG, game_completion_rewards_globals_index)) : NULL;
};

