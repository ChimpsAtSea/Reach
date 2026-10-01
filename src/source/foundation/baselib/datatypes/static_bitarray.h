#ifndef __STATIC_BITARRAY_H__
#define __STATIC_BITARRAY_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

template<long k_bit_count>
class s_static_bitarray
{
public:
    template<typename t_index>
    static bool valid(t_index index)
    {
        return VALID_INDEX(index, k_bit_count);
    }

    template<typename t_index>
    bool const operator[](t_index index) const
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_bitarray.h", 32);

        return test(index);
    }

    void clear(void)
    {
        csmemset(m_storage, 0, sizeof(m_storage));
    }

    bool test(long index) const
    {
        return BIT_VECTOR_TEST_FLAG(m_storage, index);
    }

    // $TODO nonmatching: BIT_VECTOR_SET_FLAG(m_storage, index, enable) only reaches 76.8%; the target
    // keeps each branch's new word in a temp (stores it, then uses the temp as the ternary result)
    // instead of re-reading m_storage[index >> 5] after the store
    void set(long index, bool enable);

private:
    unsigned long m_storage[(k_bit_count + 31) / 32];
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_BITARRAY_H__

