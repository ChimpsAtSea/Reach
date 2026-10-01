#pragma once
#ifndef __JM_TYPES_H__
#define __JM_TYPES_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

unsigned long const k_jm_max_num_jobs_per_work_unit = 4096;

/* ---------- definitions */

enum ejob_state
{
    _e_job_inactive = 0,
    _e_job_active,
    _e_job_executing,
};

class c_job_handle_internal
{
public:
    c_job_handle_internal() :
        m_usage(0)
    {
        mangled_ppc("??0c_job_handle_internal@@QAA@XZ");

        m_index = 0xFFFF;
        m_state = 0;
        m_unknown7 = 0;
    };

    ~c_job_handle_internal()
    {
        mangled_ppc("??1c_job_handle_internal@@QAA@XZ");
    };

    long get_usage() const
    {
        mangled_ppc("?get_usage@c_job_handle_internal@@QBAJXZ");

        return m_usage;
    };

    unsigned short const & get_index() const
    {
        mangled_ppc("?get_index@c_job_handle_internal@@QBAABGXZ");

        return m_index;
    };

    void set_state(ejob_state state)
    {
        mangled_ppc("?set_state@c_job_handle_internal@@QAAXW4ejob_state@@@Z");

        m_state = static_cast<unsigned char>(state);
    };

    ejob_state get_state() const
    {
        mangled_ppc("?get_state@c_job_handle_internal@@QBA?AW4ejob_state@@XZ");

        return static_cast<ejob_state>(m_state);
    };

    void increment_usage()
    {
        mangled_ppc("?increment_usage@c_job_handle_internal@@QAAXXZ");

        m_usage.increment();
    };

    c_synchronized_int32 m_usage;
    unsigned short m_index;
    unsigned char m_state;
    unsigned char m_unknown7;
};
static_assert(sizeof(c_job_handle_internal) == 0x8, "c_job_handle_internal");

class c_job_handle_unsafe
{
    friend class c_job_list;

protected:
    unsigned short get_index() const
    {
        mangled_ppc("?get_index@c_job_handle_unsafe@@IBAGXZ");

        return m_index;
    };

    long get_usage() const
    {
        mangled_ppc("?get_usage@c_job_handle_unsafe@@IBAJXZ");

        return m_usage;
    };

    long m_usage;
    unsigned short m_index;
    unsigned short m_unknown6;
};
static_assert(sizeof(c_job_handle_unsafe) == 0x8, "c_job_handle_unsafe");

class c_job_handle :
    public c_job_handle_unsafe
{
public:
    c_job_handle();
    c_job_handle(c_job_handle_internal & internal_handle);
};
static_assert(sizeof(c_job_handle) == 0x8, "c_job_handle");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __JM_TYPES_H__

