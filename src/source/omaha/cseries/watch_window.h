#pragma once
#ifndef __WATCH_WINDOW_H__
#define __WATCH_WINDOW_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct object_datum;

struct s_watch_object_results
{
    char const * description; // 0x0
    object_datum * datum; // 0x4
};
static_assert(sizeof(s_watch_object_results) == 0x8, "s_watch_object_results");

/* ---------- prototypes */

extern void watch_window_initialize();
extern void watch_window_dispose();
extern char const * watch_object_describe(long object_index);
extern s_watch_object_results & watch_object(long object_index);
extern bool object_index_valid_for_try_and_get(long object_index);
extern unsigned long clear_watch_window_globals();
extern char const * watch_object_describe_internal(long object_index, char * buffer, long buffer_length);

/* ---------- globals */

/* ---------- public code */

#endif // __WATCH_WINDOW_H__

