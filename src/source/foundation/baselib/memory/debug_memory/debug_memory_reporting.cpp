#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\debug_memory\\debug_memory_reporting.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\debug_memory\debug_memory_reporting.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "foundation\baselib\files\simple_file.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\algorithms\qsort.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\memory\memory_interface.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "foundation\baselib\errors\output\output_globals.h"
#include "baselib\system_time_windows.h"
#include "foundation\baselib\files\debug_paths.h"
#include "foundation\baselib\files\file_synchronous_utilities_windows.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

long const k_debug_memory_maximum_reporters = 8;

/* ---------- definitions */

struct s_debug_memory_reporting_state
{
    s_static_array<c_debug_memory_reporter *, k_debug_memory_maximum_reporters> reporters; // 0x0
    bool dump_to_output; // 0x20
    bool out_of_memory; // 0x21
    bool unknown22; // 0x22
    bool unknown23; // 0x23
    bool unknown24; // 0x24
    bool unknown25; // 0x25
    bool unknown26; // 0x26
    bool checkpoint_initialized; // 0x27
    c_simple_file checkpoint_file; // 0x28
    __int64 checkpoint_start_time; // 0x138
};
static_assert(sizeof(s_debug_memory_reporting_state) == 0x140, "s_debug_memory_reporting_state");

struct s_debug_source_file_data
{
    char const * name; // 0x0
    long total_count; // 0x4
    long heap_count; // 0x8
    long nonheap_count; // 0xC
    unsigned int total_size; // 0x10
    unsigned int heap_size; // 0x14
    unsigned int nonheap_size; // 0x18
    unsigned int minimum_size; // 0x1C
    unsigned int maximum_size; // 0x20
};
static_assert(sizeof(s_debug_source_file_data) == 0x24, "s_debug_source_file_data");

/* ---------- prototypes */

// defined in cseries_string.cpp
template<typename t_type>
t_type int_min(t_type const & a, t_type const & b);

bool compare_files_by_total_size(void const * element_a, void const * element_b, void const * context);

/* ---------- globals */

char const * k_dump_filename = "heap_dump.txt";
char const * k_dump_filename_csv = "heap_dump.csv";
char const * k_dump_by_file_filename = "heap_by_file_dump.txt";
char const * k_checkpoint_filename = "memusage.txt";

static s_debug_memory_reporting_state g_reporting_state;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<class c_debug_memory_reporter *, 8>::k_element_count; // "?k_element_count@?$s_static_array@PAVc_debug_memory_reporter@@$07@@2JB"
// char const *const k_dump_filename; // "?k_dump_filename@@3PBDB"
// char const *const k_dump_filename_csv; // "?k_dump_filename_csv@@3PBDB"
// char const *const k_dump_by_file_filename; // "?k_dump_by_file_filename@@3PBDB"
// char const *const k_checkpoint_filename; // "?k_checkpoint_filename@@3PBDB"

