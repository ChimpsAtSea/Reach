#ifndef __STATIC_HASH_TABLE_DATA_H__
#define __STATIC_HASH_TABLE_DATA_H__
#pragma once

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type, long k_maximum_count>
class c_static_hash_table_data
{
public:
    static short const k_hash_entry_invalid = -1;

    struct s_data
    {
        t_type element;
        long key_a;
        long key_b;
        long key_c;
    };

    void clear_all(void)
    {
        mangled_ppc("?clear_all@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAXXZ");

        m_total_count = 0;
        m_hash_entry_count.set_memory(0);
        m_original_hash_entry.set_memory(k_hash_entry_invalid);
    };

    t_type * get_element(long index)
    {
        mangled_ppc("?get_element@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAPAPAUs_header_tracking_info@@J@Z");

        return &m_data[index].element;
    };

    s_data * get_data(long index)
    {
        mangled_ppc("?get_data@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAPAUs_data@1@J@Z");

        return &m_data[index];
    };

    s_data const * get_data(long index) const
    {
        mangled_ppc("?get_data@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QBAPBUs_data@1@J@Z");

        return &m_data[index];
    };

    long get_total_count(void) const
    {
        mangled_ppc("?get_total_count@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QBAJXZ");

        return m_total_count;
    };

    long get_maximum_count(void) const
    {
        mangled_ppc("?get_maximum_count@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QBAJXZ");

        return k_maximum_count;
    };

    void increment_total_count(void)
    {
        mangled_ppc("?increment_total_count@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAXXZ");

        m_total_count++;
    };

    short * get_hash_entry_count(void)
    {
        mangled_ppc("?get_hash_entry_count@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAPAFXZ");

        return m_hash_entry_count.get_elements();
    };

    short const * get_hash_entry_count(void) const
    {
        mangled_ppc("?get_hash_entry_count@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QBAPBFXZ");

        return m_hash_entry_count.get_elements();
    };

    short * get_original_hash_entry(void)
    {
        mangled_ppc("?get_original_hash_entry@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QAAPAFXZ");

        return m_original_hash_entry.get_elements();
    };

    short const * get_original_hash_entry(void) const
    {
        mangled_ppc("?get_original_hash_entry@?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@QBAPBFXZ");

        return m_original_hash_entry.get_elements();
    };

protected:
    long m_total_count;
    s_static_array<s_data, k_maximum_count> m_data;
    s_static_array<short, k_maximum_count> m_hash_entry_count;
    s_static_array<short, k_maximum_count> m_original_hash_entry;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_HASH_TABLE_DATA_H__
