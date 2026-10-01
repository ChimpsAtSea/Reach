#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\hash_table.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\hash_table.h"
#include "foundation\baselib\datatypes\hash.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

inline s_hash_table_bucket ** get_buckets(s_hash_table_internals * hash_table);
inline s_hash_table_bucket * get_free_list_elements(s_hash_table_internals * hash_table);
inline s_hash_table_bucket const * get_free_list_elements_const(s_hash_table_internals const * hash_table);
inline void * get_user_data(s_hash_table_bucket * bucket);
inline void const * get_user_data_const(s_hash_table_bucket const * bucket);
static bool valid_bucket_pointer(s_hash_table_internals const * table, s_hash_table_bucket const * bucket);
static void rebase_pointer(s_hash_table_internals * table, s_hash_table_bucket ** pointer);
static s_hash_table_bucket const * hash_table_find_internal(s_hash_table_internals const * table, void const * key);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned int hash_table_allocation_size(unsigned int, long, long);
// ?hash_table_create@@YAPAUs_hash_table_internals@@PBDIJJQ6AKPBX@ZQ6A_N11@Z0JPAVc_allocation_interface@@@Z;
// void hash_table_dispose(struct s_hash_table_internals *, char const *, long);
// void hash_table_reset(struct s_hash_table_internals *);
// struct s_hash_table_bucket ** get_buckets(struct s_hash_table_internals *);
// struct s_hash_table_bucket * get_free_list_elements(struct s_hash_table_internals *);
// void hash_table_verify(struct s_hash_table_internals const *);
// struct s_hash_table_bucket const * get_free_list_elements_const(struct s_hash_table_internals const *);
// void hash_table_rebase(struct s_hash_table_internals *, bool);
// bool hash_table_add(struct s_hash_table_internals *, void const *, void const *);
// void * get_user_data(struct s_hash_table_bucket *);
// bool hash_table_remove(struct s_hash_table_internals *, void const *);
// void const * hash_table_find(struct s_hash_table_internals const *, void const *, void *);
// void const * get_user_data_const(struct s_hash_table_bucket const *);
// bool hash_table_set_data(struct s_hash_table_internals *, void const *, void const *);
// ?hash_table_set_functions@@YAXPAUs_hash_table_internals@@Q6AKPBX@ZQ6A_N11@Z@Z;
// bool valid_bucket_pointer(struct s_hash_table_internals const *, struct s_hash_table_bucket const *);
// void rebase_pointer(struct s_hash_table_internals *, struct s_hash_table_bucket **);
// struct s_hash_table_bucket const * hash_table_find_internal(struct s_hash_table_internals const *, void const *);
// unsigned long string_hash_table_hash_function(void const *);
// bool string_hash_table_compare_function(void const *, void const *);

unsigned int hash_table_allocation_size(unsigned int user_data_size, long bucket_count, long maximum_elements)
{
    mangled_ppc("?hash_table_allocation_size@@YAIIJJ@Z");

    return bucket_count * sizeof(s_hash_table_bucket *) + sizeof(s_hash_table_internals) + maximum_elements * (user_data_size + sizeof(s_hash_table_bucket));
};

s_hash_table_internals * hash_table_create(char const * name, unsigned int user_data_size, long bucket_count, long maximum_elements, hash_table_hash_function * const hash_function, hash_table_compare_function * const compare_function, char const * file, long line, c_allocation_interface * allocation)
{
    mangled_ppc("?hash_table_create@@YAPAUs_hash_table_internals@@PBDIJJQ6AKPBX@ZQ6A_N11@Z0JPAVc_allocation_interface@@@Z");

    unsigned int allocation_size = hash_table_allocation_size(user_data_size, bucket_count, maximum_elements);
    s_hash_table_internals * hash_table = NULL;

    assert_tag_debug_untracked_jul_11_2011(85, bucket_count>0);
    assert_tag_debug_untracked_jul_11_2011(86, maximum_elements>0);
    assert_tag_debug_untracked_jul_11_2011(87, hash_function);
    assert_tag_debug_untracked_jul_11_2011(88, compare_function);
    assert_tag_debug_untracked_jul_11_2011(89, allocation);

    void * buffer = allocation->allocate(allocation_size, file, line, "hash_table", NULL, name);
    if (buffer != NULL)
    {
        hash_table = static_cast<s_hash_table_internals *>(buffer);
        csmemset(hash_table, 0, sizeof(s_hash_table_internals));
        hash_table->name.set(name);
        hash_table->bucket_count = bucket_count;
        hash_table->maximum_elements = maximum_elements;
        hash_table->user_data_size = user_data_size;
        hash_table->hash_function = hash_function;
        hash_table->compare_function = compare_function;
        hash_table->allocation = allocation;
        hash_table->base_address = hash_table;
        hash_table_reset(hash_table);
    }

    return hash_table;
};

