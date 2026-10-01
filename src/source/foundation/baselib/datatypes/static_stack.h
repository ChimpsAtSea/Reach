#ifndef __STATIC_STACK_H__
#define __STATIC_STACK_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type, long k_count>
class c_static_stack
{
public:
    c_static_stack(void) :
        m_count(0)
    {
    }

    bool valid(long index) const
    {
        assert_decomp(valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 22);

        return VALID_INDEX(index, m_count);
    }

    bool valid(void) const
    {
        return IN_RANGE_INCLUSIVE(m_count, 0, k_count);
    }

    bool empty(void) const
    {
        assert_decomp(valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 23);

        return m_count == 0;
    }

    bool full(void) const
    {
        assert_decomp(valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 24);

        return m_count == k_count;
    }

    long push(void)
    {
        assert_decomp(!full(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 33);

        return m_count++;
    }

    long top(void) const
    {
        assert_decomp(!empty(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 25);

        return m_count - 1;
    }

    void clear(void)
    {
        m_count = 0;
    }

    void resize(long count)
    {
        m_count = count;

        assert_decomp(valid(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 32);
    }

    void push_back(t_type const & value)
    {
        *get(push()) = value;
    }

    void pop(void)
    {
        assert_decomp(!empty(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 35);

        m_count--;
    }

    t_type & get_element(long index)
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 40);

        return m_elements[index];
    }

    long count(void) const
    {
        return m_count;
    }

    t_type const & operator[](long index) const
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 37);

        return m_elements[index];
    }

    t_type & operator[](long index)
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 38);

        return m_elements[index];
    }

    t_type const * get(long index) const
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 41);

        return &m_elements[index];
    }

    t_type * get(long index)
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 42);

        return &m_elements[index];
    }

    t_type const * get_top(void) const
    {
        return get(top());
    }

    t_type * get_elements(void)
    {
        return m_elements;
    }

    long next(void) const
    {
        return m_count;
    }

    t_type * get_next(void)
    {
        assert_decomp(!full(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_stack.h", 47);

        return &m_elements[next()];
    }

    static unsigned int element_size(void)
    {
        return sizeof(t_type);
    }

protected:
    long m_count;
    t_type m_elements[k_count];
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_STACK_H__

