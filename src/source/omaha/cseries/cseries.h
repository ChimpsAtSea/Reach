#pragma once
#ifndef __CSERIES_H__
#define __CSERIES_H__

/* ---------- headers */

/* ---------- constants */

enum e_none_sentinel
{
    NONE = -1,
};

// $TODO enumerator names unverified; raise_exception_unhandled passes 1
enum e_crash_type
{
    _crash_type_unknown = 0,
    _crash_type_assert,
};

/* ---------- definitions */

/* ---------- prototypes */

void cseries_core_initialize(void);
void cseries_foundation_initialize(void);
void cseries_foundation_dispose(void);
void cseries_core_dispose(void);
void halt_function_initialize(void);
void halt_function_dispose(void);
long assert_stack_walk_exception_filter(unsigned long exception_code, struct _EXCEPTION_POINTERS * exception_pointers);
void raise_managed_dll_exception_immediate(char const * expression, char const * file, long line, e_crash_type crash_type);
void raise_unmanaged_exception_immediate(char const * expression, char const * file, long line);
unsigned long debug_memory_checksum_buffer(void const * data, unsigned int size);
unsigned short debug_memory_local_random(void);

// inline template in the target (??$count_bits@K@@YAKK@Z, f i); body not reversed yet
template<typename t_type>
unsigned long count_bits(t_type value);

/* ---------- globals */

/* ---------- public code */

template<typename t_type>
bool operator==(t_type const & value, e_none_sentinel const & none)
{
    return static_cast<t_type>(NONE) == value;
}

template<typename t_type>
bool operator!=(t_type const & value, e_none_sentinel const & none)
{
    return !(value == none);
}

template<typename t_type>
bool operator==(e_none_sentinel const & none, t_type const & value)
{
    return static_cast<t_type>(NONE) == value;
}

template<typename t_type>
bool operator!=(e_none_sentinel const & none, t_type const & value)
{
    return !(none == value);
}

// ?align_down@@YAKKJ@Z (f i)
inline unsigned long align_down(unsigned long value, long alignment_bits)
{
    return value & (-1 << alignment_bits);
}

template<typename t_type>
void xchg(t_type & a, t_type & b)
{
    t_type temp = a;
    a = b;
    b = temp;
}

#endif // __CSERIES_H__