void hash_table_dispose(s_hash_table_internals * hash_table, char const * file, long line)
{
    mangled_ppc("?hash_table_dispose@@YAXPAUs_hash_table_internals@@PBDJ@Z");

    hash_table_verify(hash_table);

    c_allocation_interface * allocation = hash_table->allocation;
    assert_tag_debug_untracked_jul_11_2011(124, allocation!=NULL);

    allocation->deallocate(hash_table, file, line);
};

void hash_table_reset(s_hash_table_internals * hash_table)
{
    mangled_ppc("?hash_table_reset@@YAXPAUs_hash_table_internals@@@Z");

    long size_of_buckets = hash_table->bucket_count * sizeof(s_hash_table_bucket *);
    unsigned int bucket_size = hash_table->user_data_size + sizeof(s_hash_table_bucket);

    {
        unsigned int size_of_clear = size_of_buckets + hash_table->maximum_elements * bucket_size;
        s_hash_table_bucket ** clear_location = get_buckets(hash_table);
        csmemset(clear_location, 0, size_of_clear);
    }

    {
        long free_list_count = hash_table->maximum_elements;
        s_hash_table_bucket * free_list_elements = get_free_list_elements(hash_table);
        hash_table->free_list = NULL;
        for (long free_list_index = 0; free_list_index < free_list_count; free_list_index++)
        {
            s_hash_table_bucket * next_element_to_add = static_cast<s_hash_table_bucket *>(offset_pointer(free_list_elements, free_list_index * bucket_size));
            assert_tag_debug_untracked_jul_11_2011(156, valid_bucket_pointer(hash_table, next_element_to_add));

            next_element_to_add->next = hash_table->free_list;
            hash_table->free_list = next_element_to_add;
        }
    }

    hash_table_verify(hash_table);
};

inline s_hash_table_bucket ** get_buckets(s_hash_table_internals * hash_table)
{
    mangled_ppc("?get_buckets@@YAPAPAUs_hash_table_bucket@@PAUs_hash_table_internals@@@Z");

    return reinterpret_cast<s_hash_table_bucket **>(hash_table + 1);
};

inline s_hash_table_bucket * get_free_list_elements(s_hash_table_internals * hash_table)
{
    mangled_ppc("?get_free_list_elements@@YAPAUs_hash_table_bucket@@PAUs_hash_table_internals@@@Z");

    return static_cast<s_hash_table_bucket *>(offset_pointer(hash_table, hash_table->bucket_count * sizeof(s_hash_table_bucket *) + sizeof(s_hash_table_internals)));
};

void hash_table_verify(s_hash_table_internals const * hash_table)
{
    mangled_ppc("?hash_table_verify@@YAXPBUs_hash_table_internals@@@Z");

    assert_tag_debug_untracked_jul_11_2011(174, hash_table);
    assert_tag_debug_untracked_jul_11_2011(175, hash_table->bucket_count>0);
    assert_tag_debug_untracked_jul_11_2011(176, hash_table->maximum_elements>0);
    assert_tag_debug_untracked_jul_11_2011(177, hash_table->user_data_size>0);
    assert_tag_debug_untracked_jul_11_2011(178, hash_table->hash_function);
    assert_tag_debug_untracked_jul_11_2011(179, hash_table->compare_function);
    assert_tag_debug_untracked_jul_11_2011(180, hash_table->allocation);
    assert_tag_debug_untracked_jul_11_2011(181, hash_table->base_address==static_cast<const void *>(hash_table));

    s_hash_table_bucket ** buckets = get_buckets(const_cast<s_hash_table_internals *>(hash_table));
    s_hash_table_bucket const * free_list_elements = get_free_list_elements_const(hash_table);

    for (long bucket_index = 0; bucket_index < hash_table->bucket_count; bucket_index++)
    {
        for (s_hash_table_bucket const * current_bucket = buckets[bucket_index]; current_bucket != NULL; current_bucket = current_bucket->next)
        {
            assert_tag_debug_untracked_jul_11_2011(190, valid_bucket_pointer(hash_table, current_bucket));
        }
    }

    for (s_hash_table_bucket const * current_bucket = hash_table->free_list; current_bucket != NULL; current_bucket = current_bucket->next)
    {
        assert_tag_debug_untracked_jul_11_2011(196, valid_bucket_pointer(hash_table, current_bucket));
    }
};

