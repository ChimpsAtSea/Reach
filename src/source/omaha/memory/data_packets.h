#pragma once
#ifndef __DATA_PACKETS_H__
#define __DATA_PACKETS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    __pack_pad = 0,
    __pack_char,
    __pack_short,
    __pack_long,
    __pack_int64,
    __pack_string,
    __pack_data,
    __pack_array,
    __pack_fixed_data,
    __pack_end,
};

/* ---------- definitions */

struct data_packet_field
{
    short type; // 0x0
    short count; // 0x2
    short first_version; // 0x4
    short last_version; // 0x6
    short size; // 0x8
};
static_assert(sizeof(data_packet_field) == 0xA, "data_packet_field");

struct data_packet_definition
{
    char const * name; // 0x0
    unsigned long flags; // 0x4
    short size; // 0x8
    short version; // 0xA
    data_packet_field * fields; // 0xC
    unsigned char initialized_flag; // 0x10
};
static_assert(sizeof(data_packet_definition) == 0x14, "data_packet_definition");

/* ---------- prototypes */

void data_packet_verify(data_packet_definition * packet_definition);
unsigned char data_packet_encode(data_packet_definition * packet_definition, short version, void * packet, void * buffer, short * buffer_size, short maximum_buffer_size);
unsigned char data_packet_decode(data_packet_definition * packet_definition, void * encoded_packet, short encoded_packet_size, void * decoded_packet, short * version_reference, short * actual_encoded_packet_size_reference);

/* ---------- globals */

/* ---------- public code */

#endif // __DATA_PACKETS_H__

