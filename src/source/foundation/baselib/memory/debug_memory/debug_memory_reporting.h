#pragma once
#ifndef __DEBUG_MEMORY_REPORTING_H__
#define __DEBUG_MEMORY_REPORTING_H__

/* ---------- headers */

/* ---------- constants */

enum e_alloc_failed_type
{
    _alloc_failed_heap = 0,
    _alloc_failed_nonheap,

    k_alloc_failed_type_count
};

/* ---------- definitions */

class c_file_path;
struct s_base_memory_information;

class c_debug_memory_minidump_writer
{
public:
    virtual void write_memory(void const * address, unsigned int size) = 0;
};

class c_debug_memory_reporter
{
public:
    virtual void report_usage(void) = 0;
    virtual void report_brief(long buffer_length, char * out_buffer) = 0;
    virtual long upload_report(long maximum_file_count, c_file_path * files) = 0;
};

/* ---------- prototypes */

void debug_memory_register_reporter(c_debug_memory_reporter * reporter);
void debug_memory_unregister_reporter(c_debug_memory_reporter const * reporter);
void debug_memory_reporters_report_usage(void);
long debug_memory_reporters_upload_usage(long maximum_file_count, c_file_path * files);
void debug_dump_memory(void);
void debug_dump_memory_by_file(void);
void debug_dump_memory_for_file(char const * file_filter);
void debug_dump_out_of_memory(char const * file, long line);
void debug_dump_memory_brief(long buffer_length, char * out_buffer);
void debug_report_memory_checkpoint(char const * name, char const * previous_name, long checkpoint_index, __int64 start_time, s_base_memory_information const * start_information, __int64 end_time, s_base_memory_information const * end_information);
long debug_memory_get_minidump_block_count(void);
void debug_memory_write_minidump_memory_stream(c_debug_memory_minidump_writer * writer);
long debug_memory_start_upload_heap_dump(long maximum_file_count, c_file_path * files);
void debug_dump_memory_erase_files(void);
void platform_report_out_of_memory(void);
void platform_report_dump_memory(void);
void debug_alloc_failed(unsigned int size, unsigned int old_size, e_alloc_failed_type type, char const * file, long line, long type_identifier, char const * type_name, char const * subtype_name, char const * name);

/* ---------- globals */

/* ---------- public code */

#endif // __DEBUG_MEMORY_REPORTING_H__

