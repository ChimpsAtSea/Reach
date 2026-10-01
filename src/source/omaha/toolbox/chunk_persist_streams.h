#pragma once
#ifndef __CHUNK_PERSIST_STREAMS_H__
#define __CHUNK_PERSIST_STREAMS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\persist.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_unbounded_relative_persist_stream;

// byte swap codes: 3 x 4-byte fields (c_byte_swap_traits<s_persist_chunk_header>::g_bs_codes_internal)
struct s_persist_chunk_header
{
    unsigned long tag; // 0x0
    long version; // 0x4
    unsigned long size; // 0x8
};
static_assert(sizeof(s_persist_chunk_header) == 0xC, "s_persist_chunk_header");

class c_persist_chunk_writer
{
public:
    c_persist_chunk_writer(c_persist_stream * persist_stream);
    ~c_persist_chunk_writer(void);

    c_persist_stream * add_chunk(unsigned long tag, long version, unsigned long size);
    void close_chunk(c_persist_stream * chunk_stream);
    void abort_chunk(c_persist_stream * chunk_stream);
    c_persist_stream * add_variable_chunk(void);
    bool commit_variable_chunk(unsigned long tag, long version, c_persist_stream * chunk_stream);
    void abort_variable_chunk(c_persist_stream * chunk_stream);

private:
    c_persist_stream * m_persist_stream; // 0x0
    unsigned long m_start_position; // 0x4 (filled by m_persist_stream->get_absolute_position in the constructor)
    bool m_unknown8; // 0x8
    unsigned long m_unknownC; // 0xC (unverified)
    c_typed_opaque_data<c_unbounded_relative_persist_stream, 24, 4> m_chunk_stream; // 0x10
};
static_assert(sizeof(c_persist_chunk_writer) == 0x2C, "c_persist_chunk_writer");

class c_persist_chunk_iterator
{
public:
    c_persist_chunk_iterator(c_persist_stream * persist_stream);
    c_persist_chunk_iterator(c_persist_stream * root_stream, c_persist_stream * persist_stream);
    ~c_persist_chunk_iterator(void);

    bool next(void);
    bool done(void) const;
    s_persist_chunk_header const * get_chunk_header(void) const;
    c_persist_stream * acquire_chunk_stream(void);
    void release_chunk_stream(void);

private:
    // $TODO layout
    unsigned char m_opaque_storage[0x5C]; // 0x0
};
static_assert(sizeof(c_persist_chunk_iterator) == 0x5C, "c_persist_chunk_iterator");

class c_scoped_variable_chunk
{
public:
    c_scoped_variable_chunk(c_persist_chunk_writer * chunk_writer);
    ~c_scoped_variable_chunk(void);

    bool create_chunk(void);
    c_persist_stream * get_chunk_stream(void);
    bool commit_chunk(unsigned long tag, long version);

private:
    bool m_committed; // 0x0 (name unverified)
    c_persist_chunk_writer * m_chunk_writer; // 0x4
    c_persist_stream * m_chunk_stream; // 0x8
};
static_assert(sizeof(c_scoped_variable_chunk) == 0xC, "c_scoped_variable_chunk");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CHUNK_PERSIST_STREAMS_H__

