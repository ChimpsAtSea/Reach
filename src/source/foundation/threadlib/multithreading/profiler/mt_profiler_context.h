#pragma once
#ifndef __MT_PROFILER_CONTEXT_H__
#define __MT_PROFILER_CONTEXT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\synchronized_value_windows.h"
#include "foundation\baselib\multithreading\datatypes\initialization_container.h"
#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"

/* ---------- constants */

/* ---------- definitions */

namespace mt_profiler_internal
{
    long const k_context_buffer_count = 2;
    long const k_context_buffer_bits = 11;
    long const k_contexts_per_buffer = 1 << k_context_buffer_bits;
    unsigned long const k_max_thread_stacks = 32;
    unsigned long const k_max_stack_depth = 128;

    struct s_mt_context
    {
        void set_depth(unsigned char new_depth);
        void set_wrapped(unsigned char new_wrapped);
        unsigned char get_depth(void);
        unsigned char get_wrapped(void);

        long start_time;
        long end_time;
        long hw_counter;
        unsigned short profiler_index;
        unsigned char depth : 6;
        unsigned char wrapped : 2;
        unsigned char thread_index;
    };
    static_assert(sizeof(s_mt_context) == 0x10, "s_mt_context");

    class c_context_stack
    {
    public:
        void initialize(void);
        void set_thread_id(unsigned long thread_id);
        unsigned long get_thread_id(void);
        void push(s_mt_context * context);
        s_mt_context * pop(void);
        unsigned long get_hw_thread(void);
        unsigned char get_depth(void);
        e_mt_profiler_mode get_mode(void);
        void set_mode(e_mt_profiler_mode mode);
        unsigned char get_max_depth(void);
        void set_max_depth(unsigned long max_depth);
        void decay_depth(void);
        s_mt_context ** get_stack_ptr(void);

    private:
        s_mt_context * m_stack[k_max_stack_depth];
        unsigned long m_thread_id;
        unsigned short m_depth;
        unsigned short m_max_depth;
        unsigned long m_hw_thread;
        e_mt_profiler_mode m_mode;
    };
    static_assert(sizeof(c_context_stack) == 0x210, "c_context_stack");

    class c_context_stack_manager
    {
    public:
        c_context_stack_manager(void);
        ~c_context_stack_manager(void);

        void initialize(void);
        void set_hw_mode(unsigned long hw_mode);
        c_context_stack * get_free(void);
        c_context_stack * get_details(unsigned long & count);

        static c_context_stack_manager m_internal_instance;

    private:
        c_context_stack m_stacks[k_max_thread_stacks];
        c_synchronized_int32 m_used_count;
        unsigned long m_hw_mode;
    };
    static_assert(sizeof(c_context_stack_manager) == 0x4208, "c_context_stack_manager");

    extern s_mt_context global_contexts[k_context_buffer_count][k_contexts_per_buffer];
    extern __int64 g_framestart_time;
    extern __int64 g_framestart_counter[6];
    extern __int64 g_frame_number;
    extern __int64 g_vsync_cycles;
    extern c_synchronized_int32 current_context_index;
    extern t_initialization_container<c_context_stack_manager *> g_context_stack_man;
    extern __declspec(thread) c_context_stack * g_context_stack_def;

    extern s_mt_context * get_free_context(void);
    extern void context_stack_setup(c_context_stack_manager ** manager);
    extern c_context_stack_manager * get_context_stack_manager(void);
    extern c_context_stack * get_context_stack(void);
    extern unsigned char get_thread_index(unsigned long thread_id);
    extern long get_current_time_index(void);
    extern __int64 get_hw_counter(unsigned long hw_thread, e_mt_profiler_mode mode);
    extern long get_current_hw_counter_offset(unsigned long hw_thread, e_mt_profiler_mode mode);
    extern float get_user_hw(long hw_counter, float duration);
    extern void start_context(unsigned short profiler_index);
    extern void end_context(unsigned short profiler_index);
    extern void set_vsync_point(void);
    extern void start_frame(void);
}

class c_mtp_profiler_context
{
public:
    c_mtp_profiler_context(unsigned short profiler_index);
    ~c_mtp_profiler_context();

private:
    unsigned short m_profiler_index;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MT_PROFILER_CONTEXT_H__

