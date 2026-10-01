#ifndef __FLAGS_H__
#define __FLAGS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

#define __FLAGS_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/flags.h"

template<typename t_enum, typename t_storage, long k_bit_count>
class s_flags
{
public:
    void clear()
    {
        m_storage = 0;
    };

    bool test(t_enum bit) const
    {
        assert_decomp(valid_bit(bit), __FLAGS_H_FILE__, 130);

        bool result = static_cast<bool>((m_storage & flag_size_type(bit)) != 0);

        return result;
    };

    bool is_empty() const
    {
        return (m_storage & make_mask_with_all_valid_bits_on_size_type()) == 0;
    };

    void set_unsafe(t_storage raw_bits)
    {
        m_storage = raw_bits;

        assert_decomp(valid(), __FLAGS_H_FILE__, 277);
    };

    void set(t_enum bit, bool enable)
    {
        assert_decomp(valid_bit(bit), __FLAGS_H_FILE__, 155);

        if (enable)
        {
            m_storage |= flag_size_type(bit);
        }
        else
        {
            m_storage &= ~flag_size_type(bit);
        }

        assert_decomp(valid(), __FLAGS_H_FILE__, 166);
    };

    static bool valid_bit(t_enum bit)
    {
        bool result = static_cast<bool>(bit >= 0 && bit < k_bit_count);

        return result;
    };

    bool valid() const
    {
        t_storage valid_mask = make_mask_with_all_valid_bits_on_size_type();
        bool invalid = static_cast<bool>((m_storage & ~valid_mask) != 0);
        bool valid = static_cast<bool>(!invalid);

        return valid;
    };

    bool operator==(s_flags<t_enum, t_storage, k_bit_count> const & other) const
    {
        return m_storage == other.m_storage;
    };

    s_flags<t_enum, t_storage, k_bit_count> & operator|=(s_flags<t_enum, t_storage, k_bit_count> const & other)
    {
        m_storage |= other.m_storage;

        assert_decomp(valid(), __FLAGS_H_FILE__, 354);

        return *this;
    };

private:
    static t_storage flag_size_type(t_enum bit)
    {
        t_storage result = FLAG(bit);

        return result;
    };

    static t_storage make_mask_with_all_valid_bits_on_size_type()
    {
        t_storage result = make_N_bit_mask_size_type(static_cast<t_enum>(k_bit_count));

        return result;
    };

    static t_storage make_N_bit_mask_size_type(t_enum bit_count)
    {
        t_storage const all_bits = static_cast<t_storage>(-1);

        t_storage result = all_bits >> (sizeof(t_storage) * 8 - bit_count);

        return result;
    };

    t_storage m_storage;
};

template<typename t_enum, typename t_storage, long k_bit_count>
class c_flags_zero_init :
    public s_flags<t_enum, t_storage, k_bit_count>
{
public:
    c_flags_zero_init()
    {
        clear();
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FLAGS_H__

