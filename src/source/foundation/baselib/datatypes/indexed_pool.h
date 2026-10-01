#ifndef __INDEXED_POOL_H__
#define __INDEXED_POOL_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

unsigned short const k_indexed_pool_handle_null = 0xFFFF;

/* ---------- definitions */

// each free element stores the index of the next free element in its first 2 bytes
template<typename t_type, long k_size>
class c_indexed_pool
{
public:
    c_indexed_pool()
    {
    };

    ~c_indexed_pool()
    {
    };

    void initialize()
    {
        m_free_head = 0;
        for (unsigned short index = 0; index < k_size - 1; index++)
        {
            *reinterpret_cast<unsigned short *>(&m_elements[index]) = index + 1;
        }
        *reinterpret_cast<unsigned short *>(&m_elements[k_size - 1]) = k_indexed_pool_handle_null;
        m_num_free = k_size;
    };

    void dispose()
    {
        assert_decomp(m_num_free == k_size, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\indexed_pool.h", 87);
    };

    unsigned short alloc_handle()
    {
        unsigned short handle = k_indexed_pool_handle_null;
        assert_decomp(m_num_free > 0, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\indexed_pool.h", 96);

        if (m_num_free != 0)
        {
            handle = m_free_head;
            m_num_free--;
            m_free_head = *reinterpret_cast<unsigned short *>(&m_elements[handle]);
        }

        return handle;
    };

    void free_handle(unsigned short & data_handle)
    {
        assert_decomp(data_handle < k_size, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\indexed_pool.h", 112);

        unsigned short * next = reinterpret_cast<unsigned short *>(&m_elements[data_handle]);
        *next = m_free_head;
        m_free_head = data_handle;
        data_handle = k_indexed_pool_handle_null;
        m_num_free++;
    };

    t_type * get_element(unsigned short const & data_handle)
    {
        assert_decomp(data_handle < k_size, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\indexed_pool.h", 126);

        return &m_elements[data_handle];
    };

private:
    t_type m_elements[k_size];
    unsigned long m_num_free;
    unsigned short m_free_head;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __INDEXED_POOL_H__

