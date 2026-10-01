/* ---------- headers */

#include "blamlib\player_rewards.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\game\player_rewards\internal\player_reward_persistence.h"
#include "omaha\game\player_rewards\player_commendation_definitions.h"
#include "omaha\game\player_rewards\player_cookie_purchase_definitions.h"
#include "omaha\game\player_rewards\player_cookie_purchases.h"
#include "omaha\game\player_rewards\player_cookies.h"
#include "omaha\memory\crc.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void handle_jackpot(e_controller_index controller_index, long cookies);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static int const c_enum_no_init<enum e_purchase_category, char, -1, 13, struct s_default_enum_string_resolver>::k_minimum_value; // "?k_minimum_value@?$c_enum_no_init@W4e_purchase_category@@D$0?0$0N@Us_default_enum_string_resolver@@@@2HB"
// public: static enum e_purchase_category const c_enum_no_init<enum e_purchase_category, char, -1, 13, struct s_default_enum_string_resolver>::k_maximum_value_plus_one; // "?k_maximum_value_plus_one@?$c_enum_no_init@W4e_purchase_category@@D$0?0$0N@Us_default_enum_string_resolver@@@@2W4e_purchase_category@@B"
// public: static int const c_enum_no_init<enum e_player_model_customization_area, char, -1, 8, struct s_default_enum_string_resolver>::k_minimum_value; // "?k_minimum_value@?$c_enum_no_init@W4e_player_model_customization_area@@D$0?0$07Us_default_enum_string_resolver@@@@2HB"
// public: static enum e_player_model_customization_area const c_enum_no_init<enum e_player_model_customization_area, char, -1, 8, struct s_default_enum_string_resolver>::k_maximum_value_plus_one; // "?k_maximum_value_plus_one@?$c_enum_no_init@W4e_player_model_customization_area@@D$0?0$07Us_default_enum_string_resolver@@@@2W4e_player_model_customization_area@@B"
// public: static int const c_enum_no_init<enum e_player_non_model_customization, char, 0, 4, struct s_default_enum_string_resolver>::k_minimum_value; // "?k_minimum_value@?$c_enum_no_init@W4e_player_non_model_customization@@D$0A@$03Us_default_enum_string_resolver@@@@2HB"
// public: static enum e_player_non_model_customization const c_enum_no_init<enum e_player_non_model_customization, char, 0, 4, struct s_default_enum_string_resolver>::k_maximum_value_plus_one; // "?k_maximum_value_plus_one@?$c_enum_no_init@W4e_player_non_model_customization@@D$0A@$03Us_default_enum_string_resolver@@@@2W4e_player_non_model_customization@@B"
// public: static enum e_cookie_purchase_flags const c_flags_no_init<enum e_cookie_purchase_flags, unsigned char, 5, struct s_default_enum_string_resolver>::k_maximum_count; // "?k_maximum_count@?$c_flags_no_init@W4e_cookie_purchase_flags@@E$04Us_default_enum_string_resolver@@@@2W4e_cookie_purchase_flags@@B"

// void player_rewards_initialize(void);
// void player_rewards_dispose(void);
// void player_rewards_update(float);
// void player_rewards_game_ended(void);
// void player_rewards_flush(void);
// bool player_rewards_reward_state_is_online(enum e_controller_index);
// bool player_rewards_reward_state_ever_online(enum e_controller_index);
// void player_rewards_notify_network_configuration_changed(void);
// void player_rewards_notify_local_box_quit(void);
// void player_rewards_write_to_profile_hs(void);
// void player_rewards_sync_with_lsp_hs(void);
// void player_rewards_dump_current_reward_state_hs(void);
// void player_rewards_reinitialize_reward_state_from_storage_hs(enum e_controller_index);
// void player_rewards_reset_reward_state_hs(enum e_controller_index);
// void player_rewards_force_unlock_all_purchasable_items_hs(void);
// void player_rewards_set_purchase_state_hs(enum e_controller_index, long, long);
// void handle_jackpot(enum e_controller_index, long);

