#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

class c_allocation_interface;

typedef unsigned long hash_table_hash_function(void const *);
typedef bool hash_table_compare_function(void const *, void const *);

struct s_hash_table_bucket
{
    void const * key;
    unsigned long hash;
    s_hash_table_bucket * next;
};
static_assert(sizeof(s_hash_table_bucket) == 0xC, "s_hash_table_bucket");

struct s_hash_table_internals
{
    s_static_string<32> name;
    long bucket_count;
    long maximum_elements;
    unsigned int user_data_size;
    hash_table_hash_function * hash_function;
    hash_table_compare_function * compare_function;
    c_allocation_interface * allocation;
    void const * base_address;
    s_hash_table_bucket * free_list;
};
static_assert(sizeof(s_hash_table_internals) == 0x40, "s_hash_table_internals");

/* ---------- prototypes */

extern unsigned int hash_table_allocation_size(unsigned int user_data_size, long bucket_count, long maximum_elements);
extern s_hash_table_internals * hash_table_create(char const * name, unsigned int user_data_size, long bucket_count, long maximum_elements, hash_table_hash_function * const hash_function, hash_table_compare_function * const compare_function, char const * file, long line, c_allocation_interface * allocation);
extern void hash_table_dispose(s_hash_table_internals * hash_table, char const * file, long line);
extern void hash_table_reset(s_hash_table_internals * hash_table);
extern void hash_table_verify(s_hash_table_internals const * hash_table);
extern void hash_table_rebase(s_hash_table_internals * hash_table, bool rebase_keys);
extern bool hash_table_add(s_hash_table_internals * hash_table, void const * key, void const * in_user_data);
extern bool hash_table_remove(s_hash_table_internals * hash_table, void const * key);
extern void const * hash_table_find(s_hash_table_internals const * hash_table, void const * key, void * out_user_data);
extern bool hash_table_set_data(s_hash_table_internals * hash_table, void const * key, void const * in_user_data);
extern void hash_table_set_functions(s_hash_table_internals * hash_table, hash_table_hash_function * const hash_function, hash_table_compare_function * const compare_function);
extern unsigned long string_hash_table_hash_function(void const * string);
extern bool string_hash_table_compare_function(void const * string1, void const * string2);

/* ---------- globals */

/* ---------- public code */

template<typename t_type, typename t_extra>
class c_hash_table
{
public:
    c_hash_table(void)
    {
        mangled_ppc("??0?$c_hash_table@PAUs_pointer_header@@X@@QAA@XZ");

        m_hash_table = NULL;
    };

    ~c_hash_table(void)
    {
        mangled_ppc("??1?$c_hash_table@PAUs_pointer_header@@X@@QAA@XZ");

        if (is_created())
        {
            dispose("C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 111);
        }
    };

    bool create(char const * name, long bucket_count, long maximum_elements, hash_table_hash_function * const hash_function, hash_table_compare_function * const compare_function, char const * file, long line, c_allocation_interface * allocation)
    {
        mangled_ppc("?create@?$c_hash_table@PAUs_pointer_header@@X@@QAA_NPBDJJQ6AKPBX@ZQ6A_N11@Z0JPAVc_allocation_interface@@@Z");

        assert_decomp(m_hash_table==NULL, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 140);
        m_hash_table = hash_table_create(name, sizeof(t_type), bucket_count, maximum_elements, hash_function, compare_function, file, line, allocation);
        m_debug_this = this;

        return is_created();
    };

    void dispose(char const * file, long line)
    {
        mangled_ppc("?dispose@?$c_hash_table@PAUs_pointer_header@@X@@QAAXPBDJ@Z");

        assert_decomp(is_created(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 152);
        hash_table_dispose(m_hash_table, file, line);
        m_hash_table = NULL;
    };

    void reset(void)
    {
        mangled_ppc("?reset@?$c_hash_table@JX@@QAAXXZ");

        assert_decomp(is_created(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 161);
        hash_table_reset(m_hash_table);
    };

    bool is_created(void) const
    {
        mangled_ppc("?is_created@?$c_hash_table@PAUs_pointer_header@@X@@QBA_NXZ");

        return m_hash_table != NULL;
    };

    bool add(void const * key, t_type const * user_data)
    {
        mangled_ppc("?add@?$c_hash_table@PAUs_pointer_header@@X@@QAA_NPBXPBQAUs_pointer_header@@@Z");

        assert_decomp(is_created(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 209);
        return hash_table_add(m_hash_table, key, user_data);
    };

    bool remove(void const * key)
    {
        mangled_ppc("?remove@?$c_hash_table@PAUs_pointer_header@@X@@QAA_NPBX@Z");

        assert_decomp(is_created(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 217);
        return hash_table_remove(m_hash_table, key);
    };

    void const * find(void const * key, t_type * out_user_data) const
    {
        mangled_ppc("?find@?$c_hash_table@PAUs_pointer_header@@X@@QBAPBXPBXPAPAUs_pointer_header@@@Z");

        assert_decomp(is_created(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/hash_table.h", 226);
        void const * result = hash_table_find(m_hash_table, key, out_user_data);

        return result;
    };

protected:
    s_hash_table_internals * m_hash_table;
    c_hash_table * m_debug_this;
};

#endif // __HASH_TABLE_H__
