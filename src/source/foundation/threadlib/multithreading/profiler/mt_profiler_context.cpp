#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\multithreading\\profiler\\mt_profiler_context.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\profiler\mt_profiler_context.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\system_time_windows.h"
#include "baselib\thread_manipulation.h"

#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

mt_profiler_internal::s_mt_context mt_profiler_internal::global_contexts[k_context_buffer_count][k_contexts_per_buffer];
__int64 mt_profiler_internal::g_framestart_time;
__int64 mt_profiler_internal::g_framestart_counter[6];
__int64 mt_profiler_internal::g_frame_number;
__int64 mt_profiler_internal::g_vsync_cycles;
c_synchronized_int32 mt_profiler_internal::current_context_index(0);
mt_profiler_internal::c_context_stack_manager mt_profiler_internal::c_context_stack_manager::m_internal_instance;
t_initialization_container<mt_profiler_internal::c_context_stack_manager *> mt_profiler_internal::g_context_stack_man;
__declspec(thread) mt_profiler_internal::c_context_stack * mt_profiler_internal::g_context_stack_def;
static float g_user_hw_history[120];
static unsigned long g_user_hw_history_index;
static long g_history_reset_count;
static e_mt_profiler_mode g_last_mode;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct mt_profiler_internal::s_mt_context (*mt_profiler_internal::global_contexts)[2048]; // "?global_contexts@mt_profiler_internal@@3PAY0IAA@Us_mt_context@1@A"
// __int64mt_profiler_internal::g_framestart_time; // "?g_framestart_time@mt_profiler_internal@@3_JA"
// __int64*mt_profiler_internal::g_framestart_counter; // "?g_framestart_counter@mt_profiler_internal@@3PA_JA"
// __int64mt_profiler_internal::g_frame_number; // "?g_frame_number@mt_profiler_internal@@3_JA"
// __int64mt_profiler_internal::g_vsync_cycles; // "?g_vsync_cycles@mt_profiler_internal@@3_JA"
// class c_synchronized_int32mt_profiler_internal::current_context_index; // "?current_context_index@mt_profiler_internal@@3Vc_synchronized_int32@@A"
// public: static class mt_profiler_internal::c_context_stack_manager mt_profiler_internal::c_context_stack_manager::m_internal_instance; // "?m_internal_instance@c_context_stack_manager@mt_profiler_internal@@2V12@A"
// class t_initialization_container<class mt_profiler_internal::c_context_stack_manager *> mt_profiler_internal::g_context_stack_man; // "?g_context_stack_man@mt_profiler_internal@@3V?$t_initialization_container@PAVc_context_stack_manager@mt_profiler_internal@@@@A"
// class mt_profiler_internal::c_context_stack *mt_profiler_internal::g_context_stack_def; // "?g_context_stack_def@mt_profiler_internal@@3PAVc_context_stack@1@A"

