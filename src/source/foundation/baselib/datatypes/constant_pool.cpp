#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\constant_pool.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\constant_pool.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\hash_table.h"
#include "foundation\baselib\datatypes\memory_pool.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?constant_pool_new@@YAPAUs_constant_pool@@PBDJJQ6AIPBX@ZQ6AK1@ZQ6AXPAX@ZQ6A_N11@ZQ6AX1I4@ZPAVc_allocation_interface@@0J@Z;
// long constant_pool_item_count(struct s_constant_pool const *);
// unsigned int constant_pool_used_size(struct s_constant_pool const *);
// void constant_pool_dispose(struct s_constant_pool *, char const *, long);
// void constant_pool_reset(struct s_constant_pool *);
// void const * constant_pool_add(struct s_constant_pool *, void const *);
// void const * constant_pool_find(struct s_constant_pool const *, void const *);
// bool constant_pool_contains(struct s_constant_pool const *, void const *);
// unsigned int constant_pool_string_size_function(void const *);
// unsigned int constant_pool_size(struct s_constant_pool const *, void const *);
// void constant_pool_simplify(struct s_constant_pool const *, void *);
// void constant_pool_copy(struct s_constant_pool const *, void const *, unsigned int, void *);
// public: void c_data_iterator<struct s_constant_pool_element>::begin(struct s_data_array *);
// public: bool c_data_iterator<struct s_constant_pool_element>::next(void);
// public: bool c_hash_table<long, void>::is_created(void) const;
// ?create@?$c_hash_table@JX@@QAA_NPBDJJQ6AKPBX@ZQ6A_N11@Z0JPAVc_allocation_interface@@@Z;
// public: void c_hash_table<long, void>::dispose(char const *, long);
// public: void c_hash_table<long, void>::reset(void);
// public: bool c_hash_table<long, void>::add(void const *, long const *);
// public: void const * c_hash_table<long, void>::find(void const *, long *) const;

s_constant_pool * constant_pool_new(char const * name, long maximum_count, long maximum_size, constant_pool_size_function * const size_function, constant_pool_hash_function * const hash_function, constant_pool_simplify_function * const simplify_function, constant_pool_compare_function * const compare_function, constant_pool_copy_function * const copy_function, c_allocation_interface * allocation, char const * file, long line)
{
    mangled_ppc("?constant_pool_new@@YAPAUs_constant_pool@@PBDJJQ6AIPBX@ZQ6AK1@ZQ6AXPAX@ZQ6A_N11@ZQ6AX1I4@ZPAVc_allocation_interface@@0J@Z");

    assert_tag_debug_untracked_jul_11_2011(79, size_function);
    assert_tag_debug_untracked_jul_11_2011(80, allocation);

    s_constant_pool * pool = static_cast<s_constant_pool *>(allocation->allocate(sizeof(s_constant_pool), file, line, "constant pool", "", name));
    if (pool != NULL)
    {
        csmemset(pool, 0, sizeof(s_constant_pool));
        pool->name.set(name);
        pool->size_function = size_function;
        pool->hash_function = hash_function;
        pool->simplify_function = simplify_function;
        pool->compare_function = compare_function;
        pool->copy_function = copy_function;
        pool->allocation = allocation;
        pool->hash_table.create(name, maximum_count * 2, maximum_count, hash_function, compare_function, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 94, allocation);

        pool->elements = data_new(name, maximum_count, sizeof(s_constant_pool_element), 0, file, line, allocation);
        if (pool->elements != NULL)
        {
            data_make_valid(pool->elements);
        }

        pool->element_storage = memory_pool_new("constant pool", maximum_size, NULL, allocation, file, line);
        if (pool->element_storage != NULL)
        {
            memory_pool_set_reference_tracking(pool->element_storage, false);
            memory_pool_set_verification(pool->element_storage, false);
        }

        if (pool->elements == NULL || !pool->hash_table.is_created() || pool->element_storage == NULL)
        {
            constant_pool_dispose(pool, file, line);
            pool = NULL;
        }
    }

    return pool;
};

