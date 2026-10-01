#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_log_manager.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_log_manager.h"
#include "core\corelib\config\version.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\errors\events\event_log_cache.h"
#include "foundation\baselib\errors\events\event_log_folder_manager.h"
#include "foundation\baselib\files\file_synchronous_io.h"
#include "foundation\baselib\files\file_synchronous_utilities.h"
#include "foundation\baselib\files\file_synchronous_utilities_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern char const * const k_banner_string = "============================================================================================";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const k_banner_string; // "?k_banner_string@@3PBDB"

// public: void c_event_log_manager::initialize(class c_event_log_folder_manager *);
// public: void c_event_log_manager::dispose(void);
// public: enum e_event_log_index c_event_log_manager::create_log(char const *, class s_flags<enum e_event_log_flags, unsigned long, 5>);
// public: bool c_event_log_manager::log_is_valid(enum e_event_log_index) const;
// public: void c_event_log_manager::begin_writing(enum e_event_log_index);
// public: void c_event_log_manager::write_to_log(enum e_event_log_index, enum c_event_log_manager::e_write_buffer_mode, char const *);
// public: void c_event_log_manager::flush_all_open_logs(void);
// public: bool c_event_log_manager::get_retain_open_files(void) const;
// public: void c_event_log_manager::touch_all_logs(void);
// public: void c_event_log_manager::close_all_logs(void);
// public: void c_event_log_manager::reset_all_logs_for_redirect(void);
// public: long c_event_log_manager::get_log_paths(long, class c_file_path *);
// private: static bool c_event_log_manager::can_write_to_event_log(struct c_event_log_manager::s_event_log const *, bool);
// private: bool c_event_log_manager::log_file_open(enum e_event_log_index);
// private: void c_event_log_manager::log_file_write_internal(enum e_event_log_index, enum c_event_log_manager::e_write_buffer_mode, char const *);
// private: void c_event_log_manager::log_file_close(enum e_event_log_index);
// private: enum e_event_log_index c_event_log_manager::find_existing_event_log(char const *, class s_flags<enum e_event_log_flags, unsigned long, 5>);
// public: bool c_static_stack<struct c_event_log_manager::s_event_log, 32>::valid(long) const;
// public: bool c_static_stack<struct c_event_log_manager::s_event_log, 32>::full(void) const;
// public: long c_static_stack<struct c_event_log_manager::s_event_log, 32>::count(void) const;
// public: void c_static_stack<struct c_event_log_manager::s_event_log, 32>::clear(void);
// public: long c_static_stack<struct c_event_log_manager::s_event_log, 32>::push(void);
// public: struct c_event_log_manager::s_event_log * c_static_stack<struct c_event_log_manager::s_event_log, 32>::get(long);
// public: unsigned char * s_static_array<unsigned char, 65536>::get_elements(void);
// public: unsigned int s_static_array<unsigned char, 65536>::get_total_element_size(void) const;
// public: bool c_static_stack<struct c_event_log_manager::s_event_log, 32>::valid(void) const;
// public: bool s_flags<enum e_event_log_flags, unsigned long, 5>::test(enum e_event_log_flags) const;
// public: bool s_flags<enum e_event_log_flags, unsigned long, 5>::operator==(class s_flags<enum e_event_log_flags, unsigned long, 5> const &) const;
// public: char * c_file_path::get_full_path<256>(char (&)[256]) const;

void c_event_log_manager::initialize(c_event_log_folder_manager * folder_manager)
{
    mangled_ppc("?initialize@c_event_log_manager@@QAAXPAVc_event_log_folder_manager@@@Z");

    assert_tag_debug_untracked_jul_11_2011(29, folder_manager);

    m_folder_manager = folder_manager;
    m_retain_open_files = false;
    m_logs.clear();
};

void c_event_log_manager::dispose(void)
{
    mangled_ppc("?dispose@c_event_log_manager@@QAAXXZ");

    close_all_logs();
    m_logs.clear();
};

