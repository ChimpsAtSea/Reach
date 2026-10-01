/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: long c_interlocked_int32::set(long);
// public: long c_interlocked_int32::set_if_equal(long, long);
// public: static long c_interlocked_int32::set_if_equal_external(long volatile *, long, long);
// public: long c_interlocked_int32::add(long) volatile;
// public: long c_interlocked_int32::increment(void) volatile;
// public: long c_interlocked_int32::decrement(void) volatile;
// public: long c_interlocked_int32::and(long) volatile;
// public: long c_interlocked_int32::or(long) volatile;
// public: long c_interlocked_int32::xor(long) volatile;
// public: long c_interlocked_int32::set_bit(long, bool) volatile;
// public: bool c_interlocked_int32::test_bit(long) const volatile;
// public: long c_synchronized_int32::set(long);
// public: long c_synchronized_int32::set_if_equal(long, long);
// public: static long c_synchronized_int32::set_if_equal_external(long volatile *, long, long);
// public: long c_synchronized_int32::peek(void) const volatile;
// public: long c_synchronized_int32::add(long) volatile;
// public: long c_synchronized_int32::increment(void) volatile;
// public: long c_synchronized_int32::decrement(void) volatile;
// public: long c_synchronized_int32::and(long) volatile;
// public: long c_synchronized_int32::or(long) volatile;
// public: long c_synchronized_int32::xor(long) volatile;
// public: long c_synchronized_int32::set_bit(long, bool) volatile;
// public: bool c_synchronized_int32::test_bit(long) const volatile;
// public: __int64 c_interlocked_int64::set(__int64);
// public: __int64 c_interlocked_int64::set_if_equal(__int64, __int64);
// public: __int64 c_interlocked_int64::add(__int64) volatile;
// public: __int64 c_interlocked_int64::increment(void) volatile;
// public: __int64 c_interlocked_int64::decrement(void) volatile;
// public: __int64 c_interlocked_int64::and(__int64) volatile;
// public: __int64 c_interlocked_int64::or(__int64) volatile;
// public: __int64 c_interlocked_int64::xor(__int64) volatile;
// public: __int64 c_synchronized_int64::set(__int64);
// public: __int64 c_synchronized_int64::set_if_equal(__int64, __int64);
// public: __int64 c_synchronized_int64::peek(void) const volatile;
// public: __int64 c_synchronized_int64::add(__int64) volatile;
// public: __int64 c_synchronized_int64::increment(void) volatile;
// public: __int64 c_synchronized_int64::decrement(void) volatile;
// public: __int64 c_synchronized_int64::and(__int64) volatile;
// public: __int64 c_synchronized_int64::or(__int64) volatile;
// public: __int64 c_synchronized_int64::xor(__int64) volatile;

long c_interlocked_int32::set(long value)
{
    mangled_ppc("?set@c_interlocked_int32@@QAAJJ@Z");

    return _InterlockedExchange(&m_value, value);
};

long c_interlocked_int32::set_if_equal(long value, long comperand)
{
    mangled_ppc("?set_if_equal@c_interlocked_int32@@QAAJJJ@Z");

    return _InterlockedCompareExchange(&m_value, value, comperand);
};

long c_interlocked_int32::set_if_equal_external(long volatile * destination, long value, long comperand)
{
    mangled_ppc("?set_if_equal_external@c_interlocked_int32@@SAJPCJJJ@Z");

    return _InterlockedCompareExchange(destination, value, comperand);
};

long c_interlocked_int32::add(long value) volatile
{
    mangled_ppc("?add@c_interlocked_int32@@QCAJJ@Z");

    return _InterlockedExchangeAdd(&m_value, value);
};

long c_interlocked_int32::increment(void) volatile
{
    mangled_ppc("?increment@c_interlocked_int32@@QCAJXZ");

    return _InterlockedIncrement(&m_value);
};

