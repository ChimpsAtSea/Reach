#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\hs\\hs_looper.cpp"
/* ---------- headers */

#include "omaha\hs\hs_looper.h"
#include "omaha\cseries\cseries.h"
#include "omaha\hs\hs.h"
#include "omaha\hs\hs_compile.h"
#include "omaha\hs\hs_runtime.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_hs_looper g_hs_looper;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_hs_looper g_hs_looper; // "?g_hs_looper@@3Vc_hs_looper@@A"

// public: c_hs_looper::c_hs_looper(void);
// public: void c_hs_looper::reinitialize(void);
// public: void c_hs_looper::set_loop_expression(char const *);
// public: void c_hs_looper::clear(void);
// public: void c_hs_looper::game_tick(void);
// public: void c_hs_looper::reboot_loop(void);
// public: void c_hs_looper::handle_thread_delete(long);
// public: void c_hs_looper::restore_from_saved_game(void);
// private: long c_hs_looper::create_suspended_loop_thread(void);
// void hs_looper_setup(char const *);
// void hs_looper_clear(void);
// void hs_looper_handle_thread_delete(long);
// void hs_looper_game_tick(void);
// void hs_looper_reboot(void);
// void hs_looper_reinitialize(void);
// void hs_looper_restore_from_saved_game(void);
// public: bool s_static_string<4096>::is_empty(void) const;
// public: c_static_string<4096>::c_static_string<4096>(char const *);
// public: void s_static_string<4096>::set(char const *);

c_hs_looper::c_hs_looper() :
    m_loop_expression(),
    m_loop_thread_index(NONE)
{
    mangled_ppc("??0c_hs_looper@@QAA@XZ");
};

void c_hs_looper::reinitialize()
{
    mangled_ppc("?reinitialize@c_hs_looper@@QAAXXZ");

    m_loop_thread_index = NONE;
    m_loop_enabled = true;
};

void c_hs_looper::set_loop_expression(char const * new_loop_expression)
{
    mangled_ppc("?set_loop_expression@c_hs_looper@@QAAXPBD@Z");

    clear();
    c_static_string<4096> loop_expression(new_loop_expression);
    m_loop_expression = loop_expression;
    m_loop_enabled = true;
};

void c_hs_looper::clear()
{
    mangled_ppc("?clear@c_hs_looper@@QAAXXZ");

    m_loop_expression.clear();
    if (m_loop_thread_index != NONE)
    {
        hs_thread_try_to_delete(m_loop_thread_index, true);
        m_loop_thread_index = NONE;
    }
};

void c_hs_looper::game_tick()
{
    mangled_ppc("?game_tick@c_hs_looper@@QAAXXZ");

    if (m_loop_thread_index == NONE && m_loop_enabled)
    {
        m_loop_thread_index = create_suspended_loop_thread();
        if (m_loop_thread_index != NONE)
        {
            hs_thread_main(m_loop_thread_index);
        }
    }
};

void c_hs_looper::reboot_loop()
{
    mangled_ppc("?reboot_loop@c_hs_looper@@QAAXXZ");

    m_loop_enabled = true;
};

void c_hs_looper::handle_thread_delete(long thread_index)
{
    mangled_ppc("?handle_thread_delete@c_hs_looper@@QAAXJ@Z");

    if (m_loop_thread_index == thread_index)
    {
        m_loop_thread_index = NONE;
    }
};

void c_hs_looper::restore_from_saved_game()
{
    mangled_ppc("?restore_from_saved_game@c_hs_looper@@QAAXXZ");

    m_loop_thread_index = NONE;
};

long c_hs_looper::create_suspended_loop_thread()
{
    mangled_ppc("?create_suspended_loop_thread@c_hs_looper@@AAAJXZ");

    long loop_thread_index = NONE;
    if (!m_loop_expression.is_empty())
    {
        char valid_loop_expression[4096];
        hs_validify_expression(m_loop_expression, valid_loop_expression, NUMBEROF(valid_loop_expression));
        if (hs_runtime_safe_to_gc())
        {
            hs_node_gc();
        }
        char const * error_message = NULL;
        long loop_expression_index;
        char const * error_source = NULL;
        loop_expression_index = hs_compile_expression(strlen(valid_loop_expression), valid_loop_expression, &error_message, &error_source);
        if (loop_expression_index != NONE)
        {
            long thread_index = hs_thread_new(_hs_thread_type_runtime_evaluate, NONE, false);
            if (thread_index != NONE)
            {
                hs_thread * thread = hs_thread_get(thread_index);
                hs_destination_pointer destination;
                destination.destination_type = _hs_passthrough;
                hs_evaluate(thread_index, loop_expression_index, destination, NULL);
                if (TEST_BIT(thread->flags, _hs_thread_in_function_call_bit))
                {
                    loop_thread_index = thread_index;
                }
                else
                {
                    hs_thread_delete(thread_index, true);
                }
            }
            else
            {
                event_wrapped(_event_critical, "hs_runtime_evaluate: could not allocate thread to execute a command!");
            }
        }
        else if (error_message != NULL)
        {
            hs_compile_source_error(NULL, error_message, error_source, valid_loop_expression);
            m_loop_enabled = false;
        }
    }

    return loop_thread_index;
};

void hs_looper_setup(char const * expression)
{
    mangled_ppc("?hs_looper_setup@@YAXPBD@Z");

    g_hs_looper.set_loop_expression(expression);
};

void hs_looper_clear()
{
    mangled_ppc("?hs_looper_clear@@YAXXZ");

    g_hs_looper.clear();
};

void hs_looper_handle_thread_delete(long thread_index)
{
    mangled_ppc("?hs_looper_handle_thread_delete@@YAXJ@Z");

    g_hs_looper.handle_thread_delete(thread_index);
};

void hs_looper_game_tick()
{
    mangled_ppc("?hs_looper_game_tick@@YAXXZ");

    g_hs_looper.game_tick();
};

void hs_looper_reboot()
{
    mangled_ppc("?hs_looper_reboot@@YAXXZ");

    g_hs_looper.reboot_loop();
};

void hs_looper_reinitialize()
{
    mangled_ppc("?hs_looper_reinitialize@@YAXXZ");

    g_hs_looper.reinitialize();
};

void hs_looper_restore_from_saved_game()
{
    mangled_ppc("?hs_looper_restore_from_saved_game@@YAXXZ");

    g_hs_looper.restore_from_saved_game();
};
