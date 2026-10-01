#pragma once
#ifndef __SIMPLE_PERSIST_STREAMS_H__
#define __SIMPLE_PERSIST_STREAMS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\persist.h"

/* ---------- constants */

/* ---------- definitions */

class c_simple_persist_stream_base :
    public c_persist_stream
{
public:
    c_simple_persist_stream_base(void);
    c_simple_persist_stream_base(bool enable_byte_swapping);

    // ??1c_simple_persist_stream_base@@UAA@XZ is inline (tag_groups.obj)
    virtual ~c_simple_persist_stream_base()
    {
    };

    virtual bool needs_byteswapping(void);
    virtual void set_needs_byteswapping(bool enable_byte_swapping);

private:
    bool m_needs_byteswapping; // 0x4
};
static_assert(sizeof(c_simple_persist_stream_base) == 0x8, "c_simple_persist_stream_base");

// constructor zeroes 0x8, 0xC and 0x10; field order/names from H3 (unverified), 0x10 new in Reach
class c_used_size_only_stream :
    public c_simple_persist_stream_base
{
public:
    c_used_size_only_stream(void);

    // ??1c_used_size_only_stream@@UAA@XZ is inline (tag_groups.obj)
    virtual ~c_used_size_only_stream()
    {
    };

    virtual bool read(void * buffer, unsigned long buffer_length);
    virtual bool write(void const * buffer, unsigned long buffer_length);
    virtual bool write_extend_to_position(void);
    virtual bool seek_relative(long offset);
    virtual bool seek_absolute(unsigned long offset);
    virtual bool get_absolute_position(unsigned long * out_position);
    virtual bool get_total_size(unsigned long * out_total_size);

    unsigned long get_used_size(void) const;

private:
    unsigned long m_total_size; // 0x8
    unsigned long m_position; // 0xC
    unsigned long m_unknown10; // 0x10
};
static_assert(sizeof(c_used_size_only_stream) == 0x14, "c_used_size_only_stream");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SIMPLE_PERSIST_STREAMS_H__

