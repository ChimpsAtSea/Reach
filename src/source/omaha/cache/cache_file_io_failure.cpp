#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_io_failure.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_io_failure.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\interface\damaged_media.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_simple_io_result::c_simple_io_result(void);
// public: c_io_result::c_io_result(void);
// public: c_simple_io_result::~c_simple_io_result(void);
// public: bool c_simple_io_result::check_success(void);
// public: bool c_simple_io_result::disk_failure(void) const;
// public: bool c_simple_io_result::checksum_failure(void) const;
// public: bool c_simple_io_result::unknown_failure(void) const;
// public: virtual void c_simple_io_result::set_fail_boat(void);
// public: virtual void c_simple_io_result::set_disk_failure(void);
// public: virtual void c_simple_io_result::set_checksum_failure(void);
// public: void c_simple_io_result::handle_failure(void);

c_simple_io_result::c_simple_io_result(void) :
    m_any_progress(false),
    m_fail_boat(false),
    m_disk_failure(false),
    m_checksum_failure(false),
    m_checked_failure(false)
{
    mangled_ppc("??0c_simple_io_result@@QAA@XZ");
};

c_simple_io_result::~c_simple_io_result(void)
{
    mangled_ppc("??1c_simple_io_result@@QAA@XZ");

    dassert_tag_debug_untracked_jul_11_2011(24, m_checked_failure, "you must check for failure!");
};

bool c_simple_io_result::check_success(void)
{
    mangled_ppc("?check_success@c_simple_io_result@@QAA_NXZ");

    m_checked_failure = true;
    return !m_disk_failure && !m_fail_boat && !m_checksum_failure;
};

bool c_simple_io_result::disk_failure(void) const
{
    mangled_ppc("?disk_failure@c_simple_io_result@@QBA_NXZ");

    return m_disk_failure;
};

bool c_simple_io_result::checksum_failure(void) const
{
    mangled_ppc("?checksum_failure@c_simple_io_result@@QBA_NXZ");

    return m_checksum_failure;
};

bool c_simple_io_result::unknown_failure(void) const
{
    mangled_ppc("?unknown_failure@c_simple_io_result@@QBA_NXZ");

    return m_fail_boat && !m_disk_failure && !m_checksum_failure;
};

void c_simple_io_result::set_fail_boat(void)
{
    mangled_ppc("?set_fail_boat@c_simple_io_result@@UAAXXZ");

    m_fail_boat = true;
};

void c_simple_io_result::set_disk_failure(void)
{
    mangled_ppc("?set_disk_failure@c_simple_io_result@@UAAXXZ");

    m_disk_failure = true;
};

void c_simple_io_result::set_checksum_failure(void)
{
    mangled_ppc("?set_checksum_failure@c_simple_io_result@@UAAXXZ");

    m_checksum_failure = true;
};

void c_simple_io_result::handle_failure(void)
{
    mangled_ppc("?handle_failure@c_simple_io_result@@QAAXXZ");

    damaged_media_halt_and_display_error("c_simple_io_result: i/o failed: fail_boat %d, disk %d, checksum %d", m_fail_boat, m_disk_failure, m_checksum_failure);
};
