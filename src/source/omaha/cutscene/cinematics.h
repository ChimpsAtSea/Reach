#pragma once
#ifndef __CINEMATICS_H__
#define __CINEMATICS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_cinematic_light_globals;

/* ---------- prototypes */

void cinematic_load_from_game_state(long game_state_proc_flags);
s_cinematic_light_globals * get_cinematic_light_globals(void);

/* ---------- globals */

/* ---------- public code */

#endif // __CINEMATICS_H__

