#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_ring_buffer
{
public:
    long size() const;
    long count() const;
    long available() const;
    bool empty() const;
    bool full() const;
    long first_element() const;
    long next_element(long element_index) const;
    long last_element() const;
    long current_element() const;
    long previous_element(long element_index) const;
    long nth_element(long n) const;
    void clear();
    long add_element();
    long remove_element();
    long add_elements(long add_element_count);
    long remove_elements(long remove_element_count);

private:
    long ring_size; // 0x0
    long head_index; // 0x4
    long element_count; // 0x8
};
static_assert(sizeof(c_ring_buffer) == 0xC, "c_ring_buffer");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RING_BUFFER_H__

