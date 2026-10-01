#pragma once
#ifndef __THREAD_MANIPULATION_H__
#define __THREAD_MANIPULATION_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void thread_set_current_thread_user_index(unsigned long user_index);
extern unsigned long thread_get_current_thread_user_index(void);
extern void thread_set_current_thread_name(char const * name);
extern char const * thread_get_current_thread_name(void);

/* ---------- globals */

/* ---------- public code */

#endif // __THREAD_MANIPULATION_H__

