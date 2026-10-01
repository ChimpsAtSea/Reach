#pragma once
#ifndef __KERNEL_H__
#define __KERNEL_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_scheduler_fifo;

class c_kernel
{
public:
    c_kernel();

    unsigned long do_work(unsigned long thread_index);
    bool should_exit();
    void signal_exit();
    void reset();
    void set_scheduler(c_scheduler_fifo * scheduler)
    {
        mangled_ppc("?set_scheduler@c_kernel@@QAAXPAVc_scheduler_fifo@@@Z");

        m_scheduler = scheduler;
    };

    unsigned long m_flags;
    c_scheduler_fifo * m_scheduler;
};
static_assert(sizeof(c_kernel) == 0x8, "c_kernel");

/* ---------- prototypes */

extern bool execute_one_job(c_scheduler_fifo * scheduler, unsigned long thread_index);

/* ---------- globals */

/* ---------- public code */

#endif // __KERNEL_H__

