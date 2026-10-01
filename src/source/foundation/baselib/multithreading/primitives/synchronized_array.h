#ifndef __SYNCHRONIZED_ARRAY_H__
#define __SYNCHRONIZED_ARRAY_H__
#pragma once

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

#define __SYNCHRONIZED_ARRAY_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/multithreading/primitives/synchronized_array.h"

/* ---------- definitions */

template<long k_count>
class c_synchronized_int32_array
{
public:
    static long const k_maximum_count = k_count;

    c_synchronized_int32_array(void)
    {
        set_array(0);
    }

    c_synchronized_int32 & get_member(long index)
    {
        assert_decomp(VALID_INDEX(index, k_maximum_count), __SYNCHRONIZED_ARRAY_H_FILE__, 32);

        return m_members[index];
    }

    c_synchronized_int32 const & get_member_const(long index) const
    {
        assert_decomp(VALID_INDEX(index, k_maximum_count), __SYNCHRONIZED_ARRAY_H_FILE__, 38);

        return m_members[index];
    }

    void set_array(long value)
    {
        for (long index = 0; index < k_maximum_count; index++)
        {
            m_members[index].set(value);
        }
    }

protected:
    c_synchronized_int32 m_members[k_count];
};

template<long k_bit_count>
class c_synchronized_bitvector :
    public c_synchronized_int32_array<(k_bit_count + 31) / 32>
{
public:
    void clear(void)
    {
        set_array(0);
    }

    bool test_bit(long index) const
    {
        long dword_index = index >> 5;
        long bit = index & 31;
        long value = get_member_const(dword_index).peek();

        return (value & FLAG(bit)) != 0;
    }

    void set_bit(long index, bool setting)
    {
        long dword_index = index >> 5;
        long bit = index & 31;
        c_synchronized_int32 & member = get_member(dword_index);

        if (setting)
        {
            member |= FLAG(bit);
        }
        else
        {
            member &= ~FLAG(bit);
        }
    }
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZED_ARRAY_H__

