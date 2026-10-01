#pragma once
#ifndef __HALOAUTOTEST_H__
#define __HALOAUTOTEST_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct gamepad_state;

void HATInit(void);
void HATCleanup(void);
void HATReadMain(void);
void HATRun(gamepad_state * state);
void HATRawRead(gamepad_state * state);
void HATRawLoopRead(gamepad_state * state);
void HATRawWrite(gamepad_state const * state);

/* ---------- globals */

/* ---------- public code */

#endif // __HALOAUTOTEST_H__

