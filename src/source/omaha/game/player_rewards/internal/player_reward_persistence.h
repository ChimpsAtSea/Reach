#pragma once
#ifndef __PLAYER_REWARD_PERSISTENCE_H__
#define __PLAYER_REWARD_PERSISTENCE_H__

/* ---------- headers */

#include "omaha\input\controllers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

long reward_persistence_add_cookies(e_controller_index controller_index, long cookies, bool ignore_daily_cap);
long reward_persistence_get_cookie_total(e_controller_index controller_index);
bool reward_persistence_cookie_purchasable_item_owned(e_controller_index controller_index, long purchase_index);
bool reward_persistence_cookie_purchasable_item_granted_by_LSP_or_DLC(e_controller_index controller_index, long purchase_index);
void reward_persistence_initialize(void (*jackpot_handler)(e_controller_index controller_index, long cookies));
void reward_persistence_dispose();
void reward_persistence_update();
void reward_persistence_game_ended();
void reward_persistence_sync_with_lsp();
void reward_persistence_write_to_profile();
bool reward_persistence_controller_has_synced_with_lsp(e_controller_index controller_index);
bool reward_persistence_controller_is_online_user(e_controller_index controller_index);
void reward_persistence_notify_network_configuration_changed();
void reward_persistence_notify_local_box_quit();
void reward_persistence_dump_current_reward_state_hs();
void reward_persistence_reinitialize_reward_state_from_storage_hs(e_controller_index controller_index);
void reward_persistence_reset_reward_state_hs(e_controller_index controller_index);
void reward_persistence_set_purchase_state_hs(e_controller_index controller_index, long purchase_index, long purchase_state);
unsigned long reward_persistence_get_commendation_definition_checksum();
void reward_persistence_set_commendation_definition_checksum(unsigned long checksum);
unsigned long reward_persistence_get_purchase_definition_checksum();
void reward_persistence_set_purchase_definition_checksum(unsigned long checksum);
long reward_persistence_commendation_get_progress(e_controller_index controller_index, long commendation_absolute_index);
bool reward_persistence_commendation_increment(e_controller_index controller_index, long commendation_absolute_index);
void reward_persistence_commendation_set_progress(e_controller_index controller_index, long commendation_absolute_index, long progress);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_REWARD_PERSISTENCE_H__

