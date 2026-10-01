#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\output\\output_handler.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\output\output_handler.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_static_stack<c_output_handler *, c_output_handler_registry::k_maximum_output_handlers> c_output_handler_registry::g_handlers;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// protected: static class c_static_stack<class c_output_handler *, 8> c_output_handler_registry::g_handlers; // "?g_handlers@c_output_handler_registry@@1V?$c_static_stack@PAVc_output_handler@@$07@@A"

// public: virtual void c_output_handler::handle_output_message(union argb_color const *, char const *, bool);
// public: virtual void c_output_handler::handle_output_message_block_begin(void);
// public: virtual void c_output_handler::handle_output_message_block_end(void);
// public: virtual void c_output_handler::handle_output_error(char const *);
// public: virtual void c_output_handler::handle_output_debug(char const *);
// public: virtual void c_output_handler::handle_output_event(enum e_event_level, char const *, char const *, union rgb_color const *);
// public: virtual bool c_output_handler::provides_console_window(void);
// public: virtual bool c_output_handler::handle_wait_for_keypress(void);
// public: virtual bool c_output_handler::handle_alert(char const *);
// public: virtual enum e_output_user_choice c_output_handler::handle_ask_user_with_timeout(char const *, char const *, enum e_output_user_query, long, enum e_output_user_choice);
// public: static void c_output_handler_registry::attach_handler(class c_output_handler *);
// public: static void c_output_handler_registry::detach_handler(class c_output_handler *);
// public: static bool c_output_handler_registry::active(void);
// public: c_output_handler_iterator::c_output_handler_iterator(void);
// public: class c_output_handler * c_output_handler_iterator::get_first(void);
// public: class c_output_handler * c_output_handler_iterator::get_next(void);
// public: bool c_static_stack<class c_output_handler *, 8>::valid(void) const;
// public: bool c_static_stack<class c_output_handler *, 8>::empty(void) const;
// public: long c_static_stack<class c_output_handler *, 8>::top(void) const;
// public: long c_static_stack<class c_output_handler *, 8>::count(void) const;
// public: void c_static_stack<class c_output_handler *, 8>::push_back(class c_output_handler *const &);
// public: void c_static_stack<class c_output_handler *, 8>::pop(void);
// public: class c_output_handler *& c_static_stack<class c_output_handler *, 8>::operator[](long);
// public: bool c_static_stack<class c_output_handler *, 8>::valid(long) const;
// public: long c_static_stack<class c_output_handler *, 8>::push(void);
// public: class c_output_handler ** c_static_stack<class c_output_handler *, 8>::get(long);
// public: bool c_static_stack<class c_output_handler *, 8>::full(void) const;
// public: c_static_stack<class c_output_handler *, 8>::c_static_stack<class c_output_handler *, 8>(void);

void c_output_handler::handle_output_message(argb_color const * color, char const * message, bool message_is_right_aligned)
{
    mangled_ppc("?handle_output_message@c_output_handler@@UAAXPBTargb_color@@PBD_N@Z");
};

void c_output_handler::handle_output_message_block_begin()
{
    mangled_ppc("?handle_output_message_block_begin@c_output_handler@@UAAXXZ");
};

void c_output_handler::handle_output_message_block_end()
{
    mangled_ppc("?handle_output_message_block_end@c_output_handler@@UAAXXZ");
};

void c_output_handler::handle_output_error(char const * error_string)
{
    mangled_ppc("?handle_output_error@c_output_handler@@UAAXPBD@Z");
};

void c_output_handler::handle_output_debug(char const * debug_string)
{
    mangled_ppc("?handle_output_debug@c_output_handler@@UAAXPBD@Z");
};

void c_output_handler::handle_output_event(e_event_level event_level, char const * event_category, char const * event_string, rgb_color const * event_color)
{
    mangled_ppc("?handle_output_event@c_output_handler@@UAAXW4e_event_level@@PBD1PBTrgb_color@@@Z");
};

bool c_output_handler::provides_console_window()
{
    mangled_ppc("?provides_console_window@c_output_handler@@UAA_NXZ");

    return false;
};

bool c_output_handler::handle_wait_for_keypress()
{
    mangled_ppc("?handle_wait_for_keypress@c_output_handler@@UAA_NXZ");

    return false;
};

bool c_output_handler::handle_alert(char const * alert_string)
{
    mangled_ppc("?handle_alert@c_output_handler@@UAA_NPBD@Z");

    return false;
};

e_output_user_choice c_output_handler::handle_ask_user_with_timeout(char const * title, char const * message, e_output_user_query query_type, long timeout_milliseconds, e_output_user_choice timeout_choice)
{
    mangled_ppc("?handle_ask_user_with_timeout@c_output_handler@@UAA?AW4e_output_user_choice@@PBD0W4e_output_user_query@@JW42@@Z");

    return _output_user_choice_none;
};

void c_output_handler_registry::attach_handler(c_output_handler * handler)
{
    mangled_ppc("?attach_handler@c_output_handler_registry@@SAXPAVc_output_handler@@@Z");

    assert_tag_debug_untracked_jul_11_2011(88, handler);

    g_handlers.push_back(handler);
};

void c_output_handler_registry::detach_handler(c_output_handler * handler)
{
    mangled_ppc("?detach_handler@c_output_handler_registry@@SAXPAVc_output_handler@@@Z");

    bool found = false;

    assert_tag_debug_untracked_jul_11_2011(97, handler);
    assert_tag_debug_untracked_jul_11_2011(98, g_handlers.valid());

    for (long index = 0; index < g_handlers.count(); index++)
    {
        if (g_handlers[index] == handler)
        {
            if (index != g_handlers.top())
            {
                g_handlers[index] = g_handlers[g_handlers.top()];
            }

            g_handlers.pop();
            found = true;
            break;
        }
    }

    dassert_tag_debug_untracked_jul_11_2011(114, found, "can't detach a handler that was never attached");
};

bool c_output_handler_registry::active()
{
    mangled_ppc("?active@c_output_handler_registry@@SA_NXZ");

    return !g_handlers.empty();
};

c_output_handler_iterator::c_output_handler_iterator() :
    m_index(-1)
{
    mangled_ppc("??0c_output_handler_iterator@@QAA@XZ");
};

c_output_handler * c_output_handler_iterator::get_first()
{
    mangled_ppc("?get_first@c_output_handler_iterator@@QAAPAVc_output_handler@@XZ");

    m_index = 0;

    return get_next();
};

c_output_handler * c_output_handler_iterator::get_next()
{
    mangled_ppc("?get_next@c_output_handler_iterator@@QAAPAVc_output_handler@@XZ");

    c_output_handler * handler = NULL;

    dassert_tag_debug_untracked_jul_11_2011(143, m_index >= 0, "must call get_first() before get_next()");
    assert_tag_debug_untracked_jul_11_2011(144, c_output_handler_registry::g_handlers.valid());

    if (m_index < c_output_handler_registry::g_handlers.count())
    {
        long index = m_index++;
        handler = c_output_handler_registry::g_handlers[index];
        assert_tag_debug_untracked_jul_11_2011(150, handler);
    }

    return handler;
};
