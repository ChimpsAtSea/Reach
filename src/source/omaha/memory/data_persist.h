#pragma once
#ifndef __DATA_PERSIST_H__
#define __DATA_PERSIST_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct s_data_array;
struct byte_swap_definition;
class c_persist_stream;
class c_allocation_interface;

// layout from data_persist.obj (g_bs_codes_internal: 32 bytes, 5 longs)
struct s_data_array_persist_header
{
    c_static_string<32> name; // 0x0
    unsigned int size; // 0x20
    long count; // 0x24
    long actual_count; // 0x28
    long next_identifier; // 0x2C
    unsigned long signature; // 0x30
};
static_assert(sizeof(s_data_array_persist_header) == 0x34, "s_data_array_persist_header");

// interface names unknown (no RTTI/type in the target); vtable slots verified from data_persist.obj
class c_datum_persister
{
public:
    virtual bool persist_datum(c_basic_buffer<void const> const & datum, c_persist_stream * persist_stream) = 0; // 0x0
};

class c_datum_restorer
{
public:
    virtual bool restore_datum(c_basic_buffer<void> const & datum, c_persist_stream * persist_stream) = 0; // 0x0
    virtual bool accept_datum_size(unsigned int size) = 0; // 0x4
};

/* ---------- prototypes */

long data_persist_compact_size(s_data_array const * data);
bool data_persist(s_data_array const * data, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_persister * datum_persister);
bool data_restore(s_data_array * data, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_restorer * datum_restorer);
bool data_restore_with_header(s_data_array * data, s_data_array_persist_header const * header, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_restorer * datum_restorer);
bool data_recreate_from_stream(s_data_array ** out_data, c_persist_stream * persist_stream, char const * name, unsigned int size, long alignment_bits, long maximum_count, c_allocation_interface * allocation, byte_swap_definition * datum_bs_definition, c_datum_restorer * datum_restorer);

/* ---------- globals */

/* ---------- public code */

#endif // __DATA_PERSIST_H__

