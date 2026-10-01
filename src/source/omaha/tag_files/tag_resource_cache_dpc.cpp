/* ---------- headers */

#include "omaha\tag_files\tag_resource_cache_dpc.h"
#include "omaha\math\integer_math.h"
#include "omaha\rasterizer\rasterizer_main.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long tag_resource_cache_allocate_dpc_event(void);
// void tag_resource_cache_block_on_dpc_event(long);
// bool tag_resource_cache_dpc_event_set(long);
// public: void c_tag_resource_cache_dpc_event::allocate_dpc_event(void) volatile;
// public: bool c_tag_resource_cache_dpc_event::wait_on_dpc_event(bool);
// public: __int64 c_interlocked_int64::peek(void) const volatile;
// public: void c_tag_resource_cache_dpc_event::clear_dpc_event(void);

long tag_resource_cache_allocate_dpc_event(void)
{
    mangled_ppc("?tag_resource_cache_allocate_dpc_event@@YAJXZ");

    long dpc_event = c_rasterizer::rasterizer_insert_fence();

    return dpc_event;
};

void tag_resource_cache_block_on_dpc_event(long dpc_event)
{
    mangled_ppc("?tag_resource_cache_block_on_dpc_event@@YAXJ@Z");

    c_rasterizer::rasterizer_block_on_fence(dpc_event);
};

bool tag_resource_cache_dpc_event_set(long dpc_event)
{
    mangled_ppc("?tag_resource_cache_dpc_event_set@@YA_NJ@Z");

    return !c_rasterizer::rasterizer_is_fence_pending(dpc_event);
};

void c_tag_resource_cache_dpc_event::allocate_dpc_event(void) volatile
{
    mangled_ppc("?allocate_dpc_event@c_tag_resource_cache_dpc_event@@QCAXXZ");

    long dpc_event = tag_resource_cache_allocate_dpc_event();
    __int64 dpc_plus_flag = make_int64(dpc_event, 1);
    const_cast<c_interlocked_int64 &>(m_dpc_event_plus_flag).set(dpc_plus_flag);
};

bool c_tag_resource_cache_dpc_event::wait_on_dpc_event(bool block)
{
    mangled_ppc("?wait_on_dpc_event@c_tag_resource_cache_dpc_event@@QAA_N_N@Z");

    bool wait_success = true;

    __int64 dpc_event_plus_flag = m_dpc_event_plus_flag.peek();
    long dpc_event = extract_low_long(dpc_event_plus_flag);
    bool valid_event = extract_high_long(dpc_event_plus_flag) != 0;

    if (valid_event)
    {
        if (block)
        {
            tag_resource_cache_block_on_dpc_event(dpc_event);
        }
        else
        {
            wait_success = tag_resource_cache_dpc_event_set(dpc_event);
        }
    }

    return wait_success;
};

void c_tag_resource_cache_dpc_event::clear_dpc_event(void)
{
    mangled_ppc("?clear_dpc_event@c_tag_resource_cache_dpc_event@@QAAXXZ");

    m_dpc_event_plus_flag.set(0);
};