// struct mt_profiler_internal::s_mt_context * mt_profiler_internal::get_free_context(void);
// void mt_profiler_internal::context_stack_setup(class mt_profiler_internal::c_context_stack_manager **);
// public: void mt_profiler_internal::c_context_stack_manager::initialize(void);
// public: void mt_profiler_internal::c_context_stack::initialize(void);
// public: void mt_profiler_internal::c_context_stack_manager::set_hw_mode(unsigned long);
// class mt_profiler_internal::c_context_stack_manager * mt_profiler_internal::get_context_stack_manager(void);
// class mt_profiler_internal::c_context_stack * mt_profiler_internal::get_context_stack(void);
// public: void mt_profiler_internal::c_context_stack::set_thread_id(unsigned long);
// public: class mt_profiler_internal::c_context_stack * mt_profiler_internal::c_context_stack_manager::get_free(void);
// unsigned char mt_profiler_internal::get_thread_index(unsigned long);
// public: unsigned long mt_profiler_internal::c_context_stack::get_thread_id(void);
// public: class mt_profiler_internal::c_context_stack * mt_profiler_internal::c_context_stack_manager::get_details(unsigned long &);
// long mt_profiler_internal::get_current_time_index(void);
// __int64 mt_profiler_internal::get_hw_counter(unsigned long, enum e_mt_profiler_mode);
// long mt_profiler_internal::get_current_hw_counter_offset(unsigned long, enum e_mt_profiler_mode);
// float mt_profiler_internal::get_user_hw(long, float);
// void mt_profiler_internal::start_context(unsigned short);
// public: void mt_profiler_internal::s_mt_context::set_depth(unsigned char);
// public: void mt_profiler_internal::s_mt_context::set_wrapped(unsigned char);
// public: void mt_profiler_internal::c_context_stack::push(struct mt_profiler_internal::s_mt_context *);
// public: unsigned long mt_profiler_internal::c_context_stack::get_hw_thread(void);
// public: unsigned char mt_profiler_internal::c_context_stack::get_depth(void);
// public: enum e_mt_profiler_mode mt_profiler_internal::c_context_stack::get_mode(void);
// void mt_profiler_internal::end_context(unsigned short);
// public: struct mt_profiler_internal::s_mt_context * mt_profiler_internal::c_context_stack::pop(void);
// void mt_profiler_internal::set_vsync_point(void);
// void mt_profiler_internal::start_frame(void);
// public: void s_storage_context::set_start(float);
// public: unsigned short s_storage_context::encode(float);
// public: void s_storage_context::set_end(float);
// public: unsigned char mt_profiler_internal::s_mt_context::get_depth(void);
// public: unsigned char mt_profiler_internal::s_mt_context::get_wrapped(void);
// public: unsigned char mt_profiler_internal::c_context_stack::get_max_depth(void);
// public: void mt_profiler_internal::c_context_stack::set_max_depth(unsigned long);
// public: void mt_profiler_internal::c_context_stack::decay_depth(void);
// public: void mt_profiler_internal::c_context_stack::set_mode(enum e_mt_profiler_mode);
// public: struct mt_profiler_internal::s_mt_context ** mt_profiler_internal::c_context_stack::get_stack_ptr(void);
// ?get@?$t_initialization_container@PAVc_context_stack_manager@mt_profiler_internal@@@@QAAPBQAVc_context_stack_manager@mt_profiler_internal@@Q6AXPAPAV23@@Z@Z;
// public: mt_profiler_internal::c_context_stack_manager::c_context_stack_manager(void);
// public: t_initialization_container<class mt_profiler_internal::c_context_stack_manager *>::t_initialization_container<class mt_profiler_internal::c_context_stack_manager *>(void);
// public: mt_profiler_internal::c_context_stack_manager::~c_context_stack_manager(void);
// public: t_initialization_container<class mt_profiler_internal::c_context_stack_manager *>::~t_initialization_container<class mt_profiler_internal::c_context_stack_manager *>(void);
// void mt_profiler_internal::current_context_index::`dynamic atexit destructor'(void);
// ??__F?m_internal_instance@c_context_stack_manager@mt_profiler_internal@@2V12@A@@YAXXZ;
// void mt_profiler_internal::g_context_stack_man::`dynamic atexit destructor'(void);

mt_profiler_internal::s_mt_context * mt_profiler_internal::get_free_context(void)
{
    mangled_ppc("?get_free_context@mt_profiler_internal@@YAPAUs_mt_context@1@XZ");

    while (current_context_index < 0)
    {
    }

    long context_index;
    long buffer_index;
    {
        long index = current_context_index.increment() - 1;
        context_index = index & (k_contexts_per_buffer - 1);
        buffer_index = (index >> k_context_buffer_bits) & 1;
    }

    return &global_contexts[buffer_index][context_index];
};

void mt_profiler_internal::context_stack_setup(c_context_stack_manager ** manager)
{
    mangled_ppc("?context_stack_setup@mt_profiler_internal@@YAXPAPAVc_context_stack_manager@1@@Z");

    c_context_stack_manager::m_internal_instance.initialize();
    *manager = &c_context_stack_manager::m_internal_instance;
};

