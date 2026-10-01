#pragma once
#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void game_state_lock(bool lock);
void game_state_security_write_signature(bool use_insecure_signature, void * buffer);
bool game_state_security_verify_signature_insecure(void * buffer);
bool game_state_security_verify_signature_secure(void * buffer);
void game_state_security_invalidate_signature(void);
void game_state_store_tag_file_checksum(long game_state_proc_flags);
void game_state_handle_saved_game(long game_state_proc_flags);
void game_state_reset_mapping(long game_state_proc_flags);
void game_state_restore_internal(long game_state_proc_flags);
void game_state_set_revert_time(long game_state_proc_flags);
void const * game_state_with_mirrors_get_buffer_address(long * buffer_size);

/* ---------- globals */

extern bool game_state_verify_on_write;

/* ---------- public code */

#endif // __GAME_STATE_H__