long c_interlocked_int32::decrement(void) volatile
{
    mangled_ppc("?decrement@c_interlocked_int32@@QCAJXZ");

    return _InterlockedDecrement(&m_value);
};

long c_interlocked_int32::and(long value) volatile
{
    mangled_ppc("?and@c_interlocked_int32@@QCAJJ@Z");

    return _InterlockedAnd(&m_value, value);
};

long c_interlocked_int32::or(long value) volatile
{
    mangled_ppc("?or@c_interlocked_int32@@QCAJJ@Z");

    return _InterlockedOr(&m_value, value);
};

long c_interlocked_int32::xor(long value) volatile
{
    mangled_ppc("?xor@c_interlocked_int32@@QCAJJ@Z");

    return _InterlockedXor(&m_value, value);
};

long c_interlocked_int32::set_bit(long index, bool setting) volatile
{
    mangled_ppc("?set_bit@c_interlocked_int32@@QCAJJ_N@Z");

    return setting ? or(FLAG(index)) : and(~FLAG(index));
};

bool c_interlocked_int32::test_bit(long index) const volatile
{
    mangled_ppc("?test_bit@c_interlocked_int32@@QDA_NJ@Z");

    long value = peek();
    return TEST_BIT(value, index);
};

long c_synchronized_int32::set(long value)
{
    mangled_ppc("?set@c_synchronized_int32@@QAAJJ@Z");

    __lwsync();
    return _InterlockedExchange(&m_value, value);
};

long c_synchronized_int32::set_if_equal(long value, long comperand)
{
    mangled_ppc("?set_if_equal@c_synchronized_int32@@QAAJJJ@Z");

    __lwsync();
    return _InterlockedCompareExchange(&m_value, value, comperand);
};

long c_synchronized_int32::set_if_equal_external(long volatile * destination, long value, long comperand)
{
    mangled_ppc("?set_if_equal_external@c_synchronized_int32@@SAJPCJJJ@Z");

    __lwsync();
    return _InterlockedCompareExchange(destination, value, comperand);
};

long c_synchronized_int32::peek(void) const volatile
{
    mangled_ppc("?peek@c_synchronized_int32@@QDAJXZ");

    long result = m_value;
    __lwsync();
    return result;
};

long c_synchronized_int32::add(long value) volatile
{
    mangled_ppc("?add@c_synchronized_int32@@QCAJJ@Z");

    __lwsync();
    return _InterlockedExchangeAdd(&m_value, value);
};

long c_synchronized_int32::increment(void) volatile
{
    mangled_ppc("?increment@c_synchronized_int32@@QCAJXZ");

    __lwsync();
    return _InterlockedIncrement(&m_value);
};

long c_synchronized_int32::decrement(void) volatile
{
    mangled_ppc("?decrement@c_synchronized_int32@@QCAJXZ");

    __lwsync();
    return _InterlockedDecrement(&m_value);
};

long c_synchronized_int32::and(long value) volatile
{
    mangled_ppc("?and@c_synchronized_int32@@QCAJJ@Z");

    __lwsync();
    return _InterlockedAnd(&m_value, value);
};

long c_synchronized_int32::or(long value) volatile
{
    mangled_ppc("?or@c_synchronized_int32@@QCAJJ@Z");

    __lwsync();
    return _InterlockedOr(&m_value, value);
};

long c_synchronized_int32::xor(long value) volatile
{
    mangled_ppc("?xor@c_synchronized_int32@@QCAJJ@Z");

    __lwsync();
    return _InterlockedXor(&m_value, value);
};

long c_synchronized_int32::set_bit(long index, bool setting) volatile
{
    mangled_ppc("?set_bit@c_synchronized_int32@@QCAJJ_N@Z");

    return setting ? or(FLAG(index)) : and(~FLAG(index));
};

bool c_synchronized_int32::test_bit(long index) const volatile
{
    mangled_ppc("?test_bit@c_synchronized_int32@@QDA_NJ@Z");

    long value = peek();
    return TEST_BIT(value, index);
};

