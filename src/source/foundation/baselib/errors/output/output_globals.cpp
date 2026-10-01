#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\output\\output_globals.cpp"
/* ---------- headers */

#include <stdarg.h>
#include "foundation\baselib\errors\output\output_globals.h"
#include "foundation\baselib\errors\output\output_handler.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void output_message_internal(argb_color const * color, s_static_string<16384> * message, bool message_is_right_aligned);

/* ---------- globals */

static bool g_output_route_to_default_handler = true;
static c_default_output_handler g_default_output_handler;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_string<16384>::k_index_not_found; // "?k_index_not_found@?$s_static_string@$0EAAA@@@2JB"
// public: static long const s_static_string<16384>::k_element_count; // "?k_element_count@?$s_static_string@$0EAAA@@@2JB"

// void output_route_to_default_handler(bool);
// void output_message(char const *, ...);
// void output_message_string(char const *, ...);
// void output_message_color(union argb_color const *, char const *, ...);
// void output_message_block_begin(void);
// void output_message_block_end(void);
// void output_error(char const *, ...);
// void output_debug(char const *, ...);
// void output_debug_string(char const *);
// void output_event(enum e_event_level, char const *, char const *, union rgb_color const *);
// bool output_wait_for_keypress(void);
// void output_alert(char const *);
// bool output_has_console_window(void);
// enum e_output_user_choice output_ask_user(char const *, char const *, enum e_output_user_query);
// enum e_output_user_choice output_ask_user_with_timeout(char const *, char const *, enum e_output_user_query, long, enum e_output_user_choice);
// void output_message_internal(union argb_color const *, class s_static_string<16384> *, bool);
// public: char const * s_static_string<16384>::append(char const *);
// public: void s_static_string<16384>::print_va(char const *, char *);
// public: char const * s_static_string<16384>::get_string(void) const;
// public: c_default_output_handler::c_default_output_handler(void);

void output_route_to_default_handler(bool route)
{
    mangled_ppc("?output_route_to_default_handler@@YAX_N@Z");

    g_output_route_to_default_handler = route;
};

void output_message(char const * format, ...)
{
    mangled_ppc("?output_message@@YAXPBDZZ");

    s_static_string<16384> message;

    {
        va_list arglist;
        va_start(arglist, format);
        message.print_va(format, arglist);
        va_end(arglist);
    }

    output_message_internal(NULL, &message, true);
};

void output_message_string(char const * format, ...)
{
    mangled_ppc("?output_message_string@@YAXPBDZZ");

    s_static_string<16384> message;

    {
        va_list arglist;
        va_start(arglist, format);
        message.print_va(format, arglist);
        va_end(arglist);
    }

    output_message_internal(NULL, &message, false);
};

void output_message_color(argb_color const * color, char const * format, ...)
{
    mangled_ppc("?output_message_color@@YAXPBTargb_color@@PBDZZ");

    s_static_string<16384> message;

    {
        va_list arglist;
        va_start(arglist, format);
        message.print_va(format, arglist);
        va_end(arglist);
    }

    output_message_internal(color, &message, true);
};

void output_message_block_begin()
{
    mangled_ppc("?output_message_block_begin@@YAXXZ");

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_message_block_begin();
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_message_block_begin();
    }
};

void output_message_block_end()
{
    mangled_ppc("?output_message_block_end@@YAXXZ");

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_message_block_end();
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_message_block_end();
    }
};

void output_error(char const * format, ...)
{
    mangled_ppc("?output_error@@YAXPBDZZ");

    va_list arglist;
    va_start(arglist, format);

    s_static_string<16384> error_string;
    error_string.print_va(format, arglist);

    va_end(arglist);

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_error(error_string.get_string());
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_error(error_string.get_string());
    }
};

void output_debug(char const * format, ...)
{
    mangled_ppc("?output_debug@@YAXPBDZZ");

    s_static_string<16384> debug_string;

    {
        va_list arglist;
        va_start(arglist, format);
        debug_string.print_va(format, arglist);
        va_end(arglist);
    }

    debug_string.append("\r\n");
    output_debug_string(debug_string.get_string());
};

