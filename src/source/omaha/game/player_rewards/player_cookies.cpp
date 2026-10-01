#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\player_cookies.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\player_cookies.h"
#include "omaha\game\player_rewards\player_cookie_purchase_definitions.h"
#include "omaha\game\player_rewards\internal\player_reward_persistence.h"
#include "omaha\game\game.h"
#include "omaha\game\game_results.h"
#include "omaha\game\player_mapping.h"
#include "omaha\interface\chud\chud.h"
#include "omaha\interface\c_controller.h"
#include "omaha\interface\c_player_profile.h"
#include "blamlib\player_grades.h"
#include "baselib\system_time_xenon.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long player_rewards_reconcile_cookies_from_game_results(enum e_controller_index, long, long, enum e_cookie_award_host_authoritative_type);
// long player_rewards_add_cookies_direct(enum e_controller_index, long, bool);
// bool player_rewards_add_cookies_to_controller_hs(enum e_controller_index, long);
// bool player_rewards_add_cookies_to_controller(enum e_controller_index, long, enum e_cookie_award_client_authoritative_type);
// bool player_rewards_add_cookies_local(enum e_controller_index, long, enum e_cookie_award_client_authoritative_type);
// bool player_rewards_add_cookies_to_player_hs(long, long);
// bool player_rewards_add_cookies_to_player(long, long, enum e_cookie_award_host_authoritative_type);
// long player_rewards_get_cookie_total(enum e_controller_index);
// long player_rewards_get_spent_cookies(enum e_controller_index);
// long player_rewards_get_available_cookies(enum e_controller_index);
// void player_rewards_notify_grade_advancement(enum e_controller_index, enum e_player_grade, enum e_player_grade);
// void player_rewards_notify_sub_grade_advancement(enum e_controller_index, enum e_player_sub_grade, enum e_player_sub_grade);

long player_rewards_reconcile_cookies_from_game_results(e_controller_index controller_index, long previous_cookies, long current_cookies, e_cookie_award_host_authoritative_type cookie_award_type)
{
    mangled_ppc("?player_rewards_reconcile_cookies_from_game_results@@YAJW4e_controller_index@@JJW4e_cookie_award_host_authoritative_type@@@Z");

    bool ignore_cap = false;
    long cookies_to_add = MAX(0, current_cookies - previous_cookies);
    long cookies_added = 0;
    if (cookies_to_add > 0)
    {
        cookies_added = player_rewards_add_cookies_direct(controller_index, cookies_to_add, ignore_cap);
    }

    return cookies_added;
};

long player_rewards_add_cookies_direct(e_controller_index controller_index, long cookies, bool ignore_daily_cap)
{
    mangled_ppc("?player_rewards_add_cookies_direct@@YAJW4e_controller_index@@J_N@Z");

    long cookies_added = 0;
    e_player_grade old_player_grade = player_rewards_get_controller_grade(controller_index);
    e_player_sub_grade old_player_sub_grade = player_rewards_get_controller_sub_grade(controller_index);
    assert_tag_debug_untracked_jul_11_2011(46, VALID_CONTROLLER(controller_index));

    cookies_added = reward_persistence_add_cookies(controller_index, cookies, ignore_daily_cap);
    e_player_grade new_player_grade = player_rewards_get_controller_grade(controller_index);
    e_player_sub_grade new_player_sub_grade = player_rewards_get_controller_sub_grade(controller_index);
    if (player_rewards_grade_and_subgrade_available(controller_index))
    {
        if (new_player_grade > old_player_grade)
        {
            player_rewards_notify_grade_advancement(controller_index, old_player_grade, new_player_grade);
        }
        else if (new_player_grade == old_player_grade && new_player_sub_grade > old_player_sub_grade)
        {
            player_rewards_notify_sub_grade_advancement(controller_index, old_player_sub_grade, new_player_sub_grade);
        }
    }

    return cookies_added;
};

bool player_rewards_add_cookies_to_controller_hs(e_controller_index controller_index, long cookies)
{
    mangled_ppc("?player_rewards_add_cookies_to_controller_hs@@YA_NW4e_controller_index@@J@Z");

    return player_rewards_add_cookies_to_controller(controller_index, cookies, _cookie_award_client_authoritative_type_hs);
};

bool player_rewards_add_cookies_to_controller(e_controller_index controller_index, long cookies, e_cookie_award_client_authoritative_type cookie_award_type)
{
    mangled_ppc("?player_rewards_add_cookies_to_controller@@YA_NW4e_controller_index@@JW4e_cookie_award_client_authoritative_type@@@Z");

    bool success = false;
    if (VALID_CONTROLLER(controller_index))
    {
        success = player_rewards_add_cookies_local(controller_index, cookies, cookie_award_type);
    }
    else
    {
        event_wrapped(_event_error, "player_rewards:cookies: controller_index passed to player_rewards_add_cookies_local is invalid.");
    }

    return success;
};

