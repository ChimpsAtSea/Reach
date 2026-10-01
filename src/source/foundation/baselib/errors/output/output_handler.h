#pragma once
#ifndef __OUTPUT_HANDLER_H__
#define __OUTPUT_HANDLER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "omaha\math\color_math.h"
#include "foundation\baselib\datatypes\static_stack.h"

/* ---------- constants */

// enumerator names unverified; counts from output_globals.cpp asserts
enum e_output_user_query
{
    _output_user_query_ok = 0,
    _output_user_query_ok_cancel,
    _output_user_query_yes_no,
    _output_user_query_yes_no_cancel,

    k_output_user_query_count
};

// enumerator names unverified; 0 = no answer (output_ask_user_with_timeout falls back to timeout_choice)
enum e_output_user_choice
{
    _output_user_choice_none = 0,
    _output_user_choice_ok,
    _output_user_choice_cancel,
    _output_user_choice_yes,
    _output_user_choice_no,

    k_output_user_choice_count
};

/* ---------- definitions */

// vtable order verified from output_globals.obj call offsets (0x0 .. 0x24)
class c_output_handler
{
public:
    virtual void handle_output_message(argb_color const * color, char const * message, bool message_is_right_aligned);
    virtual void handle_output_message_block_begin();
    virtual void handle_output_message_block_end();
    virtual void handle_output_error(char const * error_string);
    virtual void handle_output_debug(char const * debug_string);
    virtual void handle_output_event(e_event_level event_level, char const * event_category, char const * event_string, rgb_color const * event_color);
    virtual bool provides_console_window();
    virtual bool handle_wait_for_keypress();
    virtual bool handle_alert(char const * alert_string);
    virtual e_output_user_choice handle_ask_user_with_timeout(char const * title, char const * message, e_output_user_query query_type, long timeout_milliseconds, e_output_user_choice timeout_choice);
};

class c_output_handler_registry
{
public:
    static void attach_handler(c_output_handler * handler);
    static void detach_handler(c_output_handler * handler);
    static bool active();

protected:
    friend class c_output_handler_iterator;

    static long const k_maximum_output_handlers = 8;

    static c_static_stack<c_output_handler *, k_maximum_output_handlers> g_handlers;
};

class c_output_handler_iterator
{
public:
    c_output_handler_iterator();
    c_output_handler * get_first();
    c_output_handler * get_next();

private:
    long m_index;
};

// vtable owned by output_globals.obj; handle_output_debug in output_handler_default_xenon.obj
class c_default_output_handler : public c_output_handler
{
public:
    c_default_output_handler()
    {
        mangled_ppc("??0c_default_output_handler@@QAA@XZ");
    };

    virtual void handle_output_debug(char const * debug_string);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __OUTPUT_HANDLER_H__

