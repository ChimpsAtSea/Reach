#pragma once
#ifndef __TAG_RESOURCE_CACHE_DPC_H__
#define __TAG_RESOURCE_CACHE_DPC_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_resource_cache_dpc_event
{
public:
    void allocate_dpc_event(void) volatile;
    bool wait_on_dpc_event(bool block);
    void clear_dpc_event(void);

private:
    c_interlocked_int64 m_dpc_event_plus_flag;
};
static_assert(sizeof(c_tag_resource_cache_dpc_event) == 0x8, "c_tag_resource_cache_dpc_event");

/* ---------- prototypes */

extern long tag_resource_cache_allocate_dpc_event(void);
extern void tag_resource_cache_block_on_dpc_event(long dpc_event);
extern bool tag_resource_cache_dpc_event_set(long dpc_event);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_RESOURCE_CACHE_DPC_H__

