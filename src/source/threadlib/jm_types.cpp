/* ---------- headers */

#include "threadlib\jm_types.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_job_handle::c_job_handle(class c_job_handle_internal &);

c_job_handle::c_job_handle(c_job_handle_internal & internal_handle)
{
    mangled_ppc("??0c_job_handle@@QAA@AAVc_job_handle_internal@@@Z");

    m_usage = internal_handle.get_usage();
    m_index = internal_handle.get_index();
    m_unknown6 = 0;
};