e_event_log_index c_event_log_manager::create_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags)
{
    mangled_ppc("?create_log@c_event_log_manager@@QAA?AW4e_event_log_index@@PBDV?$s_flags@W4e_event_log_flags@@K$04@@@Z");

    e_event_log_index event_log_index = static_cast<e_event_log_index>(-1);
    assert_tag_debug_untracked_jul_11_2011(49, filename);

    event_log_index = find_existing_event_log(filename, flags);
    if (event_log_index == -1 && !m_logs.full())
    {
        s_event_log * event_log = NULL;
        event_log_index = static_cast<e_event_log_index>(m_logs.push());
        event_log = m_logs.get(event_log_index);
        csmemset(event_log, 0, sizeof(s_event_log));
        event_log->filename.set(filename);
        event_log->flags = flags;
    }

    return event_log_index;
};

bool c_event_log_manager::log_is_valid(e_event_log_index event_log_index) const
{
    mangled_ppc("?log_is_valid@c_event_log_manager@@QBA_NW4e_event_log_index@@@Z");

    return m_logs.valid(event_log_index);
};

void c_event_log_manager::begin_writing(e_event_log_index event_log_index)
{
    mangled_ppc("?begin_writing@c_event_log_manager@@QAAXW4e_event_log_index@@@Z");

    s_event_log * event_log = m_logs.get(event_log_index);
    if (can_write_to_event_log(event_log, m_folder_manager->has_subfolder()))
    {
        log_file_open(event_log_index);
    }
};

void c_event_log_manager::write_to_log(e_event_log_index event_log_index, e_write_buffer_mode mode, char const * string)
{
    mangled_ppc("?write_to_log@c_event_log_manager@@QAAXW4e_event_log_index@@W4e_write_buffer_mode@1@PBD@Z");

    s_event_log * event_log = m_logs.get(event_log_index);
    if (!event_log->file_open)
    {
        begin_writing(event_log_index);
    }

    if (event_log->file_open)
    {
        if (!event_log->unknown106)
        {
            s_static_string<1024> banner;
            banner.print("\r\n\r\n%s\r\n%s\r\n%s\r\n\r\n\r\n", k_banner_string, version_get_full_string(), k_banner_string);
            log_file_write_internal(event_log_index, mode, banner.get_string());
            event_log->unknown106 = true;
        }

        log_file_write_internal(event_log_index, mode, string);
    }
};

void c_event_log_manager::flush_all_open_logs(void)
{
    mangled_ppc("?flush_all_open_logs@c_event_log_manager@@QAAXXZ");

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < m_logs.count(); ++event_log_index)
    {
        s_event_log * event_log = m_logs.get(event_log_index);
        if (event_log->file_open)
        {
            event_log->output_buffer.flush();
            if (!get_retain_open_files())
            {
                log_file_close(event_log_index);
            }
        }
    }
};

void c_event_log_manager::touch_all_logs(void)
{
    mangled_ppc("?touch_all_logs@c_event_log_manager@@QAAXXZ");

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < m_logs.count(); ++event_log_index)
    {
        write_to_log(event_log_index, _write_buffer_mode_flush, "");
    }
};

void c_event_log_manager::close_all_logs(void)
{
    mangled_ppc("?close_all_logs@c_event_log_manager@@QAAXXZ");

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < m_logs.count(); ++event_log_index)
    {
        s_event_log * event_log = m_logs.get(event_log_index);
        if (event_log->file_open)
        {
            log_file_close(event_log_index);
        }
    }
};

void c_event_log_manager::reset_all_logs_for_redirect(void)
{
    mangled_ppc("?reset_all_logs_for_redirect@c_event_log_manager@@QAAXXZ");

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < m_logs.count(); ++event_log_index)
    {
        s_event_log * event_log = m_logs.get(event_log_index);
        if (event_log->file_open)
        {
            log_file_close(event_log_index);
            event_log->path_built = false;
        }
    }
};

long c_event_log_manager::get_log_paths(long maximum_file_count, c_file_path * out_log_paths)
{
    mangled_ppc("?get_log_paths@c_event_log_manager@@QAAJJPAVc_file_path@@@Z");

    long log_path_count = 0;
    assert_tag_debug_untracked_jul_11_2011(191, out_log_paths);

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < m_logs.count(); ++event_log_index)
    {
        s_event_log * event_log = m_logs.get(event_log_index);
        if (event_log->opened_at_least_once && log_path_count < maximum_file_count)
        {
            out_log_paths[log_path_count] = event_log->path;
            log_path_count++;
        }
    }

    return log_path_count;
};

