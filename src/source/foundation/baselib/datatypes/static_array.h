#ifndef __STATIC_ARRAY_H__
#define __STATIC_ARRAY_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type, long k_count>
class s_static_array
{
public:
    static long const k_element_count = k_count;

    static long get_count(void)
    {
        return k_element_count;
    }

    template<typename t_index>
    static bool valid(t_index index)
    {
        return VALID_INDEX(index, k_element_count);
    }

    t_type * get_elements(void)
    {
        return m_elements;
    }

    t_type const * get_elements(void) const
    {
        return m_elements;
    }

    // ?begin@?$s_static_array@Us_cache_file_codec_definition@@$0HP@@@QAAPAUs_cache_file_codec_definition@@XZ
    t_type * begin(void)
    {
        return m_elements;
    }

    // ?begin@?$s_static_array@Us_cache_file_codec_definition@@$0HP@@@QBAPBUs_cache_file_codec_definition@@XZ
    t_type const * begin(void) const
    {
        return m_elements;
    }

    static unsigned int get_element_size(void)
    {
        return sizeof(t_type);
    }

    unsigned int get_total_element_size(void) const
    {
        return sizeof(m_elements);
    }

    void set_all(t_type const & value)
    {
        for (long index = 0; index < k_count; index++)
        {
            m_elements[index] = value;
        }
    }

    void set_memory(long value)
    {
        if (sizeof(m_elements) > 32)
        {
            memset_big_crossplatform_internal(m_elements, value, sizeof(m_elements));
        }
        else if (!pointer_is_aligned(m_elements, 2) || (sizeof(m_elements) % sizeof(unsigned long)) != 0)
        {
            memset_big_crossplatform_internal(m_elements, value, sizeof(m_elements));
        }
        else
        {
            // local names affect /Od stack slot assignment
            unsigned long const word_count = sizeof(m_elements) / sizeof(unsigned long);
            long value_byte = value;
            unsigned long pattern = (value_byte << 24) | (value_byte << 16) | (value_byte << 8) | value_byte;
            for (unsigned long index = 0; index < word_count; index++)
            {
                reinterpret_cast<unsigned long *>(m_elements)[index] = pattern;
            }
        }
    }

    template<typename t_index>
    t_type const & element(t_index index) const
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_array.h", 28);

        return m_elements[index];
    }

    template<typename t_index>
    t_type & element(t_index index)
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_array.h", 29);

        return m_elements[index];
    }

    template<typename t_index>
    t_type const & operator[](t_index index) const
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_array.h", 30);

        return m_elements[index];
    }

    template<typename t_index>
    t_type & operator[](t_index index)
    {
        assert_decomp(valid(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_array.h", 31);

        return m_elements[index];
    }

    // ??$?A_N@?$s_static_array@V?$c_basic_buffer@X@@$01@@QAAAAV?$c_basic_buffer@X@@_N@Z (in-class explicit specialization, MSVC extension)
    template<>
    t_type & operator[]<bool>(bool index)
    {
        assert_decomp(valid(static_cast<int32>(index)), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_array.h", 38);

        return m_elements[index];
    }

    t_type m_elements[k_count];
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_ARRAY_H__

