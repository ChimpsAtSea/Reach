#pragma once
#ifndef __HAVOK_MEMORY_H__
#define __HAVOK_MEMORY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

class c_havok_overflow_memory_borrower
{
public:
    c_havok_overflow_memory_borrower()
    {
        mangled_ppc("??0c_havok_overflow_memory_borrower@@QAA@XZ");

        memset(this, 0, sizeof(*this));
    };

    void initialize(char const * name, long size);
    void dispose();
    void * get_buffer();
    unsigned long get_buffer_size() const;

private:
    void * m_havok_overflow_buffer; // 0x0
    unsigned long m_buffer_size; // 0x4
    char const * m_name; // 0x8
};
static_assert(sizeof(c_havok_overflow_memory_borrower) == 0xC, "c_havok_overflow_memory_borrower");

class hkMemoryRouter;
class hkMemorySystem;

// layout from the constructor (0x8312C030)
class c_havok_memory_enable_system_allocator
{
public:
    c_havok_memory_enable_system_allocator();
    ~c_havok_memory_enable_system_allocator();

private:
    hkMemoryRouter * m_previous_router; // 0x0
    hkMemorySystem * m_previous_system; // 0x4
    bool m_initialized_base_system; // 0x8
};
static_assert(sizeof(c_havok_memory_enable_system_allocator) == 0xC, "c_havok_memory_enable_system_allocator");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_MEMORY_H__

