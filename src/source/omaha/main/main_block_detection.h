#pragma once
#ifndef __MAIN_BLOCK_DETECTION_H__
#define __MAIN_BLOCK_DETECTION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include <string.h>

/* ---------- constants */

enum e_block_detection_type
{
    _block_detection_type_network = 0, // network_set_block_detection_threshold
    _block_detection_type_main, // main_set_block_detection_threshold

    k_block_detection_type_count
};

/* ---------- definitions */

struct s_block_detection_type_data
{
    bool enabled; // 0x0
    bool only_break_when_debugger_present; // 0x1
    long block_detection_threshold; // 0x4 msec
    unsigned long last_unblocked_time; // 0x8
    long suspend_block_detection_stack; // 0xC
    unsigned long suspend_start_time; // 0x10
    long suspended_time; // 0x14 msec
    bool block_detected; // 0x18
};
static_assert(sizeof(s_block_detection_type_data) == 0x1C, "s_block_detection_type_data");

struct s_block_detection_globals
{
    s_block_detection_globals(void)
    {
        mangled_ppc("??0s_block_detection_globals@@QAA@XZ");

        memset(this, 0, sizeof(*this));
    };

    s_static_array<s_block_detection_type_data, k_block_detection_type_count> types; // 0x0
    bool exit_requested; // 0x38
    bool signal_on_unblock; // 0x39
};
static_assert(sizeof(s_block_detection_globals) == 0x3C, "s_block_detection_globals");

class c_block_detection_globals_container
{
public:
    c_block_detection_globals_container(void)
    {
        mangled_ppc("??0c_block_detection_globals_container@@QAA@XZ");
    };

    s_block_detection_globals m_globals; // 0x0
};
static_assert(sizeof(c_block_detection_globals_container) == 0x3C, "c_block_detection_globals_container");

class c_block_detection_globals_accessor
{
public:
    c_block_detection_globals_accessor(void);
    ~c_block_detection_globals_accessor(void);

    s_block_detection_globals const * operator->(void) const;
    s_block_detection_globals * operator->(void);
};

/* ---------- prototypes */

extern unsigned long block_detection_thread_main(void * thread_parameter);
extern void block_detection_initialize(void);
extern void block_detection_dispose(void);
extern void block_detection_configure(e_block_detection_type type, bool enabled, bool only_break_when_debugger_present, long block_detection_threshold);
extern long block_detection_notify_unblocked(e_block_detection_type type);
extern void block_detection_suspend(e_block_detection_type type);
extern void block_detection_resume(e_block_detection_type type);
extern bool block_detection_is_debugger_present_internal(void);

/* ---------- globals */

extern c_block_detection_globals_container block_detection_globals;

/* ---------- public code */

#endif // __MAIN_BLOCK_DETECTION_H__
