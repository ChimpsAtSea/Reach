#pragma once
#ifndef __CSERIES_MACROS_H__
#define __CSERIES_MACROS_H__

/* ---------- headers */

/* ---------- constants */

#ifndef NULL
#define NULL 0
#endif

#define NUMBEROF(_array) (sizeof(_array) / sizeof(_array[0]))
#define IN_RANGE_INCLUSIVE(value, begin, end) ((value) >= (begin) && (value) <= (end))
#define VALID_INDEX(index, count) ((index) >= 0 && (index) < (count))
#define VALID_COUNT(index, count) ((index) >= 0 && (index) <= (count))
#define FLAG(bit) (1 << (bit))
#define TEST_BIT(flags, bit) (((flags) & FLAG(bit)) != 0)
#define TEST_MASK(flags, mask) (((flags) & (mask)) != 0)
#define SET_BIT(flags, bit, enable) ((enable) ? ((flags) |= FLAG(bit)) : ((flags) &= ~FLAG(bit)))
#define FLAG_64(bit) (1ull << static_cast<unsigned long long>(bit))
#define MASK_64(bit) (FLAG_64((bit)) - 1)
#define LONG_BITS 32
#ifndef UNSIGNED_CHAR_MAX
#define UNSIGNED_CHAR_MAX 255 // 0xFF
#endif
#ifndef UNSIGNED_SHORT_MAX
#define UNSIGNED_SHORT_MAX 65535 // 0xFFFF
#endif
#define BIT_VECTOR_SIZE_IN_LONGS(BIT_COUNT) (((BIT_COUNT) + (LONG_BITS - 1)) >> 5)
#define BIT_VECTOR_SIZE_IN_BYTES(BIT_COUNT) (4 * BIT_VECTOR_SIZE_IN_LONGS(BIT_COUNT))
#define BIT_VECTOR_TEST_FLAG(BIT_VECTOR, BIT) (((BIT_VECTOR)[(BIT) >> 5] & (1 << ((BIT) & (LONG_BITS - 1)))) != 0)
#define BIT_VECTOR_OR_FLAG(BIT_VECTOR, BIT) ((BIT_VECTOR)[(BIT) >> 5] |= (1 << ((BIT) & (LONG_BITS - 1))))
#define BIT_VECTOR_AND_FLAG(BIT_VECTOR, BIT) ((BIT_VECTOR)[(BIT) >> 5] &= ~(1 << ((BIT) & (LONG_BITS - 1))))
#define BIT_VECTOR_SET_FLAG(BIT_VECTOR, BIT, VALUE) ((VALUE) ? ((BIT_VECTOR)[(BIT) >> 5] |= (1 << ((BIT) & (LONG_BITS - 1)))) : ((BIT_VECTOR)[(BIT) >> 5] &= ~(1 << ((BIT) & (LONG_BITS - 1)))))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CEILING(n, ceiling) ((n) > (ceiling) ? (ceiling) : (n))
#define FLOOR(n, floor) ((n) < (floor) ? (floor) : (n))
#define PIN(n, floor, ceiling) MIN(MAX(n, floor), ceiling)
#define TAG(a, b, c, d) ((static_cast<unsigned long>(static_cast<unsigned char>(a)) << 24) | (static_cast<unsigned long>(static_cast<unsigned char>(b)) << 16) | (static_cast<unsigned long>(static_cast<unsigned char>(c)) << 8) | static_cast<unsigned long>(static_cast<unsigned char>(d)))
#define OFFSETOF(s, m) ((size_t)&reinterpret_cast<const volatile char&>((((s*)0)->m)))

// the XDK compiler predates the static_assert keyword
#define STATIC_ASSERT_JOIN_INNER(a, b) a##b
#define STATIC_ASSERT_JOIN(a, b) STATIC_ASSERT_JOIN_INNER(a, b)
#define static_assert(expression, message) typedef char STATIC_ASSERT_JOIN(static_assert_line_, __LINE__)[(expression) ? 1 : -1]

signed char const k_int8_max = 0x7F;
char const k_char_max = 0x7F;
short const k_int16_max = 0x7FFF;
unsigned short const k_uint16_max = 0xFFFF;
unsigned long const k_uint32_max = 0xFFFFFFFF;
long const k_int32_min = static_cast<long>(0x80000000);
long const k_int32_max = 0x7FFFFFFF;

/* ---------- definitions */

typedef long int32;
typedef long intptr;
typedef unsigned long uintptr;
typedef unsigned long dword;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<typename t_type>
t_type int_max(t_type const & a, t_type const & b)
{
    return a > b ? a : b;
}

template<typename t_type>
t_type int_min(t_type const & a, t_type const & b)
{
    // verified against ??$int_min@W4e_event_level@@ (event_manager.obj): compare a,b then ble -> a
    return a > b ? b : a;
}

inline long int_max(long a, int b)
{
    mangled_ppc("?int_max@@YAJJH@Z");

    return int_max<long>(a, b);
}

inline unsigned long int_min(int a, unsigned long b)
{
    mangled_ppc("?int_min@@YAKHK@Z");

    return int_min<unsigned long>(a, b);
}

// unverified codegen (instance owned by animation_manager.obj); called from perlin.obj
inline long int_max(short a, int b)
{
    mangled_ppc("?int_max@@YAJFH@Z");

    return int_max<long>(a, b);
}

// unverified codegen (instance owned by simulation_world.obj); called from perlin.obj
inline long int_min(long a, int b)
{
    mangled_ppc("?int_min@@YAJJH@Z");

    return int_min<long>(a, b);
}

// unverified codegen (instances owned by other .objs); calls per ??$int_pin@JHJ@@ -> int_floor<long,long> -> int_max<long>
template<typename t_type, typename t_bound>
t_type int_floor(t_type const & value, t_bound const & minimum)
{
    return int_max<t_type>(value, minimum);
}

template<typename t_type, typename t_bound>
t_type int_ceiling(t_type const & value, t_bound const & maximum)
{
    return int_min<t_type>(value, maximum);
}

template<typename t_type, typename t_minimum, typename t_maximum>
t_type int_pin(t_type const & value, t_minimum const & minimum, t_maximum const & maximum)
{
    t_type minimum_value = minimum;
    t_type floored = int_floor<t_type, t_type>(value, minimum_value);
    return int_ceiling<t_type, t_maximum>(floored, maximum);
}

#endif // __CSERIES_MACROS_H__