void output_debug_string(char const * string)
{
    mangled_ppc("?output_debug_string@@YAXPBD@Z");

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_debug(string);
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_debug(string);
    }
};

void output_event(e_event_level event_level, char const * event_category, char const * event_string, rgb_color const * event_color)
{
    mangled_ppc("?output_event@@YAXW4e_event_level@@PBD1PBTrgb_color@@@Z");

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_event(event_level, event_category, event_string, event_color);
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_event(event_level, event_category, event_string, event_color);
    }
};

bool output_wait_for_keypress()
{
    mangled_ppc("?output_wait_for_keypress@@YA_NXZ");

    bool handled = false;

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler && !handled; handler = iterator.get_next())
    {
        handled = handler->handle_wait_for_keypress();
    }

    if (!handled && g_output_route_to_default_handler)
    {
        handled = g_default_output_handler.handle_wait_for_keypress();
    }

    return handled;
};

void output_alert(char const * alert_string)
{
    mangled_ppc("?output_alert@@YAXPBD@Z");

    bool handled = false;

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler && !handled; handler = iterator.get_next())
    {
        handled = handler->handle_alert(alert_string);
    }

    if (!handled && g_output_route_to_default_handler)
    {
        handled = g_default_output_handler.handle_alert(alert_string);
    }
};

bool output_has_console_window()
{
    mangled_ppc("?output_has_console_window@@YA_NXZ");

    bool has_console_window = false;

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        has_console_window |= handler->provides_console_window();
    }

    if (g_output_route_to_default_handler)
    {
        has_console_window |= g_default_output_handler.provides_console_window();
    }

    return has_console_window;
};

e_output_user_choice output_ask_user(char const * title, char const * message, e_output_user_query query_type)
{
    mangled_ppc("?output_ask_user@@YA?AW4e_output_user_choice@@PBD0W4e_output_user_query@@@Z");

    return output_ask_user_with_timeout(title, message, query_type, 0, _output_user_choice_ok);
};

e_output_user_choice output_ask_user_with_timeout(char const * title, char const * message, e_output_user_query query_type, long timeout_milliseconds, e_output_user_choice timeout_choice)
{
    mangled_ppc("?output_ask_user_with_timeout@@YA?AW4e_output_user_choice@@PBD0W4e_output_user_query@@JW41@@Z");

    e_output_user_choice choice = _output_user_choice_none;

    assert_tag_debug_untracked_jul_11_2011(287, VALID_INDEX(query_type, k_output_user_query_count));
    assert_tag_debug_untracked_jul_11_2011(288, timeout_milliseconds>=0);
    assert_tag_debug_untracked_jul_11_2011(289, VALID_INDEX(timeout_choice, k_output_user_choice_count));

    {
        c_output_handler_iterator iterator;
        for (c_output_handler * handler = iterator.get_first(); handler && choice == _output_user_choice_none; handler = iterator.get_next())
        {
            choice = handler->handle_ask_user_with_timeout(title, message, query_type, timeout_milliseconds, timeout_choice);
        }
    }

    if (choice == _output_user_choice_none && g_output_route_to_default_handler)
    {
        choice = g_default_output_handler.handle_ask_user_with_timeout(title, message, query_type, timeout_milliseconds, timeout_choice);
    }

    if (choice == _output_user_choice_none)
    {
        choice = timeout_choice;
    }

    return choice;
};

void output_message_internal(argb_color const * color, s_static_string<16384> * message, bool message_is_right_aligned)
{
    mangled_ppc("?output_message_internal@@YAXPBTargb_color@@PAV?$s_static_string@$0EAAA@@@_N@Z");

    c_output_handler_iterator iterator;
    for (c_output_handler * handler = iterator.get_first(); handler; handler = iterator.get_next())
    {
        handler->handle_output_message(color, message->get_string(), message_is_right_aligned);
    }

    if (g_output_route_to_default_handler)
    {
        g_default_output_handler.handle_output_message(color, message->get_string(), message_is_right_aligned);
    }
};

