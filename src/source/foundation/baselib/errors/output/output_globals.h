#pragma once
#ifndef __OUTPUT_GLOBALS_H__
#define __OUTPUT_GLOBALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "omaha\math\color_math.h"
#include "foundation\baselib\errors\output\output_handler.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void output_route_to_default_handler(bool route);
extern void output_message(char const * format, ...);
extern void output_message_string(char const * format, ...);
extern void output_message_color(argb_color const * color, char const * format, ...);
extern void output_message_block_begin();
extern void output_message_block_end();
extern void output_error(char const * format, ...);
extern void output_debug(char const * format, ...);
extern void output_debug_string(char const * string);
extern void output_event(e_event_level event_level, char const * event_category, char const * event_string, rgb_color const * event_color);
extern bool output_wait_for_keypress();
extern void output_alert(char const * alert_string);
extern bool output_has_console_window();
extern e_output_user_choice output_ask_user(char const * title, char const * message, e_output_user_query query_type);
extern e_output_user_choice output_ask_user_with_timeout(char const * title, char const * message, e_output_user_query query_type, long timeout_milliseconds, e_output_user_choice timeout_choice);

/* ---------- globals */

/* ---------- public code */

#endif // __OUTPUT_GLOBALS_H__

