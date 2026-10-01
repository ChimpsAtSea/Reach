#pragma once
#ifndef __HAVOK_H__
#define __HAVOK_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void havok_prepare_fpu_for_update(void);
void havok_restore_fpu_from_update(void);
void havok_can_modify_state_allow(void);
void havok_can_modify_state_disallow(void);

void havok_save_to_game_state(long game_state_proc_flags);
void havok_after_save_to_game_state(long game_state_proc_flags);
void havok_prepare_for_game_state_load(long game_state_proc_flags);
void havok_load_from_game_state(long game_state_proc_flags);
long havok_last_state_reset_time_get(void);

/* ---------- globals */

extern class hkpWorld * g_havok_world;

/* ---------- public code */

#endif // __HAVOK_H__

