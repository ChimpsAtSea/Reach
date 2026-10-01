#pragma once
#ifndef __CSERIES_STRINGS_H__
#define __CSERIES_STRINGS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

template<typename t_type> class c_wrapped_array;

/* ---------- prototypes */

char const * find_string_end(char const * string, char const * delimiters);
bool string_is_not_empty(char const * string);
void string_copy_bounded(c_wrapped_array<char> destination, c_wrapped_array<char const> source);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_STRINGS_H__

