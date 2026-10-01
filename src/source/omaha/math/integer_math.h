#pragma once
#ifndef __INTEGER_MATH_H__
#define __INTEGER_MATH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

union point2d
{
    short n[2];
    struct
    {
        short x;
        short y;
    };
};
static_assert(sizeof(point2d) == 0x4, "point2d");

union rectangle2d
{
    short n[4];
    struct
    {
        short y0;
        short x0;
        short y1;
        short x1;
    };
};
static_assert(sizeof(rectangle2d) == 0x8, "rectangle2d");

/* ---------- prototypes */

short ceiling_log2(unsigned long k);
void bit_vector_or(long count, unsigned long const * v0, unsigned long const * v1, unsigned long * result);
void bit_vector_set_range_to_true(long bit_count, unsigned long * bit_vector, long start_index, long set_count);
void bit_vector_set_range_to_false(long bit_count, unsigned long * bit_vector, long start_index, long set_count);
long highest_bit_set(unsigned long flags); // $TODO inline in the target ("f i"), body not yet recovered
unsigned long align_up(unsigned long value, long alignment_bits); // $TODO inline in the target ("f i"), body not yet recovered
__int64 make_int64(long low, long high); // $TODO inline in the target ("f i"), owned by tag_file_index.obj
long extract_low_long(__int64 value); // $TODO inline in the target ("f i"), owned by tag_file_index.obj
long extract_high_long(__int64 value); // $TODO inline in the target ("f i"), owned by tag_file_index.obj

/* ---------- globals */

/* ---------- public code */

#endif // __INTEGER_MATH_H__

