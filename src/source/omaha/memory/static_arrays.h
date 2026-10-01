#ifndef __STATIC_ARRAYS_H__
#define __STATIC_ARRAYS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

struct s_default_enum_string_resolver;
template<long k_maximum_count> class c_static_string;

#define __STATIC_ARRAYS_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\static_arrays.h"

// k_max is typed t_enum: valid_bit compares signed (cmpwi) and static_arrays.cpp has `static <t_enum> const k_maximum_count`
template<typename t_enum, typename t_storage, t_enum k_max, typename t_string_resolver = s_default_enum_string_resolver>
class c_flags_no_init
{
public:
    static t_enum const k_maximum_count = k_max;

    // verified for e_game_engine_player_rating_flags (game_engine_player_rating_parameters.obj)
    t_storage get_unsafe() const
    {
        return m_flags;
    };

    // verified for e_game_engine_player_rating_flags (game_engine_player_rating_parameters.obj)
    void set_unsafe(t_storage raw_bits)
    {
        m_flags = raw_bits;

        assert_decomp(valid(), __STATIC_ARRAYS_H_FILE__, 2143);
    };

    // verified for e_cui_screen_category (camera.obj)
    void set_all()
    {
        *this = make_mask_from_range(static_cast<t_enum>(0), static_cast<t_enum>(k_max - 1));
    };

    // verified for e_cui_screen_category (camera.obj)
    static c_flags_no_init make_mask_from_range(t_enum first_bit, t_enum last_bit)
    {
        assert_decomp(valid_bit(first_bit) && valid_bit(last_bit) && (first_bit <= last_bit), __STATIC_ARRAYS_H_FILE__, 2100);

        // /Od stack slots depend on the local names (hash order), not declaration order; names found by search
        t_storage n_bit_mask = make_N_bit_mask_size_type(static_cast<t_enum>(last_bit - first_bit + 1));
        t_storage shifted_mask = n_bit_mask << first_bit;
        c_flags_no_init result;
        result.set_unsafe(shifted_mask);

        return result;
    };

    // verified for e_cui_screen_category (camera.obj)
    c_flags_no_init operator&(c_flags_no_init const & rsa) const
    {
        c_flags_no_init result;
        result.set_unsafe(m_flags & rsa.m_flags);

        return result;
    };

    // verified for e_cui_screen_category (camera.obj)
    c_flags_no_init operator|(c_flags_no_init const & rsa) const
    {
        c_flags_no_init result;
        result.set_unsafe(m_flags | rsa.m_flags);

        return result;
    };

    c_static_string<1024> to_string(void) const; // $TODO inline in the target; body not reversed yet

    // verified for e_content_item_author_flag (content_item_metadata_internal.obj)
    void clear()
    {
        m_flags = 0;
    };

    bool operator==(c_flags_no_init const & rsa) const;
    bool operator!=(c_flags_no_init const & rsa) const;

    // verified for e_game_engine_player_rating_flags (game_engine_player_rating_parameters.obj)
    bool valid() const
    {
        t_storage valid_mask = make_mask_with_all_valid_bits_on_size_type();
        bool invalid = (m_flags & ~valid_mask) != 0;
        bool valid = !invalid;

        return valid;
    };

    bool test(t_enum bit) const
    {
        assert_decomp(valid_bit(bit), __STATIC_ARRAYS_H_FILE__, 1704);

        bool result = (m_flags & flag_size_type(bit)) != 0;

        return result;
    };

    void set(t_enum bit, bool enable)
    {
        assert_decomp(valid_bit(bit), __STATIC_ARRAYS_H_FILE__, 1715);

        if (enable)
        {
            m_flags |= flag_size_type(bit);
        }
        else
        {
            m_flags &= ~flag_size_type(bit);
        }
    };

    static bool valid_bit(t_enum bit)
    {
        bool result = bit >= 0 && bit < k_max;

        return result;
    };

    // verified for e_effect_flags (determinism_debug_consumer_effects.obj) and e_cui_screen_category (camera.obj, /Od operand order)
    bool is_clear() const
    {
        return (m_flags & make_mask_with_all_valid_bits_on_size_type()) == 0;
    };

private:
    // verified for e_effect_flags (optimized) and e_game_engine_player_rating_flags (/Od, locals required)
    static t_storage make_mask_with_all_valid_bits_on_size_type()
    {
        t_storage result = make_N_bit_mask_size_type(k_max);

        return result;
    };

    // verified for e_effect_flags (optimized) and e_game_engine_player_rating_flags (/Od, unsigned char storage: sraw)
    static t_storage make_N_bit_mask_size_type(t_enum bit_count)
    {
        t_storage all_bits = static_cast<t_storage>(-1);

        t_storage result = all_bits >> (sizeof(t_storage) * 8 - bit_count);

        return result;
    };

    static t_storage flag_size_type(t_enum bit)
    {
        t_storage result = FLAG(bit);

        return result;
    };

    t_storage m_flags; // 0x0 (the target reads the flags at offset 0)
};

