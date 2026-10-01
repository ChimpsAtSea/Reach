#pragma once
#ifndef __SAVED_FILM_SCRATCH_MEMORY_H__
#define __SAVED_FILM_SCRATCH_MEMORY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\async_buffer.h"

/* ---------- constants */

/* ---------- definitions */

class c_saved_film_scratch_memory
{
public:
    enum e_system_state
    {
        _system_state_none = 0,
        _system_state_acquired,

        k_system_state_count
    };

    enum e_system
    {
        _system_film_history = 0,
        _system_screenshot,

        k_system_count
    };

    struct s_system_data
    {
        e_system_state state;
        long reference_count;
        char * buffer;
        long buffer_length;
        c_async_single_buffer<13, 6> buffer_set;
    };

public:
    c_saved_film_scratch_memory(void);
    static c_saved_film_scratch_memory * get(void);
    void initialize(void);
    void dispose(void);
    void memory_initialize(void);
    void memory_dispose(void);
    void update(void);
    s_system_data * acquire(e_system system);
    s_system_data * try_and_acquire(e_system system);
    void release(e_system system);
    void block_until_not_busy(void);

private:
    bool m_initialized;
    char * m_buffer;
    long m_buffer_length;
    s_system_data m_systems[k_system_count];
};
static_assert(sizeof(c_saved_film_scratch_memory::s_system_data) == 0xAC, "c_saved_film_scratch_memory::s_system_data");
static_assert(sizeof(c_saved_film_scratch_memory) == 0x164, "c_saved_film_scratch_memory");

/* ---------- prototypes */

/* ---------- globals */

extern c_saved_film_scratch_memory g_saved_film_scratch_memory;

/* ---------- public code */

#endif // __SAVED_FILM_SCRATCH_MEMORY_H__

