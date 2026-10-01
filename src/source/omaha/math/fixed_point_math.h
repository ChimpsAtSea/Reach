#pragma once
#ifndef __FIXED_POINT_MATH_H__
#define __FIXED_POINT_MATH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// k_fixed_one / k_fixed_half are defined out of class: the target loads them from memory (lhz) instead of folding
template<long k_fractional_bits>
class t_short_fixed
{
public:
    static short const k_fixed_one;
    static short const k_fixed_half;

    t_short_fixed()
    {
    };

    t_short_fixed(long raw_input)
    {
        raw_bits = static_cast<short>(raw_input);
    };

    t_short_fixed(t_short_fixed const & src)
    {
        raw_bits = src.raw_bits;
    };

    ~t_short_fixed()
    {
    };

    t_short_fixed & operator=(t_short_fixed const & src)
    {
        raw_bits = src.raw_bits;

        return *this;
    };

    bool operator==(t_short_fixed const & rha) const
    {
        return raw_bits == rha.raw_bits;
    };

    bool operator!=(t_short_fixed const & rha) const
    {
        return !(raw_bits == rha.raw_bits);
    };

    bool operator>(t_short_fixed const & rha) const
    {
        return raw_bits > rha.raw_bits;
    };

    bool operator>(int rha) const
    {
        return raw_bits > rha;
    };

    void import_real(float src)
    {
        static float const s_real_one = k_fixed_one;

        raw_bits = static_cast<short>(src * s_real_one);
    };

    float export_real() const
    {
        static float const s_inv_real_one = 1.0f / k_fixed_one;

        return raw_bits * s_inv_real_one;
    };

    short raw_bits; // 0x0
};
static_assert(sizeof(t_short_fixed<1>) == 0x2, "t_short_fixed");

template<long k_fractional_bits>
short const t_short_fixed<k_fractional_bits>::k_fixed_one = 1 << k_fractional_bits;

template<long k_fractional_bits>
short const t_short_fixed<k_fractional_bits>::k_fixed_half = (1 << k_fractional_bits) / 2;

typedef t_short_fixed<13> c_short_fixed_unit;
typedef t_short_fixed<8> c_short_fixed;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FIXED_POINT_MATH_H__
