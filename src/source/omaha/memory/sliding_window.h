#pragma once
#ifndef __SLIDING_WINDOW_H__
#define __SLIDING_WINDOW_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\ring_buffer.h"

/* ---------- constants */

/* ---------- definitions */

class c_sliding_window
{
public:
    bool initialized() const;
    long current_size() const;
    bool empty() const;
    bool full() const;
    long newest_sequence_number() const;
    long oldest_sequence_number() const;
    long trailing_edge() const;
    long get_storage_index(long sequence_number) const;
    void reset(bool initialize, long initial_sequence_number);
    void close(long new_trailing_edge);
    void open(long new_leading_edge);

private:
    bool m_initialized; // 0x0
    long m_size; // 0x4
    long m_leading_sequence_number; // 0x8
    long m_trailing_sequence_number; // 0xC
    c_ring_buffer m_window; // 0x10
};
static_assert(sizeof(c_sliding_window) == 0x1C, "c_sliding_window");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SLIDING_WINDOW_H__

