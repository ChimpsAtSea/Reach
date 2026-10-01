#pragma once
#ifndef __XENON_MINIDUMP_H__
#define __XENON_MINIDUMP_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_exception_information;
struct s_exception_pointers;
struct s_memory_stream_descriptor;

// names guessed from g_minidump_always_force_regular_minidumps_with_ui (sets bits 0 and 2)
enum e_minidump_flags
{
    _minidump_regular_bit = 0,
    _minidump_damaged_media_bit,
    _minidump_with_ui_bit,

    k_minidump_flags_count
};

/* ---------- prototypes */

long minidump_from_exception(long flags, char const * out_file, unsigned long exception_code, s_exception_information const * platform_exception_information, bool unknown);
void minidump_now(char const * minidump_file_name);
bool get_game_state_memory_descriptor(s_memory_stream_descriptor * descriptor);
bool get_network_memory_descriptor(s_memory_stream_descriptor * descriptor);
bool get_cache_file_tag_resource_runtime_memory_descriptor(s_memory_stream_descriptor * descriptor);
bool get_tag_memory_descriptor(s_memory_stream_descriptor * descriptor);
void minidump_progress_report(float progress, bool done);
long minidump_now_support(char const * minidump_file_name, unsigned long exception_code, s_exception_pointers * exception_pointers);

/* ---------- globals */

extern bool g_minidump_use_retail_provider;
extern bool g_minidump_always_force_regular_minidumps_with_ui;

/* ---------- public code */

#endif // __XENON_MINIDUMP_H__

