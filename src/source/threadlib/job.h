#pragma once
#ifndef __JOB_H__
#define __JOB_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\indexed_pool.h"
#include "threadlib\jm_types.h"

/* ---------- constants */

/* ---------- definitions */

class c_job_signature;
class c_jm_work_unit_handle;

typedef void (*job_entry_point_t)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, c_job_handle, c_jm_work_unit_handle);

class c_job_deps
{
public:
    void increment_depcount()
    {
        mangled_ppc("?increment_depcount@c_job_deps@@QAAXXZ");

        m_depcount.increment();
    };

    void decrement_depcount()
    {
        mangled_ppc("?decrement_depcount@c_job_deps@@QAAXXZ");

        m_depcount.decrement();
    };

    long depcount() const
    {
        mangled_ppc("?depcount@c_job_deps@@QBAJXZ");

        return m_depcount;
    };

    unsigned short get_deplist()
    {
        mangled_ppc("?get_deplist@c_job_deps@@QAAGXZ");

        return m_deplist;
    };

    unsigned short set_dependant(unsigned short dependant)
    {
        mangled_ppc("?set_dependant@c_job_deps@@QAAGG@Z");

        unsigned short old_deplist = m_deplist;
        m_deplist = dependant;
        return old_deplist;
    };

    void clear()
    {
        mangled_ppc("?clear@c_job_deps@@QAAXXZ");

        m_depcount.set(0);
        m_deplist = k_indexed_pool_handle_null;
        m_flags = 0;
    };

    c_interlocked_int32 m_depcount;
    unsigned short m_deplist;
    unsigned short m_flags;
};
static_assert(sizeof(c_job_deps) == 0x8, "c_job_deps");

typedef void (*job_pre_post_function_t)();

class c_job_pre_post
{
public:
    // inline in the target (bodies owned by other translation units)
    c_job_pre_post();
    c_job_pre_post(job_pre_post_function_t pre_function, job_pre_post_function_t post_function, char const * name);

    job_pre_post_function_t m_pre_function;
    job_pre_post_function_t m_post_function;
    unsigned long m_hash;
    char const * m_name;
};
static_assert(sizeof(c_job_pre_post) == 0x10, "c_job_pre_post");

class c_job
{
public:
    // inline in the target (bodies owned by other translation units)
    c_job();
    c_job(c_job_signature & signature, unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3);
    ~c_job();

    void setup(c_job_signature & signature, unsigned long parameter0, unsigned long parameter1, unsigned long parameter2, unsigned long parameter3);
    void execute(unsigned long thread_index, c_job_handle handle, c_jm_work_unit_handle & work_unit);
    unsigned long execute_pre(unsigned long thread_index);
    unsigned long execute_post(unsigned long thread_index);

    c_job_pre_post const & get_pre_post()
    {
        mangled_ppc("?get_pre_post@c_job@@QAAABVc_job_pre_post@@XZ");

        return m_pre_post;
    };

    c_job_deps & dependencies()
    {
        mangled_ppc("?dependencies@c_job@@QAAAAVc_job_deps@@XZ");

        return m_dependencies;
    };

    void clear()
    {
        mangled_ppc("?clear@c_job@@QAAXXZ");

        m_entry_point = 0;
        m_dependencies.clear();
    };

    job_entry_point_t m_entry_point;
    unsigned long m_parameter0;
    unsigned long m_parameter1;
    unsigned long m_parameter2;
    unsigned long m_parameter3;
    c_job_deps m_dependencies;
    c_job_pre_post m_pre_post;
    unsigned long m_unknown2C;
    __int64 m_unknown30;
};
static_assert(sizeof(c_job) == 0x38, "c_job");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __JOB_H__