inline s_hash_table_bucket const * get_free_list_elements_const(s_hash_table_internals const * hash_table)
{
    mangled_ppc("?get_free_list_elements_const@@YAPBUs_hash_table_bucket@@PBUs_hash_table_internals@@@Z");

    return static_cast<s_hash_table_bucket const *>(offset_pointer(hash_table, hash_table->bucket_count * sizeof(s_hash_table_bucket *) + sizeof(s_hash_table_internals)));
};

void hash_table_rebase(s_hash_table_internals * hash_table, bool rebase_keys)
{
    mangled_ppc("?hash_table_rebase@@YAXPAUs_hash_table_internals@@_N@Z");

    if (hash_table->user_data_size > 0)
    {
        unsigned int bucket_size = hash_table->user_data_size + sizeof(s_hash_table_bucket);
        s_hash_table_bucket ** buckets = get_buckets(hash_table);
        s_hash_table_bucket * free_list_elements = get_free_list_elements(hash_table);

        for (long bucket_index = 0; bucket_index < hash_table->bucket_count; bucket_index++)
        {
            rebase_pointer(hash_table, &buckets[bucket_index]);
        }

        rebase_pointer(hash_table, &hash_table->free_list);

        for (long free_list_index = 0; free_list_index < hash_table->maximum_elements; free_list_index++)
        {
            s_hash_table_bucket * element = static_cast<s_hash_table_bucket *>(offset_pointer(free_list_elements, free_list_index * bucket_size));
            rebase_pointer(hash_table, &element->next);
        }

        if (rebase_keys)
        {
            for (long bucket_index = 0; bucket_index < hash_table->bucket_count; bucket_index++)
            {
                for (s_hash_table_bucket * current_bucket = buckets[bucket_index]; current_bucket != NULL; current_bucket = current_bucket->next)
                {
                    long key_offset = pointer_distance(hash_table->base_address, current_bucket->key);
                    assert_tag_debug_untracked_jul_11_2011(241, current_bucket->key!=NULL);

                    current_bucket->key = offset_pointer(hash_table, key_offset);
                }
            }
        }

        hash_table->base_address = hash_table;
        hash_table_verify(hash_table);
    }
    else
    {
        assert_tag_debug_untracked_jul_11_2011(256, hash_table->base_address==NULL);
    }
};

