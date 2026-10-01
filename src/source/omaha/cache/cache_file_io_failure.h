#pragma once
#ifndef __CACHE_FILE_IO_FAILURE_H__
#define __CACHE_FILE_IO_FAILURE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_io_result
{
public:
    c_io_result()
    {
        mangled_ppc("??0c_io_result@@QAA@XZ");
    };

    virtual void set_fail_boat(void) = 0;
    virtual void set_disk_failure(void) = 0;
    virtual void set_checksum_failure(void) = 0;
};
static_assert(sizeof(c_io_result) == 0x4, "c_io_result");

class c_simple_io_result :
    public c_io_result
{
public:
    c_simple_io_result(void);
    ~c_simple_io_result(void);
    bool check_success(void);
    bool disk_failure(void) const;
    bool checksum_failure(void) const;
    bool unknown_failure(void) const;
    virtual void set_fail_boat(void);
    virtual void set_disk_failure(void);
    virtual void set_checksum_failure(void);
    void handle_failure(void);

private:
    bool m_any_progress; // 0x4
    bool m_fail_boat; // 0x5
    bool m_disk_failure; // 0x6
    bool m_checksum_failure; // 0x7
    bool m_checked_failure; // 0x8
};
static_assert(sizeof(c_simple_io_result) == 0xC, "c_simple_io_result");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_IO_FAILURE_H__

