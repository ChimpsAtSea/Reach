#pragma once
#ifndef __UNICODE_H__
#define __UNICODE_H__

/* ---------- headers */

/* ---------- constants */

enum e_utf32
{
    _unicode_utf32_identifier_character = -16777217, // 0xFEFFFFFF
    _unicode_utf32_byte_swapped_character = -2, // 0xFFFFFFFE
};

/* ---------- definitions */

/* ---------- prototypes */

extern unsigned int ustrlen(wchar_t const * string);
extern wchar_t * ustrnzcpy(wchar_t * dest, wchar_t const * source, long size);
extern int ustrncmp(wchar_t const * string1, wchar_t const * string2, long count);

/* ---------- globals */

/* ---------- public code */

#endif // __UNICODE_H__

