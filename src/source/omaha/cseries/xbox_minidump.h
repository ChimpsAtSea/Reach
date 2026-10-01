#pragma once
#ifndef __XBOX_MINIDUMP_H__
#define __XBOX_MINIDUMP_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_file_reference;

/* ---------- prototypes */

extern long upload_minidump_start(long maximum_file_count, s_file_reference * out_file_list);

/* ---------- globals */

extern char const * const k_crash_minidump_file_path;
extern char const * const k_debug_memory_minidump_memory_stream;

/* ---------- public code */

#endif // __XBOX_MINIDUMP_H__

