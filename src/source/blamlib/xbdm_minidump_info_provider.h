#pragma once
#ifndef __XBDM_MINIDUMP_INFO_PROVIDER_H__
#define __XBDM_MINIDUMP_INFO_PROVIDER_H__

/* ---------- headers */

#include "blamlib\minidump_provider_common.h"

/* ---------- constants */

/* ---------- definitions */

class c_xbdm_minidump_info_provider :
    public c_minidump_provider_common
{
public:
    c_xbdm_minidump_info_provider();

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

private:
    static unsigned long const k_max_virtual_memory_address = 0x7FFFFFFF;

    static void get_loaded_module_name_internal(unsigned long module_index, char * module_name, unsigned long module_name_size);
    static bool is_module_dll(char const * module_name);

    // $TODO: layout not recovered; size from the stack frame of minidump_from_exception (xenon_minidump.obj)
    unsigned char m_data[0x108]; // 0x4
};
static_assert(sizeof(c_xbdm_minidump_info_provider) == 0x10C, "c_xbdm_minidump_info_provider");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __XBDM_MINIDUMP_INFO_PROVIDER_H__