template<typename t_enum, typename t_storage, t_enum k_max, typename t_string_resolver = s_default_enum_string_resolver>
class c_flags :
    public c_flags_no_init<t_enum, t_storage, k_max, t_string_resolver>
{
public:
    // verified for e_effect_flags (determinism_debug_consumer_effects.obj)
    c_flags()
    {
        this->clear();
        dassert_decomp(this->is_clear(), "is_clear()", __STATIC_ARRAYS_H_FILE__, 2301);
    };
};

// k_minimum_value/k_maximum_value are `int` (target instantiates cast_to_enum<int>(k_minimum_value))
template<typename t_enum, typename t_storage, int k_minimum_value, int k_maximum_value, typename t_string_resolver = s_default_enum_string_resolver>
class c_enum_no_init
{
public:
    enum
    {
        k_enum_minimum_value = k_minimum_value,
        k_enum_maximum_value = k_maximum_value,
    };

    operator t_enum() const
    {
        return static_cast<t_enum>(m_enum_value);
    };

    c_enum_no_init & operator=(t_enum value)
    {
        m_enum_value = static_cast<t_storage>(value);

        return *this;
    };

    bool operator==(t_enum value) const
    {
        return value == m_enum_value;
    };

    bool in_range() const
    {
        return m_enum_value >= k_minimum_value && m_enum_value < k_maximum_value;
    };

    void set_raw_value(t_storage raw_value)
    {
        m_enum_value = raw_value;

        assert_decomp(in_range(), __STATIC_ARRAYS_H_FILE__, 566);
    };

    template<typename t_type>
    static t_enum cast_to_enum(t_type value)
    {
        return static_cast<t_enum>(value);
    };

    template<typename t_type>
    static t_storage cast_to_storage(t_type value)
    {
        return static_cast<t_storage>(value);
    };

protected:
    t_storage m_enum_value;
};

// $TODO member bodies not reversed yet (target: test asserts valid_bit(bit) at static_arrays.h:2353)
template<typename t_type, long k_maximum_count>
class c_big_flags_typed_no_init
{
public:
    // verified for <long, 20000> (tag_marker.obj): memset_fast expansion, dead branches are still emitted at /Od
    void clear()
    {
        if (sizeof(m_flags) > 32)
        {
            memset_big_crossplatform_internal(m_flags, 0, sizeof(m_flags));
        }
        else
        {
            dassert_decomp(pointer_is_aligned(&m_flags[0], 2), "pointer_is_aligned(&m_flag_chunks[0], 2)", __STATIC_ARRAYS_H_FILE__, 2312);
            dassert_decomp((sizeof(m_flags) & 3) == 0, "(sizeof(m_flag_chunks) & 3) == 0", __STATIC_ARRAYS_H_FILE__, 2312);

            if (!pointer_is_aligned(m_flags, 2) || (sizeof(m_flags) & 3) != 0)
            {
                event(_event_error, "memory: memset_fast (or a variant) has been called with at least one unaligned parameter (%s, %d, 0x%x, 0x%x, 0x%x).  Falling back on memset.", __STATIC_ARRAYS_H_FILE__, 2312, m_flags, 0, sizeof(m_flags));
                memset_big_crossplatform_internal(m_flags, 0, sizeof(m_flags));
            }
            else
            {
                size_t const long_count = sizeof(m_flags) >> 2;
                long const byte_value = 0;
                unsigned long const fill = (byte_value << 24) | (byte_value << 16) | (byte_value << 8) | byte_value;
                for (size_t i = 0; i < long_count; i++)
                {
                    m_flags[i] = fill;
                }
            }
        }
        dassert_decomp(is_clear(), "is_clear()", __STATIC_ARRAYS_H_FILE__, 2313);
    };

    // $TODO <long, 20000> (tag_marker.obj) best 87.8%: assert valid_bit(bit) @2362, BIT_VECTOR_SET_FLAG-style ternary,
    // assert valid() @2366; the target spills each branch value to its own temp before storing it and copies that
    // temp into the ternary result slot (frame 0x70). No C++ spelling found yet (tried |=, a = a | f, casts, volatile).
    void set(t_type bit, bool enable);

    bool test(t_type bit) const;
    bool valid() const;
    static bool valid_bit(t_type bit);

    // verified for <long, 20000> (tag_marker.obj)
    c_big_flags_typed_no_init & operator|=(c_big_flags_typed_no_init const & rsa)
    {
        for (long chunk_index = 0; chunk_index < k_flag_chunk_count; chunk_index++)
        {
            m_flags[chunk_index] |= rsa.m_flags[chunk_index];
        }

        assert_decomp(valid(), __STATIC_ARRAYS_H_FILE__, 2785);

        return *this;
    };

