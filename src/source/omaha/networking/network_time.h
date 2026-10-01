#pragma once
#ifndef __NETWORK_TIME_H__
#define __NETWORK_TIME_H__

/* ---------- headers */

#include "omaha\networking\transport\transport_security.h"
#include "baselib\system_time_xenon.h"

/* ---------- constants */

/* ---------- definitions */

class c_network_session_manager;

struct s_network_time_globals
{
    bool time_locked; // 0x0
    unsigned long time_locked_timestamp; // 0x4
    c_network_session_manager * session_manager; // 0x8
};
static_assert(sizeof(s_network_time_globals) == 0xC, "s_network_time_globals");

/* ---------- prototypes */

bool network_session_time_get_id_and_time(long session_index, s_transport_secure_identifier * session_id, unsigned long * session_timestamp);

/* ---------- globals */

extern s_network_time_globals network_time_globals;

/* ---------- public code */

// the target emits these as static (non-inline) functions in every translation unit that uses them

static unsigned long network_time_get_exact(void)
{
    mangled_ppc("?network_time_get_exact@@YAKXZ");

    return system_milliseconds();
};

static unsigned long network_time_get(void)
{
    mangled_ppc("?network_time_get@@YAKXZ");

    return network_time_globals.time_locked ? network_time_globals.time_locked_timestamp : network_time_get_exact();
};

static long network_time_difference_msec(unsigned long timestamp1, unsigned long timestamp2)
{
    mangled_ppc("?network_time_difference_msec@@YAJKK@Z");

    return timestamp2 - timestamp1;
};

static long network_time_since(unsigned long timestamp)
{
    mangled_ppc("?network_time_since@@YAJK@Z");

    return network_time_difference_msec(timestamp, network_time_get());
};

#endif // __NETWORK_TIME_H__

