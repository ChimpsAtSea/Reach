#pragma once
#ifndef __BUSY_WAIT_H__
#define __BUSY_WAIT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_busy_wait_definition
{
    char const * name;
};
static_assert(sizeof(s_busy_wait_definition) == 0x4, "s_busy_wait_definition");

struct s_busy_wait
{
    unsigned long object_id;
};
static_assert(sizeof(s_busy_wait) == 0x4, "s_busy_wait");

class c_busy_wait_timer
{
public:
    c_busy_wait_timer(s_busy_wait busy_wait);
    ~c_busy_wait_timer(void);

private:
    long m_unknown0[2]; // 0x0
    s_busy_wait m_busy_wait; // 0x8
};

/* ---------- prototypes */

extern s_busy_wait busy_wait_declare(long synchronization_group_index, s_busy_wait_definition const * definition);

/* ---------- globals */

/* ---------- public code */

#endif // __BUSY_WAIT_H__

