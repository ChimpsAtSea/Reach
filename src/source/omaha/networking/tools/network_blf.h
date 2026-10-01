#ifndef __NETWORK_BLF_H__
#define __NETWORK_BLF_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_blf_file_authentication_type
{
    _blf_file_authentication_type_none = 0,
    _blf_file_authentication_type_crc,
    _blf_file_authentication_type_sha1,
    _blf_file_authentication_type_rsa,

    k_blf_file_authentication_type_count
};

/* ---------- definitions */

struct s_blf_header
{
    long chunk_type; // 0x0
    long chunk_size; // 0x4
    short version_major; // 0x8
    short version_minor; // 0xA
};
static_assert(sizeof(s_blf_header) == 0xC, "s_blf_header");

/* ---------- prototypes */

bool network_blf_verify_start_of_file(char const * buffer, long buffer_count, bool * out_must_byte_swap, long * out_chunk_size);
bool network_blf_find_chunk(char const * buffer, long buffer_count, bool must_byte_swap, long desired_chunk_type, short desired_version_major, long * out_chunk_size, char const ** found_chunk_data, long * out_found_chunk_data_size, short * out_version_minor, bool * out_eof_found);
bool network_blf_verify_end_of_file(char const * buffer, long buffer_count, bool must_byte_swap, char const * end_of_file_chunk, e_blf_file_authentication_type authentication_type);

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_BLF_H__

