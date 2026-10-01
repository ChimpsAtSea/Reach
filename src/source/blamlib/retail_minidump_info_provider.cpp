/* ---------- headers */

#include "blamlib\retail_minidump_info_provider.h"
#include "blamlib\minidump_helper.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries_windows_debug.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_retail_minidump_info_provider::c_retail_minidump_info_provider(void);
// merged_8360A798;
// public: virtual bool c_retail_minidump_info_provider::minidump_begin(struct _EXCEPTION_POINTERS *);
// public: virtual void c_retail_minidump_info_provider::minidump_end(void);
// public: virtual void c_retail_minidump_info_provider::suspend_non_calling_threads(void);
// public: virtual void c_retail_minidump_info_provider::resume_non_calling_threads(void);
// public: virtual void c_retail_minidump_info_provider::begin_thread_dump(void);
// public: virtual void c_retail_minidump_info_provider::end_thread_dump(void);
// public: virtual void c_retail_minidump_info_provider::get_thread_id_array(unsigned long *, unsigned long, unsigned long *);
// public: virtual void c_retail_minidump_info_provider::get_thread_information(unsigned long, struct s_thread_information *);
// public: virtual void c_retail_minidump_info_provider::get_loaded_module_count(unsigned long *);
// public: virtual void c_retail_minidump_info_provider::get_loaded_module(unsigned long, struct _MINIDUMP_MODULE *);
// public: virtual void c_retail_minidump_info_provider::get_loaded_module_name(unsigned long, char *, unsigned long);
// public: virtual void c_retail_minidump_info_provider::update_exception_information(struct MINIDUMP_EXCEPTION_STREAM *);
// public: virtual bool c_retail_minidump_info_provider::start_committed_region_query(void);
// public: virtual void c_retail_minidump_info_provider::end_committed_region_query(void);
// public: virtual void c_retail_minidump_info_provider::get_committed_region_count(unsigned long *);
// public: virtual bool c_retail_minidump_info_provider::get_next_committed_region_info(unsigned long *, unsigned long *);
// public: virtual bool c_retail_minidump_info_provider::should_resolve_memory(void);
// public: virtual bool c_retail_minidump_info_provider::resolve_memory(void const *, unsigned long, void *, unsigned long *);
// public: virtual void c_retail_minidump_info_provider::get_loaded_module_section_count(unsigned long, unsigned long *);
// public: virtual bool c_retail_minidump_info_provider::start_module_section_memory_query(unsigned long);
// public: virtual void c_retail_minidump_info_provider::end_module_section_memory_query(void);
// public: virtual bool c_retail_minidump_info_provider::get_next_module_section_memory_info(unsigned long *, unsigned long *);
// void build_running_module_pe_name(char *, long);
// bool is_valid_memory_range(void const *, unsigned long);

c_retail_minidump_info_provider::c_retail_minidump_info_provider() :
    c_minidump_provider_common()
{
    mangled_ppc("??0c_retail_minidump_info_provider@@QAA@XZ");

    // the original passes value and size swapped (zero-length memset)
    memset(&m_committed_region_query_address, sizeof(m_committed_region_query_address), 0);
    memset(&m_module_section_query, sizeof(m_module_section_query), 0);
};

//merged_8360A798
//{
//    mangled_ppc("merged_8360A798");
//};

bool c_retail_minidump_info_provider::minidump_begin(_EXCEPTION_POINTERS * exception_pointers)
{
    mangled_ppc("?minidump_begin@c_retail_minidump_info_provider@@UAA_NPAU_EXCEPTION_POINTERS@@@Z");

    return true;
};

void c_retail_minidump_info_provider::minidump_end()
{
    mangled_ppc("?minidump_end@c_retail_minidump_info_provider@@UAAXXZ");
};

