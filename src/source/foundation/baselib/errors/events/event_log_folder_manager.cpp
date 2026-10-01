#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_log_folder_manager.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_log_folder_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\files\debug_paths.h"
#include "foundation\baselib\files\file_path.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const k_reports_directory_name = "reports";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const k_reports_directory_name; // "?k_reports_directory_name@@3PBDB"

// public: void c_event_log_folder_manager::initialize(void);
// public: void c_event_log_folder_manager::dispose(void);
// public: void c_event_log_folder_manager::obtain_report_directory_lock(void);
// public: void c_event_log_folder_manager::release_report_directory_lock(void);
// public: bool c_event_log_folder_manager::has_subfolder(void) const;
// public: bool c_event_log_folder_manager::get_subfolder(long, char *) const;
// public: void c_event_log_folder_manager::set_subfolder(char const *);
// public: void c_event_log_folder_manager::build_report_file_path(char const *, enum e_report_file_location, class c_file_path *) const;

void c_event_log_folder_manager::initialize(void)
{
    mangled_ppc("?initialize@c_event_log_folder_manager@@QAAXXZ");

    m_subfolder.clear();
};

void c_event_log_folder_manager::dispose(void)
{
    mangled_ppc("?dispose@c_event_log_folder_manager@@QAAXXZ");

    release_report_directory_lock();
};

void c_event_log_folder_manager::obtain_report_directory_lock(void)
{
    mangled_ppc("?obtain_report_directory_lock@c_event_log_folder_manager@@QAAXXZ");
};

void c_event_log_folder_manager::release_report_directory_lock(void)
{
    mangled_ppc("?release_report_directory_lock@c_event_log_folder_manager@@QAAXXZ");
};

bool c_event_log_folder_manager::has_subfolder(void) const
{
    mangled_ppc("?has_subfolder@c_event_log_folder_manager@@QBA_NXZ");

    return !m_subfolder.is_empty();
};

bool c_event_log_folder_manager::get_subfolder(long subfolder_length, char * out_subfolder) const
{
    mangled_ppc("?get_subfolder@c_event_log_folder_manager@@QBA_NJPAD@Z");

    m_subfolder.copy_to(out_subfolder, subfolder_length);

    return has_subfolder();
};

void c_event_log_folder_manager::set_subfolder(char const * subfolder)
{
    mangled_ppc("?set_subfolder@c_event_log_folder_manager@@QAAXPBD@Z");

    if (subfolder)
    {
        m_subfolder.set(subfolder);
    }
    else
    {
        m_subfolder.clear();
    }
};

void c_event_log_folder_manager::build_report_file_path(char const * filename, e_report_file_location location, c_file_path * out_path) const
{
    mangled_ppc("?build_report_file_path@c_event_log_folder_manager@@QBAXPBDW4e_report_file_location@@PAVc_file_path@@@Z");

    c_debug_path debug_path;

    assert_tag_debug_untracked_jul_11_2011(146, out_path);

    if (location == 0 || has_subfolder())
    {
        debug_path.get_directory_path(k_reports_directory_name, out_path);
    }
    else
    {
        debug_path.get_directory_path("", out_path);
    }

    if (has_subfolder())
    {
        out_path->add_directory(m_subfolder.get_string());
    }

    out_path->set_filename(filename);
};
