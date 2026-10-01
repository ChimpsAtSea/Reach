#pragma once
#ifndef __PERSIST_H__
#define __PERSIST_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\byte_swapping.h"

/* ---------- constants */

/* ---------- definitions */

struct byte_swap_definition;

// vtable order from ??_7c_persist_stream@@6B@ (0x821477D0)
class c_persist_stream
{
public:
    virtual ~c_persist_stream()
    {
        mangled_ppc("??1c_persist_stream@@UAA@XZ");
    };

    virtual bool read(void * buffer, unsigned long size) = 0;
    virtual bool write(void const * buffer, unsigned long size) = 0;
    virtual bool write_extend_to_position(void) = 0;
    virtual bool reserve_write(unsigned long, unsigned long);
    virtual bool seek_to_align_absolute_position(long alignment_bits, unsigned long * out_new_absolute_position);
    virtual bool seek_relative(long offset) = 0;
    virtual bool seek_absolute(unsigned long position) = 0;
    virtual bool get_absolute_position(unsigned long * out_position) = 0;
    virtual bool get_total_size(unsigned long * out_size) = 0;
    virtual bool needs_byteswapping(void) = 0;
    virtual void set_needs_byteswapping(bool needs_byteswapping) = 0;
    virtual bool get_position_relative_to_stream(c_persist_stream * other_stream, unsigned long * out_position);
    virtual bool get_absolute_position_relative_to_stream(c_persist_stream * other_stream, unsigned long, unsigned long * out_position);
    virtual c_persist_stream * get_ancestor_stream(void);
    virtual bool read_bs(void *, long, long, byte_swap_definition *);
    virtual bool write_bs(void *, long, long, byte_swap_definition *);

    // inline templates (??$read_typed@K / ??$write_typed@K, lruv_cache.obj): read_bs/write_bs(value, sizeof, count, c_byte_swap_traits<t_type>::g_bs_definition)
    template<typename t_type>
    bool read_typed(t_type * value, long count)
    {
        mangled_ppc("??$read_typed@...@c_persist_stream@@QAA_NPA...J@Z");

        return read_bs(value, sizeof(t_type), count, c_byte_swap_traits<t_type>::g_bs_definition);
    };

    template<typename t_type>
    bool write_typed(t_type * value, long count)
    {
        mangled_ppc("??$write_typed@...@c_persist_stream@@QAA_NPA...J@Z");

        return write_bs(value, sizeof(t_type), count, c_byte_swap_traits<t_type>::g_bs_definition);
    };
};
static_assert(sizeof(c_persist_stream) == 0x4, "c_persist_stream");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PERSIST_H__

