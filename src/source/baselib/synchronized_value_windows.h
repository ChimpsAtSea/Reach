#pragma once
#ifndef __SYNCHRONIZED_VALUE_WINDOWS_H__
#define __SYNCHRONIZED_VALUE_WINDOWS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_interlocked_int32
{
public:
    c_interlocked_int32(void) :
        m_value(0)
    {
    }

    c_interlocked_int32(long value) :
        m_value(value)
    {
        mangled_ppc("??0c_interlocked_int32@@QAA@J@Z");
    }

    ~c_interlocked_int32(void)
    {
    }

    c_interlocked_int32 & operator=(c_interlocked_int32 const & other)
    {
        mangled_ppc("??4c_interlocked_int32@@QAAAAV0@ABV0@@Z");

        set(other.peek());
        return *this;
    }

    operator long(void) const
    {
        mangled_ppc("??Bc_interlocked_int32@@QBAJXZ");

        return peek();
    }

    long peek(void) const volatile
    {
        mangled_ppc("?peek@c_interlocked_int32@@QDAJXZ");

        return m_value;
    }

    long set(long value);
    long set_if_equal(long value, long comperand);
    long add(long value) volatile;
    long increment(void) volatile;
    long decrement(void) volatile;
    long and(long value) volatile;
    long or(long value) volatile;
    long xor(long value) volatile;
    long set_bit(long index, bool setting) volatile;
    bool test_bit(long index) const volatile;

    static long set_if_equal_external(long volatile * destination, long value, long comperand);

private:
    long volatile m_value;
};

class c_synchronized_int32
{
public:
    c_synchronized_int32(void) :
        m_value(0)
    {
    }

    c_synchronized_int32(long value) :
        m_value(value)
    {
    }

    ~c_synchronized_int32(void)
    {
    }

    operator long(void) const;
    long set(long value);
    long set_if_equal(long value, long comperand);
    long peek(void) const volatile;
    long add(long value) volatile;
    long increment(void) volatile;
    long decrement(void) volatile;
    long and(long value) volatile;
    long or(long value) volatile;
    long xor(long value) volatile;
    long set_bit(long index, bool setting) volatile;
    bool test_bit(long index) const volatile;
    c_synchronized_int32 & operator&=(long value);
    c_synchronized_int32 & operator|=(long value);

    static long set_if_equal_external(long volatile * destination, long value, long comperand);

private:
    long volatile m_value;
};

class c_interlocked_int64
{
public:
    c_interlocked_int64(void) :
        m_value(0)
    {
    }

    ~c_interlocked_int64(void)
    {
    }

    __int64 peek(void) const volatile
    {
        mangled_ppc("?peek@c_interlocked_int64@@QDA_JXZ");

        return m_value;
    }

    __int64 set(__int64 value);
    __int64 set_if_equal(__int64 value, __int64 comperand);
    __int64 add(__int64 value) volatile;
    __int64 increment(void) volatile;
    __int64 decrement(void) volatile;
    __int64 and(__int64 value) volatile;
    __int64 or(__int64 value) volatile;
    __int64 xor(__int64 value) volatile;

private:
    __int64 volatile m_value;
};

class c_synchronized_int64
{
public:
    c_synchronized_int64(void) :
        m_value(0)
    {
    }

    ~c_synchronized_int64(void)
    {
    }

    __int64 set(__int64 value);
    __int64 set_if_equal(__int64 value, __int64 comperand);
    __int64 peek(void) const volatile;
    __int64 add(__int64 value) volatile;
    __int64 increment(void) volatile;
    __int64 decrement(void) volatile;
    __int64 and(__int64 value) volatile;
    __int64 or(__int64 value) volatile;
    __int64 xor(__int64 value) volatile;

private:
    __int64 volatile m_value;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZED_VALUE_WINDOWS_H__