// void debug_memory_register_reporter(class c_debug_memory_reporter *);
// void debug_memory_unregister_reporter(class c_debug_memory_reporter const *);
// void debug_memory_reporters_report_usage(void);
// long debug_memory_reporters_upload_usage(long, class c_file_path *);
// void debug_dump_memory(void);
// void debug_dump_memory_by_file(void);
// void debug_dump_memory_for_file(char const *);
// void const * get_base_pointer_from_header_const(struct s_pointer_header const *);
// bool memory_is_physical_address(void const *);
// public: bool c_simple_file::is_open(void) const;
// void debug_dump_out_of_memory(char const *, long);
// void debug_dump_memory_brief(long, char *);
// void debug_report_memory_checkpoint(char const *, char const *, long, __int64, struct s_base_memory_information const *, __int64, struct s_base_memory_information const *);
// void debug_alloc_failed(unsigned int, unsigned int, enum e_alloc_failed_type, char const *, long, long, char const *, char const *, char const *);
// long debug_memory_get_minidump_block_count(void);
// void debug_memory_write_minidump_memory_stream(class c_debug_memory_minidump_writer *);
// long debug_memory_start_upload_heap_dump(long, class c_file_path *);
// bool compare_files_by_total_size(void const *, void const *, void const *);
// void debug_dump_memory_erase_files(void);
// void platform_report_out_of_memory(void);
// void platform_report_dump_memory(void);
// public: static long s_static_array<class c_debug_memory_reporter *, 8>::get_count(void);
// public: bool c_static_stack<struct s_debug_source_file_data, 512>::valid(long) const;
// public: bool c_static_stack<struct s_debug_source_file_data, 512>::empty(void) const;
// public: long c_static_stack<struct s_debug_source_file_data, 512>::count(void) const;
// public: long c_static_stack<struct s_debug_source_file_data, 512>::push(void);
// public: struct s_debug_source_file_data & c_static_stack<struct s_debug_source_file_data, 512>::operator[](long);
// public: struct s_debug_source_file_data * c_static_stack<struct s_debug_source_file_data, 512>::get(long);
// public: struct s_debug_source_file_data * c_static_stack<struct s_debug_source_file_data, 512>::get_elements(void);
// public: c_static_stack<struct s_debug_source_file_data, 512>::c_static_stack<struct s_debug_source_file_data, 512>(void);
// public: bool c_static_stack<struct s_debug_source_file_data, 512>::valid(void) const;
// public: bool c_static_stack<struct s_debug_source_file_data, 512>::full(void) const;
// public: class c_debug_memory_reporter *& s_static_array<class c_debug_memory_reporter *, 8>::operator[]<long>(long);
// public: static bool s_static_array<class c_debug_memory_reporter *, 8>::valid<long>(long);
// public: s_debug_memory_reporting_state::s_debug_memory_reporting_state(void);
// public: s_debug_memory_reporting_state::~s_debug_memory_reporting_state(void);
// void g_reporting_state::`dynamic atexit destructor'(void);

void debug_memory_register_reporter(c_debug_memory_reporter * reporter)
{
    mangled_ppc("?debug_memory_register_reporter@@YAXPAVc_debug_memory_reporter@@@Z");

    bool added = false;
    assert_tag_debug_untracked_jul_11_2011(105, reporter);
    assert_tag_debug_untracked_jul_11_2011(106, thread_can_use_debug_memory());

    for (long reporter_index = 0; reporter_index < g_reporting_state.reporters.get_count(); reporter_index++)
    {
        if (!g_reporting_state.reporters[reporter_index])
        {
            g_reporting_state.reporters[reporter_index] = reporter;
            added = true;
            break;
        }
    }

    dassert_tag_debug_untracked_jul_11_2011(118, added, "failed to add reporter, increase k_debug_memory_maximum_reporters");
};

void debug_memory_unregister_reporter(c_debug_memory_reporter const * reporter)
{
    mangled_ppc("?debug_memory_unregister_reporter@@YAXPBVc_debug_memory_reporter@@@Z");

    assert_tag_debug_untracked_jul_11_2011(124, thread_can_use_debug_memory());

    for (long reporter_index = 0; reporter_index < g_reporting_state.reporters.get_count(); reporter_index++)
    {
        if (g_reporting_state.reporters[reporter_index] == reporter)
        {
            g_reporting_state.reporters[reporter_index] = NULL;
            break;
        }
    }
};