void mt_profiler_internal::c_context_stack_manager::initialize(void)
{
    mangled_ppc("?initialize@c_context_stack_manager@mt_profiler_internal@@QAAXXZ");

    m_used_count.set(0);
    for (unsigned long stack_index = 0; stack_index < k_max_thread_stacks; stack_index++)
    {
        m_stacks[stack_index].initialize();
    }

    m_hw_mode = 2;
    set_hw_mode(0);
};

void mt_profiler_internal::c_context_stack::initialize(void)
{
    mangled_ppc("?initialize@c_context_stack@mt_profiler_internal@@QAAXXZ");

    m_depth = 0;
    m_max_depth = 0;
    m_mode = _mt_profiler_mode_none;
    m_hw_thread = 0;
};

void mt_profiler_internal::c_context_stack_manager::set_hw_mode(unsigned long hw_mode)
{
    mangled_ppc("?set_hw_mode@c_context_stack_manager@mt_profiler_internal@@QAAXK@Z");

    ePMCSetup setup = PMC_SETUP_TLBS;
    if (hw_mode == 1)
    {
        setup = PMC_SETUP_OVERVIEW_6THREADS;
    }

    if (m_hw_mode != hw_mode)
    {
        if (m_hw_mode < 2)
        {
            DmPMCStop();
        }

        DmPMCInstallSetup(setup);
        DmPMCResetCounters();
        DmPMCSetTriggerProcessor(GetCurrentProcessorNumber() / 2);
        DmPMCStart();
    }
};

mt_profiler_internal::c_context_stack_manager * mt_profiler_internal::get_context_stack_manager(void)
{
    mangled_ppc("?get_context_stack_manager@mt_profiler_internal@@YAPAVc_context_stack_manager@1@XZ");

    return *g_context_stack_man.get(context_stack_setup);
};

// $TODO nonmatching: TLS slot offset (li 0x61c) is resolved by the linker in the target
mt_profiler_internal::c_context_stack * mt_profiler_internal::get_context_stack(void)
{
    mangled_ppc("?get_context_stack@mt_profiler_internal@@YAPAVc_context_stack@1@XZ");

    if (g_context_stack_def == NULL)
    {
        g_context_stack_def = get_context_stack_manager()->get_free();
        g_context_stack_def->set_thread_id(thread_get_current_thread_user_index());
    }

    return g_context_stack_def;
};

void mt_profiler_internal::c_context_stack::set_thread_id(unsigned long thread_id)
{
    mangled_ppc("?set_thread_id@c_context_stack@mt_profiler_internal@@QAAXK@Z");

    m_thread_id = thread_id;
    m_hw_thread = GetCurrentProcessorNumber();
};

mt_profiler_internal::c_context_stack * mt_profiler_internal::c_context_stack_manager::get_free(void)
{
    mangled_ppc("?get_free@c_context_stack_manager@mt_profiler_internal@@QAAPAVc_context_stack@2@XZ");

    unsigned long use = m_used_count.increment() - 1;
    assert_tag_debug_untracked_jul_11_2011(277, use < k_max_thread_stacks);

    return &m_stacks[use];
};

unsigned char mt_profiler_internal::get_thread_index(unsigned long thread_id)
{
    mangled_ppc("?get_thread_index@mt_profiler_internal@@YAEK@Z");

    unsigned long stack_count = 0;
    {
        c_context_stack * stacks = get_context_stack_manager()->get_details(stack_count);
        for (unsigned long stack_index = 0; stack_index < stack_count; stack_index++)
        {
            if (stacks[stack_index].get_thread_id() == thread_id)
            {
                return static_cast<unsigned char>(stack_index);
            }
        }
    }

    return 0xFF;
};

unsigned long mt_profiler_internal::c_context_stack::get_thread_id(void)
{
    mangled_ppc("?get_thread_id@c_context_stack@mt_profiler_internal@@QAAKXZ");

    return m_thread_id;
};

mt_profiler_internal::c_context_stack * mt_profiler_internal::c_context_stack_manager::get_details(unsigned long & count)
{
    mangled_ppc("?get_details@c_context_stack_manager@mt_profiler_internal@@QAAPAVc_context_stack@2@AAK@Z");

    count = m_used_count;
    return m_stacks;
};

