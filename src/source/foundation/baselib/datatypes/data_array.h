#pragma once
#ifndef __DATA_ARRAY_H__
#define __DATA_ARRAY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

#define DATUM_INDEX_TO_ABSOLUTE_INDEX(VALUE) ((VALUE) & 0xFFFF)
#define DATUM_INDEX_TO_IDENTIFIER(VALUE) ((VALUE) >> 16)
#define BUILD_DATUM_INDEX(IDENTIFIER, ABSOLUTE_INDEX) ((ABSOLUTE_INDEX) | ((IDENTIFIER) << 16))
#define DATUM_IS_FREE(header) ((header)->identifier == 0)

enum
{
    _data_array_can_disconnect_bit = 0,
    _data_array_disconnected_bit,
    _data_array_protection_bit,
    _data_array_verify_data_pattern_bit,
};

enum e_datum_salt
{
    _datum_salt_normal = 0,
    _datum_salt_isolated,
    k_datum_salt_count,
};

/* ---------- definitions */

class c_allocation_interface;

struct s_datum_header
{
    short identifier; // 0x0
};
static_assert(sizeof(s_datum_header) == 0x2, "s_datum_header");

struct s_data_array
{
    s_static_string<32> name; // 0x0
    unsigned int size; // 0x20
    unsigned long signature; // 0x24
    long maximum_count; // 0x28
    char alignment_bits; // 0x2C
    bool valid; // 0x2D
    unsigned short flags; // 0x2E
    c_allocation_interface * allocation; // 0x30
    long first_possibly_free_absolute_index; // 0x34
    long count; // 0x38
    long actual_count; // 0x3C
    short next_identifier; // 0x40
    short isolated_next_identifier; // 0x42
    void * data; // 0x44
    unsigned long * in_use_bit_vector; // 0x48
    long offset_to_data; // 0x4C
    long offset_to_bit_vector; // 0x50
};
static_assert(sizeof(s_data_array) == 0x54, "s_data_array");

struct s_data_iterator
{
    s_data_array const * data; // 0x0
    long index; // 0x4
    long absolute_index; // 0x8
    unsigned long signature; // 0xC
};
static_assert(sizeof(s_data_iterator) == 0x10, "s_data_iterator");

/* ---------- prototypes */

extern s_data_array * data_new(char const * name, long maximum_count, unsigned int size, long alignment_bits, char const * file, long line, c_allocation_interface * allocation);
extern s_data_array * data_new_disconnected(char const * name, long maximum_count, unsigned int size, long alignment_bits, char const * file, long line, c_allocation_interface * allocation);
extern void data_dispose(s_data_array * data, char const * file, long line);
extern unsigned int data_allocation_size(long maximum_count, unsigned int size, long alignment_bits);
extern void data_initialize(s_data_array * data, char const * name, long maximum_count, unsigned int size, long alignment_bits, c_allocation_interface * allocation);
extern void data_initialize_disconnected(s_data_array * data, char const * name, long maximum_count, unsigned int size, long alignment_bits, c_allocation_interface * allocation, unsigned long * in_use_bit_vector);
extern void data_connect(s_data_array * data, long maximum_count, void * datums);
extern void data_disconnect(s_data_array * data);
extern void data_make_valid(s_data_array * data);
extern void data_make_invalid(s_data_array * data);
extern void data_copy(s_data_array const * source, s_data_array * destination);
extern void data_delete_all(s_data_array * data);
extern long datum_new(s_data_array * data);
extern bool datum_available_at_index(s_data_array const * data, long requested_index);
extern long datum_new_at_index(s_data_array * data, long requested_index);
extern long datum_new_at_absolute_index(s_data_array * data, long absolute_index);
extern long datum_new_in_range(s_data_array * data, long minimum_index, long count_indices, e_datum_salt salt_type);
extern void datum_clear(void * address, unsigned int size);
extern void datum_delete(s_data_array * data, long index);
extern void * datum_get(s_data_array * data, long index);
extern void * datum_get_absolute(s_data_array * data, long absolute_index);
extern void * datum_try_and_get(s_data_array * data, long index);
extern void * datum_try_and_get_unsafe(s_data_array * data, long index);
extern void * datum_try_and_get_absolute(s_data_array * data, long absolute_index);
extern long datum_absolute_index_to_index(s_data_array const * data, long absolute_index);
extern void data_iterator_begin(s_data_iterator * iterator, s_data_array const * data);
extern void const * data_iterator_next(s_data_iterator * iterator);
extern long data_next_index(s_data_array const * data, long index);
extern long data_last_index(s_data_array const * data);
extern long data_previous_index(s_data_array const * data, long index);
extern void data_verify(s_data_array const * data);
extern bool data_is_empty(s_data_array const * data);
extern bool data_is_full(s_data_array const * data);
extern long data_get_count(s_data_array const * data);
extern long data_get_watermark(s_data_array const * data);
extern void data_set_new_base_address(s_data_array ** pointer_to_set, s_data_array * new_address);

/* ---------- globals */

/* ---------- public code */

template<typename t_type>
class c_data_iterator
{
public:
    void begin(s_data_array * data)
    {
        data_iterator_begin(&m_iterator, data);
    }

    bool next(void)
    {
        m_datum = static_cast<t_type *>(const_cast<void *>(data_iterator_next(&m_iterator)));

        return m_datum != NULL;
    }

    t_type * get_datum(void) const
    {
        return m_datum;
    }

    long get_index(void) const
    {
        return m_iterator.index;
    }

    long get_absolute_index(void) const
    {
        return DATUM_INDEX_TO_ABSOLUTE_INDEX(m_iterator.index);
    }

    // public: accessed directly by callers (constant_pool_reset reads m_datum without get_datum)
    t_type * m_datum; // 0x0
    s_data_iterator m_iterator; // 0x4
};

template<typename t_type>
class c_data_iterator_const
{
public:
    void begin(s_data_array const * data)
    {
        data_iterator_begin(&m_iterator, data);
    }

    bool next(void)
    {
        m_datum = static_cast<t_type const *>(data_iterator_next(&m_iterator));

        return m_datum != NULL;
    }

    t_type const * get_datum(void) const
    {
        return m_datum;
    }

    long get_index(void) const
    {
        return m_iterator.index;
    }

    long get_absolute_index(void) const
    {
        return DATUM_INDEX_TO_ABSOLUTE_INDEX(m_iterator.index);
    }

private:
    t_type const * m_datum; // 0x0
    s_data_iterator m_iterator; // 0x4
};

#endif // __DATA_ARRAY_H__
