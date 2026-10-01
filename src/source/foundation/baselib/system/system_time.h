#pragma once
#ifndef __SYSTEM_TIME_H__
#define __SYSTEM_TIME_H__

/* ---------- headers */

/* ---------- constants */

enum e_date_and_time_print_format
{
    _date_and_time_print_format_default = 0,
    _date_and_time_print_format_filename,

    k_date_and_time_print_format_count
};

/* ---------- definitions */

/* ---------- prototypes */

void system_print_date_and_time(e_date_and_time_print_format format, char * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __SYSTEM_TIME_H__

