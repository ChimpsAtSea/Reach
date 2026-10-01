#pragma once
#ifndef __MINIDUMP_SECURE_WRITER_HELPER_H__
#define __MINIDUMP_SECURE_WRITER_HELPER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\toolbox\file_helpers.h"
#include "omaha\zlib\blam_zlib_memory.h"

/* ---------- constants */

/* ---------- definitions */

// layout from begin_stream/end_stream/initialize; opaque members not yet typed
class c_minidump_secure_writer_helper
{
public:
    c_minidump_secure_writer_helper(void);
    ~c_minidump_secure_writer_helper(void);

    void initialize(c_aligned_stored_buffered_file_writer<4096> * aligned_file_writer);
    void clear(void);
    bool begin_stream(void);
    bool write_to_stream(void const * data, unsigned long size);
    bool end_stream(unsigned long * compressed_bytes, unsigned long * encrypted_bytes, unsigned long * uncompressed_bytes);
    void get_encrypted_session_key(char * const encrypted_session_key);

private:
    bool write_to_stream_internal(void const * data, unsigned long size, bool flush);

    unsigned char m_session_key[0x10]; // 0x0
    c_aligned_stored_buffered_file_writer<4096> * m_aligned_file_writer; // 0x10
    unsigned char m_zlib_stream[0x38]; // 0x14 z_stream_s
    s_blam_zlib_memory m_zlib_memory; // 0x4C
    unsigned char m_initialization_vector[0x10]; // 0x50
    unsigned char m_cipher_state[0x160]; // 0x60
    long m_pending_bytes; // 0x1C0
    unsigned long m_uncompressed_bytes; // 0x1C4
    unsigned long m_compressed_bytes; // 0x1C8
    unsigned long m_encrypted_bytes; // 0x1CC
};
static_assert(sizeof(c_minidump_secure_writer_helper) == 0x1D0, "c_minidump_secure_writer_helper");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MINIDUMP_SECURE_WRITER_HELPER_H__