void c_retail_minidump_info_provider::suspend_non_calling_threads()
{
    mangled_ppc("?suspend_non_calling_threads@c_retail_minidump_info_provider@@UAAXXZ");

    _THREAD_LIST thread_list;
    GetProcessThreads(2, &thread_list);
    for (unsigned long thread_index = 0; thread_index < thread_list.count; thread_index++)
    {
        SuspendThread(thread_list.threads[thread_index]);
        CloseHandle(thread_list.threads[thread_index]);
    }
};

void c_retail_minidump_info_provider::resume_non_calling_threads()
{
    mangled_ppc("?resume_non_calling_threads@c_retail_minidump_info_provider@@UAAXXZ");

    _THREAD_LIST thread_list;
    GetProcessThreads(2, &thread_list);
    for (unsigned long thread_index = 0; thread_index < thread_list.count; thread_index++)
    {
        ResumeThread(thread_list.threads[thread_index]);
        CloseHandle(thread_list.threads[thread_index]);
    }
};

void c_retail_minidump_info_provider::begin_thread_dump()
{
    mangled_ppc("?begin_thread_dump@c_retail_minidump_info_provider@@UAAXXZ");
};

void c_retail_minidump_info_provider::end_thread_dump()
{
    mangled_ppc("?end_thread_dump@c_retail_minidump_info_provider@@UAAXXZ");
};

void c_retail_minidump_info_provider::get_thread_id_array(unsigned long * thread_ids, unsigned long thread_id_count, unsigned long * thread_count)
{
    mangled_ppc("?get_thread_id_array@c_retail_minidump_info_provider@@UAAXPAKK0@Z");

    _THREAD_LIST thread_list;
    GetProcessThreads(1, &thread_list);
    if (thread_list.count > thread_id_count)
    {
        thread_list.count = thread_id_count;
    }
    if (thread_count)
    {
        *thread_count = thread_list.count;
    }
    if (thread_ids)
    {
        memcpy(thread_ids, thread_list.threads, thread_list.count * sizeof(unsigned long));
    }
};

void c_retail_minidump_info_provider::get_thread_information(unsigned long thread_id, s_thread_information * thread_information)
{
    mangled_ppc("?get_thread_information@c_retail_minidump_info_provider@@UAAXKPAUs_thread_information@@@Z");

    __int64 stack_limit = 0;
    __int64 stack_base = 0;
    __int64 stack_pointer = 0;
    if (thread_information)
    {
        void * handle = OpenThread(thread_id);
        _THREAD_INFO info;
        GetThreadInfo(handle, &info);
        thread_information->context.ContextFlags = CONTEXT_FULL;
        GetThreadContext(handle, &thread_information->context);
        thread_information->thread.Priority = info.priority;
        thread_information->thread.PriorityClass = 0;
        thread_information->thread.SuspendCount = info.suspend_count;
        thread_information->thread.Teb = convert_32bit_address_to_64bit_value(info.tls_base);
        thread_information->thread.ThreadContext.DataSize = sizeof(CONTEXT);
        thread_information->thread.ThreadContext.Rva = 0;
        thread_information->thread.ThreadId = thread_id;
        stack_limit = convert_32bit_address_to_64bit_value(info.stack_limit);
        stack_base = convert_32bit_address_to_64bit_value(info.stack_base);
        stack_pointer = static_cast<long>(thread_information->context.Gpr1);
        if (stack_pointer >= stack_limit && stack_pointer < stack_base && stack_pointer - info.stack_slack_space >= stack_limit)
        {
            thread_information->stack_size = stack_base - (stack_pointer - info.stack_slack_space);
            thread_information->stack_address = stack_pointer - info.stack_slack_space;
        }
        else
        {
            thread_information->stack_size = stack_base - stack_limit;
            thread_information->stack_address = stack_limit;
        }
        thread_information->thread.Stack.Memory.DataSize = thread_information->stack_size;
        thread_information->thread.Stack.Memory.Rva = 0;
        thread_information->thread.Stack.StartOfMemoryRange = convert_32bit_address_to_64bit_value(reinterpret_cast<void const *>(thread_information->stack_address));
        CloseHandle(handle);
    }
};

