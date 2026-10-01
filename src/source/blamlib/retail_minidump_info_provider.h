#pragma once
#ifndef __RETAIL_MINIDUMP_INFO_PROVIDER_H__
#define __RETAIL_MINIDUMP_INFO_PROVIDER_H__

/* ---------- headers */

#include "blamlib\minidump_provider_common.h"

/* ---------- constants */

enum
{
    k_retaildump_maximum_thread_count = 63,
    k_retaildump_maximum_name_length = 260,
};

/* ---------- definitions */

// retaildump.lib (XDK retail crash dump helpers, C++ linkage)
struct _THREAD_LIST
{
    unsigned long count; // 0x0
    void * threads[k_retaildump_maximum_thread_count]; // 0x4
};
static_assert(sizeof(_THREAD_LIST) == 0x100, "_THREAD_LIST");

struct _THREAD_INFO
{
    unsigned long suspend_count; // 0x0
    unsigned long priority; // 0x4
    void * tls_base; // 0x8
    void * start_address; // 0xC
    void * stack_base; // 0x10
    void * stack_limit; // 0x14
    unsigned long create_time[2]; // 0x18
    unsigned long stack_slack_space; // 0x20
    char * thread_name_address; // 0x24
    unsigned long thread_name_length; // 0x28
};
static_assert(sizeof(_THREAD_INFO) == 0x2C, "_THREAD_INFO");

struct _MODULE_INFO
{
    void * base_address; // 0x0
    unsigned long size; // 0x4
    unsigned long time_date_stamp; // 0x8
    unsigned long check_sum; // 0xC
    unsigned long flags; // 0x10
    char name[k_retaildump_maximum_name_length]; // 0x14
};
static_assert(sizeof(_MODULE_INFO) == 0x118, "_MODULE_INFO");

struct _SECTION_INFO
{
    unsigned long base_address; // 0x0
    unsigned long size; // 0x4
    char name[k_retaildump_maximum_name_length]; // 0x8
};
static_assert(sizeof(_SECTION_INFO) == 0x10C, "_SECTION_INFO");

struct _MEMORY_INFO
{
    unsigned long base_address; // 0x0
    unsigned long region_size; // 0x4
};
static_assert(sizeof(_MEMORY_INFO) == 0x8, "_MEMORY_INFO");

class c_retail_minidump_info_provider :
    public c_minidump_provider_common
{
public:
    c_retail_minidump_info_provider();

    virtual bool minidump_begin(_EXCEPTION_POINTERS * exception_pointers);
    virtual void minidump_end();
    virtual void suspend_non_calling_threads();
    virtual void resume_non_calling_threads();
    virtual void begin_thread_dump();
    virtual void end_thread_dump();
    virtual void get_thread_id_array(unsigned long * thread_ids, unsigned long thread_id_count, unsigned long * thread_count);
    virtual void get_thread_information(unsigned long thread_id, s_thread_information * thread_information);
    virtual void get_loaded_module_count(unsigned long * module_count);
    virtual void get_loaded_module(unsigned long module_index, _MINIDUMP_MODULE * module);
    virtual void get_loaded_module_name(unsigned long module_index, char * module_name, unsigned long module_name_size);
    virtual void update_exception_information(MINIDUMP_EXCEPTION_STREAM * exception_stream);
    virtual bool start_committed_region_query();
    virtual void end_committed_region_query();
    virtual void get_committed_region_count(unsigned long * region_count);
    virtual bool get_next_committed_region_info(unsigned long * base_address, unsigned long * region_size);
    virtual bool should_resolve_memory();
    virtual bool resolve_memory(void const * address, unsigned long size, void * buffer, unsigned long * bytes_read);
    virtual bool start_module_section_memory_query(unsigned long module_index);
    virtual void end_module_section_memory_query();
    virtual void get_loaded_module_section_count(unsigned long module_index, unsigned long * section_count);
    virtual bool get_next_module_section_memory_info(unsigned long * base_address, unsigned long * section_size);

    static unsigned long const k_max_virtual_memory_address = 0x7FFFFFFF;

private:
    struct s_module_section_query
    {
        unsigned long module_index; // 0x0
        unsigned long section_index; // 0x4
        unsigned long section_count; // 0x8
    };

    void * m_committed_region_query_address; // 0x4
    s_module_section_query m_module_section_query; // 0x8
};
static_assert(sizeof(c_retail_minidump_info_provider) == 0x14, "c_retail_minidump_info_provider");

/* ---------- prototypes */

// retaildump.lib
void GetProcessThreads(unsigned long flags, _THREAD_LIST * thread_list);
void * OpenThread(unsigned long thread_id);
void GetThreadInfo(void * thread_handle, _THREAD_INFO * thread_info);
void GetThreadContext(void * thread_handle, _CONTEXT * context);
unsigned long GetModuleCount();
int GetModuleInfo(unsigned long module_index, _MODULE_INFO * module_info);
unsigned long GetSectionCount(unsigned long module_index);
int GetSectionInfo(unsigned long module_index, unsigned long section_index, _SECTION_INFO * section_info);
void * GetMemoryInfo(void * address, _MEMORY_INFO * memory_info);

void build_running_module_pe_name(char * module_name, long module_name_size);
bool is_valid_memory_range(void const * address, unsigned long size);

/* ---------- globals */

/* ---------- public code */

#endif // __RETAIL_MINIDUMP_INFO_PROVIDER_H__