long mt_profiler_internal::get_current_time_index(void)
{
    mangled_ppc("?get_current_time_index@mt_profiler_internal@@YAJXZ");

    __int64 current_time = system_performance_timer_get();
    return static_cast<long>(current_time - g_framestart_time);
};

__int64 mt_profiler_internal::get_hw_counter(unsigned long hw_thread, e_mt_profiler_mode mode)
{
    mangled_ppc("?get_hw_counter@mt_profiler_internal@@YA_JKW4e_mt_profiler_mode@@@Z");

    __int64 counter = 0;
    if (mode == _mt_profiler_mode_1)
    {
        unsigned long value;
        DmPMCGetCounter((hw_thread >> 1) + 8, &value);
        counter = value;
    }
    if (mode == _mt_profiler_mode_2)
    {
        unsigned long value;
        DmPMCGetCounter(6, &value);
        counter = value;
    }
    if (mode == _mt_profiler_mode_3)
    {
        unsigned long value;
        DmPMCGetCounter(hw_thread << 1, &value);
        counter = value;
    }

    return counter;
};

long mt_profiler_internal::get_current_hw_counter_offset(unsigned long hw_thread, e_mt_profiler_mode mode)
{
    mangled_ppc("?get_current_hw_counter_offset@mt_profiler_internal@@YAJKW4e_mt_profiler_mode@@@Z");

    __int64 counter = get_hw_counter(hw_thread, mode);
    return static_cast<long>(counter - g_framestart_counter[hw_thread]);
};

float mt_profiler_internal::get_user_hw(long hw_counter, float duration)
{
    mangled_ppc("?get_user_hw@mt_profiler_internal@@YAMJM@Z");

    if (duration > 0.001f)
    {
        return hw_counter / duration;
    }

    return 0.0f;
};

void mt_profiler_internal::start_context(unsigned short profiler_index)
{
    mangled_ppc("?start_context@mt_profiler_internal@@YAXG@Z");

    s_mt_context * context = get_free_context();
    context->thread_index = static_cast<unsigned char>(thread_get_current_thread_user_index());
    context->start_time = get_current_time_index();
    context->end_time = context->start_time;
    context->hw_counter = get_current_hw_counter_offset(get_context_stack()->get_hw_thread(), get_context_stack()->get_mode());
    context->profiler_index = profiler_index;
    context->set_depth(get_context_stack()->get_depth());
    context->set_wrapped(0);
    get_context_stack()->push(context);
};

void mt_profiler_internal::s_mt_context::set_depth(unsigned char new_depth)
{
    mangled_ppc("?set_depth@s_mt_context@mt_profiler_internal@@QAAXE@Z");

    depth = new_depth;
};

void mt_profiler_internal::s_mt_context::set_wrapped(unsigned char new_wrapped)
{
    mangled_ppc("?set_wrapped@s_mt_context@mt_profiler_internal@@QAAXE@Z");

    wrapped = new_wrapped;
};

void mt_profiler_internal::c_context_stack::push(s_mt_context * context)
{
    mangled_ppc("?push@c_context_stack@mt_profiler_internal@@QAAXPAUs_mt_context@2@@Z");

    if (m_depth < NUMBEROF(m_stack))
    {
        m_stack[m_depth] = context;
        m_depth++;
    }
};

unsigned long mt_profiler_internal::c_context_stack::get_hw_thread(void)
{
    mangled_ppc("?get_hw_thread@c_context_stack@mt_profiler_internal@@QAAKXZ");

    return m_hw_thread;
};

unsigned char mt_profiler_internal::c_context_stack::get_depth(void)
{
    mangled_ppc("?get_depth@c_context_stack@mt_profiler_internal@@QAAEXZ");

    return static_cast<unsigned char>(m_depth);
};

e_mt_profiler_mode mt_profiler_internal::c_context_stack::get_mode(void)
{
    mangled_ppc("?get_mode@c_context_stack@mt_profiler_internal@@QAA?AW4e_mt_profiler_mode@@XZ");

    return m_mode;
};

