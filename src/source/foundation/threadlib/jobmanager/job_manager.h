#pragma once
#ifndef __JOB_MANAGER_H__
#define __JOB_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"
#include "threadlib\work_unit_handle.h"

/* ---------- constants */

/* ---------- definitions */

struct s_work_unit_params;

typedef void (*job_manager_block_callback_t)(void);

class c_job_manager
{
public:
    c_job_manager()
    {
        mangled_ppc("??0c_job_manager@@QAA@XZ");

        m_block_callback = NULL;
    };

    ~c_job_manager()
    {
        mangled_ppc("??1c_job_manager@@QAA@XZ");
    };

    bool initialize(s_critical_section const & activelist_critical_section, s_critical_section const & freelist_critical_section, s_critical_section const & deps_critical_section, s_semaphore const & semaphore0, s_semaphore const & semaphore1);
    void dispose();
    static c_jm_work_unit_handle create_work_unit(s_work_unit_params const & params);
    static void destroy_work_unit(c_jm_work_unit_handle & handle);
    void register_block_callback(job_manager_block_callback_t callback);
    void invoke_block_callback();

    s_critical_section const & get_cs(unsigned long index) const
    {
        mangled_ppc("?get_cs@c_job_manager@@QBAABUs_critical_section@@K@Z");

        return m_critical_sections[index];
    };

    s_semaphore const & get_semaphore(unsigned long index) const
    {
        mangled_ppc("?get_semaphore@c_job_manager@@QBAABUs_semaphore@@K@Z");

        return m_semaphores[index];
    };

    s_critical_section m_critical_sections[3];
    s_semaphore m_semaphores[2];
    job_manager_block_callback_t m_block_callback;
};
static_assert(sizeof(c_job_manager) == 0x18, "c_job_manager");

/* ---------- prototypes */

extern c_job_manager & get_job_manager(void);
extern void job_manager_initialize(s_critical_section const & activelist_critical_section, s_critical_section const & freelist_critical_section, s_critical_section const & deps_critical_section, s_semaphore const & semaphore0, s_semaphore const & semaphore1);
extern void job_manager_dispose(void);
extern void job_manager_set_default_work_unit(c_jm_work_unit_handle const & work_unit);
extern c_jm_work_unit_handle & job_manager_get_default_work_unit(void);

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_MANAGER_H__

