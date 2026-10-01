#ifndef __CSERIES_MEMORY_H__
#define __CSERIES_MEMORY_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <new>
#include <string.h>

/* ---------- constants */

// inline csmemset expansion: large or unaligned fills go through memset_big_crossplatform_internal,
// small aligned fills are written a long at a time (see data_array.cpp)
#define csmemset_inline(DESTINATION, C, SIZE) \
    if (static_cast<size_t>(SIZE) > 32) \
    { \
        memset_big_crossplatform_internal(DESTINATION, C, SIZE); \
    } \
    else if (!pointer_is_aligned(DESTINATION, 2) || (static_cast<size_t>(SIZE) & 3) != 0) \
    { \
        memset_big_crossplatform_internal(DESTINATION, C, SIZE); \
    } \
    else \
    { \
        size_t const long_count = static_cast<size_t>(SIZE) >> 2; \
        long const byte_value = (C); \
        unsigned long const fill = (byte_value << 24) | (byte_value << 16) | (byte_value << 8) | byte_value; \
        for (size_t i = 0; i < long_count; i++) \
        { \
            static_cast<unsigned long *>(static_cast<void *>(DESTINATION))[i] = fill; \
        } \
    }

// inline csmemcpy expansion: large copies go through memcpy_big_crossplatform_internal,
// unaligned copies call csmemcpy, small aligned copies are done a long at a time (see base_memory_windows.cpp)
#define csmemcpy_inline(DESTINATION, SOURCE, SIZE)     if ((SIZE) > 100)     {         memcpy_big_crossplatform_internal(DESTINATION, SOURCE, SIZE);     }     else if (!pointer_is_aligned(DESTINATION, 2) || !pointer_is_aligned(SOURCE, 2) || ((SIZE) & 3) != 0)     {         csmemcpy(DESTINATION, SOURCE, SIZE);     }     else     {         size_t const long_count = (SIZE) >> 2;         for (size_t i = 0; i < long_count; i++)         {             static_cast<unsigned long *>(static_cast<void *>(DESTINATION))[i] = static_cast<unsigned long const *>(static_cast<void const *>(SOURCE))[i];         }     }

/* ---------- definitions */

/* ---------- prototypes */

bool memory_is_filled_with(void const * source, size_t size, unsigned char c);
bool memory_is_zeroed(const void* source, size_t size);
void const * offset_pointer(const void* pointer, long offset); // $todo is this intptr_t equivelant?
void memmove_guarded(void* destination, const void* source, size_t size, const void* bounds_start, size_t bounds_size);
void * memcpy_big_crossplatform_internal(void * destination, void const * source, size_t size);
void * memset_big_crossplatform_internal(void * destination, int c, size_t size);
void prefetch_memory(void const * pointer, unsigned long offset); // inline in the target (definition not yet recovered)
void prefetch_block(void const * pointer, long size); // inline in the target (emitted in simulation_world.obj; definition not yet recovered)

extern "C"
{
    void* csmemcpy(void* destination, const void* source, size_t size);
    void* csmemmove(void* destination, const void* source, size_t size);
    void* csmemset(void* buffer, int c, size_t size);
    int csmemcmp(const void* p1, const void* p2, size_t size);
}

/* ---------- globals */

/* ---------- public code */

inline unsigned long address_from_pointer(void const * pointer);
inline bool address_is_aligned(unsigned long address, long alignment_bits);

inline bool pointer_is_aligned(void const * pointer, long alignment_bits)
{
    mangled_ppc("?pointer_is_aligned@@YA_NPBXJ@Z");

    return address_is_aligned(address_from_pointer(pointer), alignment_bits);
};

inline unsigned long address_from_pointer(void const * pointer)
{
    mangled_ppc("?address_from_pointer@@YAKPBX@Z");

    return reinterpret_cast<unsigned long>(pointer);
};

inline bool address_is_aligned(unsigned long address, long alignment_bits)
{
    mangled_ppc("?address_is_aligned@@YA_NKJ@Z");

    return (address & static_cast<unsigned long>((1i64 << alignment_bits) - 1)) == 0;
};

inline void * pointer_from_address(unsigned long)
{
    mangled_ppc("?pointer_from_address@@YAPAXK@Z");

    NOT_IMPLEMENTED;
};

inline void * offset_pointer(void * pointer, long offset)
{
    mangled_ppc("?offset_pointer@@YAPAXPAXJ@Z");

    return pointer_from_address(address_from_pointer(pointer) + offset);
};

inline void const * offset_pointer(const void* pointer, long offset)
{
    mangled_ppc("?offset_pointer@@YAPBXPBXJ@Z");

    return pointer_from_address(address_from_pointer(pointer) + offset);
};

inline long pointer_distance(void const * pointer1, void const * pointer2)
{
    mangled_ppc("?pointer_distance@@YAJPBX0@Z");

    return static_cast<char const *>(pointer2) - static_cast<char const *>(pointer1);
};

inline long pointer_distance32(void const * pointer1, void const * pointer2)
{
    mangled_ppc("?pointer_distance32@@YAJPBX0@Z");

    long distance = pointer_distance(pointer1, pointer2);
    assert_decomp(distance>=k_int32_min && distance<=k_int32_max, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\core\\corelib/cseries/cseries_memory.h", 81);

    return distance;
};

inline unsigned long align_address(unsigned long address, long alignment_bits)
{
    mangled_ppc("?align_address@@YAKKJ@Z");

    unsigned long mask = static_cast<unsigned long>((1i64 << alignment_bits) - 1);
    return (address + mask) & ~mask;
};

inline void * align_pointer(void * pointer, long alignment_bits)
{
    mangled_ppc("?align_pointer@@YAPAXPAXJ@Z");

    return pointer_from_address(align_address(address_from_pointer(pointer), alignment_bits));
};

// verified for s_storage_device_manager_main_thread_globals (storage_device_manager.obj): placement new is a call at /Od
template<typename t_type>
void reconstruct(t_type * object)
{
    new (object) t_type;
};

// verified for s_storage_device_manager_main_thread_globals (storage_device_manager.obj)
template<typename t_type>
void zero_and_reconstruct(t_type * object)
{
    memset(object, 0, sizeof(t_type));
    reconstruct(object);
};

#endif // __CSERIES_MEMORY_H__
