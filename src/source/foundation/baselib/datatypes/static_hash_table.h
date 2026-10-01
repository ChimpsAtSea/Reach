#ifndef __STATIC_HASH_TABLE_H__
#define __STATIC_HASH_TABLE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_hash_table_data.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_hash_data, long k_hash_a, long k_hash_b, long k_hash_c>
class c_static_hash_table
{
public:
    static long const k_hash_invalid = -1;

    static long iterator_begin(t_hash_data const * hash_data)
    {
        mangled_ppc("?iterator_begin@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@SAJPBV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@@Z");

        return k_hash_invalid;
    };

    static long iterator_next(t_hash_data const * hash_data, long index)
    {
        mangled_ppc("?iterator_next@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@SAJPBV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@J@Z");

        if (hash_data->get_total_count() == 0)
        {
            index = k_hash_invalid;
        }
        else
        {
            bool empty = true;
            while (empty)
            {
                if (index == hash_data->get_maximum_count() - 1)
                {
                    empty = false;
                    index = k_hash_invalid;
                }
                else
                {
                    empty = hash_data->get_original_hash_entry()[++index] == t_hash_data::k_hash_entry_invalid;
                }
            }
        }

        return index;
    };

    static long add_entry(t_hash_data * hash_data, long key_a, long key_b, long key_c)
    {
        mangled_ppc("?add_entry@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@SAJPAV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@JJJ@Z");

        long actual_hash_index = k_hash_invalid;

        if (hash_data->get_total_count() < hash_data->get_maximum_count())
        {
            long original_hash_index = calculate_hash(hash_data, key_a, key_b, key_c);
            actual_hash_index = find_new_hash_entry(hash_data, original_hash_index);
            if (actual_hash_index != k_hash_invalid)
            {
                typename t_hash_data::s_data * element = hash_data->get_data(actual_hash_index);
                long new_count = hash_data->get_hash_entry_count()[original_hash_index] + 1;

                element->key_a = key_a;
                element->key_b = key_b;
                element->key_c = key_c;
                hash_data->get_original_hash_entry()[actual_hash_index] = static_cast<short>(original_hash_index);

                assert_decomp(new_count<=k_int16_max, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_hash_table.h", 69);
                hash_data->get_hash_entry_count()[original_hash_index] = static_cast<short>(new_count);
            }

            hash_data->increment_total_count();
        }

        return actual_hash_index;
    };

    static long find_entry(t_hash_data const * hash_data, long key_a, long key_b, long key_c)
    {
        mangled_ppc("?find_entry@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@SAJPBV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@JJJ@Z");

        long const original_hash_index = calculate_hash(hash_data, key_a, key_b, key_c);
        long current_hash_index = original_hash_index;
        long original_count = hash_data->get_hash_entry_count()[original_hash_index];

        assert_decomp(original_count<=hash_data->get_maximum_count(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_hash_table.h", 103);

        long found_index = k_hash_invalid;
        if (original_count > 0)
        {
            short const * original_hash_entry = hash_data->get_original_hash_entry();
            long count;
            for (count = 0; count < hash_data->get_maximum_count(); count++)
            {
                if (original_hash_entry[current_hash_index] == original_hash_index)
                {
                    typename t_hash_data::s_data const * element = hash_data->get_data(current_hash_index);
                    if (element->key_a == key_a && element->key_b == key_b && element->key_c == key_c)
                    {
                        found_index = current_hash_index;
                        break;
                    }

                    if (--original_count <= 0)
                    {
                        break;
                    }
                }

                current_hash_index = (current_hash_index + 1) % hash_data->get_maximum_count();
            }

            if (count == hash_data->get_maximum_count())
            {
                event(_event_warning, "c_static_hash_table: didn't find entry in hash table");
            }
        }

        return found_index;
    };

private:
    static long calculate_hash(t_hash_data const * hash_data, long key_a, long key_b, long key_c)
    {
        mangled_ppc("?calculate_hash@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@CAJPBV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@JJJ@Z");

        unsigned long hash = key_a * k_hash_a + key_b * k_hash_b + key_c * k_hash_c;

        return hash % hash_data->get_maximum_count();
    };

    static long find_new_hash_entry(t_hash_data * hash_data, long original_hash_index)
    {
        mangled_ppc("?find_new_hash_entry@?$c_static_hash_table@V?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@$0LLJ@$0BMBD@$0CGPF@@@CAJPAV?$c_static_hash_table_data@PAUs_header_tracking_info@@$0CAAA@@@J@Z");

        long original_count = hash_data->get_hash_entry_count()[original_hash_index];
        long current_offset = original_hash_index;

        while (original_count > 0)
        {
            if (hash_data->get_original_hash_entry()[current_offset++ % hash_data->get_maximum_count()] == original_hash_index)
            {
                original_count--;
            }
        }

        bool found_empty = false;
        while (!found_empty)
        {
            found_empty = hash_data->get_original_hash_entry()[current_offset % hash_data->get_maximum_count()] == t_hash_data::k_hash_entry_invalid;
            if (!found_empty)
            {
                current_offset++;
            }
        }

        return current_offset % hash_data->get_maximum_count();
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_HASH_TABLE_H__