long constant_pool_item_count(s_constant_pool const * pool)
{
    mangled_ppc("?constant_pool_item_count@@YAJPBUs_constant_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(125, pool);

    return data_get_count(pool->elements);
};

unsigned int constant_pool_used_size(s_constant_pool const * pool)
{
    mangled_ppc("?constant_pool_used_size@@YAIPBUs_constant_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(132, pool);

    return memory_pool_get_used_size(pool->element_storage);
};

void constant_pool_dispose(s_constant_pool * pool, char const * file, long line)
{
    mangled_ppc("?constant_pool_dispose@@YAXPAUs_constant_pool@@PBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(142, pool);

    c_allocation_interface * allocation = pool->allocation;
    constant_pool_reset(pool);

    if (pool->hash_table.is_created())
    {
        pool->hash_table.dispose(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 149);
    }

    if (pool->elements != NULL)
    {
        data_dispose(pool->elements, file, line);
        pool->elements = NULL;
    }

    if (pool->element_storage != NULL)
    {
        memory_pool_dispose(pool->element_storage, file, line);
        pool->element_storage = NULL;
    }

    allocation->deallocate(pool, file, line);
};

void constant_pool_reset(s_constant_pool * pool)
{
    mangled_ppc("?constant_pool_reset@@YAXPAUs_constant_pool@@@Z");

    assert_tag_debug_untracked_jul_11_2011(170, pool);

    pool->hash_table.reset();

    c_data_iterator<s_constant_pool_element> iterator;
    iterator.begin(pool->elements);
    while (iterator.next())
    {
        memory_pool_block_free(pool->element_storage, &iterator.m_datum->data);
    }

    memory_pool_clear(pool->element_storage);
    data_delete_all(pool->elements);
};

void const * constant_pool_add(s_constant_pool * pool, void const * item)
{
    mangled_ppc("?constant_pool_add@@YAPBXPAUs_constant_pool@@PBX@Z");

    void const * result = constant_pool_find(pool, item);
    if (result == NULL)
    {
        long element_index = datum_new(pool->elements);
        if (element_index != NONE)
        {
            bool success = false;
            unsigned int size = constant_pool_size(pool, item);
            s_constant_pool_element * element = static_cast<s_constant_pool_element *>(datum_get(pool->elements, element_index));
            if (memory_pool_block_allocate_tracked(pool->element_storage, &element->data, size, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 206))
            {
                constant_pool_copy(pool, item, size, element->data);
                constant_pool_simplify(pool, element->data);
                success = pool->hash_table.add(element->data, &element_index);
            }

            if (success)
            {
                result = element->data;
            }
            else if (!success)
            {
                if (element->data != NULL)
                {
                    memory_pool_block_free(pool->element_storage, &element->data);
                }
                datum_delete(pool->elements, element_index);
            }
        }
    }

    return result;
};

void const * constant_pool_find(s_constant_pool const * pool, void const * item)
{
    mangled_ppc("?constant_pool_find@@YAPBXPBUs_constant_pool@@PBX@Z");

    char buffer[1024];
    assert_tag_debug_untracked_jul_11_2011(240, pool->size_function(item)<sizeof(buffer));

    constant_pool_copy(pool, item, sizeof(buffer), buffer);
    constant_pool_simplify(pool, buffer);
    void const * result = pool->hash_table.find(buffer, NULL);

    return result;
};

bool constant_pool_contains(s_constant_pool const * pool, void const * item)
{
    mangled_ppc("?constant_pool_contains@@YA_NPBUs_constant_pool@@PBX@Z");

    assert_tag_debug_untracked_jul_11_2011(257, pool);

    void * start;
    void * end;
    memory_pool_get_bounds(pool->element_storage, &start, &end);

    return item >= start && item < end;
};

unsigned int constant_pool_string_size_function(void const * item)
{
    mangled_ppc("?constant_pool_string_size_function@@YAIPBX@Z");

    char const * string = static_cast<char const *>(item);
    unsigned int size = strlen_debug(string) + 1;

    return size;
};

unsigned int constant_pool_size(s_constant_pool const * pool, void const * item)
{
    mangled_ppc("?constant_pool_size@@YAIPBUs_constant_pool@@PBX@Z");

    assert_tag_debug_untracked_jul_11_2011(278, pool);
    assert_tag_debug_untracked_jul_11_2011(279, pool->size_function);

    return pool->size_function(item);
};

void constant_pool_simplify(s_constant_pool const * pool, void * item)
{
    mangled_ppc("?constant_pool_simplify@@YAXPBUs_constant_pool@@PAX@Z");

    assert_tag_debug_untracked_jul_11_2011(287, pool);

    if (pool->simplify_function != NULL)
    {
        pool->simplify_function(item);
    }
};

void constant_pool_copy(s_constant_pool const * pool, void const * item, unsigned int dst_size, void * destination)
{
    mangled_ppc("?constant_pool_copy@@YAXPBUs_constant_pool@@PBXIPAX@Z");

    if (pool->copy_function != NULL)
    {
        pool->copy_function(item, dst_size, destination);
    }
    else
    {
        unsigned int src_size = constant_pool_size(pool, item);
        assert_tag_debug_untracked_jul_11_2011(360, src_size<=dst_size);

        csmemcpy(destination, item, src_size);
    }
};
