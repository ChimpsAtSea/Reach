#pragma once
#ifndef __MINIDUMP_WRITER_H__
#define __MINIDUMP_WRITER_H__

/* ---------- headers */

#include "blamlib\xenon_minidump_endian.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

struct _EXCEPTION_POINTERS;
struct _MINIDUMP_HEADER;
struct _MINIDUMP_MODULE;
struct _MINIDUMP_MISC_INFO;
struct _MINIDUMP_SYSTEM_INFO;
struct MINIDUMP_EXCEPTION_STREAM;

struct s_thread_information
{
    MINIDUMP_THREAD thread; // 0x0
    CONTEXT context; // 0x30
    long stack_address; // 0xA70
    long stack_size; // 0xA74
};
static_assert(sizeof(s_thread_information) == 0xA78, "s_thread_information");

// vtable order from ??_7c_xbdm_minidump_info_provider@@6B@ (destructor is the last slot)
class c_minidump_provider_interface
{
public:
    virtual bool minidump_begin(_EXCEPTION_POINTERS * exception_pointers) = 0;
    virtual void minidump_end() = 0;
    virtual void suspend_non_calling_threads() = 0;
    virtual void resume_non_calling_threads() = 0;
    virtual void begin_thread_dump() = 0;
    virtual void end_thread_dump() = 0;
    virtual void get_thread_id_array(unsigned long * thread_ids, unsigned long thread_id_count, unsigned long * thread_count) = 0;
    virtual void get_thread_information(unsigned long thread_id, s_thread_information * thread_information) = 0;
    virtual void get_minidump_header(_MINIDUMP_HEADER * header, unsigned long number_of_streams) = 0;
    virtual void get_loaded_module_count(unsigned long * module_count) = 0;
    virtual void get_loaded_module(unsigned long module_index, _MINIDUMP_MODULE * module) = 0;
    virtual void get_loaded_module_name(unsigned long module_index, char * module_name, unsigned long module_name_size) = 0;
    virtual void get_misc_information(_MINIDUMP_MISC_INFO * misc_info) = 0;
    virtual void get_system_information(_MINIDUMP_SYSTEM_INFO * system_info) = 0;
    virtual void get_system_version_string(char * buffer, unsigned long buffer_size) = 0;
    virtual void update_exception_information(MINIDUMP_EXCEPTION_STREAM * exception_stream) = 0;
    virtual bool start_committed_region_query() = 0;
    virtual void end_committed_region_query() = 0;
    virtual void get_committed_region_count(unsigned long * region_count) = 0;
    virtual bool get_next_committed_region_info(unsigned long * base_address, unsigned long * region_size) = 0;
    virtual bool should_resolve_memory() = 0;
    virtual bool resolve_memory(void const * address, unsigned long size, void * buffer, unsigned long * bytes_read) = 0;
    virtual bool start_module_section_memory_query(unsigned long module_index) = 0;
    virtual void end_module_section_memory_query() = 0;
    virtual void get_loaded_module_section_count(unsigned long module_index, unsigned long * section_count) = 0;
    virtual bool get_next_module_section_memory_info(unsigned long * base_address, unsigned long * section_size) = 0;
    virtual ~c_minidump_provider_interface()
    {
    };
};

struct s_memory_stream_descriptor
{
    void const * address; // 0x0
    unsigned long size; // 0x4
};
static_assert(sizeof(s_memory_stream_descriptor) == 0x8, "s_memory_stream_descriptor");

typedef void (*minidump_progress_callback_t)(float progress, bool done);

// field names not recovered (set by minidump_from_exception, copied by c_minidump_writer::set_minidump_configuration)
struct s_minidump_configuration
{
    s_minidump_configuration() :
        write_full_memory(0),
        unknown4(0),
        progress_callback(NULL)
    {
        mangled_ppc("??0s_minidump_configuration@@QAA@XZ");
    };

    long write_full_memory; // 0x0
    long unknown4; // 0x4
    minidump_progress_callback_t progress_callback; // 0x8
    bool unknownC; // 0xC
};
static_assert(sizeof(s_minidump_configuration) == 0x10, "s_minidump_configuration");

struct s_minidump_exception_information
{
    _EXCEPTION_POINTERS * exception_pointers; // 0x0
    unsigned long thread_id; // 0x4
};
static_assert(sizeof(s_minidump_exception_information) == 0x8, "s_minidump_exception_information");

class c_minidump_writer
{
public:
    c_minidump_writer();
    ~c_minidump_writer();

    void set_minidump_configuration(s_minidump_configuration const & configuration);
    bool write(c_minidump_provider_interface * provider, char const * file_name, s_minidump_exception_information const & exception_information);
    bool add_memory_descriptor(s_memory_stream_descriptor const & descriptor);

private:
    static long const k_minidump_directory_count = 8;
    static long const k_max_thread_dump_count = 64;
    static long const k_max_memory_descriptor_count = 64;
    static long const k_total_memory_descriptors_supported = 0x1000;

    // $TODO: layout not recovered (configuration at 0x10, memory descriptors at 0x80, descriptor count at 0x288)
    unsigned char m_data[0x28C]; // 0x0
};
static_assert(sizeof(c_minidump_writer) == 0x28C, "c_minidump_writer");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MINIDUMP_WRITER_H__

