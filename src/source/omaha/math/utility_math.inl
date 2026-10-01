#pragma once
#ifndef __UTILITY_MATH_INL__
#define __UTILITY_MATH_INL__

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_array>
void array_index_min_and_max(t_array const & array, long count, long * out_min_index, long * out_max_index)
{
    long min_index = 0;
    long max_index = 0;
    assert_decomp(out_min_index && out_max_index, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\math\\utility_math.inl", 51);

    for (long index = 1; index < count; index++)
    {
        if (array[index] < array[min_index])
        {
            min_index = index;
        }
        if (array[index] > array[max_index])
        {
            max_index = index;
        }
    }

    *out_min_index = min_index;
    *out_max_index = max_index;
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __UTILITY_MATH_INL__
