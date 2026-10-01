/* ---------- headers */

#include "threadlib\work_unit_params.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: s_work_unit_params::s_work_unit_params(unsigned long, struct s_critical_section, struct s_critical_section, struct s_critical_section, struct s_semaphore);

s_work_unit_params::s_work_unit_params(unsigned long num_workers, s_critical_section activelist_critical_section, s_critical_section freelist_critical_section, s_critical_section deps_critical_section, s_semaphore semaphore) :
    m_num_workers(num_workers),
    m_activelist_critical_section(activelist_critical_section),
    m_freelist_critical_section(freelist_critical_section),
    m_deps_critical_section(deps_critical_section),
    m_semaphore(semaphore)
{
    mangled_ppc("??0s_work_unit_params@@QAA@KUs_critical_section@@00Us_semaphore@@@Z");
};

