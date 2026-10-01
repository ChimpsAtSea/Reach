#ifndef __STL_HELPERS_H__
#define __STL_HELPERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"

#include <algorithm>
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

template<typename t_type>
class c_memcmp_value_compare
{
public:
    // ??0?$c_memcmp_value_compare@Us_cache_file_codec_definition@@@@QAA@ABUs_cache_file_codec_definition@@@Z
    c_memcmp_value_compare(t_type const & value) :
        m_value(value)
    {
    };

    // ??R?$c_memcmp_value_compare@Us_cache_file_codec_definition@@@@QBA_NABUs_cache_file_codec_definition@@@Z
    bool operator()(t_type const & rhs) const
    {
        return memcmp(&m_value, &rhs, sizeof(t_type)) == 0;
    };

private:
    t_type const & m_value; // 0x0
};

// ??$value_compare@Us_cache_file_codec_definition@@@@YA?AV?$c_memcmp_value_compare@Us_cache_file_codec_definition@@@@ABUs_cache_file_codec_definition@@@Z
template<typename t_type>
c_memcmp_value_compare<t_type> value_compare(t_type const & value)
{
    return c_memcmp_value_compare<t_type>(value);
};

// ??$find_if_container_value@V?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@V?$c_memcmp_value_compare@Us_cache_file_codec_definition@@@@PBUs_cache_file_codec_definition@@@@YA_NABV?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@V?$c_memcmp_value_compare@Us_cache_file_codec_definition@@@@PAPBUs_cache_file_codec_definition@@@Z
template<typename t_container, typename t_predicate, typename t_iterator>
bool find_if_container_value(t_container const & container, t_predicate pred, t_iterator * out_value_iterator)
{
    assert_decomp(out_value_iterator, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\stl_helpers.h", 296);

    bool success = false;
    t_iterator iter = std::find_if(container.begin(), container.end(), pred);
    if (iter != container.end())
    {
        *out_value_iterator = iter;
        success = true;
    }

    return success;
};

// ??$find_container_value_index@V?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@Us_cache_file_codec_definition@@@@YA_NABV?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@ABUs_cache_file_codec_definition@@PAJ@Z
template<typename t_container, typename t_type>
bool find_container_value_index(t_container const & container, t_type const & key, long * out_index)
{
    assert_decomp(out_index, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\stl_helpers.h", 312);

    bool success = false;
    typename t_container::const_iterator value_iterator;
    if (find_if_container_value(container, value_compare(key), &value_iterator))
    {
        *out_index = value_iterator - container.begin();
        success = true;
    }

    return success;
};

// ??$find_or_add_container_value@V?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@Us_cache_file_codec_definition@@@@YAJPAV?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@ABUs_cache_file_codec_definition@@@Z
template<typename t_container, typename t_type>
long find_or_add_container_value(t_container * container, t_type const & value)
{
    long index = NONE;
    typename t_container::const_iterator value_iterator;
    if (find_if_container_value(*container, value_compare(value), &value_iterator))
    {
        index = value_iterator - container->begin();
    }
    else
    {
        index = container->new_element_index();
        (*container)[index] = value;
    }

    return index;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STL_HELPERS_H__

