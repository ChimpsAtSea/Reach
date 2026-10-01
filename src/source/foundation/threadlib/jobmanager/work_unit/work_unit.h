#pragma once
#ifndef __WORK_UNIT_H__
#define __WORK_UNIT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\jobmanager\scheduler\job_list.h"
#include "threadlib\jm_types.h"
#include "threadlib\kernel.h"
#include "threadlib\scheduler.h"

/* ---------- constants */

unsigned long const k_jm_max_num_workers = 8;

/* ---------- definitions */

struct s_work_unit_params;

class c_work_unit
{
public:
    c_work_unit()
    {
        mangled_ppc("??0c_work_unit@@QAA@XZ");
    };

    ~c_work_unit()
    {
        mangled_ppc("??1c_work_unit@@QAA@XZ");
    };

    void initialize(s_work_unit_params const & params);
    void execute(unsigned long kernel_index);
    void dispose();
    bool is_done(c_job_handle const & handle);

    bool is_used()
    {
        mangled_ppc("?is_used@c_work_unit@@QAA_NXZ");

        return 0 != (m_flags & 1);
    };

    void set_used()
    {
        mangled_ppc("?set_used@c_work_unit@@QAAXXZ");

        set_flag(1);
    };

    void set_flag(unsigned long flag)
    {
        mangled_ppc("?set_flag@c_work_unit@@QAAXK@Z");

        m_flags |= flag;
    };

    void unset_flag(unsigned long flag)
    {
        mangled_ppc("?unset_flag@c_work_unit@@QAAXK@Z");

        m_flags &= ~flag;
    };

    unsigned long m_flags;
    unsigned long m_num_workers;
    c_kernel m_kernels[k_jm_max_num_workers];
    c_job_list m_job_list;
    unsigned long m_unknown50090;
    c_scheduler_fifo m_scheduler;
};
static_assert(sizeof(c_work_unit) == 0x50098, "c_work_unit");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __WORK_UNIT_H__

