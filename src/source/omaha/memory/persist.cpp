#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\persist.cpp"
/* ---------- headers */

#include "omaha\memory\persist.h"
#include "omaha\memory\byte_swapping.h"
#include "omaha\math\integer_math.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

template<> byte_swap_definition * c_byte_swap_traits<unsigned char>::g_bs_definition = &byte_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<char>::g_bs_definition = &byte_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<short>::g_bs_definition = &word_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<unsigned short>::g_bs_definition = &word_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<long>::g_bs_definition = &long_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<unsigned long>::g_bs_definition = &long_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<__int64>::g_bs_definition = &int64_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<unsigned __int64>::g_bs_definition = &int64_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<float>::g_bs_definition = &long_bs_definition;
template<> byte_swap_definition * c_byte_swap_traits<double>::g_bs_definition = &int64_bs_definition;

template<> long const c_byte_swap_traits<real32_quaternion>::g_bs_codes_internal[] = { _begin_bs_array, 4, _4byte, _end_bs_array };
template<> byte_swap_definition c_byte_swap_traits<real32_quaternion>::g_bs_definition_internal = { "real_quaternion", sizeof(real32_quaternion), c_byte_swap_traits<real32_quaternion>::g_bs_codes_internal, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 24, BYTE_SWAP_DEFINITION_SIGNATURE, false };
template<> byte_swap_definition * c_byte_swap_traits<real32_quaternion>::g_bs_definition = c_byte_swap_traits<real32_quaternion>::get_bs_definition();

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const *const const c_byte_swap_traits<struct real32_quaternion>::g_bs_codes_internal; // "?g_bs_codes_internal@?$c_byte_swap_traits@Ureal32_quaternion@@@@2QBJB"
// public: static struct byte_swap_definition *c_byte_swap_traits<unsigned char>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@E@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<char>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@D@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<short>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@F@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<unsigned short>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@G@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<long>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@J@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<unsigned long>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@K@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<__int64>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@_J@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<unsigned __int64>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@_K@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<float>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@M@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<double>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@N@@2PAUbyte_swap_definition@@A"
// public: static struct byte_swap_definition c_byte_swap_traits<struct real32_quaternion>::g_bs_definition_internal; // "?g_bs_definition_internal@?$c_byte_swap_traits@Ureal32_quaternion@@@@2Ubyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<struct real32_quaternion>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@Ureal32_quaternion@@@@2PAUbyte_swap_definition@@A"

// public: virtual bool c_persist_stream::reserve_write(unsigned long, unsigned long);
// public: virtual bool c_persist_stream::seek_to_align_absolute_position(long, unsigned long *);
// public: virtual bool c_persist_stream::get_position_relative_to_stream(class c_persist_stream *, unsigned long *);
// public: virtual bool c_persist_stream::get_absolute_position_relative_to_stream(class c_persist_stream *, unsigned long, unsigned long *);
// public: virtual class c_persist_stream * c_persist_stream::get_ancestor_stream(void);
// public: virtual bool c_persist_stream::read_bs(void *, long, long, struct byte_swap_definition *);
// public: virtual bool c_persist_stream::write_bs(void *, long, long, struct byte_swap_definition *);
// public: static struct byte_swap_definition * c_byte_swap_traits<struct real32_quaternion>::get_bs_definition(void);

bool c_persist_stream::reserve_write(unsigned long position, unsigned long size)
{
    mangled_ppc("?reserve_write@c_persist_stream@@UAA_NKK@Z");

    return true;
};

bool c_persist_stream::seek_to_align_absolute_position(long alignment_bits, unsigned long * out_new_absolute_position)
{
    mangled_ppc("?seek_to_align_absolute_position@c_persist_stream@@UAA_NJPAK@Z");

    bool success = false;
    unsigned long absolute_position;

    if (get_absolute_position(&absolute_position))
    {
        unsigned long aligned_absolute_position = align_up(absolute_position, alignment_bits);

        if (absolute_position == aligned_absolute_position)
        {
            success = true;
        }
        else
        {
            success = seek_absolute(aligned_absolute_position);
        }

        if (success && out_new_absolute_position != NULL)
        {
            *out_new_absolute_position = aligned_absolute_position;
        }
    }

    return success;
};

bool c_persist_stream::get_position_relative_to_stream(c_persist_stream * other_stream, unsigned long * out_position)
{
    mangled_ppc("?get_position_relative_to_stream@c_persist_stream@@UAA_NPAV1@PAK@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(77, out_position);
    assert_tag_debug_untracked_jul_11_2011(78, other_stream);

    if (this == other_stream)
    {
        success = get_absolute_position(out_position);
    }

    return success;
};

bool c_persist_stream::get_absolute_position_relative_to_stream(c_persist_stream * other_stream, unsigned long absolute_position, unsigned long * out_position)
{
    mangled_ppc("?get_absolute_position_relative_to_stream@c_persist_stream@@UAA_NPAV1@KPAK@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(95, out_position);
    assert_tag_debug_untracked_jul_11_2011(96, other_stream);

    if (this == other_stream)
    {
        *out_position = absolute_position;
        success = true;
    }

    return success;
};

c_persist_stream * c_persist_stream::get_ancestor_stream(void)
{
    mangled_ppc("?get_ancestor_stream@c_persist_stream@@UAAPAV1@XZ");

    return this;
};

bool c_persist_stream::read_bs(void * buffer, long element_size, long element_count, byte_swap_definition * bs_definition)
{
    mangled_ppc("?read_bs@c_persist_stream@@UAA_NPAXJJPAUbyte_swap_definition@@@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(123, bs_definition->size==element_size);
    assert_tag_debug_untracked_jul_11_2011(124, buffer || element_size*element_count==0);

    success = read(buffer, element_size * element_count);
    if (success && needs_byteswapping())
    {
        byte_swap_data(bs_definition, buffer, element_count);
    }

    return success;
};

bool c_persist_stream::write_bs(void * buffer, long element_size, long element_count, byte_swap_definition * bs_definition)
{
    mangled_ppc("?write_bs@c_persist_stream@@UAA_NPAXJJPAUbyte_swap_definition@@@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(145, bs_definition->size==element_size);
    assert_tag_debug_untracked_jul_11_2011(146, buffer || element_size*element_count==0);

    if (needs_byteswapping())
    {
        byte_swap_data(bs_definition, buffer, element_count);
    }

    success = write(buffer, element_size * element_count);

    if (needs_byteswapping())
    {
        byte_swap_data(bs_definition, buffer, element_count);
    }

    return success;
};
