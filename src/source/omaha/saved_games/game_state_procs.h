#pragma once
#ifndef __GAME_STATE_PROCS_H__
#define __GAME_STATE_PROCS_H__

/* ---------- headers */

/* ---------- constants */

// $TODO: only the two bits below are verified for Reach (H3 used bits 8/9 for these)
enum e_game_state_proc_flags
{
    _use_insecure_signature_bit = 11,
    _defer_writing_signature_bit = 12,
};

enum e_game_state_proc_state
{
    _game_state_proc_state_none = 0,
    _game_state_proc_state_loading,
    _game_state_proc_state_saving,

    k_game_state_proc_state_count
};

/* ---------- definitions */

typedef void (*game_state_proc)(long game_state_proc_flags);

/* ---------- prototypes */

void game_state_proc_globals_initialize(void);
void game_state_proc_globals_dispose(void);
e_game_state_proc_state game_state_proc_globals_get_state(void);
void game_state_call_before_save_procs(long game_state_proc_flags);
void game_state_call_after_save_procs(long game_state_proc_flags);
void game_state_call_before_load_procs(long game_state_proc_flags);
void game_state_call_after_load_procs(long game_state_proc_flags);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_STATE_PROCS_H__
