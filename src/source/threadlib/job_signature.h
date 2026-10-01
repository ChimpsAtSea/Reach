#pragma once
#ifndef __JOB_SIGNATURE_H__
#define __JOB_SIGNATURE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "threadlib\job.h"

/* ---------- constants */

/* ---------- definitions */

class c_job_signature
{
public:
    // inline in the target (bodies owned by other translation units)
    c_job_signature(job_entry_point_t entry_point);
    c_job_signature(job_entry_point_t entry_point, c_job_pre_post const * pre_post);
    ~c_job_signature();

    job_entry_point_t get_entry_point()
    {
        mangled_ppc("?get_entry_point@c_job_signature@@QAAP6AXKKKKKVc_job_handle@@Vc_jm_work_unit_handle@@@ZXZ");

        return m_entry_point;
    };

    c_job_pre_post const * get_pre_post() const
    {
        mangled_ppc("?get_pre_post@c_job_signature@@QBAPBVc_job_pre_post@@XZ");

        return m_pre_post;
    };

    job_entry_point_t m_entry_point;
    unsigned long m_context;
    c_job_pre_post const * m_pre_post;
};
static_assert(sizeof(c_job_signature) == 0xC, "c_job_signature");

/* ---------- prototypes */

extern unsigned long context_string_hash(char const * string);

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_SIGNATURE_H__

