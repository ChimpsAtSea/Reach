#pragma once
#ifndef __WORK_UNIT_PARAMS_H__
#define __WORK_UNIT_PARAMS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"

/* ---------- constants */

/* ---------- definitions */

struct s_work_unit_params
{
    s_work_unit_params(unsigned long num_workers, s_critical_section activelist_critical_section, s_critical_section freelist_critical_section, s_critical_section deps_critical_section, s_semaphore semaphore);

    unsigned long m_num_workers;
    s_critical_section m_activelist_critical_section;
    s_critical_section m_freelist_critical_section;
    s_critical_section m_deps_critical_section;
    s_semaphore m_semaphore;
};
static_assert(sizeof(s_work_unit_params) == 0x14, "s_work_unit_params");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __WORK_UNIT_PARAMS_H__

