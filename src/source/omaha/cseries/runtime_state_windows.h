#pragma once
#ifndef __RUNTIME_STATE_WINDOWS_H__
#define __RUNTIME_STATE_WINDOWS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void * runtime_state_allocate_buffer(long size);
void runtime_state_free_buffer(void * buffer);

/* ---------- globals */

/* ---------- public code */

#endif // __RUNTIME_STATE_WINDOWS_H__