void player_rewards_initialize(void)
{
    mangled_ppc("?player_rewards_initialize@@YAXXZ");

    reward_persistence_initialize(handle_jackpot);
    reward_persistence_set_commendation_definition_checksum(commendation_globals_generate_checksum());
    reward_persistence_set_purchase_definition_checksum(cookie_purchase_definition_generate_checksum());
};

void player_rewards_dispose(void)
{
    mangled_ppc("?player_rewards_dispose@@YAXXZ");

    reward_persistence_dispose();
};

void player_rewards_update(float dt)
{
    mangled_ppc("?player_rewards_update@@YAXM@Z");

    reward_persistence_update();

    if (reward_persistence_get_commendation_definition_checksum() == crc_new())
    {
        reward_persistence_set_commendation_definition_checksum(commendation_globals_generate_checksum());
    }

    if (reward_persistence_get_purchase_definition_checksum() == crc_new())
    {
        reward_persistence_set_purchase_definition_checksum(cookie_purchase_definition_generate_checksum());
    }
};

void player_rewards_game_ended(void)
{
    mangled_ppc("?player_rewards_game_ended@@YAXXZ");

    reward_persistence_game_ended();
};

void player_rewards_flush(void)
{
    mangled_ppc("?player_rewards_flush@@YAXXZ");

    reward_persistence_sync_with_lsp();
    reward_persistence_write_to_profile();
};

bool player_rewards_reward_state_is_online(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_reward_state_is_online@@YA_NW4e_controller_index@@@Z");

    return reward_persistence_controller_has_synced_with_lsp(controller_index);
};

bool player_rewards_reward_state_ever_online(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_reward_state_ever_online@@YA_NW4e_controller_index@@@Z");

    return reward_persistence_controller_is_online_user(controller_index);
};

void player_rewards_notify_network_configuration_changed(void)
{
    mangled_ppc("?player_rewards_notify_network_configuration_changed@@YAXXZ");

    reward_persistence_notify_network_configuration_changed();
};

void player_rewards_notify_local_box_quit(void)
{
    mangled_ppc("?player_rewards_notify_local_box_quit@@YAXXZ");

    reward_persistence_notify_local_box_quit();
};

void player_rewards_write_to_profile_hs(void)
{
    mangled_ppc("?player_rewards_write_to_profile_hs@@YAXXZ");

    reward_persistence_write_to_profile();
};

void player_rewards_sync_with_lsp_hs(void)
{
    mangled_ppc("?player_rewards_sync_with_lsp_hs@@YAXXZ");

    reward_persistence_sync_with_lsp();
};

void player_rewards_dump_current_reward_state_hs(void)
{
    mangled_ppc("?player_rewards_dump_current_reward_state_hs@@YAXXZ");

    reward_persistence_dump_current_reward_state_hs();
};

void player_rewards_reinitialize_reward_state_from_storage_hs(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_reinitialize_reward_state_from_storage_hs@@YAXW4e_controller_index@@@Z");

    reward_persistence_reinitialize_reward_state_from_storage_hs(controller_index);
};

void player_rewards_reset_reward_state_hs(e_controller_index controller_index)
{
    mangled_ppc("?player_rewards_reset_reward_state_hs@@YAXW4e_controller_index@@@Z");

    reward_persistence_reset_reward_state_hs(controller_index);
};

void player_rewards_force_unlock_all_purchasable_items_hs(void)
{
    mangled_ppc("?player_rewards_force_unlock_all_purchasable_items_hs@@YAXXZ");

    cookie_purchase_force_grant_all_prerequisites_hs();
};

void player_rewards_set_purchase_state_hs(e_controller_index controller_index, long purchase_index, long purchase_state)
{
    mangled_ppc("?player_rewards_set_purchase_state_hs@@YAXW4e_controller_index@@JJ@Z");

    reward_persistence_set_purchase_state_hs(controller_index, purchase_index, purchase_state);
};

void handle_jackpot(e_controller_index controller_index, long cookies)
{
    mangled_ppc("?handle_jackpot@@YAXW4e_controller_index@@J@Z");

    event_wrapped(_event_message, "networking:player_reward: %d controller just got an lsp jackpot of %d", controller_index, cookies);
    player_rewards_add_cookies_to_controller(controller_index, cookies, _cookie_award_client_authoritative_type_ignore_daily_cap);
};