bool player_rewards_add_cookies_local(e_controller_index controller_index, long cookies, e_cookie_award_client_authoritative_type cookie_award_type)
{
    mangled_ppc("?player_rewards_add_cookies_local@@YA_NW4e_controller_index@@JW4e_cookie_award_client_authoritative_type@@@Z");

    bool ignore_cap = cookie_award_type == _cookie_award_client_authoritative_type_ignore_daily_cap;
    long cookies_added = player_rewards_add_cookies_direct(controller_index, cookies, ignore_cap);
    game_results_local_cookies_add(controller_index, cookies_added, cookie_award_type);
    long player_index = player_mapping_get_player_by_input_controller(controller_index);
    if (player_index != NONE)
    {
        chud_awarded_cookies(player_index, cookies_added);
    }

    return cookies_added > 0;
};

bool player_rewards_add_cookies_to_player_hs(long player_index, long cookies)
{
    mangled_ppc("?player_rewards_add_cookies_to_player_hs@@YA_NJJ@Z");

    return player_rewards_add_cookies_to_player(player_index, cookies, _cookie_award_host_authoritative_type_hs);
};

bool player_rewards_add_cookies_to_player(long player_index, long cookies, e_cookie_award_host_authoritative_type cookie_award_type)
{
    mangled_ppc("?player_rewards_add_cookies_to_player@@YA_NJJW4e_cookie_award_host_authoritative_type@@@Z");

    bool success = true;
    bool added = false;
    bool is_playback = game_is_playback();
    if (game_is_authoritative() && game_results_get_game_recording())
    {
        game_results_cookies_add(DATUM_INDEX_TO_ABSOLUTE_INDEX(player_index), cookies, cookie_award_type);
        added = true;
    }

    if (!added)
    {
        if (is_playback)
        {
            // cookies are not granted during playback
        }
        else
        {
            event_wrapped(_event_warning, "player_rewards:cookies: addition of cookies had no effect - didn't successfully grant to a local player or increment game results.");
        }
    }

    return success;
};

long player_rewards_get_cookie_total(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_get_cookie_total@@YAJW4e_controller_index@@@Z");

    long cookie_total = 0;
    if (VALID_CONTROLLER(controller_index))
    {
        cookie_total = reward_persistence_get_cookie_total(controller_index);
    }
    else
    {
        static unsigned long x_last_event_time = 0;
        if (system_milliseconds() > x_last_event_time + 1000)
        {
            event_wrapped(_event_error, "player_rewards:cookies: player_rewards_get_cookie_total called with invalid controller index, returning 0.");
            x_last_event_time = system_milliseconds();
        }
    }

    return cookie_total;
};

long player_rewards_get_spent_cookies(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_get_spent_cookies@@YAJW4e_controller_index@@@Z");

    long spent_cookies = 0;
    if (VALID_CONTROLLER(controller_index))
    {
        long item_count = cookie_purchase_get_global_item_count();
        for (long item_index = 0; item_index < item_count; item_index++)
        {
            if (reward_persistence_cookie_purchasable_item_owned(controller_index, item_index) && !reward_persistence_cookie_purchasable_item_granted_by_LSP_or_DLC(controller_index, item_index))
            {
                s_cookie_purchase_definition const * purchase = cookie_purchase_global_item_get_definition(item_index);
                spent_cookies += purchase->cookie_cost;
            }
        }
    }
    else
    {
        static unsigned long x_last_event_time = 0;
        if (system_milliseconds() > x_last_event_time + 1000)
        {
            event_wrapped(_event_error, "player_rewards:cookies: player_rewards_get_spent_cookies called with invalid controller index, returning 0.");
            x_last_event_time = system_milliseconds();
        }
    }

    return spent_cookies;
};

long player_rewards_get_available_cookies(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_get_available_cookies@@YAJW4e_controller_index@@@Z");

    long cookie_total = player_rewards_get_cookie_total(controller_index);
    long cookies_spent = player_rewards_get_spent_cookies(controller_index);

    return cookie_total - cookies_spent;
};

void player_rewards_notify_grade_advancement(e_controller_index controller_index, e_player_grade old_grade, e_player_grade new_grade)
{
    mangled_ppc("?player_rewards_notify_grade_advancement@@YAXW4e_controller_index@@W4e_player_grade@@1@Z");

    c_controller_interface * controller = controller_get(controller_index);
    c_player_profile_interface * player_profile = controller->get_player_profile_interface_writable();
    assert_tag_debug_untracked_jul_11_2011(249, new_grade > old_grade);

    if (player_profile)
    {
        player_profile->set_recently_advanced_grades(true);
    }
};

void player_rewards_notify_sub_grade_advancement(e_controller_index controller_index, e_player_sub_grade old_sub_grade, e_player_sub_grade new_sub_grade)
{
    mangled_ppc("?player_rewards_notify_sub_grade_advancement@@YAXW4e_controller_index@@W4e_player_sub_grade@@1@Z");

    c_controller_interface * controller = controller_get(controller_index);
    c_player_profile_interface * player_profile = controller->get_player_profile_interface_writable();
    assert_tag_debug_untracked_jul_11_2011(267, new_sub_grade > old_sub_grade);

    if (player_profile)
    {
        player_profile->set_recently_advanced_sub_grades(true);
    }
};

