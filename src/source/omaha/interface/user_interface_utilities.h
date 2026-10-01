#pragma once
#ifndef __USER_INTERFACE_UTILITIES_H__
#define __USER_INTERFACE_UTILITIES_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

enum e_user_interface_timespan_format
{
    _user_interface_timespan_format_days_hours_minutes_seconds = 0,
    _user_interface_timespan_format_hours_minutes_seconds,
    _user_interface_timespan_format_minutes_seconds,
    _user_interface_timespan_format_seconds,
};

/* ---------- prototypes */

bool user_interface_get_timespan_string(long length_in_seconds, e_user_interface_timespan_format format, bool show_unused_components, c_static_wchar_string<1024> * text);

/* ---------- globals */

/* ---------- public code */

#endif // __USER_INTERFACE_UTILITIES_H__

