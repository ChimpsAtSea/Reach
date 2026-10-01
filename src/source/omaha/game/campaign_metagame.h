#pragma once
#ifndef __CAMPAIGN_METAGAME_H__
#define __CAMPAIGN_METAGAME_H__

/* ---------- headers */

/* ---------- constants */

// named e_game_skulls per the target mangled names (c_flags_no_init<e_game_skulls, unsigned long, 17>)
enum e_game_skulls
{
    k_game_skull_count = 17
};

enum e_campaign_metagame_scoring
{
    _metagame_off = 0,
    _metagame_on_group_scoring,
    _metagame_on,

    k_metagame_scoring_count
};

/* ---------- definitions */

/* ---------- prototypes */

void campaign_metagame_save_to_game_state(long game_state_proc_flags);
void campaign_metagame_initialize_for_saved_game(long game_state_proc_flags);
bool campaign_metagame_enabled(void);

/* ---------- globals */

extern char const * global_skull_names[];

/* ---------- public code */

#endif // __CAMPAIGN_METAGAME_H__