__int64 c_interlocked_int64::set(__int64 value)
{
    mangled_ppc("?set@c_interlocked_int64@@QAA_J_J@Z");

    return _InterlockedExchange64(&m_value, value);
};

__int64 c_interlocked_int64::set_if_equal(__int64 value, __int64 comperand)
{
    mangled_ppc("?set_if_equal@c_interlocked_int64@@QAA_J_J0@Z");

    return _InterlockedCompareExchange64(&m_value, value, comperand);
};

__int64 c_interlocked_int64::add(__int64 value) volatile
{
    mangled_ppc("?add@c_interlocked_int64@@QCA_J_J@Z");

    return _InterlockedExchangeAdd64(&m_value, value);
};

__int64 c_interlocked_int64::increment(void) volatile
{
    mangled_ppc("?increment@c_interlocked_int64@@QCA_JXZ");

    return _InterlockedIncrement64(&m_value);
};

__int64 c_interlocked_int64::decrement(void) volatile
{
    mangled_ppc("?decrement@c_interlocked_int64@@QCA_JXZ");

    return _InterlockedDecrement64(&m_value);
};

__int64 c_interlocked_int64::and(__int64 value) volatile
{
    mangled_ppc("?and@c_interlocked_int64@@QCA_J_J@Z");

    return _InterlockedAnd64(&m_value, value);
};

__int64 c_interlocked_int64::or(__int64 value) volatile
{
    mangled_ppc("?or@c_interlocked_int64@@QCA_J_J@Z");

    return _InterlockedOr64(&m_value, value);
};

__int64 c_interlocked_int64::xor(__int64 value) volatile
{
    mangled_ppc("?xor@c_interlocked_int64@@QCA_J_J@Z");

    return _InterlockedXor64(&m_value, value);
};

__int64 c_synchronized_int64::set(__int64 value)
{
    mangled_ppc("?set@c_synchronized_int64@@QAA_J_J@Z");

    __lwsync();
    return _InterlockedExchange64(&m_value, value);
};

__int64 c_synchronized_int64::set_if_equal(__int64 value, __int64 comperand)
{
    mangled_ppc("?set_if_equal@c_synchronized_int64@@QAA_J_J0@Z");

    __lwsync();
    return _InterlockedCompareExchange64(&m_value, value, comperand);
};

__int64 c_synchronized_int64::peek(void) const volatile
{
    mangled_ppc("?peek@c_synchronized_int64@@QDA_JXZ");

    __int64 result = m_value;
    __lwsync();
    return result;
};

__int64 c_synchronized_int64::add(__int64 value) volatile
{
    mangled_ppc("?add@c_synchronized_int64@@QCA_J_J@Z");

    __lwsync();
    return _InterlockedExchangeAdd64(&m_value, value);
};

__int64 c_synchronized_int64::increment(void) volatile
{
    mangled_ppc("?increment@c_synchronized_int64@@QCA_JXZ");

    __lwsync();
    return _InterlockedIncrement64(&m_value);
};

__int64 c_synchronized_int64::decrement(void) volatile
{
    mangled_ppc("?decrement@c_synchronized_int64@@QCA_JXZ");

    __lwsync();
    return _InterlockedDecrement64(&m_value);
};

__int64 c_synchronized_int64::and(__int64 value) volatile
{
    mangled_ppc("?and@c_synchronized_int64@@QCA_J_J@Z");

    __lwsync();
    return _InterlockedAnd64(&m_value, value);
};

__int64 c_synchronized_int64::or(__int64 value) volatile
{
    mangled_ppc("?or@c_synchronized_int64@@QCA_J_J@Z");

    __lwsync();
    return _InterlockedOr64(&m_value, value);
};

__int64 c_synchronized_int64::xor(__int64 value) volatile
{
    mangled_ppc("?xor@c_synchronized_int64@@QCA_J_J@Z");

    __lwsync();
    return _InterlockedXor64(&m_value, value);
};

