#pragma once
#ifndef __JOB_GROUPS_H__
#define __JOB_GROUPS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "threadlib\jm_types.h"

/* ---------- constants */

/* ---------- definitions */

class c_job;
class c_job_signature;
class c_jm_work_unit_handle;

enum e_job_group_setup
{
    e_job_group_unset = 0,
    e_job_group_setup,
    e_job_group_activated = 3,
};

class c_job_group
{
public:
    c_job_group(c_jm_work_unit_handle & work_unit);
    ~c_job_group();

    void activate_jobs(unsigned long start, unsigned long end);
    void allocate_jobs(unsigned long num);
    c_job_handle setup(unsigned long index, c_job_signature & signature, unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3);

    static unsigned long const k_job_group_max = 2048;

    c_job_handle_unsafe m_handles[k_job_group_max]; // not c_job_handle: the target constructor runs no per-element constructor
    c_job * m_jobs[k_job_group_max];
    unsigned char m_setup[k_job_group_max];
    unsigned long m_num_allocated;
    c_jm_work_unit_handle & m_work_unit;
    bool m_unknown6808;
};
static_assert(sizeof(c_job_group) == 0x680C, "c_job_group");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_GROUPS_H__