void mt_profiler_internal::end_context(unsigned short profiler_index)
{
    mangled_ppc("?end_context@mt_profiler_internal@@YAXG@Z");

    s_mt_context * context = get_context_stack()->pop();
    if (context != NULL)
    {
        context->end_time = get_current_time_index();
        context->hw_counter = get_current_hw_counter_offset(get_context_stack()->get_hw_thread(), get_context_stack()->get_mode()) - context->hw_counter;
    }
};

mt_profiler_internal::s_mt_context * mt_profiler_internal::c_context_stack::pop(void)
{
    mangled_ppc("?pop@c_context_stack@mt_profiler_internal@@QAAPAUs_mt_context@2@XZ");

    s_mt_context * context = NULL;
    if (m_depth > 0)
    {
        m_depth--;
        context = m_stack[m_depth];
    }

    return context;
};

void mt_profiler_internal::set_vsync_point(void)
{
    mangled_ppc("?set_vsync_point@mt_profiler_internal@@YAXXZ");

    g_vsync_cycles = system_performance_timer_get();
};

// note: this compiler orders a scope's locals by identifier hash rather than declaration order,
// so the local names and the extra blocks below reproduce the original stack layout
void mt_profiler_internal::start_frame(void)
{
    mangled_ppc("?start_frame@mt_profiler_internal@@YAXXZ");

    long time_index = get_current_time_index();
    float frame_ms = static_cast<float>(time_index) / static_cast<float>(system_performance_timer_frequency() / 1000);
    if (frame_ms < 0.0f)
    {
        g_framestart_time = system_performance_timer_get();
    }

    if (frame_ms > 16.0f)
    {
        e_mt_profiler_mode mode = mt_profiler_get_mode();
        if (mode != g_last_mode)
        {
            g_history_reset_count = 5;
            g_last_mode = mode;
            get_context_stack_manager()->set_hw_mode(mode == _mt_profiler_mode_3);
        }

        long packed_value = current_context_index;
        current_context_index.set(-1);
        long front_buffer = (packed_value >> k_context_buffer_bits) & 1;
        long back_buffer = (front_buffer + 1) & 1;
        long new_write_index = 0;

        {
            unsigned long stack_count = 0;
            c_context_stack * thread_stacks = get_context_stack_manager()->get_details(stack_count);
            for (unsigned long stack_index = 0; stack_index < stack_count; stack_index++)
            {
                s_mt_context ** stack_ptr;
                c_context_stack * stack = &thread_stacks[stack_index];
                long depth = stack->get_depth();
                stack_ptr = stack->get_stack_ptr();
                if (depth != 0)
                {
                    for (long depth_index = 0; depth_index < depth; depth_index++)
                    {
                        s_mt_context * destination = &global_contexts[back_buffer][new_write_index];
                        s_mt_context * source = stack_ptr[depth_index];
                        source->end_time = get_current_time_index();
                        source->hw_counter = get_current_hw_counter_offset(stack->get_hw_thread(), mode) - source->hw_counter;
                        *destination = *source;
                        destination->set_wrapped(1);
                        source->set_wrapped(2);
                        destination->start_time = 0;
                        destination->hw_counter = 0;
                        stack_ptr[depth_index] = destination;
                        new_write_index++;
                    }
                }
            }
        }

        long restart_index = (back_buffer << k_context_buffer_bits) | (new_write_index & (k_contexts_per_buffer - 1));
        long used_count = packed_value & (k_contexts_per_buffer - 1);
        if (used_count != 0)
        {
            unsigned long thread_count = 0;
            c_context_stack * thread_stacks = get_context_stack_manager()->get_details(thread_count);
            s_profiler_frame_header * frame = profiler_storage_request(used_count, thread_count);
            if (frame != NULL)
            {
                float max_end_time;
                float min_start_time;
                s_storage_thread * thread_storage;
                {
                    float max_hw = 0.0f;
                    s_storage_context * frame_context = frame->get_context_ptr();
                    thread_storage = frame->get_thread_ptr();
                    max_end_time = 0.0f;
                    min_start_time = 100000.0f;
                    unsigned long max_thread = 0;

                    for (unsigned long thread_index = 0; thread_index < thread_count; thread_index++)
                    {
                        thread_stacks[thread_index].set_mode(mode);
                        thread_stacks[thread_index].decay_depth();
                        thread_storage[thread_index].thread_id = thread_stacks[thread_index].get_thread_id();
                        thread_storage[thread_index].depth = 0;
                        thread_storage[thread_index].unknown_C = 0;
                        thread_storage[thread_index].hw_thread = thread_stacks[thread_index].get_hw_thread();
                    }

                    {
                        s_mt_context * context = global_contexts[front_buffer];
                        for (long context_index = 0; context_index < used_count; context_index++)
                        {
                            float context_start = static_cast<float>(context->start_time) / static_cast<float>(system_performance_timer_frequency() / 1000);
                            float context_end = static_cast<float>(context->end_time) / static_cast<float>(system_performance_timer_frequency() / 1000);
                            if (context_end > max_end_time)
                            {
                                max_end_time = context_end;
                            }
                            if (min_start_time > context_start)
                            {
                                min_start_time = context_start;
                            }
                            float duration = context_end - context_start;

                            frame_context->set_start(context_start);
                            frame_context->set_end(context_end);
                            frame_context->depth = context->get_depth();
                            frame_context->wrapped = context->get_wrapped();
                            frame_context->profiler_index = context->profiler_index;
                            frame_context->thread_index = get_thread_index(context->thread_index);
                            frame_context->user_hw = get_user_hw(context->hw_counter, duration);
                            if (frame_context->wrapped == 0 && frame_context->user_hw > max_hw)
                            {
                                max_hw = frame_context->user_hw;
                            }
                            if (max_thread < context->thread_index)
                            {
                                max_thread = context->thread_index;
                            }
                            if (thread_storage[frame_context->thread_index].depth < context->get_depth())
                            {
                                thread_storage[frame_context->thread_index].depth = context->get_depth();
                            }

                            frame_context++;
                            context++;
                        }

                        context = global_contexts[front_buffer];
                        frame_context = frame->get_context_ptr();

                        {
                            for (unsigned long thread_index = 0; thread_index < thread_count; thread_index++)
                            {
                                if (thread_storage[thread_index].depth > thread_stacks[thread_index].get_max_depth())
                                {
                                    thread_stacks[thread_index].set_max_depth(thread_storage[thread_index].depth);
                                }
                            }

                            unsigned long row_offset = 0;
                            for (unsigned long thread_id = 0; thread_id <= max_thread; thread_id++)
                            {
                                for (unsigned long thread_index = 0; thread_index < thread_count; thread_index++)
                                {
                                    if (thread_storage[thread_index].thread_id == thread_id)
                                    {
                                        unsigned long max_depth = thread_stacks[thread_index].get_max_depth();
                                        thread_storage[thread_index].depth = row_offset;
                                        row_offset += max_depth + 2;
                                    }
                                }
                            }
                        }
                    }

                    g_user_hw_history[g_user_hw_history_index] = max_hw;
                    g_user_hw_history_index = (g_user_hw_history_index + 1) % NUMBEROF(g_user_hw_history);

                    float average = 0.0f;
                    for (unsigned long history_index = 0; history_index < NUMBEROF(g_user_hw_history); history_index++)
                    {
                        average += g_user_hw_history[history_index];
                    }
                    average /= 120.0f;

                    if (g_history_reset_count > 0)
                    {
                        for (unsigned long history_index = 0; history_index < NUMBEROF(g_user_hw_history); history_index++)
                        {
                            g_user_hw_history[history_index] = max_hw;
                        }
                        g_history_reset_count--;
                    }

                    frame->max_end_time = max_end_time;
                    frame->start_time = g_framestart_time;
                    frame->end_time = system_performance_timer_get();
                    frame->frame_number = g_frame_number;
                    frame->vsync_cycles = g_vsync_cycles;
                    frame->average_user_hw = average > 0.01f ? average : 1.0f;
                    g_framestart_time = system_performance_timer_get();
                }

                float scaled_value = 0.0f;
                float cycles_per_sec = 3200000000.0f;
                __int64 hw_counters[k_profiler_hw_counter_count] = { 0 };
                for (unsigned long counter_index = 0; counter_index < k_profiler_hw_counter_count; counter_index++)
                {
                    __int64 counter = get_hw_counter(counter_index, mode);
                    hw_counters[counter_index] = counter - g_framestart_counter[counter_index];
                    g_framestart_counter[counter_index] = counter;
                }

                if (mode == _mt_profiler_mode_2)
                {
                    hw_counters[0] *= 25;
                    frame->hw_counters[0] = hw_counters[0] / cycles_per_sec;
                }
                if (mode == _mt_profiler_mode_1)
                {
                    hw_counters[0] *= 610;
                    hw_counters[2] *= 610;
                    hw_counters[4] *= 610;
                    frame->hw_counters[0] = hw_counters[0] / cycles_per_sec;
                    frame->hw_counters[1] = hw_counters[2] / cycles_per_sec;
                    frame->hw_counters[2] = hw_counters[4] / cycles_per_sec;
                }
                if (mode == _mt_profiler_mode_3)
                {
                    __int64 elapsed = frame->end_time - frame->start_time;
                    elapsed *= static_cast<__int64>(cycles_per_sec);
                    elapsed /= system_performance_timer_frequency();
                    for (unsigned long counter_index = 0; counter_index < k_profiler_hw_counter_count; counter_index++)
                    {
                        scaled_value = static_cast<float>(hw_counters[counter_index]);
                        scaled_value /= static_cast<float>(elapsed);
                        frame->hw_counters[counter_index] = scaled_value;
                    }
                }

                profiler_publish_frame(frame);
            }
        }

        current_context_index.set(restart_index);
        g_frame_number++;
    }
};

