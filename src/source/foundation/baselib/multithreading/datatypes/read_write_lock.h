#pragma once
#ifndef __READ_WRITE_LOCK_H__
#define __READ_WRITE_LOCK_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\semaphore_windows.h"

/* ---------- constants */

/* ---------- definitions */

class c_read_write_lock
{
public:
    c_read_write_lock(void);
    ~c_read_write_lock(void);

    void initialize_automatic(char const * critical_section_name, char const * semaphore_name);
    void initialize_manual(s_critical_section write_lock, s_semaphore read_lock);
    void dispose(void);
    bool ready_for_use(void) const;
    void get_synchronization_objects(s_critical_section * out_write_lock, s_semaphore * out_read_lock) const;
    void read_lock(void);
    bool read_try_and_lock(void);
    void read_unlock(void);
    void write_lock(void);
    bool write_try_and_lock(void);
    void write_unlock(void);

    static void declare_synchronization_objects(long synchronization_group_index, long semaphore_maximum_count, char const * critical_section_name, char const * semaphore_name, s_critical_section * out_write_lock, s_semaphore * out_read_lock);

private:
    bool m_initialized; // 0x0
    long m_max_readers; // 0x4
    s_critical_section m_write_lock; // 0x8
    s_semaphore m_read_lock; // 0xC
};
static_assert(sizeof(c_read_write_lock) == 0x10, "c_read_write_lock");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __READ_WRITE_LOCK_H__
