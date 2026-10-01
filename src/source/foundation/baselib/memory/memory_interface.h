#ifndef __MEMORY_INTERFACE_H__
#define __MEMORY_INTERFACE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

long const k_physical_memory_page_size = 65536;
long const k_physical_memory_page_size_bits = 16;
unsigned long const k_physical_memory_page_mask = 65535;

enum e_memory_protection
{
    _memory_protection_noaccess = 0,
    _memory_protection_readonly,
    _memory_protection_readwrite,

    k_memory_protection_count
};

/* ---------- definitions */

/* ---------- prototypes */

extern void memory_set_protection(void * address, unsigned int size, e_memory_protection protection);

/* ---------- globals */

/* ---------- public code */

inline bool memory_is_physical_address(void const * pointer)
{
    mangled_ppc("?memory_is_physical_address@@YA_NPBX@Z");

    unsigned long const physical_address_mask = 0x80000000;
    unsigned long address = address_from_pointer(pointer);

    return (address & physical_address_mask) == physical_address_mask;
};

#endif // __MEMORY_INTERFACE_H__