bool c_event_log_manager::can_write_to_event_log(s_event_log const * event_log, bool has_subfolder)
{
    mangled_ppc("?can_write_to_event_log@c_event_log_manager@@CA_NPBUs_event_log@1@_N@Z");

    return has_subfolder ? !event_log->flags.test(_event_log_disable_file_trimming) : !event_log->flags.test(_event_log_only_for_custom_subfolder);
};

bool c_event_log_manager::log_file_open(e_event_log_index event_log_index)
{
    mangled_ppc("?log_file_open@c_event_log_manager@@AAA_NW4e_event_log_index@@@Z");

    s_event_log * event_log = m_logs.get(event_log_index);
    if (!event_log->file_open)
    {
        if (!event_log->path_built)
        {
            e_report_file_location location = static_cast<e_report_file_location>(event_log->flags.test(_event_log_place_in_root_bit) != false);
            e_file_overwrite_mode overwrite_mode = static_cast<e_file_overwrite_mode>(!event_log->flags.test(_event_log_append_to_file_bit));
            m_folder_manager->build_report_file_path(event_log->filename, location, &event_log->path);
            event_log->path_built = true;
            file_create_parent_directories(&event_log->path);
            file_create(&event_log->path, overwrite_mode);

            if (event_log->flags.test(_event_log_trim_file_bit))
            {
                unsigned int const k_maximum_log_file_size = 0x40000;
                file_trim_fast(&event_log->path, k_maximum_log_file_size, m_file_buffer.get_elements(), m_file_buffer.get_total_element_size());
            }
        }

        {
            c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> open_flags;
            open_flags.set(_file_open_write_bit, true);
            open_flags.set(_file_open_write_append_bit, true);
            open_flags.set(_file_open_write_allow_read_bit, true);
            if (file_open(&event_log->path, open_flags, _file_error_mode_report, &event_log->file) == _file_open_result_success)
            {
                event_log->output_buffer.attach_file(&event_log->file);
                event_log->file_open = true;
                event_log->opened_at_least_once = true;
            }
            else
            {
                s_static_string<256> full_path;
                events_internal_error("events:log_manager: failed to open log file '%s'", event_log->path.get_full_path(full_path.get_buffer()));
            }
        }
    }

    return event_log->file_open;
};

void c_event_log_manager::log_file_write_internal(e_event_log_index event_log_index, e_write_buffer_mode mode, char const * string)
{
    mangled_ppc("?log_file_write_internal@c_event_log_manager@@AAAXW4e_event_log_index@@W4e_write_buffer_mode@1@PBD@Z");

    s_event_log * event_log = m_logs.get(event_log_index);
    if (event_log->file_open)
    {
        long string_length = csstrnlen(string, 2048);
        if (mode == _write_buffer_mode_buffered)
        {
            event_log->output_buffer.write(string_length, string);
        }
        else
        {
            event_log->output_buffer.flush();
            file_print(&event_log->file, string);
        }
    }
};

void c_event_log_manager::log_file_close(e_event_log_index event_log_index)
{
    mangled_ppc("?log_file_close@c_event_log_manager@@AAAXW4e_event_log_index@@@Z");

    s_event_log * event_log = m_logs.get(event_log_index);
    if (event_log->file_open)
    {
        event_log->output_buffer.release_file();
        file_close(&event_log->file);
        event_log->file_open = false;
    }
};

e_event_log_index c_event_log_manager::find_existing_event_log(char const * filename, s_flags<e_event_log_flags, unsigned long, k_event_log_flag_count> flags)
{
    mangled_ppc("?find_existing_event_log@c_event_log_manager@@AAA?AW4e_event_log_index@@PBDV?$s_flags@W4e_event_log_flags@@K$04@@@Z");

    e_event_log_index existing_event_log_index = static_cast<e_event_log_index>(-1);
    assert_tag_debug_untracked_jul_11_2011(316, filename);

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); existing_event_log_index == -1 && event_log_index < m_logs.count(); ++event_log_index)
    {
        s_event_log * event_log = m_logs.get(event_log_index);
        if (event_log->filename.is_equal(filename) && event_log->flags == flags)
        {
            existing_event_log_index = event_log_index;
        }
    }

    return existing_event_log_index;
};
