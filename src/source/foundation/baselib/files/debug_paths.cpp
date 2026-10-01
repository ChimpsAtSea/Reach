#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\baselib\files\debug_paths.cpp"
/* ---------- headers */

#include "foundation\baselib\files\debug_paths.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const k_crash_report_directory = "crash_report\\";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const k_crash_report_directory; // "?k_crash_report_directory@@3PBDB"

// public: c_debug_path::c_debug_path(void);
// public: enum e_file_location c_debug_path::get_location(void);
// public: char const * c_debug_path::get_full_path(char const *);
// public: void c_debug_path::get_path(char const *, class c_file_path *);
// public: void c_debug_path::get_directory_path(char const *, class c_file_path *);
// private: void c_debug_path::build_output_location_if_necessary(void);
// public: c_crash_report_path::c_crash_report_path(void);
// public: enum e_file_location c_crash_report_path::get_location(void);
// public: char const * c_crash_report_path::get_full_path(char const *);
// public: void c_crash_report_path::get_path(char const *, class c_file_path *);
// public: void c_crash_report_path::get_directory_path(char const *, class c_file_path *);
// private: void c_crash_report_path::build_crash_report_location_if_necessary(void);

c_debug_path::c_debug_path(void)
{
    mangled_ppc("??0c_debug_path@@QAA@XZ");

    m_location = k_file_location_invalid;
    m_path.clear();
    m_full_path.clear();
};

e_file_location c_debug_path::get_location(void)
{
    mangled_ppc("?get_location@c_debug_path@@QAA?AW4e_file_location@@XZ");

    build_output_location_if_necessary();
    return m_location;
};

char const * c_debug_path::get_full_path(char const * filename)
{
    mangled_ppc("?get_full_path@c_debug_path@@QAAPBDPBD@Z");

    m_path.set_file_path(get_location(), filename);
    return m_path.get_full_path(&m_full_path);
};

void c_debug_path::get_path(char const * filename, c_file_path * out_path)
{
    mangled_ppc("?get_path@c_debug_path@@QAAXPBDPAVc_file_path@@@Z");

    assert_tag_debug_untracked_jul_11_2011(50, out_path);
    out_path->set_file_path(get_location(), filename);
};

void c_debug_path::get_directory_path(char const * directory, c_file_path * out_directory_path)
{
    mangled_ppc("?get_directory_path@c_debug_path@@QAAXPBDPAVc_file_path@@@Z");

    assert_tag_debug_untracked_jul_11_2011(58, out_directory_path);
    out_directory_path->set_directory_path(get_location(), directory);
};

void c_debug_path::build_output_location_if_necessary(void)
{
    mangled_ppc("?build_output_location_if_necessary@c_debug_path@@AAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(68, file_location_available(_file_location_development_relative, _file_location_write));
    m_location = _file_location_development_relative;
};

c_crash_report_path::c_crash_report_path(void)
{
    mangled_ppc("??0c_crash_report_path@@QAA@XZ");

    m_location = k_file_location_invalid;
    m_directory.clear();
    m_path.clear();
    m_full_path.clear();
};

e_file_location c_crash_report_path::get_location(void)
{
    mangled_ppc("?get_location@c_crash_report_path@@QAA?AW4e_file_location@@XZ");

    build_crash_report_location_if_necessary();
    return m_location;
};

char const * c_crash_report_path::get_full_path(char const * filename)
{
    mangled_ppc("?get_full_path@c_crash_report_path@@QAAPBDPBD@Z");

    get_path(filename, &m_path);
    return m_path.get_full_path(&m_full_path);
};

void c_crash_report_path::get_path(char const * filename, c_file_path * out_path)
{
    mangled_ppc("?get_path@c_crash_report_path@@QAAXPBDPAVc_file_path@@@Z");

    assert_tag_debug_untracked_jul_11_2011(100, out_path);
    out_path->set_directory_path(get_location(), m_directory.get_string());
    out_path->set_filename(filename);
};

void c_crash_report_path::get_directory_path(char const * directory, c_file_path * out_directory_path)
{
    mangled_ppc("?get_directory_path@c_crash_report_path@@QAAXPBDPAVc_file_path@@@Z");

    assert_tag_debug_untracked_jul_11_2011(109, out_directory_path);
    out_directory_path->set_directory_path(get_location(), m_directory.get_string());
    out_directory_path->add_directory(directory);
};

void c_crash_report_path::build_crash_report_location_if_necessary(void)
{
    mangled_ppc("?build_crash_report_location_if_necessary@c_crash_report_path@@AAAXXZ");

    m_location = _file_location_development_relative;
    c_debug_path debug_path;
    m_location = debug_path.get_location();
    m_directory.clear();
};

