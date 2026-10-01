#pragma once
#ifndef __CONSTANT_POOL_H__
#define __CONSTANT_POOL_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\hash_table.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

class c_allocation_interface;
struct s_data_array;
struct s_memory_pool;

typedef unsigned int constant_pool_size_function(void const * item);
typedef unsigned long constant_pool_hash_function(void const * item);
typedef void constant_pool_simplify_function(void * item);
typedef bool constant_pool_compare_function(void const * item1, void const * item2);
typedef void constant_pool_copy_function(void const * item, unsigned int size, void * destination);

struct s_constant_pool_element
{
    short identifier; // 0x0
    short pad; // 0x2
    void * data; // 0x4
};
static_assert(sizeof(s_constant_pool_element) == 0x8, "s_constant_pool_element");

struct s_constant_pool
{
    s_static_string<32> name; // 0x0
    constant_pool_size_function * size_function; // 0x20
    constant_pool_hash_function * hash_function; // 0x24
    constant_pool_simplify_function * simplify_function; // 0x28
    constant_pool_compare_function * compare_function; // 0x2C
    constant_pool_copy_function * copy_function; // 0x30
    c_allocation_interface * allocation; // 0x34
    c_hash_table<long, void> hash_table; // 0x38
    s_data_array * elements; // 0x40
    s_memory_pool * element_storage; // 0x44
};
static_assert(sizeof(s_constant_pool) == 0x48, "s_constant_pool");

/* ---------- prototypes */

extern s_constant_pool * constant_pool_new(char const * name, long maximum_count, long maximum_size, constant_pool_size_function * const size_function, constant_pool_hash_function * const hash_function, constant_pool_simplify_function * const simplify_function, constant_pool_compare_function * const compare_function, constant_pool_copy_function * const copy_function, c_allocation_interface * allocation, char const * file, long line);
extern long constant_pool_item_count(s_constant_pool const * pool);
extern unsigned int constant_pool_used_size(s_constant_pool const * pool);
extern void constant_pool_dispose(s_constant_pool * pool, char const * file, long line);
extern void constant_pool_reset(s_constant_pool * pool);
extern void const * constant_pool_add(s_constant_pool * pool, void const * item);
extern void const * constant_pool_find(s_constant_pool const * pool, void const * item);
extern bool constant_pool_contains(s_constant_pool const * pool, void const * item);
extern unsigned int constant_pool_string_size_function(void const * item);
extern unsigned int constant_pool_size(s_constant_pool const * pool, void const * item);
extern void constant_pool_simplify(s_constant_pool const * pool, void * item);
extern void constant_pool_copy(s_constant_pool const * pool, void const * item, unsigned int dst_size, void * destination);

/* ---------- globals */

/* ---------- public code */

#endif // __CONSTANT_POOL_H__