    // verified for <long, 20000> (tag_marker.obj)
    void and_not_range(c_big_flags_typed_no_init const * rsa, t_type first_bit, t_type last_bit)
    {
        long first_chunk_index = bit_index_to_flag_chunk_index(first_bit);
        long last_chunk_index = bit_index_to_flag_chunk_index(last_bit);

        assert_decomp(valid_bit(first_bit), __STATIC_ARRAYS_H_FILE__, 2974);
        assert_decomp(valid_bit(last_bit), __STATIC_ARRAYS_H_FILE__, 2975);
        assert_decomp(valid(), __STATIC_ARRAYS_H_FILE__, 2976);
        assert_decomp(rsa->valid(), __STATIC_ARRAYS_H_FILE__, 2977);

        if (first_chunk_index == last_chunk_index)
        {
            unsigned long mask = get_mask_of_second_slice_of_chunk_inclusive(first_bit) & get_mask_of_first_slice_of_chunk_inclusive(last_bit);
            m_flags[first_chunk_index] &= ~(rsa->m_flags[first_chunk_index] | ~mask);
        }
        else
        {
            unsigned long first_slice_mask = get_mask_of_second_slice_of_chunk_inclusive(first_bit);
            m_flags[first_chunk_index] &= ~(rsa->m_flags[first_chunk_index] | ~first_slice_mask);

            unsigned long last_slice_mask = get_mask_of_first_slice_of_chunk_inclusive(first_bit);
            m_flags[last_chunk_index] &= ~(rsa->m_flags[last_chunk_index] | ~last_slice_mask);

            for (long chunk_index = first_chunk_index + 1; chunk_index < last_chunk_index; chunk_index++)
            {
                m_flags[chunk_index] &= ~rsa->m_flags[chunk_index];
            }
        }

        assert_decomp(valid(), __STATIC_ARRAYS_H_FILE__, 3009);
    };

    // verified for <long, 20000> (tag_marker.obj)
    bool is_clear() const
    {
        bool result = true;
        for (long chunk_index = 0; chunk_index < k_flag_chunk_count; chunk_index++)
        {
            result &= m_flags[chunk_index] == 0;
        }

        return result;
    };

    // verified for <long, 212> (sound_xaudio_xenon_voice_manager.obj)
    void set_all()
    {
        memset(m_flags, 0xFFFFFFFF, sizeof(m_flags));
        unsigned long mask = get_mask_of_second_slice_of_chunk_inclusive(k_maximum_count);
        m_flags[NUMBEROF(m_flags) - 1] &= ~mask;
        assert_decomp(valid(), __STATIC_ARRAYS_H_FILE__, 2345);
    };

protected:
    static long const k_flag_chunk_count = BIT_VECTOR_SIZE_IN_LONGS(k_maximum_count);

    static unsigned long get_mask_of_second_slice_of_chunk_inclusive(long bit_index);
    static long bit_index_to_flag_chunk_index(long bit_index);
    static long flag_chunk_index_to_bit_index(long flag_chunk_index);

    // verified for <long, 20000> (tag_marker.obj)
    static unsigned long get_mask_of_first_slice_of_chunk_inclusive(long bit_index)
    {
        unsigned long mask = 0;
        long flag_chunk_index = bit_index_to_flag_chunk_index(bit_index);
        if (flag_chunk_index < k_flag_chunk_count)
        {
            long bit_count = bit_index - flag_chunk_index_to_bit_index(flag_chunk_index) + 1;
            mask = static_cast<unsigned long>((1i64 << bit_count) - 1);
        }

        return mask;
    };

    unsigned long m_flags[BIT_VECTOR_SIZE_IN_LONGS(k_maximum_count)];
};

template<typename t_type, long k_maximum_count>
class c_big_flags_typed :
    public c_big_flags_typed_no_init<t_type, k_maximum_count>
{
public:
    // verified for <long, 20000> (tag_marker.obj)
    c_big_flags_typed()
    {
        this->clear();
        dassert_decomp(this->is_clear(), "is_clear()", __STATIC_ARRAYS_H_FILE__, 3225);
    };
};

template<long k_maximum_count>
class c_big_flags :
    public c_big_flags_typed<long, k_maximum_count>
{
public:
    // verified for <20000> (tag_marker.obj)
    c_big_flags()
    {
    };
};

template<typename t_enum, typename t_storage, int k_minimum_value, int k_maximum_value, typename t_string_resolver = s_default_enum_string_resolver>
class c_enum :
    public c_enum_no_init<t_enum, t_storage, k_minimum_value, k_maximum_value, t_string_resolver>
{
public:
    // verified empty for e_change_color_reference (determinism_debug_consumer_lights.obj)
    c_enum()
    {
    };

    // f i in players.obj for e_loadout_palette_type (IDA: stores the value); /Od codegen not verified
    c_enum(t_enum value)
    {
        this->m_enum_value = static_cast<t_storage>(value);
    };
};

/* ---------- prototypes */

void static_arrays_test();

/* ---------- globals */

/* ---------- public code */

template<typename t_enum, typename t_storage, t_enum k_max, typename t_string_resolver>
bool c_flags_no_init<t_enum, t_storage, k_max, t_string_resolver>::operator==(c_flags_no_init const & rsa) const
{
    return m_flags == rsa.m_flags;
}

template<typename t_enum, typename t_storage, t_enum k_max, typename t_string_resolver>
bool c_flags_no_init<t_enum, t_storage, k_max, t_string_resolver>::operator!=(c_flags_no_init const & rsa) const
{
    return m_flags != rsa.m_flags;
}

#endif // __STATIC_ARRAYS_H__