bool hash_table_add(s_hash_table_internals * hash_table, void const * key, void const * in_user_data)
{
    mangled_ppc("?hash_table_add@@YA_NPAUs_hash_table_internals@@PBX1@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(268, hash_table_find_internal(hash_table, key)==NULL);
    assert_tag_debug_untracked_jul_11_2011(269, in_user_data);

    if (hash_table->free_list != NULL)
    {
        unsigned long new_element_hash_value = hash_table->hash_function(key);
        long target_bucket_index = new_element_hash_value % hash_table->bucket_count;
        s_hash_table_bucket ** buckets = get_buckets(hash_table);
        s_hash_table_bucket * new_element = hash_table->free_list;

        hash_table->free_list = new_element->next;

        assert_tag_debug_untracked_jul_11_2011(284, valid_bucket_pointer(hash_table, new_element));
        assert_tag_debug_untracked_jul_11_2011(285, valid_bucket_pointer(hash_table, hash_table->free_list));

        new_element->key = key;
        new_element->hash = new_element_hash_value;
        csmemcpy(get_user_data(new_element), in_user_data, hash_table->user_data_size);

        assert_tag_debug_untracked_jul_11_2011(293, VALID_INDEX(target_bucket_index, hash_table->bucket_count));

        s_hash_table_bucket * next_element_in_bucket = buckets[target_bucket_index];
        new_element->next = next_element_in_bucket;
        buckets[target_bucket_index] = new_element;

        success = true;
    }

    return success;
};

inline void * get_user_data(s_hash_table_bucket * bucket)
{
    mangled_ppc("?get_user_data@@YAPAXPAUs_hash_table_bucket@@@Z");

    return bucket + 1;
};

bool hash_table_remove(s_hash_table_internals * hash_table, void const * key)
{
    mangled_ppc("?hash_table_remove@@YA_NPAUs_hash_table_internals@@PBX@Z");

    bool success = false;
    unsigned long new_element_hash_value = hash_table->hash_function(key);
    long target_bucket_index = new_element_hash_value % hash_table->bucket_count;
    s_hash_table_bucket ** buckets = get_buckets(hash_table);
    s_hash_table_bucket * previous_bucket = NULL;

    assert_tag_debug_untracked_jul_11_2011(315, VALID_INDEX(target_bucket_index, hash_table->bucket_count));

    for (s_hash_table_bucket * current_bucket = buckets[target_bucket_index]; current_bucket != NULL; current_bucket = current_bucket->next)
    {
        assert_tag_debug_untracked_jul_11_2011(319, valid_bucket_pointer(hash_table, current_bucket));

        if (hash_table->compare_function(key, current_bucket->key))
        {
            assert_tag_debug_untracked_jul_11_2011(323, hash_table_find_internal(hash_table, key)==current_bucket);

            if (previous_bucket == NULL)
            {
                buckets[target_bucket_index] = current_bucket->next;
            }
            else
            {
                previous_bucket->next = current_bucket->next;
            }

            current_bucket->next = hash_table->free_list;
            hash_table->free_list = current_bucket;

            success = true;
            break;
        }

        previous_bucket = current_bucket;
    }

    if (!success)
    {
        assert_tag_debug_untracked_jul_11_2011(348, hash_table_find_internal(hash_table, key)==NULL);
    }

    return success;
};

void const * hash_table_find(s_hash_table_internals const * hash_table, void const * key, void * out_user_data)
{
    mangled_ppc("?hash_table_find@@YAPBXPBUs_hash_table_internals@@PBXPAX@Z");

    void const * result = NULL;
    s_hash_table_bucket const * bucket = hash_table_find_internal(hash_table, key);

    if (bucket != NULL)
    {
        if (out_user_data != NULL)
        {
            csmemcpy(out_user_data, get_user_data_const(bucket), hash_table->user_data_size);
        }

        result = bucket->key;
    }

    return result;
};

inline void const * get_user_data_const(s_hash_table_bucket const * bucket)
{
    mangled_ppc("?get_user_data_const@@YAPBXPBUs_hash_table_bucket@@@Z");

    return bucket + 1;
};

bool hash_table_set_data(s_hash_table_internals * hash_table, void const * key, void const * in_user_data)
{
    mangled_ppc("?hash_table_set_data@@YA_NPAUs_hash_table_internals@@PBX1@Z");

    s_hash_table_bucket * bucket = const_cast<s_hash_table_bucket *>(hash_table_find_internal(hash_table, key));
    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(385, in_user_data);

    if (bucket != NULL)
    {
        csmemcpy(get_user_data(bucket), in_user_data, hash_table->user_data_size);
        success = true;
    }

    return success;
};

void hash_table_set_functions(s_hash_table_internals * hash_table, hash_table_hash_function * const hash_function, hash_table_compare_function * const compare_function)
{
    mangled_ppc("?hash_table_set_functions@@YAXPAUs_hash_table_internals@@Q6AKPBX@ZQ6A_N11@Z@Z");

    assert_tag_debug_untracked_jul_11_2011(401, hash_table);

    hash_table->hash_function = hash_function;
    hash_table->compare_function = compare_function;
};

static bool valid_bucket_pointer(s_hash_table_internals const * table, s_hash_table_bucket const * bucket)
{
    mangled_ppc("?valid_bucket_pointer@@YA_NPBUs_hash_table_internals@@PBUs_hash_table_bucket@@@Z");

    bool valid = true;

    assert_tag_debug_untracked_jul_11_2011(415, table);

    if (bucket != NULL)
    {
        unsigned int bucket_size = table->user_data_size + sizeof(s_hash_table_bucket);
        s_hash_table_bucket const * first_bucket = get_free_list_elements(const_cast<s_hash_table_internals *>(table));
        s_hash_table_bucket const * last_bucket = static_cast<s_hash_table_bucket const *>(offset_pointer(first_bucket, bucket_size * (table->maximum_elements - 1)));

        valid = valid && (bucket >= first_bucket && bucket <= last_bucket);
        valid = valid && (pointer_distance(first_bucket, bucket) % bucket_size) == 0;
    }

    return valid;
};

static void rebase_pointer(s_hash_table_internals * table, s_hash_table_bucket ** pointer)
{
    mangled_ppc("?rebase_pointer@@YAXPAUs_hash_table_internals@@PAPAUs_hash_table_bucket@@@Z");

    if (*pointer != NULL)
    {
        long pointer_offset = pointer_distance(table->base_address, *pointer);
        s_hash_table_bucket * new_pointer = static_cast<s_hash_table_bucket *>(offset_pointer(table, pointer_offset));
        unsigned int bucket_size = table->user_data_size + sizeof(s_hash_table_bucket);
        s_hash_table_bucket * first_bucket = get_free_list_elements(table);
        void const * last_bucket = offset_pointer(static_cast<void const *>(first_bucket), bucket_size * (table->maximum_elements - 1));
        long first_bucket_offset = pointer_distance(table, first_bucket);
        long last_bucket_offset = pointer_distance(table, last_bucket);

        assert_tag_debug_untracked_jul_11_2011(448, IN_RANGE_INCLUSIVE(pointer_offset, first_bucket_offset, last_bucket_offset));
        assert_tag_debug_untracked_jul_11_2011(449, ((pointer_offset-first_bucket_offset)%bucket_size)==0);
        assert_tag_debug_untracked_jul_11_2011(451, valid_bucket_pointer(table, new_pointer));

        *pointer = new_pointer;
    }
};

static s_hash_table_bucket const * hash_table_find_internal(s_hash_table_internals const * table, void const * key)
{
    mangled_ppc("?hash_table_find_internal@@YAPBUs_hash_table_bucket@@PBUs_hash_table_internals@@PBX@Z");

    s_hash_table_bucket const * result = NULL;
    unsigned long search_hash_value = table->hash_function(key);
    long target_bucket_index = search_hash_value % table->bucket_count;
    s_hash_table_bucket ** buckets = get_buckets(const_cast<s_hash_table_internals *>(table));

    assert_tag_debug_untracked_jul_11_2011(468, VALID_INDEX(target_bucket_index, table->bucket_count));

    for (s_hash_table_bucket const * current_bucket = buckets[target_bucket_index]; current_bucket != NULL; current_bucket = current_bucket->next)
    {
        assert_tag_debug_untracked_jul_11_2011(472, valid_bucket_pointer(table, current_bucket));

        if (current_bucket->hash == search_hash_value && table->compare_function(key, current_bucket->key))
        {
            assert_tag_debug_untracked_jul_11_2011(478, result==NULL);
            result = current_bucket;
        }
    }

    return result;
};

unsigned long string_hash_table_hash_function(void const * string)
{
    mangled_ppc("?string_hash_table_hash_function@@YAKPBX@Z");

    c_hash hash;
    for (char const * current = static_cast<char const *>(string); *current; current++)
    {
        hash.add_byte(*current);
    }

    return hash.get_hash();
};

bool string_hash_table_compare_function(void const * string1, void const * string2)
{
    mangled_ppc("?string_hash_table_compare_function@@YA_NPBX0@Z");

    return strcmp_debug(static_cast<char const *>(string1), static_cast<char const *>(string2)) == 0;
};