unsigned char mt_profiler_internal::s_mt_context::get_depth(void)
{
    mangled_ppc("?get_depth@s_mt_context@mt_profiler_internal@@QAAEXZ");

    return depth;
};

unsigned char mt_profiler_internal::s_mt_context::get_wrapped(void)
{
    mangled_ppc("?get_wrapped@s_mt_context@mt_profiler_internal@@QAAEXZ");

    return wrapped;
};

unsigned char mt_profiler_internal::c_context_stack::get_max_depth(void)
{
    mangled_ppc("?get_max_depth@c_context_stack@mt_profiler_internal@@QAAEXZ");

    return static_cast<unsigned char>(m_max_depth >> 8);
};

void mt_profiler_internal::c_context_stack::set_max_depth(unsigned long max_depth)
{
    mangled_ppc("?set_max_depth@c_context_stack@mt_profiler_internal@@QAAXK@Z");

    m_max_depth = static_cast<unsigned short>(max_depth << 8);
};

void mt_profiler_internal::c_context_stack::decay_depth(void)
{
    mangled_ppc("?decay_depth@c_context_stack@mt_profiler_internal@@QAAXXZ");

    if (m_max_depth > 0)
    {
        m_max_depth--;
    }
};

void mt_profiler_internal::c_context_stack::set_mode(e_mt_profiler_mode mode)
{
    mangled_ppc("?set_mode@c_context_stack@mt_profiler_internal@@QAAXW4e_mt_profiler_mode@@@Z");

    m_mode = mode;
};

mt_profiler_internal::s_mt_context ** mt_profiler_internal::c_context_stack::get_stack_ptr(void)
{
    mangled_ppc("?get_stack_ptr@c_context_stack@mt_profiler_internal@@QAAPAPAUs_mt_context@2@XZ");

    return m_stack;
};

mt_profiler_internal::c_context_stack_manager::c_context_stack_manager(void)
{
    mangled_ppc("??0c_context_stack_manager@mt_profiler_internal@@QAA@XZ");
};

mt_profiler_internal::c_context_stack_manager::~c_context_stack_manager(void)
{
    mangled_ppc("??1c_context_stack_manager@mt_profiler_internal@@QAA@XZ");
};