void c_retail_minidump_info_provider::get_loaded_module_count(unsigned long * module_count)
{
    mangled_ppc("?get_loaded_module_count@c_retail_minidump_info_provider@@UAAXPAK@Z");

    if (module_count)
    {
        *module_count = GetModuleCount();
    }
};

void c_retail_minidump_info_provider::get_loaded_module(unsigned long module_index, _MINIDUMP_MODULE * module)
{
    mangled_ppc("?get_loaded_module@c_retail_minidump_info_provider@@UAAXKPAU_MINIDUMP_MODULE@@@Z");

    _MODULE_INFO module_info = { 0 };
    if (module && GetModuleInfo(module_index, &module_info))
    {
        module->BaseOfImage = convert_32bit_address_to_64bit_value(module_info.base_address);
        module->SizeOfImage = module_info.size;
        module->CheckSum = module_info.check_sum;
        module->TimeDateStamp = module_info.time_date_stamp;
        module->ModuleNameRva = 0;
    }
};

void c_retail_minidump_info_provider::get_loaded_module_name(unsigned long module_index, char * module_name, unsigned long module_name_size)
{
    mangled_ppc("?get_loaded_module_name@c_retail_minidump_info_provider@@UAAXKPADK@Z");

    if (module_name)
    {
        bool is_exe = false;
        _MODULE_INFO module_information;
        GetModuleInfo(module_index, &module_information);
        strncpy(module_name, module_information.name, module_name_size);
        is_exe = (module_information.flags & 1) == 1;
        char * name_extension = NULL;
        char const * new_extension = NULL;
        char const * exe_suffix = ".exe";
        char const * xex_suffix = ".xex";
        char const * kernel_module = "xboxkrnl";
        char const * d_exe_suffix = "d.exe";
        char const * dll_string = ".dll";
        if (is_exe)
        {
            name_extension = strstr(module_name, xex_suffix);
            new_extension = dll_string;
        }
        else
        {
            name_extension = strstr(module_name, kernel_module);
            if (name_extension)
            {
                name_extension = strstr(module_name, exe_suffix);
                if (name_extension)
                {
                    new_extension = d_exe_suffix;
                }
            }
            else
            {
                new_extension = NULL;
                name_extension = NULL;
                build_running_module_pe_name(module_name, module_name_size);
            }
        }
        if (name_extension && new_extension)
        {
            strncpy(name_extension, new_extension, strlen(new_extension) + 1);
        }
    }
};

void c_retail_minidump_info_provider::update_exception_information(MINIDUMP_EXCEPTION_STREAM * exception_stream)
{
    mangled_ppc("?update_exception_information@c_retail_minidump_info_provider@@UAAXPAUMINIDUMP_EXCEPTION_STREAM@@@Z");
};

bool c_retail_minidump_info_provider::start_committed_region_query()
{
    mangled_ppc("?start_committed_region_query@c_retail_minidump_info_provider@@UAA_NXZ");

    m_committed_region_query_address = NULL;
    return true;
};

void c_retail_minidump_info_provider::end_committed_region_query()
{
    mangled_ppc("?end_committed_region_query@c_retail_minidump_info_provider@@UAAXXZ");

    m_committed_region_query_address = NULL;
};

void c_retail_minidump_info_provider::get_committed_region_count(unsigned long * region_count)
{
    mangled_ppc("?get_committed_region_count@c_retail_minidump_info_provider@@UAAXPAK@Z");

    if (region_count)
    {
        *region_count = 0;
        _MEMORY_INFO memory_info;
        void * address = GetMemoryInfo(NULL, &memory_info);
        while (address)
        {
            if (is_valid_memory_range(reinterpret_cast<void const *>(memory_info.base_address), memory_info.region_size))
            {
                (*region_count)++;
            }
            address = GetMemoryInfo(address, &memory_info);
        }
    }
};

