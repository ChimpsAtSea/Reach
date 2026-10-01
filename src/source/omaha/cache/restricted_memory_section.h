#pragma once
#ifndef __RESTRICTED_MEMORY_SECTION_H__
#define __RESTRICTED_MEMORY_SECTION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\datatypes\read_write_lock.h"
#include "omaha\multithreading\synchronization_spasm.h"

/* ---------- constants */

/* ---------- definitions */

class c_restricted_section
{
public:
    c_restricted_section(void);
    ~c_restricted_section(void);

    void initialize(void * base_address, unsigned int size, e_critical_sections critical_section_id, e_synchronization_semaphore semaphore_id);
    bool initialized(void) const;

private:
    unsigned long m_internal_flags; // 0x0
    long m_protection_scheme; // 0x4
    e_critical_sections m_external_write_lock; // 0x8
    e_synchronization_semaphore m_external_read_lock; // 0xC
    c_read_write_lock m_read_write_lock; // 0x10
    unsigned char * m_address; // 0x20
    unsigned int m_size; // 0x24
    long m_owner_thread; // 0x28
};
static_assert(sizeof(c_restricted_section) == 0x2C, "c_restricted_section");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RESTRICTED_MEMORY_SECTION_H__

