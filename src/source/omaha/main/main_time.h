#pragma once
#ifndef __MAIN_TIME_H__
#define __MAIN_TIME_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void main_time_restore(long game_state_proc_flags);
extern __int64 main_time_get_absolute(void);
extern long main_time_get_absolute_rate(void);

/* ---------- globals */

/* ---------- public code */

#endif // __MAIN_TIME_H__

