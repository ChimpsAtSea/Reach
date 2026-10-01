#pragma once
#ifndef __FILE_TIME_WINDOWS_H__
#define __FILE_TIME_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_file_time_unpack_mode
{
    _file_time_unpack_mode_local = 0,
    _file_time_unpack_mode_utc,

    k_file_time_unpack_mode_count
};

/* ---------- definitions */

struct s_file_time
{
    unsigned long low_date_time; // 0x0
    unsigned long high_date_time; // 0x4
};
static_assert(sizeof(s_file_time) == 0x8, "s_file_time");

struct s_file_time_unpacked
{
    short year; // 0x0
    short month; // 0x2
    short day; // 0x4
    short hour; // 0x6
    short minute; // 0x8
    short second; // 0xA
    short millisecond; // 0xC
};
static_assert(sizeof(s_file_time_unpacked) == 0xE, "s_file_time_unpacked");

/* ---------- prototypes */

long file_time_compare(s_file_time const * time1, s_file_time const * time2);
void file_time_get_current_time(s_file_time * out_time);
bool file_time_unpack(s_file_time const * time, e_file_time_unpack_mode unpack_mode, s_file_time_unpacked * out_unpacked_time);
bool file_time_pack(s_file_time_unpacked const * unpacked_time, e_file_time_unpack_mode unpack_mode, s_file_time * out_time);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_TIME_WINDOWS_H__