bool c_retail_minidump_info_provider::get_next_committed_region_info(unsigned long * base_address, unsigned long * region_size)
{
    mangled_ppc("?get_next_committed_region_info@c_retail_minidump_info_provider@@UAA_NPAK0@Z");

    bool result = false;
    void * current_address;
    if (base_address && region_size)
    {
        _MEMORY_INFO memory_info;
        current_address = GetMemoryInfo(m_committed_region_query_address, &memory_info);
        while (current_address && !result)
        {
            if (is_valid_memory_range(reinterpret_cast<void const *>(memory_info.base_address), memory_info.region_size))
            {
                *base_address = memory_info.base_address;
                *region_size = memory_info.region_size;
                result = true;
            }
            else
            {
                current_address = GetMemoryInfo(current_address, &memory_info);
            }
        }
        m_committed_region_query_address = current_address;
    }
    return result;
};

bool c_retail_minidump_info_provider::should_resolve_memory()
{
    mangled_ppc("?should_resolve_memory@c_retail_minidump_info_provider@@UAA_NXZ");

    return true;
};

bool c_retail_minidump_info_provider::resolve_memory(void const * address, unsigned long size, void * buffer, unsigned long * bytes_read)
{
    mangled_ppc("?resolve_memory@c_retail_minidump_info_provider@@UAA_NPBXKPAXPAK@Z");

    bool result = false;
    if (address && buffer && bytes_read && size > 0 &&
        (static_cast<char const *>(address) + size <= buffer || static_cast<char *>(buffer) + size <= address) &&
        !is_bad_read_ptr(address, size))
    {
        memcpy(buffer, address, size);
        *bytes_read = size;
        result = true;
    }
    return result;
};

void c_retail_minidump_info_provider::get_loaded_module_section_count(unsigned long module_index, unsigned long * section_count)
{
    mangled_ppc("?get_loaded_module_section_count@c_retail_minidump_info_provider@@UAAXKPAK@Z");

    if (section_count)
    {
        *section_count = GetSectionCount(module_index);
    }
};

bool c_retail_minidump_info_provider::start_module_section_memory_query(unsigned long module_index)
{
    mangled_ppc("?start_module_section_memory_query@c_retail_minidump_info_provider@@UAA_NK@Z");

    memset(&m_module_section_query, 0, sizeof(m_module_section_query));
    m_module_section_query.module_index = module_index;
    m_module_section_query.section_count = GetSectionCount(module_index);
    return true;
};

void c_retail_minidump_info_provider::end_module_section_memory_query()
{
    mangled_ppc("?end_module_section_memory_query@c_retail_minidump_info_provider@@UAAXXZ");

    memset(&m_module_section_query, sizeof(m_module_section_query), 0);
};

bool c_retail_minidump_info_provider::get_next_module_section_memory_info(unsigned long * base_address, unsigned long * section_size)
{
    mangled_ppc("?get_next_module_section_memory_info@c_retail_minidump_info_provider@@UAA_NPAK0@Z");

    bool result = false;
    if (base_address && section_size && m_module_section_query.section_index < m_module_section_query.section_count)
    {
        _SECTION_INFO section_info;
        if (GetSectionInfo(m_module_section_query.module_index, m_module_section_query.section_index, &section_info))
        {
            *base_address = section_info.base_address;
            *section_size = section_info.size;
            m_module_section_query.section_index++;
            result = true;
        }
    }
    return result;
};

void build_running_module_pe_name(char * module_name, long module_name_size)
{
    mangled_ppc("?build_running_module_pe_name@@YAXPADJ@Z");

    if (module_name)
    {
        c_static_string<260> binary_filename;
        debug_get_binary_filename(&binary_filename);
        binary_filename.append(".exe");
        csstrnzcpy(module_name, binary_filename.get_string(), module_name_size);
    }
};

bool is_valid_memory_range(void const * address, unsigned long size)
{
    mangled_ppc("?is_valid_memory_range@@YA_NPBXK@Z");

    bool result = false;
    if (reinterpret_cast<unsigned long>(address) < c_retail_minidump_info_provider::k_max_virtual_memory_address)
    {
        result = true;
    }
    return result;
};

