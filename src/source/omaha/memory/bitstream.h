#ifndef __BITSTREAM_H__
#define __BITSTREAM_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\static_arrays.h"

union vector3d;

/* ---------- constants */

/* ---------- definitions */

// number of bits needed to encode `k_value` (compile-time)
template<unsigned long k_value>
struct s_bitstream_required_bits
{
    enum { value = 1 + s_bitstream_required_bits<(k_value >> 1)>::value };
};

template<>
struct s_bitstream_required_bits<0>
{
    enum { value = 0 };
};

template<unsigned long k_maximum_count>
long required_encoding_bits_for_index(void)
{
    return s_bitstream_required_bits<k_maximum_count>::value;
}

// $TODO: members/layout not yet reversed; only the methods used so far are declared
class c_bitstream
{
public:
    c_bitstream(unsigned char * data, long data_length);
    ~c_bitstream(void);
    bool error_occurred(void) const;
    void begin_reading(void);
    void finish_reading(void);

    void write_bool(char const * name, bool value);
    void write_integer(char const * name, unsigned long value, long size_in_bits);
    bool read_bool(char const * name);
    unsigned long read_integer(char const * name, long size_in_bits);
    void write_signed_integer(char const * name, long value, long size_in_bits);
    long read_signed_integer(char const * name, long size_in_bits);
    void write_vector(char const * name, vector3d const * vector, float min_magnitude, float max_magnitude, long magnitude_bits, long orientation_bits);
    void read_vector(char const * name, vector3d * vector, float min_magnitude, float max_magnitude, long magnitude_bits, long orientation_bits);
    static bool compare_vectors(vector3d const * vector1, vector3d const * vector2, float min_magnitude, float max_magnitude, long magnitude_bits, long orientation_bits);

    template<unsigned long k_maximum_count, typename t_type>
    void write_index(char const * name, t_type value)
    {
        assert_decomp(value==NONE || VALID_INDEX(value, k_maximum_count), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 234);

        // power-of-two counts have no spare encoding for NONE, so it gets its own bit
        if (k_maximum_count == (1 << s_bitstream_required_bits<k_maximum_count - 1>::value))
        {
            bool is_none = value == NONE;
            write_bool(name, is_none);
            if (!is_none)
            {
                write_integer(name, value, s_bitstream_required_bits<k_maximum_count - 1>::value);
            }
        }
        else
        {
            // verified for <101, unsigned char>; target also truncates for short/char (extsh/extsb after the add)
            write_integer(name, static_cast<t_type>(value + 1), required_encoding_bits_for_index<k_maximum_count>());
        }
    }

    template<unsigned long k_maximum_count>
    long read_index(char const * name)
    {
        long value;
        if (k_maximum_count == (1 << s_bitstream_required_bits<k_maximum_count - 1>::value))
        {
            bool is_none = read_bool(name);
            if (is_none)
            {
                value = NONE;
            }
            else
            {
                value = read_integer(name, s_bitstream_required_bits<k_maximum_count - 1>::value);
            }
        }
        else
        {
            value = read_integer(name, required_encoding_bits_for_index<k_maximum_count>()) - 1;
        }

        assert_decomp(value==NONE || VALID_INDEX(value, k_maximum_count), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 418);

        return value;
    }

    template<unsigned long k_maximum_count, typename t_type>
    void write_count(char const * name, t_type value)
    {
        assert_decomp(VALID_COUNT(value, k_maximum_count), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 277);

        write_integer(name, value, s_bitstream_required_bits<k_maximum_count>::value);
    }

    template<unsigned long k_maximum_count>
    long read_count(char const * name)
    {
        long value = read_integer(name, s_bitstream_required_bits<k_maximum_count>::value);

        assert_decomp(VALID_COUNT(value, k_maximum_count), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 442);

        return value;
    }

    template<typename t_enum_type>
    void write_enum(char const * name, t_enum_type enum_value);

    template<typename t_enum_type>
    void read_enum(char const * name, t_enum_type * enum_value);

    // verified for c_flags_no_init<e_game_engine_player_rating_flags, unsigned char, 1> (game_engine_player_rating_parameters.obj)
    template<typename t_flags_type>
    void write_flags(char const * name, t_flags_type flags)
    {
        write_integer(name, flags.get_unsafe(), t_flags_type::k_maximum_count);
    }

    // verified for c_flags_no_init<e_game_engine_player_rating_flags, unsigned char, 1> (game_engine_player_rating_parameters.obj)
    template<typename t_flags_type>
    void read_flags(char const * name, t_flags_type * flags)
    {
        flags->set_unsafe(read_integer(name, t_flags_type::k_maximum_count));
    }

private:
    // $TODO: layout not yet reversed; sizeof from load_variant_from_file's stack frame
    unsigned __int64 m_storage[0x10160 / sizeof(unsigned __int64)];
};

template<typename t_enum_type>
long required_encoding_bits_for_enum(t_enum_type enum_value)
{
    return s_bitstream_required_bits<t_enum_type::k_enum_maximum_value - t_enum_type::k_enum_minimum_value - 1>::value;
}

template<typename t_enum_type>
void c_bitstream::write_enum(char const * name, t_enum_type enum_value)
{
    assert_decomp(enum_value.in_range(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 186);

    write_integer(name, enum_value - t_enum_type::k_enum_minimum_value, required_encoding_bits_for_enum(enum_value));
}

template<typename t_enum_type>
void c_bitstream::read_enum(char const * name, t_enum_type * enum_value)
{
    enum_value->set_raw_value(t_enum_type::cast_to_storage(read_integer(name, required_encoding_bits_for_enum(*enum_value)) + t_enum_type::cast_to_enum(static_cast<int>(t_enum_type::k_enum_minimum_value))));

    assert_decomp(enum_value->in_range(), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\bitstream.h", 327);
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BITSTREAM_H__