void debug_memory_reporters_report_usage(void)
{
    mangled_ppc("?debug_memory_reporters_report_usage@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(139, thread_can_use_debug_memory());

    for (long reporter_index = 0; reporter_index < g_reporting_state.reporters.get_count(); reporter_index++)
    {
        if (g_reporting_state.reporters[reporter_index])
        {
            g_reporting_state.reporters[reporter_index]->report_usage();
        }
    }
};

long debug_memory_reporters_upload_usage(long maximum_file_count, c_file_path * files)
{
    mangled_ppc("?debug_memory_reporters_upload_usage@@YAJJPAVc_file_path@@@Z");

    long file_count = 0;
    assert_tag_debug_untracked_jul_11_2011(156, thread_can_use_debug_memory());

    for (long reporter_index = 0; reporter_index < g_reporting_state.reporters.get_count(); reporter_index++)
    {
        if (g_reporting_state.reporters[reporter_index])
        {
            file_count += g_reporting_state.reporters[reporter_index]->upload_report(maximum_file_count - file_count, &files[file_count]);
            assert_tag_debug_untracked_jul_11_2011(163, file_count<=maximum_file_count);
        }
    }

    return file_count;
};

void debug_dump_memory(void)
{
    mangled_ppc("?debug_dump_memory@@YAXXZ");

    platform_report_dump_memory();
    debug_memory_free_emergency_reserve();
    debug_dump_memory_erase_files();
    debug_dump_memory_by_file();
    debug_dump_memory_for_file(NULL);
    debug_memory_reporters_report_usage();
};

void debug_dump_memory_by_file(void)
{
    mangled_ppc("?debug_dump_memory_by_file@@YAXXZ");

    c_static_stack<s_debug_source_file_data, 512> files;
    long total_count = 0;
    unsigned int total_size = 0;
    long heap_count = 0;
    unsigned int heap_size = 0;
    long nonheap_count = 0;
    unsigned int nonheap_size = 0;
    s_pointer_header const * header = get_heap_queue();

    debug_verify_memory(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 197);

    while (header)
    {
        long file_index;
        for (file_index = 0; file_index < files.count(); file_index++)
        {
            if (header->tracking->file == files[file_index].name)
            {
                break;
            }
        }

        if (file_index == files.count())
        {
            s_debug_source_file_data * file = files.get(files.push());
            csmemset(file, 0, sizeof(s_debug_source_file_data));
            file->name = header->tracking->file;
            file->minimum_size = 0xFFFFFFFF;
            file->maximum_size = 0;
        }

        assert_tag_debug_untracked_jul_11_2011(220, files.valid(file_index));

        total_count++;
        total_size += header->size;
        files[file_index].total_count++;
        files[file_index].total_size += header->size;

        if (!header->nonheap_resource)
        {
            heap_count++;
            heap_size += header->size;
            files[file_index].heap_count++;
            files[file_index].heap_size += header->size;
        }
        else
        {
            nonheap_count++;
            nonheap_size += header->size;
            files[file_index].nonheap_count++;
            files[file_index].nonheap_size += header->size;
        }

        files[file_index].minimum_size = int_min(files[file_index].minimum_size, header->size);
        files[file_index].maximum_size = int_max(files[file_index].maximum_size, header->size);

        header = header->next;
    }

    if (!files.empty())
    {
        long file_index;
        c_simple_file file(k_dump_by_file_filename);
        if (file.open(FLAG(_simple_file_open_write_bit)))
        {
            s_static_string<256> str;

            qsort_elements(files.get_elements(), files.count(), sizeof(s_debug_source_file_data), compare_files_by_total_size, NULL);

            str.print("%-65s %12s %12s %6s %12s %6s %12s %12s %11s\n", "file", "bytes", "heap size", "blocks", "nonheap size", "blocks", "min", "max", "avg");
            file.print(str);

            for (file_index = 0; file_index < files.count(); file_index++)
            {
                str.print("%-65s %12d %12d %6d %12d %6d %12d %12d %11.1f\n",
                    files[file_index].name,
                    files[file_index].total_size,
                    files[file_index].heap_size,
                    files[file_index].heap_count,
                    files[file_index].nonheap_size,
                    files[file_index].nonheap_count,
                    files[file_index].minimum_size,
                    files[file_index].maximum_size,
                    static_cast<real>(files[file_index].total_size) / static_cast<real>(files[file_index].total_count));
                file.print(str);
            }

            s_base_memory_information base_information;
            base_memory_information_get(&base_information);

            s_debug_memory_information information;
            debug_memory_get_memory_information(&information);

            if (heap_size != information.current_heap_size)
            {
                event(_event_error, "memory:debug_memory: heap size mismatch actual=%d != tracked=%d", heap_size, information.current_heap_size);
            }

            if (nonheap_size + information.pretracked_nonheap_size != information.current_nonheap_size)
            {
                event(_event_error, "memory:debug_memory: heap size mismatch actual=%d pretracked=%d sum=%d != tracked=%d", nonheap_size, information.pretracked_nonheap_size, nonheap_size + information.pretracked_nonheap_size, information.current_nonheap_size);
            }

            total_size += information.pretracked_nonheap_size;
            assert_tag_debug_untracked_jul_11_2011(294, total_size==information.current_heap_size+information.current_nonheap_size);

            file.printf("\n");
            file.printf("largest sizes: heap %d bytes, nonheap %d bytes\n", information.largest_heap_size, information.largest_nonheap_size);
            file.printf("current sizes: %d bytes (heap %d in %d blocks, nonheap %d in %d blocks + %d pretracked)\n", total_size, heap_size, heap_count, nonheap_size, nonheap_count, information.pretracked_nonheap_size);
            file.printf("physical usage: %d bytes (%d bytes free, %d bytes total)\n", base_information.total - base_information.free, base_information.free, base_information.total);
            file.printf("\n");
            file.close();
        }
    }
};

void debug_dump_memory_for_file(char const * file_filter)
{
    mangled_ppc("?debug_dump_memory_for_file@@YAXPBD@Z");

    c_simple_file dump_file(k_dump_filename);
    c_simple_file csv_file(k_dump_filename_csv);
    unsigned int sum_allocated = 0;
    unsigned int actual_sum_alloc = 0;
    unsigned int virtual_alloc = 0;
    unsigned int physical_alloc = 0;

    assert_tag_debug_untracked_jul_11_2011(322, thread_can_use_debug_memory());

    debug_verify_memory(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 324);

    for (long queue_index = 0; queue_index < 2; queue_index++)
    {
        s_pointer_header const * header = queue_index == 0 ? get_heap_queue() : get_free_queue();
        if (header)
        {
            while (header && header->next)
            {
                header = header->next;
            }

            while (header)
            {
                if (!file_filter || header->tracking->file && strstr_debug(header->tracking->file, file_filter))
                {
                    char type_string[256];
                    void const * base_address = header->nonheap_resource ? header->nonheap_resource : get_base_pointer_from_header_const(header);

                    if (!dump_file.is_open())
                    {
                        output_debug_string("\n### MEMORY LEAKS DETECTED ###. Check root folder for heap_dump.txt!\n");
                        if (!dump_file.open(FLAG(_simple_file_open_write_bit)))
                        {
                            break;
                        }

                        dump_file.printf("%-65s %5s %10s       %10s   %-80s %75s %10s %10s %10s %10s %10s %10s %18s\n", "file", "line", "size", "real-size", "type/subtype", "name", "heap?", "id", "total-free", "address", "hex-addr", "sum-alloc", "actual-sum-alloc");
                    }

                    if (!csv_file.is_open())
                    {
                        if (!csv_file.open(FLAG(_simple_file_open_write_bit)))
                        {
                            break;
                        }

                        csv_file.printf("%s\n", "file,line,size,real-size,type,subtype,name,heap?,id,total-free,address,hex-addr,sum-alloc,actual-sum-alloc");
                    }

                    if (!header->tracking->type)
                    {
                        csstrnzcpy(type_string, "", sizeof(type_string));
                    }
                    else if (!header->tracking->subtype)
                    {
                        csstrnzcpy(type_string, header->tracking->type, sizeof(type_string));
                    }
                    else
                    {
                        csnzprintf(type_string, sizeof(type_string), "%s/%s", header->tracking->type, header->tracking->subtype);
                    }

                    if (queue_index == 0)
                    {
                        sum_allocated += header->size;
                        actual_sum_alloc += header_get_actual_size(header);
                        if (memory_is_physical_address(base_address))
                        {
                            physical_alloc += header_get_actual_size(header);
                        }
                        else
                        {
                            virtual_alloc += header_get_actual_size(header);
                        }
                    }

                    dump_file.printf("%-65s %5d %10d %s %10d   %-80s %75s %10c %10d %10d %10u %10p %10d %18d\n",
                        safe_printable_string(header->tracking->file),
                        header->tracking->line,
                        header->size,
                        queue_index == 0 ? "bytes" : "freed",
                        header_get_actual_size(header),
                        type_string,
                        safe_printable_string(header->tracking->name),
                        header->nonheap_resource ? 'n' : 'h',
                        header->identifier,
                        header->total_free_at_allocation,
                        base_address,
                        base_address,
                        sum_allocated,
                        actual_sum_alloc);

                    if (queue_index == 0)
                    {
                        csv_file.printf("%s,%d,%d,%d,%s,%s,%s,%c,%d,%d,%u,%p,%d,%d\n",
                            safe_printable_string(header->tracking->file),
                            header->tracking->line,
                            header->size,
                            header_get_actual_size(header),
                            safe_printable_string(header->tracking->type),
                            safe_printable_string(header->tracking->subtype),
                            safe_printable_string(header->tracking->name),
                            header->nonheap_resource ? 'n' : 'h',
                            header->identifier,
                            header->total_free_at_allocation,
                            base_address,
                            base_address,
                            sum_allocated,
                            actual_sum_alloc);
                    }

                    if (file_filter || g_reporting_state.dump_to_output)
                    {
                        char output[2048];
                        csnzprintf(output, sizeof(output), "%s(%d): %d %s %s %s(%d) %c%d %d\n",
                            safe_printable_string(header->tracking->file),
                            header->tracking->line,
                            header->size,
                            queue_index == 0 ? "bytes" : "freed",
                            type_string,
                            safe_printable_string(header->tracking->name),
                            header->type_identifier,
                            header->nonheap_resource ? 'n' : 'h',
                            header->identifier,
                            header->total_free_at_allocation);
                        output_debug_string(output);
                    }
                }

                header = header->previous;
            }
        }
    }

    if (dump_file.is_open())
    {
        char text[2048];
        s_base_memory_information information;
        base_memory_information_get(&information);

        csnzprintf(text, sizeof(text), "\nTotal Base Memory: %d (%.2fM)\nTotal Base Free: %d (%.2fM)\nTotal Allocated: %d bytes (%.2fM)\nTotal Actually Allocated: %d bytes (%.2fM)\nTotal Virtual Tracked: %d (%.2fM)\nTotal Physical Tracked: %d (%.2fM)\n",
            information.total,
            information.total / 1048576.0f,
            information.free,
            information.free / 1048576.0f,
            sum_allocated,
            sum_allocated / 1048576.0f,
            actual_sum_alloc,
            actual_sum_alloc / 1048576.0f,
            virtual_alloc,
            virtual_alloc / 1048576.0f,
            physical_alloc,
            physical_alloc / 1048576.0f);
        output_debug_string(text);
        dump_file.print(text);
    }

    dump_file.close();
    csv_file.close();
};

void debug_dump_out_of_memory(char const * file, long line)
{
    mangled_ppc("?debug_dump_out_of_memory@@YAXPBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(503, thread_can_use_debug_memory());

    s_debug_memory_information information;
    debug_memory_get_memory_information(&information);

    event(_event_critical, "dumping heap usage (currently %d bytes) to %s...", information.current_heap_size + information.current_nonheap_size, k_dump_filename);

    g_reporting_state.out_of_memory = true;
    debug_dump_memory();
};

void debug_dump_memory_brief(long buffer_length, char * out_buffer)
{
    mangled_ppc("?debug_dump_memory_brief@@YAXJPAD@Z");

    assert_tag_debug_untracked_jul_11_2011(524, buffer_length>0);
    assert_tag_debug_untracked_jul_11_2011(525, out_buffer);
    assert_tag_debug_untracked_jul_11_2011(526, thread_can_use_debug_memory());

    csstrnzcpy(out_buffer, "", buffer_length);

    for (long reporter_index = 0; reporter_index < g_reporting_state.reporters.get_count(); reporter_index++)
    {
        if (g_reporting_state.reporters[reporter_index])
        {
            g_reporting_state.reporters[reporter_index]->report_brief(buffer_length, out_buffer);
        }
    }
};

void debug_report_memory_checkpoint(char const * name, char const * file, long line, __int64 start_time, s_base_memory_information const * start_information, __int64 end_time, s_base_memory_information const * end_information)
{
    mangled_ppc("?debug_report_memory_checkpoint@@YAXPBD0J_JPBUs_base_memory_information@@12@Z");

    assert_tag_debug_untracked_jul_11_2011(549, thread_can_use_debug_memory());

    if (!g_reporting_state.checkpoint_initialized)
    {
        if (false)
        {
            g_reporting_state.checkpoint_file.set_debug_filename(k_checkpoint_filename);
            g_reporting_state.checkpoint_file.open(FLAG(_simple_file_open_write_bit));
        }

        g_reporting_state.checkpoint_start_time = start_time;
        g_reporting_state.checkpoint_initialized = true;
    }

    real megabytes_free = end_information->free / 1048576.0f;
    __int64 frequency = system_performance_timer_frequency();
    __int64 elapsed_ticks = end_time - start_time;
    real milliseconds = static_cast<real>(elapsed_ticks) * 1000.0f / static_cast<real>(frequency);
    s_static_string<256> string;
    string.print("%7.3fM %8.2fms %s\n", megabytes_free, milliseconds, name);
    output_debug_string(string);

    if (g_reporting_state.checkpoint_file.is_open())
    {
        g_reporting_state.checkpoint_file.print(string);
        g_reporting_state.checkpoint_file.flush();
    }
};

void debug_alloc_failed(unsigned int size, unsigned int old_size, e_alloc_failed_type type, char const * file, long line, long type_identifier, char const * type_name, char const * subtype_name, char const * name)
{
    mangled_ppc("?debug_alloc_failed@@YAXIIW4e_alloc_failed_type@@PBDJJ111@Z");

    assert_tag_debug_untracked_jul_11_2011(590, thread_can_use_debug_memory());

    debug_memory_free_emergency_reserve();

    if (type == _alloc_failed_nonheap)
    {
        event(_event_critical, "### OUT OF MEMORY: %s line %d failed to allocate a nonheap tracking block: type= '%s', subtype= '%s', name= '%s'", file, line, safe_printable_string(type_name), safe_printable_string(subtype_name), safe_printable_string(name));
    }
    else if (old_size == 0)
    {
        event(_event_critical, "### OUT OF MEMORY: %s line %d failed to allocate %d bytes: type= '%s'(%d), subtype= '%s', name= '%s'", file, line, size, safe_printable_string(type_name), type_identifier, safe_printable_string(subtype_name), safe_printable_string(name));
    }
    else
    {
        event(_event_critical, "### OUT OF MEMORY: %s line %d failed to reallocate %d -> %d bytes: type= '%s'(%d), subtype= '%s', name= '%s'", file, line, old_size, size, safe_printable_string(type_name), type_identifier, safe_printable_string(subtype_name), safe_printable_string(name));
    }

    if (!g_reporting_state.out_of_memory)
    {
        g_reporting_state.out_of_memory = true;
        debug_dump_out_of_memory(file, line);
        platform_report_out_of_memory();
        dassert_tag_debug_untracked_jul_11_2011(620, false, "out of memory: heap_dump.txt created");
    }
};

long debug_memory_get_minidump_block_count(void)
{
    mangled_ppc("?debug_memory_get_minidump_block_count@@YAJXZ");

    s_pointer_header const * header = get_heap_queue();
    long block_count = 0;

    while (header)
    {
        if (!header->nonheap_resource && !header->exclude_from_minidump)
        {
            block_count++;
        }

        header = header->next;
    }

    return block_count;
};

void debug_memory_write_minidump_memory_stream(c_debug_memory_minidump_writer * minidump_stream)
{
    mangled_ppc("?debug_memory_write_minidump_memory_stream@@YAXPAVc_debug_memory_minidump_writer@@@Z");

    s_pointer_header const * header = get_heap_queue();
    assert_tag_debug_untracked_jul_11_2011(652, minidump_stream);

    while (header)
    {
        if (!header->nonheap_resource && !header->exclude_from_minidump)
        {
            unsigned int size = header->size + sizeof(s_pointer_header) + sizeof(s_pointer_trailer);
            minidump_stream->write_memory(header, size);
        }

        header = header->next;
    }
};

long debug_memory_start_upload_heap_dump(long maximum_file_count, c_file_path * out_file_list)
{
    mangled_ppc("?debug_memory_start_upload_heap_dump@@YAJJPAVc_file_path@@@Z");

    long file_count = 0;
    assert_tag_debug_untracked_jul_11_2011(676, out_file_list);
    assert_tag_debug_untracked_jul_11_2011(677, maximum_file_count>=3);
    assert_tag_debug_untracked_jul_11_2011(678, thread_can_use_debug_memory());

    if (g_reporting_state.out_of_memory)
    {
        c_debug_path debug_path;
        c_file_path * file_path = &out_file_list[file_count];
        debug_path.get_path(k_dump_filename, file_path);
        file_count++;
        c_file_path * heap_by_file_dump_path = &out_file_list[file_count];
        debug_path.get_path(k_dump_by_file_filename, heap_by_file_dump_path);
        file_count++;
        c_file_path * csv_path = &out_file_list[file_count];
        debug_path.get_path(k_dump_filename_csv, csv_path);
        file_count++;
    }

    assert_tag_debug_untracked_jul_11_2011(688, file_count<maximum_file_count);
    file_count += debug_memory_reporters_upload_usage(maximum_file_count - file_count, &out_file_list[file_count]);

    return file_count;
};

bool compare_files_by_total_size(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?compare_files_by_total_size@@YA_NPBX00@Z");

    s_debug_source_file_data const * a = static_cast<s_debug_source_file_data const *>(element_a);
    s_debug_source_file_data const * b = static_cast<s_debug_source_file_data const *>(element_b);

    return a->total_size > b->total_size;
};

void debug_dump_memory_erase_files(void)
{
    mangled_ppc("?debug_dump_memory_erase_files@@YAXXZ");

    char const * filenames[] = { k_dump_filename, k_dump_by_file_filename, k_dump_filename_csv };
    c_debug_path debug_path;
    c_file_path file_path;

    for (long filename_index = 0; filename_index < NUMBEROF(filenames); filename_index++)
    {
        debug_path.get_path(filenames[filename_index], &file_path);
        if (file_exists(&file_path))
        {
            file_delete(&file_path);
        }
    }
};

void platform_report_out_of_memory(void)
{
    mangled_ppc("?platform_report_out_of_memory@@YAXXZ");

    unsigned int unused = 0;
    unsigned int busy_size = 0;
    unsigned int leaked = 0;
    unsigned int overhead = 0;
    unsigned int heap_size = 0;
    HANDLE heap = GetProcessHeap();
    PROCESS_HEAP_ENTRY heap_entry = {};

    while (HeapWalk(heap, &heap_entry))
    {
        if ((heap_entry.wFlags & PROCESS_HEAP_REGION) == PROCESS_HEAP_REGION)
        {
            heap_size += heap_entry.cbData;
            overhead += heap_entry.cbOverhead;
        }
        else if ((heap_entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) == PROCESS_HEAP_UNCOMMITTED_RANGE)
        {
            event(_event_warning, "HEAP uncommit: %p   0x%08x   %12d", heap_entry.lpData, heap_entry.cbData, heap_entry.cbData);
            unused += heap_entry.cbData;
            overhead += heap_entry.cbOverhead;
        }
        else if ((heap_entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) == PROCESS_HEAP_ENTRY_BUSY)
        {
            overhead += heap_entry.cbOverhead;
            busy_size += heap_entry.cbData;
            if (heap_entry.cbData >= sizeof(s_pointer_header))
            {
                s_pointer_header const * possible_header = static_cast<s_pointer_header const *>(heap_entry.lpData);
                s_pointer_header * found_header;
                if (query_possible_header(possible_header))
                {
                    // tracked heap allocation
                }
                else if (g_nonheap_hash_table.is_created() && g_nonheap_hash_table.find(heap_entry.lpData, &found_header))
                {
                    // tracked nonheap allocation
                }
                else
                {
                    leaked += heap_entry.cbData;
                    event(_event_warning, "HEAP untracked?: %p   0x%08x   %12d", heap_entry.lpData, heap_entry.cbData, heap_entry.cbData);
                }
            }
        }
    }

    event(_event_warning, "HEAP OVERHEAD: %d", overhead);
    event(_event_warning, "HEAP TOTAL: %d", heap_size);
    event(_event_warning, "HEAP UNUSED: %d", unused);
    event(_event_warning, "HEAP USED: %d", busy_size);
    event(_event_warning, "HEAP LEAKED?: %d", leaked);
};

void platform_report_dump_memory(void)
{
    mangled_ppc("?platform_report_dump_memory@@YAXXZ");
};

