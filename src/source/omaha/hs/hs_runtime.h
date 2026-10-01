#pragma once
#ifndef __HS_RUNTIME_H__
#define __HS_RUNTIME_H__

/* ---------- headers */

#include "omaha\hs\hs.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void hs_restore_from_saved_game(long game_state_proc_flags);
bool hs_runtime_safe_to_gc();
long hs_thread_new(e_hs_thread_type type, long script_index, bool deterministic);
hs_thread * hs_thread_get(long thread_index);
void hs_thread_try_to_delete(long thread_index, bool validate);
void hs_thread_delete(long thread_index, bool validate);
void hs_thread_main(long thread_index);
bool hs_evaluate(long thread_index, long expression_index, hs_destination_pointer destination, long * out_cast);
bool hs_runtime_evaluate(long expression_index, long * result, bool deterministic);

/* ---------- globals */

/* ---------- public code */

#endif // __HS_RUNTIME_H__

