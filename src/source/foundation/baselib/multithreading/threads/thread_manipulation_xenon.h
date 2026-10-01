#pragma once
#ifndef __THREAD_MANIPULATION_XENON_H__
#define __THREAD_MANIPULATION_XENON_H__

/* ---------- headers */

#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"

/* ---------- constants */

/* ---------- definitions */

enum e_thread_xenon_processor
{
    _thread_xenon_processor_core_0_hw_thread_0 = 0,
    _thread_xenon_processor_core_0_hw_thread_1,
    _thread_xenon_processor_core_1_hw_thread_0,
    _thread_xenon_processor_core_1_hw_thread_1,
    _thread_xenon_processor_core_2_hw_thread_0,
    _thread_xenon_processor_core_2_hw_thread_1,

    k_thread_xenon_processor_count
};

/* ---------- prototypes */

extern e_thread_xenon_processor thread_get_current_thread_xenon_processor(void);
extern void thread_set_xenon_processor(s_thread_handle thread_handle, e_thread_xenon_processor processor);

/* ---------- globals */

/* ---------- public code */

#endif // __THREAD_MANIPULATION_XENON_H__

