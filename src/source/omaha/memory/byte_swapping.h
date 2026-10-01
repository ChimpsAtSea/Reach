#pragma once
#ifndef __BYTE_SWAPPING_H__
#define __BYTE_SWAPPING_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_byte_swap_code_constant
{
    _1byte = 1,
    _2byte = -2,
    _4byte = -4,
    _8byte = -8,
    _begin_bs_array = -100,
    _end_bs_array = -101,
    _extern_bs_definition = -102,
    BYTE_SWAP_DEFINITION_SIGNATURE = 'bysw',
};

/* ---------- definitions */

struct byte_swap_definition
{
    char const *name; // 0x0
    long size; // 0x4
    long const *codes; // 0x8
    char const *source_file; // 0xC
    long source_line; // 0x10
    unsigned long signature; // 0x14
    bool verified; // 0x18
};
static_assert(sizeof(byte_swap_definition) == 0x1C, "byte_swap_definition");

/* ---------- prototypes */

template<typename t_type>
void byte_swap_type(t_type *data, long count);

void byte_swap_data(byte_swap_definition *definition, void *data, long data_count);
void byte_swap_memory(void *memory, long count, long code);
byte_swap_definition * byte_swap_definition_verify(byte_swap_definition * definition);

/* ---------- globals */

extern byte_swap_definition byte_bs_definition;
extern byte_swap_definition word_bs_definition;
extern byte_swap_definition long_bs_definition;
extern byte_swap_definition int64_bs_definition;

/* ---------- public code */

// per-type byte swap definitions. primitive g_bs_definition specializations live in persist.cpp;
// struct types specialize g_bs_codes_internal / g_bs_definition_internal / g_bs_definition in the
// .cpp that owns them (see persist.cpp for real32_quaternion)
template<typename t_type>
class c_byte_swap_traits
{
public:
    static byte_swap_definition * get_bs_definition(void)
    {
        mangled_ppc("?get_bs_definition@?$c_byte_swap_traits@...@@SAPAUbyte_swap_definition@@XZ");

        return byte_swap_definition_verify(&g_bs_definition_internal);
    };

    static long const g_bs_codes_internal[];
    static byte_swap_definition g_bs_definition_internal;
    static byte_swap_definition * g_bs_definition;
};

#endif // __BYTE_SWAPPING_H__

