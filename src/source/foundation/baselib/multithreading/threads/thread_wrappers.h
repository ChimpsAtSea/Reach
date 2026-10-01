#pragma once
#ifndef __THREAD_WRAPPERS_H__
#define __THREAD_WRAPPERS_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "baselib\system_exception_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_xenon.h"

/* ---------- constants */

enum e_thread_platform_flags
{
    _thread_platform_flag_create_suspended = 0,

    k_thread_platform_flags_count
};

/* ---------- definitions */

struct s_thread_platform_parameters
{
    s_thread_platform_parameters(void)
    {
        mangled_ppc("??0s_thread_platform_parameters@@QAA@XZ");

        stack_size = 0;
        priority = _thread_priority_normal;
    };

    s_thread_platform_parameters(long in_stack_size, e_thread_priority in_priority, e_thread_xenon_processor in_processor, c_flags_zero_init<e_thread_platform_flags, unsigned long, k_thread_platform_flags_count> in_flags) :
        stack_size(in_stack_size),
        priority(in_priority),
        processor(in_processor),
        flags(in_flags)
    {
        mangled_ppc("??0s_thread_platform_parameters@@QAA@JW4e_thread_priority@@W4e_thread_xenon_processor@@V?$c_flags_zero_init@W4e_thread_platform_flags@@K$00@@@Z");
    };

    unsigned int stack_size;
    e_thread_priority priority;
    e_thread_xenon_processor processor;
    c_flags_zero_init<e_thread_platform_flags, unsigned long, k_thread_platform_flags_count> flags;
};
static_assert(sizeof(s_thread_platform_parameters) == 0x10, "s_thread_platform_parameters");

class c_thread_base
{
public:
    c_thread_base(void);
    virtual ~c_thread_base(void);

    void start_with_parameters(s_thread_platform_parameters const * platform_parameters);
    void start(void);
    void resume(void);
    void wait(void);
    bool wait_timeout(long timeout);
    void stop(void);
    char const * get_name(void) const;
    void set_name(char const * name);
    void set_name_by_group(char const * name, long index, long count);
    long get_thread_index(void) const;
    void set_thread_index(long thread_index);
    static void allocate_thread_indices(long thread_count, long * out_thread_indices);
    s_thread_id get_thread_id(void) const;
    unsigned long do_work_wrapper(void);
    unsigned long get_exit_code(void) const;
    bool has_been_started(void) const;
    bool has_crashed(void) const;
    void on_crash(void);
    static unsigned long entry_point(void * parameters);

protected:
    virtual unsigned long do_work(void) = 0;

    void validate_graceful_exit(void) const;

    s_thread_handle m_thread_handle;
    s_thread_id m_thread_id;
    long m_thread_index;
    c_synchronized_int32 m_exit_code;
    c_synchronized_int32 m_has_crashed;
    s_static_string<32> m_name;
    s_exception_information m_exception_information;
};
static_assert(sizeof(c_thread_base) == 0xAA8, "c_thread_base");

class c_thread_wrapper :
    public c_thread_base
{
public:
    c_thread_wrapper(void);
    c_thread_wrapper(unsigned long (* const thread_function)(void *), void * thread_parameters);

    void setup(unsigned long (* const thread_function)(void *), void * thread_parameters);
    void setup_with_thread_index(unsigned long (* const thread_function)(void *), void * thread_parameters, long thread_index);

protected:
    virtual unsigned long do_work(void);

    unsigned long (* m_thread_function)(void *);
    void * m_thread_parameters;
};
static_assert(sizeof(c_thread_wrapper) == 0xAB0, "c_thread_wrapper");

class c_thread_crew
{
public:
    c_thread_crew(void);

    void setup(char const * name, long count, unsigned long (* const thread_function)(void *), void ** thread_parameters);
    void setup_array(char const * name, long count, unsigned long (* const thread_function)(void *), void * thread_parameters_array, unsigned int thread_parameters_size);
    void start(void);
    void start_with_parameters(s_thread_platform_parameters const * platform_parameters, long count);
    void resume(void);
    void wait(void);
    c_thread_wrapper * get_thread(long thread_index);

private:
    static long const k_maximum_crew_size = 16;

    long m_count;
    s_static_array<c_thread_wrapper, k_maximum_crew_size> m_threads;
};
static_assert(sizeof(c_thread_crew) == 0xAB04, "c_thread_crew");

/* ---------- prototypes */

extern unsigned long thread_exception_handler(c_thread_base * thread, s_exception_pointers * exception_pointers, s_exception_information * exception_information);

/* ---------- globals */

/* ---------- public code */

#endif // __THREAD_WRAPPERS_H__
