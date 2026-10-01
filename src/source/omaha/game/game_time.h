#pragma once
#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern long game_time_get(void);
extern long game_tick_rate();
extern float game_tick_length();
extern long game_seconds_to_ticks_round(float seconds);
extern void game_time_set_speed(float speed);
extern float game_ticks_to_seconds(float ticks);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_TIME_H__

